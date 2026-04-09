#!/usr/bin/env python3
"""
Network Utilities for TCP Reset Attack
BUET CSE406 Computer Security Sessional
Educational Purpose Only
"""

import socket
import struct
import netifaces
import subprocess
import platform
import time
from scapy.all import srp, Ether
from scapy.layers.inet import IP, TCP, ICMP
from scapy.layers.l2 import ARP

class NetworkUtils:
    @staticmethod
    def get_mac_address(ip_address, interface=None, timeout=3):
        """Get MAC address for given IP using ARP"""
        try:
            # For Windows, try multiple approaches
            if platform.system() == "Windows":
                # Method 1: Try without interface specification (let Scapy auto-route)
                try:
                    arp_request = ARP(pdst=ip_address)
                    broadcast = Ether(dst="ff:ff:ff:ff:ff:ff")
                    arp_request_broadcast = broadcast / arp_request
                    
                    answered_list = srp(arp_request_broadcast, 
                                      timeout=timeout, 
                                      verbose=False)[0]
                    
                    if answered_list:
                        return answered_list[0][1].hwsrc
                except Exception as e1:
                    print(f"[DEBUG] Method 1 failed: {e1}")
                
                # Method 2: Try using Windows arp command
                try:
                    result = subprocess.run(['arp', '-a', ip_address], 
                                          capture_output=True, text=True, timeout=5)
                    if result.returncode == 0:
                        lines = result.stdout.strip().split('\n')
                        for line in lines:
                            if ip_address in line and 'dynamic' in line.lower():
                                parts = line.split()
                                for part in parts:
                                    if '-' in part and len(part) == 17:  # MAC format xx-xx-xx-xx-xx-xx
                                        return part.replace('-', ':')
                except Exception as e2:
                    print(f"[DEBUG] Method 2 failed: {e2}")
                
                # Method 3: Try with interface (original method)
                try:
                    arp_request = ARP(pdst=ip_address)
                    broadcast = Ether(dst="ff:ff:ff:ff:ff:ff")
                    arp_request_broadcast = broadcast / arp_request
                    
                    answered_list = srp(arp_request_broadcast, 
                                      timeout=timeout, 
                                      verbose=False, 
                                      iface=interface)[0]
                    
                    if answered_list:
                        return answered_list[0][1].hwsrc
                except Exception as e3:
                    print(f"[DEBUG] Method 3 failed: {e3}")
                
                return None
            else:
                # Unix/Linux: Use original method
                arp_request = ARP(pdst=ip_address)
                broadcast = Ether(dst="ff:ff:ff:ff:ff:ff")
                arp_request_broadcast = broadcast / arp_request
                
                answered_list = srp(arp_request_broadcast, 
                                  timeout=timeout, 
                                  verbose=False, 
                                  iface=interface)[0]
                
                if answered_list:
                    return answered_list[0][1].hwsrc
                else:
                    return None
        except Exception as e:
            print(f"Error getting MAC address for {ip_address}: {e}")
            return None
    
    @staticmethod
    def get_local_mac_address(interface=None):
        """Get MAC address of local interface"""
        try:
            if platform.system() == "Windows":
                # Method 1: Try netifaces if interface is provided
                if interface:
                    try:
                        addrs = netifaces.ifaddresses(interface)
                        if netifaces.AF_LINK in addrs:
                            return addrs[netifaces.AF_LINK][0]['addr']
                    except Exception as e1:
                        print(f"[DEBUG] netifaces method failed: {e1}")
                
                # Method 2: Use ipconfig /all and parse output
                try:
                    result = subprocess.run(['ipconfig', '/all'], 
                                          capture_output=True, text=True, timeout=10)
                    if result.returncode == 0:
                        lines = result.stdout.split('\n')
                        for i, line in enumerate(lines):
                            # Look for adapter sections
                            if 'adapter' in line.lower() and ':' in line:
                                # Look for Physical Address in the next few lines
                                for j in range(i+1, min(i+15, len(lines))):
                                    if 'physical address' in lines[j].lower():
                                        mac_line = lines[j]
                                        if ':' in mac_line:
                                            mac = mac_line.split(':')[-1].strip()
                                            if len(mac) == 17 and '-' in mac:  # Format: XX-XX-XX-XX-XX-XX
                                                return mac.replace('-', ':')
                except Exception as e2:
                    print(f"[DEBUG] ipconfig method failed: {e2}")
                
                # Method 3: Try to get from getmac command
                try:
                    result = subprocess.run(['getmac'], 
                                          capture_output=True, text=True, timeout=5)
                    if result.returncode == 0:
                        lines = result.stdout.strip().split('\n')
                        for line in lines[1:]:  # Skip header
                            parts = line.split()
                            if len(parts) >= 1:
                                mac = parts[0]
                                if len(mac) == 17 and '-' in mac:
                                    return mac.replace('-', ':')
                except Exception as e3:
                    print(f"[DEBUG] getmac method failed: {e3}")
            else:
                # Unix/Linux: try netifaces first, then fallback methods
                if interface:
                    try:
                        addrs = netifaces.ifaddresses(interface)
                        if netifaces.AF_LINK in addrs:
                            return addrs[netifaces.AF_LINK][0]['addr']
                    except Exception:
                        pass
            
            return None
        except Exception as e:
            print(f"Error getting local MAC address: {e}")
            return None

    @staticmethod
    def get_local_ip(interface=None):
        """Get local IP address of specified interface"""
        try:
            if interface:
                addrs = netifaces.ifaddresses(interface)
                if netifaces.AF_INET in addrs:
                    return addrs[netifaces.AF_INET][0]['addr']
            
            # Fallback: connect to external address to determine local IP
            s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
            s.connect(("8.8.8.8", 80))
            local_ip = s.getsockname()[0]
            s.close()
            return local_ip
        except Exception as e:
            print(f"Error getting local IP: {e}")
            return "127.0.0.1"
    
    @staticmethod
    def get_default_gateway():
        """Get default gateway IP address"""
        try:
            gws = netifaces.gateways()
            return gws['default'][netifaces.AF_INET][0]
        except Exception as e:
            print(f"Error getting default gateway: {e}")
            return None
    
    @staticmethod
    def ping_host(host, count=1, timeout=3):
        """Ping host to check connectivity"""
        try:
            system = platform.system().lower()
            if system == "windows":
                cmd = ["ping", "-n", str(count), "-w", str(timeout * 1000), host]
            else:
                cmd = ["ping", "-c", str(count), "-W", str(timeout), host]
            
            result = subprocess.run(cmd, capture_output=True, text=True, timeout=timeout + 2)
            return result.returncode == 0
        except Exception as e:
            print(f"Error pinging {host}: {e}")
            return False
    
    @staticmethod
    def scan_network_range(network_prefix, timeout=1):
        """Scan network range for active hosts"""
        active_hosts = []
        
        try:
            # Create network range (e.g., 192.168.1.1-254)
            base_ip = ".".join(network_prefix.split(".")[:-1])
            
            for i in range(1, 255):
                ip = f"{base_ip}.{i}"
                if NetworkUtils.ping_host(ip, count=1, timeout=timeout):
                    active_hosts.append(ip)
                    print(f"Found active host: {ip}")
        
        except Exception as e:
            print(f"Error scanning network: {e}")
        
        return active_hosts
    
    @staticmethod
    def get_youtube_servers():
        """Get common YouTube server IP ranges"""
        youtube_domains = [
            "youtube.com",
            "googlevideo.com", 
            "ytimg.com"
        ]
        
        youtube_ips = []
        
        for domain in youtube_domains:
            try:
                ip = socket.gethostbyname(domain)
                youtube_ips.append(ip)
            except Exception as e:
                print(f"Could not resolve {domain}: {e}")
        
        return youtube_ips
    
    @staticmethod
    def is_youtube_traffic(packet):
        """Check if packet is YouTube traffic with improved detection (including demo traffic)"""
        if not packet.haslayer(IP) or not packet.haslayer(TCP):
            return False
        
        ip_layer = packet[IP]
        tcp_layer = packet[TCP]
        
        # Check for demo server traffic (port 8080)
        is_demo_traffic = (tcp_layer.sport == 8080 or tcp_layer.dport == 8080)
        
        # Check for HTTPS traffic (port 443) which is primary for YouTube
        is_https = (tcp_layer.sport == 443 or tcp_layer.dport == 443)
        
        # Check for HTTP traffic (port 80) as fallback
        is_http = (tcp_layer.sport == 80 or tcp_layer.dport == 80)
        
        # For video streaming, we want larger packets (adjusted for demo)
        is_large_packet = len(packet) > 500  # Lowered threshold for demo
        
        # Check for data packets (PSH+ACK flags indicate data transfer)
        has_data_flags = (tcp_layer.flags & 0x18) == 0x18  # PSH+ACK
        
        # Demo traffic detection
        if is_demo_traffic and len(packet) > 200:
            # Check if it contains our demo video data pattern
            if tcp_layer.payload:
                try:
                    payload_str = str(tcp_layer.payload)
                    if 'FAKE_VIDEO_DATA_CHUNK' in payload_str:
                        return True
                except:
                    pass
            # Or if it's a large data packet
            if is_large_packet and has_data_flags:
                return True
        
        if (is_https or is_http) and is_large_packet and has_data_flags:
            # Enhanced YouTube IP range detection
            youtube_ranges = [
                "172.217.0.0/16",   # Google services
                "216.58.0.0/16",    # Google services  
                "74.125.0.0/16",    # Google services
                "64.233.0.0/16",    # Google services
                "142.250.0.0/15",   # Additional Google ranges (expanded)
                "173.194.0.0/16",   # Additional Google ranges
                "108.177.0.0/16",   # YouTube CDN ranges
                "74.125.0.0/16",    # YouTube CDN ranges
                "209.85.0.0/16"     # Additional YouTube ranges
            ]
            
            for ip_range in youtube_ranges:
                if NetworkUtils.ip_in_range(ip_layer.src, ip_range) or \
                   NetworkUtils.ip_in_range(ip_layer.dst, ip_range):
                    return True
            
            # Additional heuristic: check for video streaming patterns
            # Look for sustained data transfer with consistent packet sizes
            if is_https and len(packet) > 1400:  # Likely video chunks
                return True
        
        # Secondary check: HTTP traffic with video indicators
        if (is_http or is_demo_traffic) and tcp_layer.payload and len(packet) > 200:
            try:
                payload_str = str(tcp_layer.payload).lower()
                video_keywords = ['video', 'stream', 'youtube', 'googlevideo', 'ytimg', 'fake_video_data']
                if any(keyword in payload_str for keyword in video_keywords):
                    return True
            except:
                pass
        
        return False
    
    @staticmethod
    def ip_in_range(ip, cidr):
        """Check if IP is in CIDR range"""
        try:
            import ipaddress
            return ipaddress.ip_address(ip) in ipaddress.ip_network(cidr, strict=False)
        except:
            return False
    
    @staticmethod
    def calculate_tcp_checksum(packet):
        """Calculate TCP checksum"""
        if packet.haslayer(IP) and packet.haslayer(TCP):
            # Remove existing checksum
            del packet[TCP].chksum
            # Scapy will recalculate
            return packet
        return packet
    
    @staticmethod
    def create_raw_socket(protocol=socket.IPPROTO_TCP):
        """Create raw socket with proper permissions"""
        try:
            sock = socket.socket(socket.AF_INET, socket.SOCK_RAW, protocol)
            sock.setsockopt(socket.IPPROTO_IP, socket.IP_HDRINCL, 1)
            return sock
        except PermissionError:
            print("Error: Raw socket requires administrator/root privileges")
            return None
        except Exception as e:
            print(f"Error creating raw socket: {e}")
            return None
    
    @staticmethod
    def get_network_interfaces():
        """Get all available network interfaces"""
        interfaces = []
        try:
            for interface in netifaces.interfaces():
                if interface != 'lo':  # Skip loopback
                    addrs = netifaces.ifaddresses(interface)
                    if netifaces.AF_INET in addrs:
                        ip = addrs[netifaces.AF_INET][0]['addr']
                        interfaces.append({
                            'name': interface,
                            'ip': ip,
                            'status': 'active' if NetworkUtils.ping_host(ip) else 'inactive'
                        })
        except Exception as e:
            print(f"Error getting network interfaces: {e}")
        
        return interfaces

if __name__ == "__main__":
    # Test network utilities
    print("=== Network Utilities Test ===")
    
    # Test local IP detection
    local_ip = NetworkUtils.get_local_ip()
    print(f"Local IP: {local_ip}")
    
    # Test gateway detection
    gateway = NetworkUtils.get_default_gateway()
    print(f"Default Gateway: {gateway}")
    
    # Test interface enumeration
    interfaces = NetworkUtils.get_network_interfaces()
    print(f"Network Interfaces: {interfaces}")
    
    # Test YouTube server detection
    youtube_servers = NetworkUtils.get_youtube_servers()
    print(f"YouTube Servers: {youtube_servers}")
