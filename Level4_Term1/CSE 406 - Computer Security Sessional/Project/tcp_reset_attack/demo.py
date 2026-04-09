#!/usr/bin/env python3
"""
TCP Reset Attack - Safe Demo Mode
BUET CSE406 Computer Security Sessional
Educational Purpose Only

This script demonstrates the attack components without actually
performing any network attacks. Safe for testing and demonstration.
"""

import sys
import time
from pathlib import Path

# Add src directory to path
sys.path.append(str(Path(__file__).parent / "src"))

def demo_network_discovery():
    """Demonstrate network discovery without scanning"""
    print("=== Network Discovery Demo ===")
    
    try:
        from network_utils import NetworkUtils
        
        print("1. Local Network Information:")
        local_ip = NetworkUtils.get_local_ip()
        gateway = NetworkUtils.get_default_gateway()
        interfaces = NetworkUtils.get_network_interfaces()
        
        print(f"   Local IP: {local_ip}")
        print(f"   Gateway: {gateway}")
        print(f"   Interfaces: {len(interfaces)} found")
        
        for iface in interfaces[:3]:  # Show first 3 interfaces
            print(f"     - {iface['name']}: {iface['ip']} ({iface['status']})")
        
        print("\n2. YouTube Server Detection:")
        youtube_servers = NetworkUtils.get_youtube_servers()
        for server in youtube_servers[:3]:  # Show first 3 servers
            print(f"   - {server}")
        
        print("✓ Network discovery completed successfully")
        return True
        
    except Exception as e:
        print(f"✗ Network discovery failed: {e}")
        return False

def demo_configuration():
    """Demonstrate configuration management"""
    print("\n=== Configuration Demo ===")
    
    try:
        from config_manager import ConfigManager
        
        config = ConfigManager()
        
        print("Current configuration:")
        print(f"  Target IP: {config.get('NETWORK', 'TARGET_IP')}")
        print(f"  Gateway IP: {config.get('NETWORK', 'GATEWAY_IP')}")
        print(f"  Interface: {config.get('NETWORK', 'INTERFACE')}")
        print(f"  ARP Interval: {config.get_int('ATTACK', 'ARP_INTERVAL')}s")
        print(f"  Max RST Packets: {config.get_int('ATTACK', 'MAX_RST_PACKETS')}")
        print(f"  Safety Enabled: {config.get_boolean('SAFETY', 'ENABLE_SAFETY')}")
        
        print("✓ Configuration loaded successfully")
        return True
        
    except Exception as e:
        print(f"✗ Configuration demo failed: {e}")
        return False

def demo_packet_crafting():
    """Demonstrate packet crafting without sending"""
    print("\n=== Packet Crafting Demo ===")
    
    try:
        from scapy.layers.inet import IP, TCP
        from scapy.layers.l2 import ARP
        
        print("1. Creating sample TCP RST packet:")
        rst_packet = IP(src="192.168.1.1", dst="192.168.1.100") / \
                     TCP(sport=443, dport=54321, flags="R", seq=12345)
        
        print(f"   IP: {rst_packet[IP].src} -> {rst_packet[IP].dst}")
        print(f"   TCP: {rst_packet[TCP].sport} -> {rst_packet[TCP].dport}")
        print(f"   Flags: RST={rst_packet[TCP].flags}")
        print(f"   Sequence: {rst_packet[TCP].seq}")
        
        print("\n2. Creating sample ARP packet:")
        arp_packet = ARP(op=2, pdst="192.168.1.100", psrc="192.168.1.1")
        print(f"   Operation: {arp_packet.op} (ARP Reply)")
        print(f"   Target: {arp_packet.pdst}")
        print(f"   Source: {arp_packet.psrc}")
        
        print("✓ Packet crafting demonstration completed")
        return True
        
    except Exception as e:
        print(f"✗ Packet crafting demo failed: {e}")
        return False

def demo_attack_logic():
    """Demonstrate attack logic without execution"""
    print("\n=== Attack Logic Demo ===")
    
    try:
        print("1. Attack Flow:")
        print("   ┌─────────────────┐")
        print("   │ ARP Poisoning   │ ← Position as man-in-the-middle")
        print("   └─────────┬───────┘")
        print("             │")
        print("   ┌─────────▼───────┐")
        print("   │ Packet Monitor  │ ← Capture and analyze traffic")
        print("   └─────────┬───────┘")
        print("             │")
        print("   ┌─────────▼───────┐")
        print("   │ YouTube Traffic │ ← Detect video streaming")
        print("   │   Detection     │")
        print("   └─────────┬───────┘")
        print("             │")
        print("   ┌─────────▼───────┐")
        print("   │ RST Injection   │ ← Send forged reset packets")
        print("   └─────────────────┘")
        
        print("\n2. Success Conditions:")
        print("   ✓ Valid sequence number within receiver window")
        print("   ✓ Correct connection 4-tuple (src_ip, src_port, dst_ip, dst_port)")
        print("   ✓ Proper timing during active data transmission")
        print("   ✓ Man-in-the-middle network position")
        
        print("\n3. Expected Results:")
        print("   • Video playback interruption")
        print("   • Connection termination")
        print("   • User experience degradation")
        
        print("✓ Attack logic demonstration completed")
        return True
        
    except Exception as e:
        print(f"✗ Attack logic demo failed: {e}")
        return False

def main():
    """Run safe demonstration mode"""
    print("TCP Reset Attack - Safe Demo Mode")
    print("BUET CSE406 Computer Security Project")
    print("=" * 50)
    print("This demo shows attack components WITHOUT performing actual attacks")
    print("Safe for testing and educational demonstration")
    print("=" * 50)
    
    demos = [
        ("Network Discovery", demo_network_discovery),
        ("Configuration Management", demo_configuration),
        ("Packet Crafting", demo_packet_crafting),
        ("Attack Logic", demo_attack_logic)
    ]
    
    passed = 0
    total = len(demos)
    
    for demo_name, demo_func in demos:
        try:
            print(f"\n{'='*20} {demo_name} {'='*20}")
            if demo_func():
                passed += 1
                time.sleep(1)  # Pause between demos
            else:
                print(f"⚠ {demo_name} demo failed")
        except Exception as e:
            print(f"⚠ {demo_name} demo crashed: {e}")
    
    print("\n" + "=" * 70)
    print(f"Demo Results: {passed}/{total} demonstrations completed")
    
    if passed == total:
        print("✅ All demonstrations successful!")
        print("\nThis tool is ready for controlled testing in authorized environments.")
        print("\nIMPORTANT:")
        print("• Only use on networks you own or have permission to test")
        print("• This demo mode performs NO actual attacks")
        print("• Real attack mode requires explicit confirmation")
    else:
        print("❌ Some demonstrations failed.")
        print("Check error messages above and ensure all dependencies are installed.")
    
    print("\nFor actual attack execution:")
    print("python src/tcp_reset_attack.py")

if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        print("\n\nDemo interrupted by user")
    except Exception as e:
        print(f"\nDemo failed: {e}")
