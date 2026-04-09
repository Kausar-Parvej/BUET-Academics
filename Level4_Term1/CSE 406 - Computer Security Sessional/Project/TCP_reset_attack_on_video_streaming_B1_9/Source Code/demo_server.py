#!/usr/bin/env python3
"""
Demo Video Streaming Server
Simulates a video streaming service for TCP Reset Attack demonstration
"""

import http.server
import socketserver
import threading
import time
import os

class VideoStreamHandler(http.server.SimpleHTTPRequestHandler):
    """Custom handler that simulates video streaming"""
    
    def do_GET(self):
        """Handle GET requests with streaming simulation"""
        if self.path == '/video':
            self.send_video_stream()
        elif self.path == '/':
            self.send_index_page()
        else:
            super().do_GET()
    
    def send_index_page(self):
        """Send a simple index page"""
        content = """
<!DOCTYPE html>
<html>
<head>
    <title>Demo Video Streaming Service</title>
    <style>
        body { font-family: Arial, sans-serif; margin: 40px; }
        .video-container { background: #f0f0f0; padding: 20px; margin: 20px 0; }
        .status { color: #666; margin: 10px 0; }
    </style>
</head>
<body>
    <h1>Demo Video Streaming Service</h1>
    <div class="video-container">
        <h2>Simulated Video Stream</h2>
        <p class="status">Status: <span id="status">Ready</span></p>
        <button onclick="startStream()">Start Video Stream</button>
        <div id="progress"></div>
    </div>
    
    <script>
        function startStream() {
            document.getElementById('status').textContent = 'Streaming...';
            const xhr = new XMLHttpRequest();
            xhr.open('GET', '/video', true);
            xhr.onreadystatechange = function() {
                if (xhr.readyState === 4) {
                    if (xhr.status === 200) {
                        document.getElementById('status').textContent = 'Stream completed';
                    } else {
                        document.getElementById('status').textContent = 'Stream interrupted (TCP Reset?)';
                    }
                }
            };
            xhr.send();
        }
    </script>
</body>
</html>
        """.strip()
        
        self.send_response(200)
        self.send_header('Content-Type', 'text/html')
        self.send_header('Content-Length', str(len(content)))
        self.end_headers()
        self.wfile.write(content.encode())
    
    def send_video_stream(self):
        """Simulate a video stream with large data chunks"""
        self.send_response(200)
        self.send_header('Content-Type', 'application/octet-stream')
        self.send_header('Content-Disposition', 'attachment; filename="video.mp4"')
        # Don't send Content-Length to simulate streaming
        self.end_headers()
        
        print(f"[SERVER] Starting video stream to {self.client_address[0]}:{self.client_address[1]}")
        
        # Send large chunks to simulate video data
        chunk_size = 8192  # 8KB chunks
        total_chunks = 1000  # Total chunks to send
        
        try:
            for i in range(total_chunks):
                # Create fake video data (pattern that might be detected as video)
                chunk_data = b'FAKE_VIDEO_DATA_CHUNK_' + str(i).zfill(6).encode() + b'_' + (b'X' * (chunk_size - 30))
                
                self.wfile.write(chunk_data)
                self.wfile.flush()
                
                # Small delay to simulate realistic streaming
                time.sleep(0.1)
                
                if i % 10 == 0:
                    print(f"[SERVER] Sent chunk {i+1}/{total_chunks}")
                
        except (ConnectionResetError, BrokenPipeError) as e:
            print(f"[SERVER] Connection reset by client or network! This indicates TCP Reset Attack success!")
            print(f"[SERVER] Error: {e}")
        except Exception as e:
            print(f"[SERVER] Stream error: {e}")
        
        print(f"[SERVER] Stream ended for {self.client_address[0]}:{self.client_address[1]}")

def start_demo_server(port=8080):
    """Start the demo streaming server"""
    print(f"[SERVER] Starting demo video streaming server on port {port}")
    
    with socketserver.TCPServer(("", port), VideoStreamHandler) as httpd:
        print(f"[SERVER] Server running at http://localhost:{port}")
        print(f"[SERVER] Visit http://localhost:{port} to test streaming")
        print(f"[SERVER] Press Ctrl+C to stop")
        
        try:
            httpd.serve_forever()
        except KeyboardInterrupt:
            print(f"\n[SERVER] Shutting down server...")

if __name__ == "__main__":
    start_demo_server()
