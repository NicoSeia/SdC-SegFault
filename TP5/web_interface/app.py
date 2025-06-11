import os
import sys
import time
import threading
from flask import Flask, render_template, Response, jsonify

app = Flask(__name__)

# Global variables
DEVICE_PATH = '/dev/sensor_drv'
current_signal = 0  # 0 for sine, 1 for square
should_run = True
device_thread = None

def check_device_permissions():
    """Check if we can read and write to the device"""
    if not os.path.exists(DEVICE_PATH):
        print(f"Error: {DEVICE_PATH} does not exist")
        return False
    
    try:
        with open(DEVICE_PATH, 'r+') as f:
            return True
    except PermissionError:
        print(f"Error: No permission to access {DEVICE_PATH}")
        print("Run as root or use: sudo chmod 666 /dev/sensor_drv")
        return False

def read_device():
    """Background thread to read from the device"""
    global should_run
    while should_run:
        try:
            with open(DEVICE_PATH, 'r') as f:
                value = int(f.readline().strip())
                timestamp = time.time()
                yield f"data:{timestamp},{value}\n\n"
            time.sleep(1)
        except Exception as e:
            print(f"Error reading device: {e}")
            time.sleep(1)

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/select/<int:signal_id>', methods=['POST'])
def select_signal(signal_id):
    if signal_id not in (0, 1):
        return jsonify({'ok': False, 'error': 'Invalid signal ID'}), 400
    
    try:
        with open(DEVICE_PATH, 'w') as f:
            f.write(str(signal_id))
        global current_signal
        current_signal = signal_id
        return jsonify({'ok': True})
    except Exception as e:
        return jsonify({'ok': False, 'error': str(e)}), 500

@app.route('/stream')
def stream():
    return Response(read_device(), mimetype='text/event-stream')

def cleanup():
    """Cleanup function to stop the background thread"""
    global should_run
    should_run = False
    if device_thread:
        device_thread.join()

if __name__ == '__main__':
    if not check_device_permissions():
        sys.exit(1)
    
    try:
        app.run(debug=True, threaded=True)
    except KeyboardInterrupt:
        print("\nShutting down gracefully...")
        cleanup() 