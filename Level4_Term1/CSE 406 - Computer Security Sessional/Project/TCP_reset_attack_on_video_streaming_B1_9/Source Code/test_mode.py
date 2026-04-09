#!/usr/bin/env python3
"""
TCP Reset Attack - Test Mode
For testing the attack logic without external network access
"""

import sys
import os
import time
import threading
import subprocess
from pathlib import Path

# Add src directory to Python path
src_path = str(Path(__file__).parent / "src")
if src_path not in sys.path:
    sys.path.insert(0, src_path)

from tcp_reset_attack import TCPResetAttack

def setup_test_environment():
    """Set up a local test environment"""
    print("=== Setting up Test Environment ===")
    
    # Start a simple HTTP server for testing
    print("Starting test HTTP server on port 8080...")
    server_process = subprocess.Popen([
        'python3', '-m', 'http.server', '8080'
    ], stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    
    time.sleep(2)
    
    # Test if server is running
    try:
        import urllib.request
        response = urllib.request.urlopen('http://127.0.0.1:8080', timeout=3)
        print("✅ Test server running successfully")
        return server_process
    except Exception as e:
        print(f"❌ Test server failed: {e}")
        server_process.terminate()
        return None

def create_test_traffic():
    """Generate test traffic that mimics video streaming"""
    print("Generating test traffic...")
    
    def traffic_generator():
        import urllib.request
        for i in range(10):
            try:
                urllib.request.urlopen('http://127.0.0.1:8080', timeout=3)
                time.sleep(1)
            except:
                pass
    
    thread = threading.Thread(target=traffic_generator, daemon=True)
    thread.start()
    return thread

def run_test_attack():
    """Run the attack in test mode"""
    print("\n=== Running Test Attack ===")
    
    # Modify config for local testing
    config_path = Path(__file__).parent / "config" / "test_config.ini"
    
    # Create test configuration
    test_config = """[NETWORK]
TARGET_IP = 127.0.0.1
GATEWAY_IP = 127.0.0.1
SERVER_IP = auto
INTERFACE = lo

[ATTACK]
ARP_INTERVAL = 2
RST_DELAY = 50
MAX_RST_PACKETS = 3
MONITOR_DURATION = 0

[DETECTION]
VIDEO_PORTS = 8080,80,443
MIN_VIDEO_PACKET_SIZE = 100
CONNECTION_TIMEOUT = 300

[LOGGING]
LOG_LEVEL = DEBUG
LOG_FILE = logs/test_attack.log
CAPTURE_PACKETS = true

[SAFETY]
ENABLE_SAFETY = false
RESTRICT_TO_LOCAL = true
MAX_DURATION = 1
"""
    
    with open(config_path, 'w') as f:
        f.write(test_config)
    
    try:
        # Initialize attack with test config
        attack = TCPResetAttack(str(config_path))
        
        # Override safety checks for testing
        attack.config.config.set('SAFETY', 'ENABLE_SAFETY', 'false')
        
        print("Starting test attack for 30 seconds...")
        
        if attack.setup_attack_components():
            if attack.start_attack():
                time.sleep(30)  # Run for 30 seconds
                attack.stop_attack()
                
                # Show results
                status = attack.get_attack_status()
                print(f"\nTest Results: {status}")
            else:
                print("Failed to start attack")
        else:
            print("Failed to setup attack components")
    
    except Exception as e:
        print(f"Test attack failed: {e}")
        import traceback
        traceback.print_exc()

def main():
    """Main test function"""
    if os.geteuid() != 0:
        print("Test mode requires root privileges for packet capture")
        print("Run: sudo python3 test_mode.py")
        sys.exit(1)
    
    # Setup test environment
    server = setup_test_environment()
    if not server:
        print("Failed to setup test environment")
        return
    
    try:
        # Create background traffic
        traffic_thread = create_test_traffic()
        
        # Run test attack
        run_test_attack()
        
    finally:
        # Cleanup
        if server:
            server.terminate()
        print("\nTest completed")

if __name__ == "__main__":
    main()
