#!/usr/bin/env python3
"""
TCP Reset Attack - Installation Test
BUET CSE406 Computer Security Sessional
Educational Purpose Only
"""

import sys
import os
from pathlib import Path

# Add src directory to path
sys.path.append(str(Path(__file__).parent / "src"))

def test_imports():
    """Test if all required modules can be imported"""
    print("=== Testing Module Imports ===")
    
    try:
        print("Testing Scapy...")
        from scapy.all import IP, TCP, send, sniff
        print("✓ Scapy imported successfully")
    except ImportError as e:
        print(f"✗ Scapy import failed: {e}")
        return False
    
    try:
        print("Testing netifaces...")
        import netifaces
        print("✓ netifaces imported successfully")
    except ImportError as e:
        print(f"✗ netifaces import failed: {e}")
        return False
    
    try:
        print("Testing project modules...")
        from config_manager import ConfigManager
        from network_utils import NetworkUtils
        from arp_poisoner import ARPPoisoner
        from packet_monitor import PacketMonitor
        print("✓ All project modules imported successfully")
    except ImportError as e:
        print(f"✗ Project module import failed: {e}")
        return False
    
    return True

def test_network_detection():
    """Test basic network detection functionality"""
    print("\n=== Testing Network Detection ===")
    
    try:
        from network_utils import NetworkUtils
        
        # Test local IP detection
        local_ip = NetworkUtils.get_local_ip()
        print(f"✓ Local IP detected: {local_ip}")
        
        # Test gateway detection
        gateway = NetworkUtils.get_default_gateway()
        print(f"✓ Gateway detected: {gateway}")
        
        # Test interface enumeration
        interfaces = NetworkUtils.get_network_interfaces()
        print(f"✓ Found {len(interfaces)} network interfaces")
        
        return True
        
    except Exception as e:
        print(f"✗ Network detection failed: {e}")
        return False

def test_configuration():
    """Test configuration management"""
    print("\n=== Testing Configuration ===")
    
    try:
        from config_manager import ConfigManager
        
        config = ConfigManager()
        target_ip = config.get('NETWORK', 'TARGET_IP')
        gateway_ip = config.get('NETWORK', 'GATEWAY_IP')
        interface = config.get('NETWORK', 'INTERFACE')
        
        print(f"✓ Configuration loaded successfully")
        print(f"  Target IP: {target_ip}")
        print(f"  Gateway IP: {gateway_ip}")
        print(f"  Interface: {interface}")
        
        return True
        
    except Exception as e:
        print(f"✗ Configuration test failed: {e}")
        return False

def test_permissions():
    """Test if running with required permissions"""
    print("\n=== Testing Permissions ===")
    
    if os.name == 'nt':  # Windows
        try:
            import ctypes
            is_admin = ctypes.windll.shell32.IsUserAnAdmin()
            if is_admin:
                print("✓ Running with administrator privileges")
                return True
            else:
                print("✗ Administrator privileges required")
                return False
        except:
            print("✗ Cannot check administrator privileges")
            return False
    else:  # Unix-like
        is_root = os.geteuid() == 0
        if is_root:
            print("✓ Running with root privileges")
            return True
        else:
            print("✗ Root privileges required")
            return False

def main():
    """Run all tests"""
    print("TCP Reset Attack - Installation Test")
    print("BUET CSE406 Computer Security Project")
    print("=" * 50)
    
    tests = [
        ("Module Imports", test_imports),
        ("Network Detection", test_network_detection),
        ("Configuration", test_configuration),
        ("Permissions", test_permissions)
    ]
    
    passed = 0
    total = len(tests)
    
    for test_name, test_func in tests:
        try:
            if test_func():
                passed += 1
            else:
                print(f"⚠ {test_name} test failed")
        except Exception as e:
            print(f"⚠ {test_name} test crashed: {e}")
    
    print("\n" + "=" * 50)
    print(f"Test Results: {passed}/{total} tests passed")
    
    if passed == total:
        print("✅ All tests passed! Tool is ready to use.")
        print("\nNext steps:")
        print("1. python scripts/network_discovery.py")
        print("2. python src/tcp_reset_attack.py")
    else:
        print("❌ Some tests failed. Please check the errors above.")
        print("\nCommon solutions:")
        print("- Run: pip install -r requirements.txt")
        print("- Run as administrator/root")
        print("- Check network connectivity")
    
    return passed == total

if __name__ == "__main__":
    try:
        success = main()
        sys.exit(0 if success else 1)
    except KeyboardInterrupt:
        print("\nTest interrupted by user")
        sys.exit(1)
    except Exception as e:
        print(f"Test failed with error: {e}")
        sys.exit(1)
