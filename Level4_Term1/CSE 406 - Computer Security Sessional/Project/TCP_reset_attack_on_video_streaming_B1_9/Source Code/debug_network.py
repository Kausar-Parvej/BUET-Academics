#!/usr/bin/env python3
"""
Network Debug Script
Check network connectivity and interface accessibility
"""

import os
import sys
import subprocess
import socket
import netifaces

def check_wsl_networking():
    """Check WSL2 networking capabilities"""
    print("=== WSL2 Networking Debug ===")
    
    # Check if we're in WSL
    try:
        with open('/proc/version', 'r') as f:
            version = f.read()
            if 'microsoft' in version.lower() or 'wsl' in version.lower():
                print("✅ Running in WSL2")
            else:
                print("❌ Not running in WSL")
    except:
        print("❓ Cannot determine WSL status")
    
    # Check network interfaces
    print("\n--- Network Interfaces ---")
    interfaces = netifaces.interfaces()
    for iface in interfaces:
        try:
            addrs = netifaces.ifaddresses(iface)
            if netifaces.AF_INET in addrs:
                ip = addrs[netifaces.AF_INET][0]['addr']
                print(f"{iface}: {ip}")
        except:
            print(f"{iface}: No IP")
    
    # Check Windows host IP
    print("\n--- Windows Host Access ---")
    try:
        # WSL2 usually can access Windows host via the default gateway
        import subprocess
        result = subprocess.run(['ip', 'route', 'show', 'default'], 
                              capture_output=True, text=True)
        if result.returncode == 0:
            # Extract default gateway (Windows host IP)
            for line in result.stdout.split('\n'):
                if 'default via' in line:
                    gateway = line.split()[2]
                    print(f"Windows Host IP (probable): {gateway}")
                    
                    # Test connectivity to Windows host
                    ping_result = subprocess.run(['ping', '-c', '1', '-W', '2', gateway],
                                               capture_output=True)
                    if ping_result.returncode == 0:
                        print(f"✅ Can reach Windows host at {gateway}")
                    else:
                        print(f"❌ Cannot reach Windows host at {gateway}")
                    break
    except Exception as e:
        print(f"Error checking Windows host: {e}")
    
    # Check for bridge networking
    print("\n--- Bridge Network Check ---")
    try:
        result = subprocess.run(['ip', 'route'], capture_output=True, text=True)
        if '192.168.137.0/24' in result.stdout:
            print("✅ Route to 192.168.137.0/24 exists")
        else:
            print("❌ No route to target network 192.168.137.0/24")
            
        # Check if we can add a route (requires sudo)
        print("\nTrying to add route to target network...")
        gateway_result = subprocess.run(['ip', 'route', 'show', 'default'], 
                                       capture_output=True, text=True)
        if gateway_result.returncode == 0:
            for line in gateway_result.stdout.split('\n'):
                if 'default via' in line:
                    default_gw = line.split()[2]
                    print(f"Would add route: sudo ip route add 192.168.137.0/24 via {default_gw}")
                    break
    except Exception as e:
        print(f"Error checking routes: {e}")

def test_raw_socket():
    """Test raw socket capabilities"""
    print("\n=== Raw Socket Test ===")
    try:
        # Test if we can create raw sockets (requires root)
        sock = socket.socket(socket.AF_INET, socket.SOCK_RAW, socket.IPPROTO_TCP)
        sock.close()
        print("✅ Raw socket creation successful")
    except PermissionError:
        print("❌ Raw socket requires root privileges")
    except Exception as e:
        print(f"❌ Raw socket error: {e}")

def test_scapy_interfaces():
    """Test Scapy interface detection"""
    print("\n=== Scapy Interface Test ===")
    try:
        from scapy.all import get_if_list, get_if_addr
        interfaces = get_if_list()
        print("Scapy detected interfaces:")
        for iface in interfaces:
            try:
                ip = get_if_addr(iface)
                print(f"  {iface}: {ip}")
            except:
                print(f"  {iface}: No IP")
    except Exception as e:
        print(f"Scapy interface test failed: {e}")

if __name__ == "__main__":
    if os.geteuid() != 0:
        print("⚠️  This script should be run as root for complete testing")
        print("   Run: sudo python3 debug_network.py")
    
    check_wsl_networking()
    test_raw_socket()
    test_scapy_interfaces()
    
    print("\n=== Recommendations ===")
    print("For WSL2 TCP Reset Attack:")
    print("1. Consider using bridge networking mode")
    print("2. Or run attack directly on Windows with Npcap")
    print("3. Or use WSL1 instead of WSL2 for direct network access")
    print("4. Or set up network namespace sharing")
