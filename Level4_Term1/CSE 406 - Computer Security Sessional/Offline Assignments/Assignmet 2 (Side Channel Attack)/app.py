from flask import Flask, send_from_directory

# additional imports
import os
import io
import json
import matplotlib.pyplot as plt
import numpy as np
from flask import request, jsonify, send_file

# Ensure the directory exists
os.makedirs("static/heatmaps", exist_ok=True)


app = Flask(__name__)

stored_traces = []
stored_heatmaps = []

@app.route('/')
def index():
    return send_from_directory('static', 'index.html')

@app.route('/<path:path>')
def static_files(path):
    return send_from_directory('static', path)

@app.route('/collect_trace', methods=['POST'])
def collect_trace():
    """ 
    Implement the collect_trace endpoint to receive trace data from the frontend and generate a heatmap.
    1. Receive trace data from the frontend as JSON
    2. Generate a heatmap using matplotlib
    3. Store the heatmap and trace data in the backend temporarily
    4. Return the heatmap image and optionally other statistics to the frontend
    """

    try:
        data = request.get_json()
        trace = data.get("data")
        if not trace:
            return jsonify({"error": "No trace data provided"}), 400

        stored_traces.append(trace)

        # Generate heatmap
        fig, ax = plt.subplots(figsize=(10,1))
        ax.imshow([trace], aspect='auto', cmap='hot')
        ax.set_title(f"Trace {len(stored_traces)}")
        ax.axis("off")

        #save image
        filename = f"trace_{len(stored_traces)}.png"
        filepath = os.path.join("static/heatmaps", filename)
        plt.savefig(filepath, bbox_inches='tight', pad_inches=0.1)
        plt.close(fig)

        stored_heatmaps.append(filepath)
        return jsonify({"heatmap_url": f"/static/heatmaps/{filename}"})
    
    except Exception as e:
        return jsonify({"error": str(e)}), 500

@app.route('/api/clear_results', methods=['POST'])
def clear_results():
    """ 
    Implment a clear results endpoint to reset stored data.
    1. Clear stored traces and heatmaps
    2. Return success/error message
    """

    try:
        global stored_traces, stored_heatmaps

        # Clear memory
        stored_traces = []
        stored_heatmaps = []

        # Delete image files
        heatmap_dir = "static/heatmaps"
        for f in os.listdir(heatmap_dir):
            os.remove(os.path.join(heatmap_dir, f))

        return jsonify({"status": "success"})
    except Exception as e:
        return jsonify({"status": "error", "message": str(e)}), 500


@app.route('/api/trace_data', methods=['GET'])
def get_trace_data():
    return jsonify(stored_traces)

@app.route('/api/get_results')
def get_results():
    return jsonify({"traces": stored_traces})



# Additional endpoints can be implemented here as needed.

if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0', port=5000)