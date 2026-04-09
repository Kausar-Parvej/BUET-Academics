#!/usr/bin/env python3
"""
WSL2 Bridge Network Setup for TCP Reset Attack
This script helps configure WSL2 to access Windows host networks
"""

import subprocess
import sys
import os

def setup_wsl_bridge():
    """Set up WSL2 bridge networking"""
    print("=== WSL2 Bridge Network Setup ===")
    
    print("""
This script will help you set up WSL2 networking to access your Windows hotspot.

WINDOWS SIDE SETUP (Run in Windows PowerShell as Administrator):
1. Disable Hyper-V (if enabled):
   Disable-WindowsOptionalFeature -Online -FeatureName Microsoft-Hyper-V-All
   
2. Enable WSL2 bridged networking:
   netsh wlan set hostednetwork mode=allow ssid="YourHotspot" key="password"
   netsh wlan start hostednetwork
   
3. Share network connection:
   - Go to Network Connections
   - Right-click your internet connection
   - Properties -> Sharing
   - Allow other network users to connect through this computer's Internet connection
   - Select the hotspot adapter

ALTERNATIVE: Use Hyper-V Bridge Mode
1. Create a Hyper-V external switch:
   New-VMSwitch -Name "WSL" -NetAdapterName "Wi-Fi" -AllowManagementOS $true
   
2. Restart WSL:
   wsl --shutdown
   wsl

LINUX SIDE SETUP (Run in WSL2):
""")
    
    # Check current routing
    print("Current routing table:")
    subprocess.run(['ip', 'route'])
    
    print("\nCurrent interface configuration:")
    subprocess.run(['ip', 'addr'])
    
    # Try to add route to target network
    print("\n--- Attempting to add route to target network ---")
    try:
        # Get default gateway
        result = subprocess.run(['ip', 'route', 'show', 'default'], 
                              capture_output=True, text=True)
        if result.returncode == 0:
            for line in result.stdout.split('\n'):
                if 'default via' in line:
                    default_gw = line.split()[2]
                    print(f"Default gateway: {default_gw}")
                    
                    # Add route to Windows hotspot network
                    print("Adding route to 192.168.137.0/24...")
                    route_cmd = ['sudo', 'ip', 'route', 'add', '192.168.137.0/24', 'via', default_gw]
                    print(f"Command: {' '.join(route_cmd)}")
                    
                    confirm = input("Execute this command? (y/N): ")
                    if confirm.lower() == 'y':
                        result = subprocess.run(route_cmd)
                        if result.returncode == 0:
                            print("✅ Route added successfully")
                        else:
                            print("❌ Failed to add route")
                    break
    except Exception as e:
        print(f"Error: {e}")

def test_connectivity():
    """Test connectivity to target network"""
    print("\n=== Testing Connectivity ===")
    
    targets = [
        ("192.168.137.1", "Windows Hotspot Gateway"),
        ("192.168.137.44", "Target Phone")
    ]
    
    for ip, description in targets:
        print(f"Testing {description} ({ip})...")
        result = subprocess.run(['ping', '-c', '3', '-W', '2', ip], 
                              capture_output=True)
        if result.returncode == 0:
            print(f"✅ {description} is reachable")
        else:
            print(f"❌ {description} is not reachable")

if __name__ == "__main__":
    if os.geteuid() != 0:
        print("This script requires root privileges")
        print("Run: sudo python3 wsl_bridge_setup.py")
        sys.exit(1)
    
    setup_wsl_bridge()
    test_connectivity()
    
    print("\n=== Next Steps ===")
    print("If connectivity works, you can proceed with the attack:")
    print("sudo python3 src/tcp_reset_attack.py --target 192.168.137.44 --gateway 192.168.137.1")
