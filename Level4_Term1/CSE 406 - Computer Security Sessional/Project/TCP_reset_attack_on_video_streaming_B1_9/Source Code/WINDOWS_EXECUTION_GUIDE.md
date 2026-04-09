# TCP Reset Attack - Windows Execution Guide

## Problem: WSL2 Network Isolation

WSL2 runs in a virtualized environment that cannot directly access Windows network interfaces. This prevents direct execution of the TCP reset attack against devices on your Windows hotspot network.

## Solution Options

### Option 1: Run on Windows Directly (Recommended)

1. **Install Python on Windows**:
   - Download Python 3.8+ from python.org
   - During installation, check "Add Python to PATH"

2. **Install Npcap** (required for Scapy on Windows):
   - Download from https://npcap.com/
   - Install with WinPcap compatibility mode enabled

3. **Install Python packages**:
   ```cmd
   pip install scapy netifaces colorama psutil
   ```

4. **Copy project to Windows**:
   - Copy the entire tcp_reset_attack folder to Windows
   - Or access via WSL path: `\\wsl$\Ubuntu\home\kausar\CSE-406\tcp_reset_attack`

5. **Run as Administrator**:
   ```cmd
   cd C:\path\to\tcp_reset_attack
   python src\tcp_reset_attack.py --target 192.168.137.44 --gateway 192.168.137.1
   ```

### Option 2: WSL1 (Alternative)

WSL1 provides direct network access:

1. **Convert to WSL1**:
   ```powershell
   wsl --set-version Ubuntu 1
   ```

2. **Restart WSL and test**:
   ```bash
   ping 192.168.137.44
   ```

3. **If successful, run attack**:
   ```bash
   sudo python3 src/tcp_reset_attack.py --target 192.168.137.44 --gateway 192.168.137.1
   ```

### Option 3: Bridge Networking (Advanced)

Set up bridge networking in WSL2:

1. **Windows PowerShell (as Administrator)**:
   ```powershell
   # Create Hyper-V external switch
   New-VMSwitch -Name "WSLBridge" -NetAdapterName "Wi-Fi" -AllowManagementOS $true
   
   # Restart WSL
   wsl --shutdown
   ```

2. **Configure WSL networking**:
   Edit `.wslconfig` in `%USERPROFILE%`:
   ```ini
   [wsl2]
   networkingMode=bridged
   vmSwitch=WSLBridge
   ```

3. **Restart WSL and test connectivity**

## Current Status & Next Steps

Given the WSL2 limitations, I recommend:

1. **Immediate testing**: Use the test mode to verify attack logic works
2. **Production attack**: Run directly on Windows with Npcap
3. **Alternative**: Switch to WSL1 for this project

## Test the Fixed Code Logic

Even though we can't reach the target network from WSL2, we can test the attack logic using local traffic. The code fixes I implemented include:

- ✅ Corrected RST sequence number calculation
- ✅ Improved YouTube traffic detection  
- ✅ Enhanced packet filtering
- ✅ Better connection tracking
- ✅ Debugging output for troubleshooting

## Verification Commands

To verify the fixes are working:

```bash
# Test basic functionality
sudo python3 preflight_check.py

# Test network utilities
sudo python3 src/network_utils.py

# Test individual components
sudo python3 src/arp_poisoner.py
sudo python3 src/packet_monitor.py
```

## Expected Results on Windows

When run on Windows with proper network access:

1. ARP poisoning should start without "Interface not found" errors
2. YouTube traffic detection should identify video streams
3. RST packets should be injected with correct sequence numbers
4. YouTube playback on phone should be disrupted
5. Attack should auto-terminate after specified duration

The code is now ready for execution once network access is available!
