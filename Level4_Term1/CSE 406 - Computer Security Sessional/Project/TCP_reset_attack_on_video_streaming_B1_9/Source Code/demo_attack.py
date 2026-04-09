#!/usr/bin/env python3
"""
Demo Attack Controller - Modified for localhost demonstration
"""

import sys
import os
import time
import threading
from pathlib import Path

# Add src directory to Python path
sys.path.append(str(Path(__file__).parent / "src"))

from config_manager import ConfigManager
from packet_monitor import PacketMonitor

class DemoAttack:
    """Simplified attack controller for localhost demonstration"""
    
    def __init__(self, config_file=None):
        if config_file is None:
            config_file = Path(__file__).parent / "config" / "demo_config.ini"
        
        self.config = ConfigManager(config_file)
        self.packet_monitor = None
        self.running = False
        
        print("=== TCP Reset Attack Demo ===")
        print("Targeting localhost traffic - no ARP poisoning needed")
    
    def start_demo_attack(self):
        """Start the demo attack (packet monitoring only)"""
        if self.running:
            print("[DEMO] Attack already running")
            return False
        
        print("\n[DEMO] Starting TCP Reset Attack Demo...")
        
        target_ip = self.config.get('NETWORK', 'TARGET_IP')
        interface = self.config.get('NETWORK', 'INTERFACE')
        
        print(f"[DEMO] Target IP: {target_ip}")
        print(f"[DEMO] Interface: {interface}")
        
        try:
            # Initialize packet monitor (no ARP poisoning for localhost)
            self.packet_monitor = PacketMonitor(
                target_ip=target_ip,
                interface=interface,
                config=self.config
            )
            
            # Start packet monitoring
            print("[DEMO] Starting packet monitoring...")
            if self.packet_monitor.start_monitoring():
                self.running = True
                print("\n" + "=" * 50)
                print("TCP RESET ATTACK DEMO ACTIVE")
                print("=" * 50)
                print("Monitoring traffic on localhost:8080")
                print("Start the demo client to see the attack in action!")
                print("Press Ctrl+C to stop")
                print("=" * 50)
                return True
            else:
                print("[DEMO] Failed to start packet monitoring")
                return False
                
        except Exception as e:
            print(f"[DEMO] Error starting attack: {e}")
            return False
    
    def stop_demo_attack(self):
        """Stop the demo attack"""
        if not self.running:
            return
        
        print("\n[DEMO] Stopping attack...")
        self.running = False
        
        if self.packet_monitor:
            self.packet_monitor.stop_monitoring()
        
        print("[DEMO] Demo attack stopped")
    
    def wait_for_interrupt(self):
        """Wait for user interrupt"""
        try:
            while self.running:
                time.sleep(1)
        except KeyboardInterrupt:
            self.stop_demo_attack()

def main():
    """Main demo function"""
    if os.geteuid() != 0:
        print("Demo requires root privileges for packet capture")
        print("Run: sudo python3 demo_attack.py")
        sys.exit(1)
    
    demo = DemoAttack()
    
    if demo.start_demo_attack():
        demo.wait_for_interrupt()
    else:
        print("Failed to start demo attack")
        sys.exit(1)

if __name__ == "__main__":
    main()
