#!/usr/bin/env python3
"""
TCP Reset Attack Setup Script
BUET CSE406 Computer Security Sessional
Educational Purpose Only
"""

import os
import sys
import subprocess
import platform
from pathlib import Path

def check_python_version():
    """Check if Python version is compatible"""
    if sys.version_info < (3, 7):
        print("Error: Python 3.7 or higher is required")
        return False
    
    print(f"✓ Python {sys.version_info.major}.{sys.version_info.minor}.{sys.version_info.micro}")
    return True

def check_admin_privileges():
    """Check if running with administrator/root privileges"""
    if os.name == 'nt':  # Windows
        try:
            import ctypes
            is_admin = ctypes.windll.shell32.IsUserAnAdmin()
            if is_admin:
                print("✓ Running with administrator privileges")
            else:
                print("⚠ Administrator privileges required for raw sockets")
            return is_admin
        except:
            return False
    else:  # Unix-like
        is_root = os.geteuid() == 0
        if is_root:
            print("✓ Running with root privileges")
        else:
            print("⚠ Root privileges required for raw sockets")
        return is_root

def install_requirements():
    """Install Python requirements"""
    print("\n=== Installing Python Requirements ===")
    
    # Essential packages for TCP reset attack
    essential_packages = ["scapy", "netifaces", "colorama"]
    optional_packages = ["psutil"]
    
    try:
        # Upgrade pip first
        subprocess.check_call([sys.executable, "-m", "pip", "install", "--upgrade", "pip"])
        
        # Install essential packages
        for package in essential_packages:
            try:
                print(f"Installing {package}...")
                subprocess.check_call([sys.executable, "-m", "pip", "install", package])
                print(f"✓ {package} installed successfully")
            except subprocess.CalledProcessError as e:
                print(f"✗ Failed to install {package}: {e}")
                return False
        
        # Try to install optional packages
        for package in optional_packages:
            try:
                print(f"Installing optional package {package}...")
                subprocess.check_call([sys.executable, "-m", "pip", "install", package])
                print(f"✓ {package} installed successfully")
            except subprocess.CalledProcessError as e:
                print(f"⚠ Optional package {package} failed to install (non-critical): {e}")
        
        print("✓ Essential requirements installed successfully")
        return True
        
    except Exception as e:
        print(f"Error installing requirements: {e}")
        return False

def test_scapy_import():
    """Test if Scapy can be imported and works"""
    print("\n=== Testing Scapy Installation ===")
    
    try:
        from scapy.all import IP, TCP, send
        print("✓ Scapy imported successfully")
        
        # Test packet creation
        test_packet = IP(dst="127.0.0.1") / TCP(dport=80)
        print("✓ Packet creation works")
        
        return True
        
    except ImportError as e:
        print(f"Error importing Scapy: {e}")
        return False
    except Exception as e:
        print(f"Error testing Scapy: {e}")
        return False

def check_network_interfaces():
    """Check available network interfaces"""
    print("\n=== Checking Network Interfaces ===")
    
    try:
        import netifaces
        
        interfaces = netifaces.interfaces()
        print(f"Available interfaces: {interfaces}")
        
        for interface in interfaces:
            if interface != 'lo':  # Skip loopback
                addrs = netifaces.ifaddresses(interface)
                if netifaces.AF_INET in addrs:
                    ip = addrs[netifaces.AF_INET][0]['addr']
                    print(f"  {interface}: {ip}")
        
        return True
        
    except ImportError:
        print("Error: netifaces not installed")
        return False
    except Exception as e:
        print(f"Error checking interfaces: {e}")
        return False

def create_log_directory():
    """Create logs directory if it doesn't exist"""
    log_dir = Path(__file__).parent.parent / "logs"
    log_dir.mkdir(exist_ok=True)
    print(f"✓ Log directory created: {log_dir}")

