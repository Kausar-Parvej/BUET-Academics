"""
TCP Reset Attack Tool
BUET CSE406 Computer Security Sessional
Educational Purpose Only

This package contains the implementation of a TCP Reset Attack
for educational and authorized security testing purposes only.
"""

__version__ = "1.0.0"
__author__ = "BUET CSE406 Security Project"
__description__ = "TCP Reset Attack on Video Streaming - Educational Tool"

# Import main components for easier access
try:
    from .tcp_reset_attack import TCPResetAttack
    from .config_manager import ConfigManager
    from .network_utils import NetworkUtils
    from .arp_poisoner import ARPPoisoner
    from .packet_monitor import PacketMonitor
except ImportError:
    # Imports will fail if dependencies aren't installed yet
    pass
