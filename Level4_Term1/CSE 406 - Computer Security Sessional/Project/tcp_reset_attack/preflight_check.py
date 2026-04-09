#!/usr/bin/env python3
"""
TCP Reset Attack - Pre-flight Check
BUET CSE406 Computer Security Sessional
Educational Purpose Only

This script performs comprehensive system checks before running the attack.
"""

import sys
import os
import subprocess
import platform
import socket
from pathlib import Path

def check_python_version():
    """Check Python version compatibility"""
    print("🐍 Checking Python version...")
    version = sys.version_info
    
    if version.major < 3 or (version.major == 3 and version.minor < 7):
        print(f"❌ Python {version.major}.{version.minor} is too old")
        print("   Minimum required: Python 3.7")
        return False
    
    print(f"✅ Python {version.major}.{version.minor}.{version.micro} is compatible")
    return True

def check_administrator_privileges():
    """Check if running with required privileges"""
    print("🔐 Checking administrator privileges...")
    
    if os.name == 'nt':  # Windows
        try:
            import ctypes
            is_admin = ctypes.windll.shell32.IsUserAnAdmin()
            if is_admin:
                print("✅ Running with administrator privileges")
                return True
            else:
                print("❌ Administrator privileges required")
                print("   Right-click and 'Run as Administrator'")
                return False
        except:
            print("❓ Cannot determine privilege level")
            return False
    else:  # Unix-like
        is_root = os.geteuid() == 0
        if is_root:
            print("✅ Running with root privileges")
            return True
        else:
            print("❌ Root privileges required")
            print("   Run with: sudo python preflight_check.py")
            return False

def check_required_packages():
    """Check if required Python packages are installed"""
    print("📦 Checking required packages...")
    
    required_packages = [
        ('scapy', 'scapy'),
        ('netifaces', 'netifaces'),
        ('colorama', 'colorama'),
        ('psutil', 'psutil')
    ]
    
    missing_packages = []
    
    for package_name, import_name in required_packages:
        try:
            __import__(import_name)
            print(f"✅ {package_name} is installed")
        except ImportError:
            print(f"❌ {package_name} is missing")
            missing_packages.append(package_name)
    
    if missing_packages:
        print(f"\n📥 To install missing packages:")
        print(f"   pip install {' '.join(missing_packages)}")
        return False
    
    return True

def test_scapy_functionality():
    """Test if Scapy can create packets"""
    print("🔧 Testing Scapy functionality...")
    
    try:
        from scapy.layers.inet import IP, TCP
        from scapy.layers.l2 import ARP
        
        # Test packet creation
        test_ip = IP(dst="127.0.0.1")
        test_tcp = TCP(dport=80)
        test_arp = ARP(pdst="192.168.1.1")
        
        print("✅ Scapy packet creation works")
        return True
        
    except Exception as e:
        print(f"❌ Scapy test failed: {e}")
        return False

def check_network_interfaces():
    """Check available network interfaces"""
    print("🌐 Checking network interfaces...")
    
    try:
        import netifaces
        
        interfaces = netifaces.interfaces()
        active_interfaces = []
        
        for iface in interfaces:
            if iface.lower() in ['lo', 'loopback']:
                continue
            
            try:
                addrs = netifaces.ifaddresses(iface)
                if netifaces.AF_INET in addrs:
                    ip = addrs[netifaces.AF_INET][0]['addr']
                    if not ip.startswith('127.'):
                        active_interfaces.append((iface, ip))
            except:
                continue
        
        if active_interfaces:
            print(f"✅ Found {len(active_interfaces)} active interfaces:")
            for iface, ip in active_interfaces[:3]:  # Show first 3
                print(f"   - {iface}: {ip}")
            return True
        else:
            print("❌ No active network interfaces found")
            return False
            
    except Exception as e:
        print(f"❌ Network interface check failed: {e}")
        return False

def check_network_connectivity():
    """Test basic network connectivity"""
    print("🌍 Testing network connectivity...")
    
    test_hosts = [
        ("8.8.8.8", "Google DNS"),
        ("1.1.1.1", "Cloudflare DNS")
    ]
    
    for host, description in test_hosts:
        try:
            # Simple socket test
            sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            sock.settimeout(3)
            result = sock.connect_ex((host, 53))
            sock.close()
            
            if result == 0:
                print(f"✅ Can reach {description} ({host})")
                return True
            else:
                print(f"❌ Cannot reach {description} ({host})")
        except Exception as e:
            print(f"❌ Network test failed: {e}")
    
    return False

