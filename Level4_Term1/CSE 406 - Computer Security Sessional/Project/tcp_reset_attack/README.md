# TCP Reset Attack on Video Streaming

**BUET CSE406 Computer Security Sessional Project**

⚠️ **EDUCATIONAL PURPOSE ONLY** - This tool is designed for educational use and authorized security testing only.

## Project Overview

This project implements a TCP Reset Attack targeting video streaming connections (specifically YouTube) to demonstrate network security vulnerabilities and attack vectors. The implementation follows the design specifications from the academic research paper.

## Attack Methodology

### 1. **Man-in-the-Middle Setup**
- **ARP Poisoning**: Intercepts traffic between victim and gateway
- **Traffic Monitoring**: Captures and analyzes TCP packets
- **Connection Tracking**: Maintains state of active video streaming connections

### 2. **Attack Execution**
- **Packet Analysis**: Identifies YouTube video streaming traffic (HTTPS on port 443)
- **Sequence Number Extraction**: Captures current TCP sequence numbers
- **RST Injection**: Sends forged TCP Reset packets to both client and server
- **Connection Termination**: Successfully disrupts video streaming sessions

### 3. **Technical Implementation**
- **Python + Scapy**: Professional packet manipulation and injection
- **Multi-threaded Architecture**: Concurrent ARP poisoning and packet monitoring
- **Real-time Analysis**: Live traffic inspection and attack decision making

## Project Structure

```
tcp_reset_attack/
├── src/                          # Core attack modules
│   ├── tcp_reset_attack.py       # Main attack controller
│   ├── arp_poisoner.py          # ARP spoofing implementation
│   ├── packet_monitor.py        # Packet capture and RST injection
│   ├── network_utils.py         # Network utilities and helpers
│   └── config_manager.py        # Configuration management
├── config/                       # Configuration files
│   └── attack_config.ini        # Main configuration
├── scripts/                      # Utility scripts
│   └── network_discovery.py     # Network reconnaissance
├── logs/                        # Attack logs and outputs
├── requirements.txt             # Python dependencies
├── setup.py                     # Setup and installation script
└── README.md                    # This file
```

## Installation and Setup

### Prerequisites
- **Python 3.7+** (Required for modern packet handling)
- **Administrator/Root privileges** (Required for raw sockets)
- **Network access** to target environment
- **Windows/Linux/macOS** (Cross-platform compatibility)

### Step 1: Environment Setup
```bash
# Clone or extract the project
cd tcp_reset_attack

# Run preflight checks (recommended first step)
python preflight_check.py

# Run the setup script
python setup.py
```

The preflight check will:
- 🔍 **System Validation**: Python version, privileges, network interfaces
- 📦 **Dependency Check**: Verify all required packages are available
- 🛡️ **Security Assessment**: Firewall and permission warnings
- 🔧 **Functionality Test**: Scapy packet creation and network access
- 📁 **Project Integrity**: Ensure all required files are present

The setup script will:
- ✅ Check Python version compatibility
- ✅ Verify administrator privileges  
- ✅ Install required Python packages
- ✅ Test Scapy functionality
- ✅ Check network interfaces
- ✅ Display security warnings

### Step 2: Network Discovery
```bash
# Discover network topology and targets
python scripts/network_discovery.py

# Quick discovery (skip network scanning)
python scripts/network_discovery.py --quick

# Scan specific network
python scripts/network_discovery.py --network 192.168.1
```

### Step 3: Configuration
Edit `config/attack_config.ini` with your network settings:

```ini
[NETWORK]
TARGET_IP = 192.168.1.100      # Victim's IP address
GATEWAY_IP = 192.168.1.1       # Router/Gateway IP
INTERFACE = eth0               # Network interface to use

[ATTACK]
ARP_INTERVAL = 2               # ARP poisoning frequency
MAX_RST_PACKETS = 3            # RST packets per connection
MONITOR_DURATION = 0           # 0 = infinite, >0 = minutes

[SAFETY]
ENABLE_SAFETY = true           # Safety checks enabled
RESTRICT_TO_LOCAL = true       # Only attack local networks
MAX_DURATION = 30              # Maximum attack duration (minutes)
```

## Usage Instructions

### Interactive Mode (Recommended)
```bash
python src/tcp_reset_attack.py
```

