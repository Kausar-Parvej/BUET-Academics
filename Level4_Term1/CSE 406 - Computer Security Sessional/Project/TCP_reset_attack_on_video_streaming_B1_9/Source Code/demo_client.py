#!/usr/bin/env python3
"""
Demo Client for TCP Reset Attack
Downloads content from the demo server to simulate video streaming
"""

import requests
import threading
import time
import sys

class DemoClient:
    """Simulates a client downloading video content"""
    
    def __init__(self, server_url="http://127.0.0.1:8080"):
        self.server_url = server_url
        self.downloading = False
        self.bytes_downloaded = 0
        self.download_thread = None
    
    def start_download(self):
        """Start downloading the video stream"""
        if self.downloading:
            print("[CLIENT] Download already in progress")
            return
        
        print(f"[CLIENT] Starting download from {self.server_url}/video")
        self.downloading = True
        self.bytes_downloaded = 0
        
        self.download_thread = threading.Thread(target=self._download_loop, daemon=True)
        self.download_thread.start()
    
    def _download_loop(self):
        """Main download loop"""
        try:
            response = requests.get(f"{self.server_url}/video", stream=True, timeout=30)
            
            if response.status_code == 200:
                print("[CLIENT] Connected to server, starting download...")
                
                for chunk in response.iter_content(chunk_size=8192):
                    if not self.downloading:
                        break
                    
                    if chunk:
                        self.bytes_downloaded += len(chunk)
                        
                        # Print progress every 10 chunks
                        if self.bytes_downloaded % (8192 * 10) == 0:
                            print(f"[CLIENT] Downloaded {self.bytes_downloaded:,} bytes")
                
                print(f"[CLIENT] Download completed! Total: {self.bytes_downloaded:,} bytes")
            
            else:
                print(f"[CLIENT] Server error: {response.status_code}")
        
        except requests.exceptions.ConnectionError as e:
            print(f"[CLIENT] Connection error: {e}")
            print("[CLIENT] *** This could indicate a TCP Reset Attack! ***")
        except requests.exceptions.RequestException as e:
            print(f"[CLIENT] Request error: {e}")
        except Exception as e:
            print(f"[CLIENT] Unexpected error: {e}")
        finally:
            self.downloading = False
    
    def stop_download(self):
        """Stop the download"""
        if self.downloading:
            print("[CLIENT] Stopping download...")
            self.downloading = False
            if self.download_thread:
                self.download_thread.join(timeout=5)
    
    def is_downloading(self):
        """Check if currently downloading"""
        return self.downloading

def run_demo_client():
    """Run the demo client"""
    client = DemoClient()
    
    print("=== Demo Client for TCP Reset Attack ===")
    print("Commands:")
    print("  start - Start downloading video")
    print("  stop  - Stop downloading")
    print("  status - Show download status")
    print("  quit  - Exit client")
    print()
    
    while True:
        try:
            command = input("[CLIENT] Command: ").strip().lower()
            
            if command == "start":
                client.start_download()
            elif command == "stop":
                client.stop_download()
            elif command == "status":
                if client.is_downloading():
                    print(f"[CLIENT] Downloading... {client.bytes_downloaded:,} bytes so far")
                else:
                    print("[CLIENT] Not downloading")
            elif command == "quit":
                client.stop_download()
                print("[CLIENT] Goodbye!")
                break
            else:
                print("[CLIENT] Unknown command")
        
        except KeyboardInterrupt:
            client.stop_download()
            print("\n[CLIENT] Interrupted by user")
            break
        except EOFError:
            break

if __name__ == "__main__":
    run_demo_client()
