#!/usr/bin/env python3
"""
Network Discovery and Target Identification Script
BUET CSE406 Computer Security Sessional
Educational Purpose Only
"""

import sys
import os
import time
import threading
import argparse
from pathlib import Path

# Add src directory to Python path
sys.path.append(str(Path(__file__).parent.parent / "src"))

from srcnetwork_utils.py import NetworkUtils
from config_manager import ConfigManager

class NetworkDiscovery:
    """Network discovery and target identification"""
    
    def __init__(self):
        self.active_hosts = []
        self.youtube_servers = []
        self.network_info = {}
    
    def discover_network_topology(self):
        """Discover local network topology"""
        print("=== Network Discovery ===")
        
        # Get local network information
        local_ip = NetworkUtils.get_local_ip()
        gateway_ip = NetworkUtils.get_default_gateway()
        
        print(f"Local IP: {local_ip}")
        print(f"Gateway IP: {gateway_ip}")
        
        self.network_info = {
            'local_ip': local_ip,
            'gateway_ip': gateway_ip,
            'network_prefix': '.'.join(local_ip.split('.')[:-1])
        }
        
        return self.network_info
    
    def scan_for_active_hosts(self, network_prefix=None, timeout=1):
        """Scan for active hosts in the network"""
        if not network_prefix:
            network_prefix = self.network_info.get('local_ip', '192.168.1.1')
        
        print(f"\n=== Scanning Network: {network_prefix}/24 ===")
        print("This may take a few minutes...")
        
        base_ip = '.'.join(network_prefix.split('.')[:-1])
        active_hosts = []
        
        # Threaded scanning for faster results
        threads = []
        results = []
        
        def ping_host(ip):
            if NetworkUtils.ping_host(ip, count=1, timeout=timeout):
                results.append(ip)
                print(f"✓ Found active host: {ip}")
        
        # Scan IP range
        for i in range(1, 255):
            ip = f"{base_ip}.{i}"
            thread = threading.Thread(target=ping_host, args=(ip,))
            threads.append(thread)
            thread.start()
            
            # Limit concurrent threads
            if len(threads) >= 20:
                for t in threads:
                    t.join()
                threads = []
        
        # Wait for remaining threads
        for thread in threads:
            thread.join()
        
        self.active_hosts = sorted(results, key=lambda x: int(x.split('.')[-1]))
        print(f"\nFound {len(self.active_hosts)} active hosts:")
        for host in self.active_hosts:
            print(f"  {host}")
        
        return self.active_hosts
    
    def identify_youtube_servers(self):
        """Identify YouTube servers"""
        print("\n=== Identifying YouTube Servers ===")
        
        self.youtube_servers = NetworkUtils.get_youtube_servers()
        
        print("YouTube/Google servers found:")
        for server in self.youtube_servers:
            print(f"  {server}")
        
        return self.youtube_servers
    
    def get_network_interfaces(self):
        """Get available network interfaces"""
        print("\n=== Network Interfaces ===")
        
        interfaces = NetworkUtils.get_network_interfaces()
        
        for iface in interfaces:
            print(f"Interface: {iface['name']}")
            print(f"  IP: {iface['ip']}")
            print(f"  Status: {iface['status']}")
            print()
        
        return interfaces
    
    def generate_attack_config(self, target_ip=None, gateway_ip=None, interface=None):
        """Generate attack configuration based on discovery"""
        print("\n=== Generating Attack Configuration ===")
        
        if not target_ip and self.active_hosts:
            print("Available targets:")
            for i, host in enumerate(self.active_hosts):
                print(f"  {i+1}. {host}")
            
            try:
                choice = int(input("Select target (number): ")) - 1
                target_ip = self.active_hosts[choice]
            except (ValueError, IndexError):
                print("Invalid selection")
                return None
        
        if not gateway_ip:
            gateway_ip = self.network_info.get('gateway_ip')
        
        if not interface:
            interfaces = NetworkUtils.get_network_interfaces()
            if interfaces:
                interface = interfaces[0]['name']  # Use first active interface
        
        config_data = f"""# Auto-generated TCP Reset Attack Configuration
# Generated on: {time.strftime('%Y-%m-%d %H:%M:%S')}

[NETWORK]
TARGET_IP = {target_ip or '192.168.1.100'}
GATEWAY_IP = {gateway_ip or '192.168.1.1'}
SERVER_IP = auto
INTERFACE = {interface or 'auto'}

[ATTACK]
ARP_INTERVAL = 2
RST_DELAY = 50
MAX_RST_PACKETS = 3
MONITOR_DURATION = 0

[DETECTION]
VIDEO_PORTS = 443,80,8080
MIN_VIDEO_PACKET_SIZE = 1400
CONNECTION_TIMEOUT = 300

[LOGGING]
LOG_LEVEL = INFO
LOG_FILE = logs/attack.log
CAPTURE_PACKETS = false

[SAFETY]
ENABLE_SAFETY = true
RESTRICT_TO_LOCAL = true
MAX_DURATION = 30
"""
        
        config_file = Path(__file__).parent.parent / "config" / "attack_config_auto.ini"
        
        try:
            with open(config_file, 'w') as f:
                f.write(config_data)
            
            print(f"Configuration saved to: {config_file}")
            print(f"Target IP: {target_ip}")
            print(f"Gateway IP: {gateway_ip}")
            print(f"Interface: {interface}")
            
            return str(config_file)
            
        except Exception as e:
            print(f"Error saving configuration: {e}")
            return None
    
    def run_full_discovery(self):
        """Run complete network discovery process"""
        print("TCP Reset Attack - Network Discovery")
        print("BUET CSE406 Computer Security Project")
        print("=" * 50)
        
        # Discover network topology
        self.discover_network_topology()
        
        # Scan for active hosts
        scan_network = input(f"\nScan network {self.network_info['network_prefix']}.0/24 for active hosts? (y/N): ")
        if scan_network.lower() == 'y':
            self.scan_for_active_hosts()
        
        # Identify YouTube servers
        self.identify_youtube_servers()
        
        # Show network interfaces
        self.get_network_interfaces()
        
        # Generate configuration
        generate_config = input("\nGenerate attack configuration file? (y/N): ")
        if generate_config.lower() == 'y':
            config_file = self.generate_attack_config()
            if config_file:
                print(f"\nUse this configuration file with:")
                print(f"python src/tcp_reset_attack.py --config {config_file}")
        
        print("\n" + "=" * 50)
        print("Network discovery completed!")
        print("Review the information above before proceeding with the attack.")

def main():
    """Main function"""
    parser = argparse.ArgumentParser(
        description="Network Discovery for TCP Reset Attack",
        formatter_class=argparse.RawDescriptionHelpFormatter
    )
    
    parser.add_argument(
        '--network', '-n',
        type=str,
        help='Network prefix to scan (e.g., 192.168.1)'
    )
    
    parser.add_argument(
        '--timeout', '-t',
        type=int,
        default=1,
        help='Ping timeout in seconds (default: 1)'
    )
    
    parser.add_argument(
        '--quick',
        action='store_true',
        help='Skip network scanning for faster results'
    )
    
    args = parser.parse_args()
    
    try:
        discovery = NetworkDiscovery()
        
        if args.quick:
            # Quick discovery without network scanning
            discovery.discover_network_topology()
            discovery.identify_youtube_servers()
            discovery.get_network_interfaces()
            discovery.generate_attack_config()
        else:
            # Full discovery process
            discovery.run_full_discovery()
    
    except KeyboardInterrupt:
        print("\n\nDiscovery interrupted by user")
    except Exception as e:
        print(f"Discovery failed: {e}")

if __name__ == "__main__":
    main()
