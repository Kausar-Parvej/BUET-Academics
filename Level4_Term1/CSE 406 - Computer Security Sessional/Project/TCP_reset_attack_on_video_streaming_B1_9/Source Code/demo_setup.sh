#!/usr/bin/env bash
# TCP Reset Attack Demo Script
# Complete demonstration setup for WSL2

echo "========================================"
echo "TCP Reset Attack Demo Setup"
echo "BUET CSE406 Computer Security Project"
echo "========================================"

# Check if running as root
if [ "$EUID" -ne 0 ]; then
    echo "Please run as root: sudo bash demo_setup.sh"
    exit 1
fi

# Create logs directory
mkdir -p logs

echo "Starting demo in 3 terminals..."
echo ""
echo "Terminal 1: Demo Server (port 8080)"
echo "Terminal 2: Demo Client (download video)"  
echo "Terminal 3: TCP Reset Attack"
echo ""

# Function to run server
run_server() {
    echo "[SERVER] Starting demo video server..."
    cd /home/kausar/CSE-406/tcp_reset_attack
    source .venv/bin/activate
    python demo_server.py
}

# Function to run attack
run_attack() {
    echo "[ATTACK] Starting TCP Reset Attack..."
    sleep 5  # Give server time to start
    cd /home/kausar/CSE-406/tcp_reset_attack
    source .venv/bin/activate
    python src/tcp_reset_attack.py --config config/demo_config.ini --target 127.0.0.1
}

# Function to run client
run_client() {
    echo "[CLIENT] Starting demo client..."
    sleep 10  # Give server and attack time to start
    cd /home/kausar/CSE-406/tcp_reset_attack
    source .venv/bin/activate
    python demo_client.py
}

echo "Choose demo mode:"
echo "1. Full automatic demo (recommended)"
echo "2. Manual terminal setup"
echo "3. Simple test mode"

read -p "Enter choice (1-3): " choice

case $choice in
    1)
        echo ""
        echo "Starting automatic demo..."
        echo "This will show the attack in action automatically"
        echo ""
        
        # Start server in background
        (run_server) &
        SERVER_PID=$!
        
        # Wait for server to start
        sleep 3
        
        # Start attack in background  
        (run_attack) &
        ATTACK_PID=$!
        
        # Wait for attack to start
        sleep 5
        
        # Start client download
        echo "Starting client download - this should be interrupted by the attack..."
        (run_client) &
        CLIENT_PID=$!
        
        # Wait for demo to run
        sleep 30
        
        # Cleanup
        echo ""
        echo "Demo completed. Cleaning up..."
        kill $SERVER_PID $ATTACK_PID $CLIENT_PID 2>/dev/null
        ;;
        
    2)
        echo ""
        echo "Manual setup instructions:"
        echo ""
        echo "Terminal 1 - Start server:"
        echo "  cd /home/kausar/CSE-406/tcp_reset_attack"
        echo "  source .venv/bin/activate"
        echo "  python demo_server.py"
        echo ""
        echo "Terminal 2 - Start attack:"
        echo "  cd /home/kausar/CSE-406/tcp_reset_attack"
        echo "  source .venv/bin/activate"
        echo "  sudo python src/tcp_reset_attack.py --config config/demo_config.ini --target 127.0.0.1"
        echo ""
        echo "Terminal 3 - Start client:"
        echo "  cd /home/kausar/CSE-406/tcp_reset_attack"
        echo "  source .venv/bin/activate"
        echo "  python demo_client.py"
        echo ""
        ;;
        
    3)
        echo ""
        echo "Running simple test..."
        cd /home/kausar/CSE-406/tcp_reset_attack
        source .venv/bin/activate
        
        # Test network utilities
        echo "Testing network utilities..."
        python src/network_utils.py
        
        # Test configuration
        echo ""
        echo "Testing configuration..."
        python src/config_manager.py config/demo_config.ini
        
        echo ""
        echo "Test completed!"
        ;;
        
    *)
        echo "Invalid choice"
        exit 1
        ;;
esac

echo ""
echo "Demo script finished!"