def check_firewall_warnings():
    """Check for potential firewall issues"""
    print("🛡️ Checking firewall considerations...")
    
    system = platform.system().lower()
    
    if system == "windows":
        print("⚠️  Windows Firewall considerations:")
        print("   - May block raw socket operations")
        print("   - Consider adding Python to firewall exceptions")
        print("   - Windows Defender may flag packet injection tools")
    
    elif system == "linux":
        print("⚠️  Linux firewall considerations:")
        print("   - Check iptables rules: sudo iptables -L")
        print("   - Ensure packet forwarding is enabled")
        print("   - Some distributions block raw sockets by default")
    
    elif system == "darwin":  # macOS
        print("⚠️  macOS firewall considerations:")
        print("   - System Integrity Protection may interfere")
        print("   - Check Privacy & Security settings")
        print("   - Raw socket access may require additional permissions")
    
    print("✅ Firewall check completed (warnings noted)")
    return True

def check_project_structure():
    """Verify project files are present"""
    print("📁 Checking project structure...")
    
    project_root = Path(__file__).parent
    required_files = [
        "src/tcp_reset_attack.py",
        "src/config_manager.py",
        "src/network_utils.py",
        "src/arp_poisoner.py",
        "src/packet_monitor.py",
        "config/attack_config.ini",
        "requirements.txt"
    ]
    
    missing_files = []
    
    for file_path in required_files:
        full_path = project_root / file_path
        if full_path.exists():
            print(f"✅ {file_path}")
        else:
            print(f"❌ {file_path} (missing)")
            missing_files.append(file_path)
    
    if missing_files:
        print(f"\n❌ Missing {len(missing_files)} required files")
        return False
    
    print("✅ All required files present")
    return True

def display_summary(results):
    """Display check summary and recommendations"""
    print("\n" + "=" * 60)
    print("PREFLIGHT CHECK SUMMARY")
    print("=" * 60)
    
    total_checks = len(results)
    passed_checks = sum(results.values())
    
    print(f"✅ Passed: {passed_checks}/{total_checks} checks")
    
    if passed_checks == total_checks:
        print("\n🎉 ALL CHECKS PASSED!")
        print("Your system is ready for TCP Reset Attack testing.")
        print("\nNext steps:")
        print("1. Review config/attack_config.ini")
        print("2. Run: python scripts/network_discovery.py")
        print("3. Run: python src/tcp_reset_attack.py")
    
    else:
        print(f"\n⚠️  {total_checks - passed_checks} CHECKS FAILED")
        print("Please resolve the issues above before proceeding.")
        
        print("\nCommon solutions:")
        if not results.get('packages'):
            print("• Install packages: pip install -r requirements.txt")
        if not results.get('privileges'):
            print("• Run as administrator/root")
        if not results.get('scapy'):
            print("• Reinstall Scapy: pip uninstall scapy && pip install scapy")
    
    print("=" * 60)

def main():
    """Run all preflight checks"""
    print("TCP Reset Attack - Preflight Check")
    print("BUET CSE406 Computer Security Project")
    print("=" * 60)
    
    checks = [
        ("python", check_python_version),
        ("privileges", check_administrator_privileges),
        ("packages", check_required_packages),
        ("scapy", test_scapy_functionality),
        ("interfaces", check_network_interfaces),
        ("connectivity", check_network_connectivity),
        ("firewall", check_firewall_warnings),
        ("structure", check_project_structure)
    ]
    
    results = {}
    
    for check_name, check_func in checks:
        try:
            print(f"\n--- {check_name.upper()} CHECK ---")
            results[check_name] = check_func()
        except Exception as e:
            print(f"❌ Check crashed: {e}")
            results[check_name] = False
    
    display_summary(results)
    
    # Return appropriate exit code
    all_passed = all(results.values())
    return 0 if all_passed else 1

if __name__ == "__main__":
    try:
        exit_code = main()
        sys.exit(exit_code)
    except KeyboardInterrupt:
        print("\n\nPreflight check interrupted by user")
        sys.exit(1)
    except Exception as e:
        print(f"\nPreflight check failed: {e}")
        sys.exit(1)