def check_firewall_settings():
    """Check firewall settings and provide recommendations"""
    print("\n=== Firewall Recommendations ===")
    
    system = platform.system().lower()
    
    if system == "windows":
        print("Windows Defender Firewall:")
        print("  - May block raw socket operations")
        print("  - Consider temporarily disabling for testing")
        print("  - Or add exception for Python")
    
    elif system == "linux":
        print("Linux iptables/ufw:")
        print("  - May drop forged packets")
        print("  - Check with: sudo iptables -L")
        print("  - Consider: sudo ufw disable (temporarily)")
    
    elif system == "darwin":  # macOS
        print("macOS pf firewall:")
        print("  - May block raw socket operations")
        print("  - Check System Preferences > Security & Privacy")
    
    print("\n⚠ Remember to restore firewall settings after testing!")

def display_security_warning():
    """Display important security and legal warnings"""
    print("""
╔══════════════════════════════════════════════════════════════════════════════╗
║                              SECURITY WARNING                               ║
╠══════════════════════════════════════════════════════════════════════════════╣
║                                                                              ║
║  This tool is designed for EDUCATIONAL PURPOSES ONLY                        ║
║                                                                              ║
║  ⚠ LEGAL NOTICE:                                                           ║
║    • Only use on networks you own or have explicit permission to test       ║
║    • Unauthorized network attacks are ILLEGAL in most jurisdictions         ║
║    • You are responsible for compliance with local laws                     ║
║                                                                              ║
║  🛡️ ETHICAL GUIDELINES:                                                    ║
║    • Use only in controlled lab environments                                ║
║    • Do not disrupt production systems                                      ║
║    • Always restore network state after testing                            ║
║    • Report vulnerabilities responsibly                                     ║
║                                                                              ║
║  🎯 INTENDED USE:                                                           ║
║    • Computer security education (BUET CSE406)                              ║
║    • Authorized penetration testing                                         ║
║    • Network security research                                              ║
║    • Vulnerability assessment with permission                               ║
║                                                                              ║
╚══════════════════════════════════════════════════════════════════════════════╝
    """)
    
    accept = input("Do you understand and accept these terms? (type 'I UNDERSTAND'): ")
    if accept != "I UNDERSTAND":
        print("Setup cancelled. Terms not accepted.")
        return False
    
    return True

def main():
    """Main setup function"""
    print("TCP Reset Attack Tool - Setup")
    print("BUET CSE406 Computer Security Sessional")
    print("=" * 50)
    
    # Display security warning first
    if not display_security_warning():
        sys.exit(1)
    
    print("\n=== System Compatibility Check ===")
    
    # Check Python version
    if not check_python_version():
        sys.exit(1)
    
    # Check privileges
    has_privileges = check_admin_privileges()
    if not has_privileges:
        print("\n⚠ Warning: This tool requires elevated privileges to function properly")
        print("  Windows: Run as Administrator")
        print("  Linux/macOS: Run with sudo")
        
        continue_anyway = input("\nContinue setup anyway? (y/N): ")
        if continue_anyway.lower() != 'y':
            sys.exit(1)
    
    # Install requirements
    if not install_requirements():
        print("Failed to install requirements")
        sys.exit(1)
    
    # Test Scapy
    if not test_scapy_import():
        print("Scapy installation test failed")
        sys.exit(1)
    
    # Check network interfaces
    if not check_network_interfaces():
        print("Network interface check failed")
        sys.exit(1)
    
    # Create directories
    create_log_directory()
    
    # Firewall recommendations
    check_firewall_settings()
    
    print("\n" + "=" * 50)
    print("✅ Setup completed successfully!")
    print("\nNext steps:")
    print("1. Edit config/attack_config.ini with your network settings")
    print("2. Run: python src/tcp_reset_attack.py")
    print("3. Follow the interactive prompts")
    print("\nFor help: python src/tcp_reset_attack.py --help")
    print("=" * 50)

if __name__ == "__main__":
    main()
