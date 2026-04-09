#!/usr/bin/env python3
"""
Logging Configuration for TCP Reset Attack
BUET CSE406 Computer Security Sessional
Educational Purpose Only
"""

import logging
import os
from datetime import datetime
from pathlib import Path

class AttackLogger:
    """Centralized logging for attack components"""
    
    def __init__(self, config_manager=None, log_level="INFO"):
        self.config = config_manager
        self.log_level = getattr(logging, log_level.upper(), logging.INFO)
        
        # Create logs directory if it doesn't exist
        log_dir = Path(__file__).parent.parent / "logs"
        log_dir.mkdir(exist_ok=True)
        
        # Setup main logger
        self.logger = logging.getLogger("tcp_reset_attack")
        self.logger.setLevel(self.log_level)
        
        # Prevent duplicate handlers
        if not self.logger.handlers:
            self._setup_handlers(log_dir)
    
    def _setup_handlers(self, log_dir):
        """Setup file and console handlers"""
        # File handler with timestamp
        timestamp = datetime.now().strftime("%Y%m%d_%H%M%S")
        log_file = log_dir / f"attack_{timestamp}.log"
        
        file_handler = logging.FileHandler(log_file)
        file_handler.setLevel(self.log_level)
        
        # Console handler
        console_handler = logging.StreamHandler()
        console_handler.setLevel(self.log_level)
        
        # Formatter
        formatter = logging.Formatter(
            '%(asctime)s - %(name)s - %(levelname)s - %(message)s'
        )
        
        file_handler.setFormatter(formatter)
        console_handler.setFormatter(formatter)
        
        self.logger.addHandler(file_handler)
        self.logger.addHandler(console_handler)
        
        self.logger.info(f"Logging initialized - Level: {logging.getLevelName(self.log_level)}")
        self.logger.info(f"Log file: {log_file}")
    
    def get_logger(self, component_name=None):
        """Get logger for specific component"""
        if component_name:
            return logging.getLogger(f"tcp_reset_attack.{component_name}")
        return self.logger
    
    def log_attack_start(self, config):
        """Log attack start with configuration"""
        self.logger.info("=" * 60)
        self.logger.info("TCP RESET ATTACK STARTED")
        self.logger.info("=" * 60)
        self.logger.info(f"Target IP: {config.get('NETWORK', 'TARGET_IP')}")
        self.logger.info(f"Gateway IP: {config.get('NETWORK', 'GATEWAY_IP')}")
        self.logger.info(f"Interface: {config.get('NETWORK', 'INTERFACE')}")
        self.logger.info(f"ARP Interval: {config.get('ATTACK', 'ARP_INTERVAL')}s")
        self.logger.info(f"Max RST Packets: {config.get('ATTACK', 'MAX_RST_PACKETS')}")
        self.logger.info("=" * 60)
    
    def log_attack_stop(self, duration, stats=None):
        """Log attack stop with statistics"""
        self.logger.info("=" * 60)
        self.logger.info("TCP RESET ATTACK STOPPED")
        self.logger.info("=" * 60)
        self.logger.info(f"Duration: {duration}")
        
        if stats:
            self.logger.info(f"Total Injections: {stats.get('total_injections', 0)}")
            self.logger.info(f"Successful Injections: {stats.get('successful_injections', 0)}")
            self.logger.info(f"Success Rate: {stats.get('injection_rate', 0):.1f}%")
            self.logger.info(f"Connections Attacked: {stats.get('connections_attacked', 0)}")
        
        self.logger.info("=" * 60)
    
    def log_packet_injection(self, src_ip, src_port, dst_ip, dst_port, seq_num):
        """Log RST packet injection"""
        self.logger.debug(f"RST Injection: {src_ip}:{src_port} -> {dst_ip}:{dst_port} (seq={seq_num})")
    
    def log_youtube_detection(self, src_ip, src_port, dst_ip, dst_port, packet_size):
        """Log YouTube traffic detection"""
        self.logger.debug(f"YouTube Traffic: {src_ip}:{src_port} -> {dst_ip}:{dst_port} (size={packet_size})")
    
    def log_arp_poisoning(self, target_ip, gateway_ip, status):
        """Log ARP poisoning events"""
        self.logger.info(f"ARP Poisoning {status}: Target={target_ip}, Gateway={gateway_ip}")
    
    def log_error(self, component, error_msg):
        """Log error with component context"""
        self.logger.error(f"[{component}] {error_msg}")
    
    def log_warning(self, component, warning_msg):
        """Log warning with component context"""
        self.logger.warning(f"[{component}] {warning_msg}")

# Global logger instance
_attack_logger = None

def get_attack_logger(config_manager=None, log_level="INFO"):
    """Get global attack logger instance"""
    global _attack_logger
    if _attack_logger is None:
        _attack_logger = AttackLogger(config_manager, log_level)
    return _attack_logger

def setup_component_logger(component_name, config_manager=None):
    """Setup logger for specific component"""
    attack_logger = get_attack_logger(config_manager)
    return attack_logger.get_logger(component_name)