This mode provides:
- 🔍 **Configuration validation** and network checks
- ⚡ **Interactive prompts** for safety confirmation
- 📊 **Real-time status** and attack statistics
- 🛡️ **Graceful shutdown** with ARP table restoration

### Command Line Mode
```bash
# Basic usage
python src/tcp_reset_attack.py --target 192.168.1.100 --gateway 192.168.1.1

# With custom configuration
python src/tcp_reset_attack.py --config config/custom.ini

# Time-limited attack
python src/tcp_reset_attack.py --target 192.168.1.100 --duration 10

# Advanced usage (disable safety - NOT RECOMMENDED)
python src/tcp_reset_attack.py --target 192.168.1.100 --no-safety
```

### Attack Process
1. **Pre-Attack Validation**
   - ✅ Network connectivity tests
   - ✅ Interface availability check
   - ✅ Privilege verification
   - ✅ Safety confirmations

2. **Attack Execution**
   - 🔄 **ARP Poisoning**: Starts man-in-the-middle position
   - 👀 **Traffic Monitoring**: Captures and analyzes packets
   - 🎯 **Target Identification**: Detects YouTube streaming traffic
   - ⚡ **RST Injection**: Sends forged reset packets
   - 📊 **Status Reporting**: Real-time attack statistics

3. **Post-Attack Cleanup**
   - 🔄 **ARP Restoration**: Restores legitimate ARP entries
   - 📋 **Statistics Report**: Attack success metrics
   - 🧹 **Resource Cleanup**: Stops all attack components

## Attack Demonstration Scenario

### Setup
1. **Victim Machine**: Connected to local network, watching YouTube videos
2. **Attacker Machine**: Running this tool on same network segment
3. **Network Environment**: Standard home/lab network with router

### Expected Results
- ✅ **ARP Poisoning Success**: Tool positions itself as man-in-the-middle
- ✅ **Traffic Interception**: Captures YouTube HTTPS traffic on port 443
- ✅ **Connection Identification**: Detects active video streaming sessions
- ✅ **RST Injection**: Successfully sends forged TCP Reset packets
- ✅ **Video Disruption**: YouTube playback stops or buffers indefinitely
- ✅ **Clean Restoration**: Network returns to normal after attack stops

### Attack Output Example
```
╔══════════════════════════════════════════════════════════════════════════════╗
║                           TCP Reset Attack Tool                              ║
║                        BUET CSE406 Security Project                         ║
╚══════════════════════════════════════════════════════════════════════════════╝

[MAIN] Validating environment...
✓ Running with administrator privileges
✓ Network connectivity verified
[MAIN] Environment validation passed

[ARP] Discovering MAC addresses...
[ARP] Target 192.168.1.100 -> aa:bb:cc:dd:ee:ff
[ARP] Gateway 192.168.1.1 -> 11:22:33:44:55:66
[ARP] Starting ARP poisoning (interval: 2s)

[MONITOR] Starting packet capture on eth0
[MONITOR] YouTube packet: 172.217.164.142:443 -> 192.168.1.100:54321 (seq=12345, size=1500)
[RST] Injected RST to client: 192.168.1.100:54321
[RST] Injected RST to server: 172.217.164.142:443

[STATS] Packets: 1000, YouTube: 45, RST Injections: 90, Success Rate: 95.6%
```

## Technical Details

### Network Traffic Analysis
- **Port Detection**: Monitors TCP port 443 (HTTPS) for video traffic
- **Packet Size Filtering**: Targets large packets (>1400 bytes) indicating video data
- **YouTube IP Detection**: Identifies Google/YouTube IP address ranges
- **Connection State Tracking**: Maintains TCP sequence numbers for accurate RST injection

### RST Packet Crafting
```python
# Forged RST packet structure
rst_packet = IP(
    src=server_ip,           # Spoofed server address
    dst=client_ip,           # Target client
    ttl=64                   # Standard TTL
) / TCP(
    sport=443,               # HTTPS port
    dport=client_port,       # Client's ephemeral port
    flags="R",               # RST flag set
    seq=next_expected_seq,   # Critical: correct sequence number
    ack=0                    # RST packets don't acknowledge
)
```

