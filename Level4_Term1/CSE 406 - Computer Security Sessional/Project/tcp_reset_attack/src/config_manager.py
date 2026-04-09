#!/usr/bin/env python3
"""
Configuration Manager for TCP Reset Attack
BUET CSE406 Computer Security Sessional
Educational Purpose Only
"""

import configparser
import os
import sys
import netifaces
import socket
from pathlib import Path

class ConfigManager:
    def __init__(self, config_file=None):
        self.config = configparser.ConfigParser()
        
        if config_file is None:
            config_file = Path(__file__).parent.parent / "config" / "attack_config.ini"
        
        if not os.path.exists(config_file):
            raise FileNotFoundError(f"Configuration file not found: {config_file}")
        
        self.config.read(config_file)
        self._validate_config()
    
    def _validate_config(self):
        """Validate and auto-detect configuration parameters"""
        # Auto-detect network interface
        if self.get('NETWORK', 'INTERFACE') == 'auto':
            self.config.set('NETWORK', 'INTERFACE', self._get_default_interface())
        
        # Validate IP addresses
        target_ip = self.get('NETWORK', 'TARGET_IP')
        gateway_ip = self.get('NETWORK', 'GATEWAY_IP')
        
        if not self._is_valid_ip(target_ip):
            raise ValueError(f"Invalid target IP address: {target_ip}")
        
        if not self._is_valid_ip(gateway_ip):
            raise ValueError(f"Invalid gateway IP address: {gateway_ip}")
        
        # Safety checks
        if self.get_boolean('SAFETY', 'RESTRICT_TO_LOCAL'):
            if not self._is_local_ip(target_ip):
                raise ValueError(f"Target IP {target_ip} is not in local network range")
    
    def _get_default_interface(self):
        """Get the default network interface"""
        try:
            # Method 1: Try netifaces for default gateway interface
            gws = netifaces.gateways()
            default_gw = gws['default'][netifaces.AF_INET]
            return default_gw[1]
        except Exception:
            try:
                # Method 2: Get first active interface with IP
                interfaces = netifaces.interfaces()
                for iface in interfaces:
                    if iface.lower() in ['lo', 'loopback']:
                        continue
                    try:
                        addrs = netifaces.ifaddresses(iface)
                        if netifaces.AF_INET in addrs:
                            ip = addrs[netifaces.AF_INET][0]['addr']
                            if not ip.startswith('127.'):  # Skip loopback
                                return iface
                    except:
                        continue
            except Exception:
                pass
            
            # Method 3: Platform-specific fallbacks
            import platform
            system = platform.system().lower()
            if system == "windows":
                return "Wi-Fi"  # Common Windows interface name
            elif system == "darwin":  # macOS
                return "en0"
            else:  # Linux and others
                return "eth0"
    
    def _is_valid_ip(self, ip):
        """Validate IP address format"""
        try:
            socket.inet_aton(ip)
            return True
        except socket.error:
            return False
    
    def _is_local_ip(self, ip):
        """Check if IP is in local network ranges"""
        local_ranges = [
            ('192.168.0.0', '192.168.255.255'),
            ('10.0.0.0', '10.255.255.255'),
            ('172.16.0.0', '172.31.255.255'),
            ('127.0.0.0', '127.255.255.255')
        ]
        
        ip_int = int(socket.inet_aton(ip).hex(), 16)
        
        for start, end in local_ranges:
            start_int = int(socket.inet_aton(start).hex(), 16)
            end_int = int(socket.inet_aton(end).hex(), 16)
            if start_int <= ip_int <= end_int:
                return True
        return False
    
    def get(self, section, key, fallback=None):
        """Get configuration value"""
        return self.config.get(section, key, fallback=fallback)
    
    def get_int(self, section, key, fallback=0):
        """Get integer configuration value"""
        return self.config.getint(section, key, fallback=fallback)
    
    def get_float(self, section, key, fallback=0.0):
        """Get float configuration value"""
        return self.config.getfloat(section, key, fallback=fallback)
    
    def get_boolean(self, section, key, fallback=False):
        """Get boolean configuration value"""
        return self.config.getboolean(section, key, fallback=fallback)
    
    def get_list(self, section, key, delimiter=',', fallback=None):
        """Get list configuration value"""
        value = self.get(section, key, fallback='')
        if not value and fallback:
            return fallback
        return [item.strip() for item in value.split(delimiter) if item.strip()]
    
    def print_config(self):
        """Print current configuration"""
        print("\n=== TCP Reset Attack Configuration ===")
        for section in self.config.sections():
            print(f"\n[{section}]")
            for key, value in self.config.items(section):
                # Mask sensitive values
                if 'password' in key.lower() or 'key' in key.lower():
                    value = '*' * len(value)
                print(f"{key} = {value}")
        print("=" * 40)

if __name__ == "__main__":
    # Test configuration manager
    try:
        config = ConfigManager()
        config.print_config()
    except Exception as e:
        print(f"Configuration error: {e}")
        sys.exit(1)