### Success Factors
1. **Correct Sequence Number**: Must be within receiver's acceptable window
2. **Accurate 4-tuple**: (src_ip, src_port, dst_ip, dst_port) must match exactly
3. **Timing**: Injection must occur during active data transmission
4. **Network Position**: Man-in-the-middle position required for interception

## Safety Features

### Built-in Protections
- 🛡️ **Local Network Restriction**: Only attacks RFC 1918 private addresses
- ⏱️ **Time Limits**: Automatic shutdown after configurable duration
- 🔒 **Privilege Checks**: Ensures proper permissions before execution
- ✋ **Interactive Confirmation**: Requires explicit user consent
- 🔄 **Graceful Cleanup**: Always restores network state on exit

### Legal and Ethical Safeguards
- 📋 **Terms Acceptance**: Explicit legal disclaimer and acknowledgment
- 🎓 **Educational Purpose**: Clearly marked for educational use only
- 🏠 **Authorized Use Only**: Strong warnings against unauthorized deployment
- 📖 **Documentation**: Comprehensive guidance on proper usage

## Troubleshooting

### Common Issues

#### 1. Permission Errors
```
Error: Raw socket requires administrator/root privileges
```
**Solution**: Run with elevated privileges
- Windows: "Run as Administrator"
- Linux/macOS: `sudo python src/tcp_reset_attack.py`

#### 2. Scapy Import Errors
```
ImportError: No module named 'scapy'
```
**Solution**: Install requirements
```bash
pip install -r requirements.txt
```

#### 3. Network Interface Issues
```
Error: Network interface 'eth0' not found
```
**Solution**: Check available interfaces
```bash
python scripts/network_discovery.py --quick
```

#### 4. ARP Discovery Failures
```
Could not discover MAC address for target
```
**Solutions**:
- Verify target IP is reachable: `ping 192.168.1.100`
- Check network interface is active
- Ensure target is on same network segment

#### 5. No YouTube Traffic Detected
```
[STATS] Packets: 1000, YouTube: 0
```
**Solutions**:
- Start video playback on target device
- Verify target is using YouTube (not cached content)
- Check firewall isn't blocking traffic analysis

### Debug Mode
Enable detailed logging for troubleshooting:
```ini
[LOGGING]
LOG_LEVEL = DEBUG
CAPTURE_PACKETS = true
```

## Project Deliverables

### 1. **Source Code** ✅
- Complete Python implementation with professional architecture
- Modular design with separated concerns
- Comprehensive error handling and logging
- Cross-platform compatibility

### 2. **Documentation** ✅
- Detailed README with usage instructions
- Code comments and docstrings
- Configuration examples
- Troubleshooting guide

### 3. **Research Report** ✅
- LaTeX-formatted academic paper (`design_report_fixed.tex`)
- Attack methodology and implementation details
- Network diagrams and timing sequences
- Security analysis and countermeasures

### 4. **Demonstration** ✅
- Working proof-of-concept implementation
- Network discovery and reconnaissance tools
- Real-time attack monitoring and statistics
- Clean network restoration capabilities

## Educational Outcomes

### Learning Objectives Met
1. **Network Security Understanding**: Deep dive into TCP/IP vulnerabilities
2. **Attack Implementation**: Hands-on experience with security testing tools
3. **Packet Manipulation**: Advanced networking with Scapy and raw sockets
4. **Ethical Hacking**: Responsible disclosure and authorized testing practices
5. **System Programming**: Multi-threaded Python application development

### Skills Developed
- 🔧 **Python Programming**: Advanced networking and concurrency
- 🌐 **Network Analysis**: Packet capture and protocol analysis
- 🛡️ **Security Testing**: Vulnerability assessment methodologies
- 📊 **Data Analysis**: Real-time monitoring and statistics
- 📝 **Technical Writing**: Academic research documentation

## Conclusion

This TCP Reset Attack implementation successfully demonstrates the vulnerability of TCP connections to sequence number attacks when an attacker has man-in-the-middle capabilities. The project showcases both the technical execution of the attack and the importance of network security measures.

The educational value lies in understanding how fundamental internet protocols can be exploited and what defensive measures are necessary to protect against such attacks in production environments.

---

**BUET CSE406 Computer Security Sessional**  
**Educational Project - January 2025**

⚠️ **Remember**: Always use responsibly and only on networks you own or have explicit permission to test!
