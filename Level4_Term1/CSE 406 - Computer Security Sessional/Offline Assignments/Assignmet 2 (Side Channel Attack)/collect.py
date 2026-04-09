import time
import json
import os
import signal
import sys
import random
import traceback
import socket
from selenium import webdriver
from selenium.webdriver.chrome.options import Options
from selenium.webdriver.chrome.service import Service
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from webdriver_manager.chrome import ChromeDriverManager
import database
from database import Database

WEBSITES = [
    # websites of your choice
    "https://cse.buet.ac.bd/moodle/",
    "https://google.com",
    "https://prothomalo.com",
]

#TRACES_PER_SITE = 1000
TRACES_PER_SITE = 600  # Reduced for testing purposes
FINGERPRINTING_URL = "http://localhost:5000" 
OUTPUT_PATH = "dataset_my.json"

# Initialize the database to save trace data reliably
database.db = Database(WEBSITES)

""" Signal handler to ensure data is saved before quitting. """
def signal_handler(sig, frame):
    print("\nReceived termination signal. Exiting gracefully...")
    try:
        database.db.export_to_json(OUTPUT_PATH)
    except:
        pass
    sys.exit(0)
signal.signal(signal.SIGINT, signal_handler)


"""
Some helper functions to make your life easier.
"""

def is_server_running(host='127.0.0.1', port=5000):
    """Check if the Flask server is running."""
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    result = sock.connect_ex((host, port))
    sock.close()
    return result == 0

# def setup_webdriver():
#     """Set up the Selenium WebDriver with Chrome options."""
#     chrome_options = Options()
#     chrome_options.add_argument("--window-size=1920,1080")
#     service = Service(ChromeDriverManager().install())
#     driver = webdriver.Chrome(service=service, options=chrome_options)
#     return driver


def setup_webdriver():
    chrome_options = Options()
    chrome_options.add_argument("--window-size=1920,1080")

    # For WSL: enable no-sandbox and disable GPU (optional but helps stability)
    chrome_options.add_argument("--no-sandbox")
    chrome_options.add_argument("--disable-dev-shm-usage")

    driver = webdriver.Chrome(options=chrome_options)  # No Service() or ChromeDriverManager
    return driver




def retrieve_traces_from_backend(driver):
    """Retrieve traces from the backend API."""
    traces = driver.execute_script("""
        return fetch('/api/get_results')
            .then(response => response.ok ? response.json() : {traces: []})
            .then(data => data.traces || [])
            .catch(() => []);
    """)
    
    count = len(traces) if traces else 0
    print(f"  - Retrieved {count} traces from backend API" if count else "  - No traces found in backend storage")
    return traces or []

def clear_trace_results(driver, wait):
    """Clear all results from the backend by pressing the button."""
    clear_button = driver.find_element(By.XPATH, "//button[contains(text(), 'Clear all results')]")
    clear_button.click()

    wait.until(EC.text_to_be_present_in_element(
        (By.XPATH, "//div[@role='alert']"), "Cleared"))
    
def is_collection_complete():
    """Check if target number of traces have been collected."""
    current_counts = database.db.get_traces_collected()
    remaining_counts = {website: max(0, TRACES_PER_SITE - count) 
                      for website, count in current_counts.items()}
    return sum(remaining_counts.values()) == 0

"""
Your implementation starts here.
"""


def clear_heatmaps_via_api():
    import requests
    try:
        res = requests.post("http://localhost:5000/api/clear_results")
        if res.ok:
            print("[*] Cleared previous results (traces + heatmaps)")
        else:
            print("[-] Failed to clear previous results")
    except Exception as e:
        print(f"[-] Error clearing heatmaps: {e}")


def collect_single_trace(driver, wait, website_url):
    """ Implement the trace collection logic here. 
    1. Open the fingerprinting website
    2. Click the button to collect trace
    3. Open the target website in a new tab
    4. Interact with the target website (scroll, click, etc.)
    5. Return to the fingerprinting tab and close the target website tab
    6. Wait for the trace to be collected
    7. Return success or failure status
    """


    try:
        print(f"\n[*] Collecting trace for {website_url}")

        # 1. Open fingerprinting website in first tab
        driver.get(FINGERPRINTING_URL)
        wait.until(EC.presence_of_element_located((By.TAG_NAME, "button")))

        # 2. Open target website in new tab
        driver.execute_script(f"window.open('{website_url}', '_blank');")
        driver.switch_to.window(driver.window_handles[1])
        time.sleep(3)

        # 3. Interact with target site (scroll randomly)
        for _ in range(3):
            scroll_amount = random.randint(200, 500)
            driver.execute_script(f"window.scrollBy(0, {scroll_amount});")
            time.sleep(0.5)

        # 4. Return to fingerprinting tab
        driver.close()  # Close target tab
        driver.switch_to.window(driver.window_handles[0])

        # 5. Click "Collect Trace" button
        button = wait.until(EC.element_to_be_clickable((By.XPATH, "//button[contains(text(), 'Collect Trace')]")))
        button.click()
        time.sleep(0.5)  # Optional stabilization delay

        # 6. Wait until heatmap appears (wait for image or success message)
        wait.until(EC.presence_of_element_located((By.XPATH, "//img[contains(@src, 'trace_')]")))

        # 7. Retrieve traces from backend
        traces = retrieve_traces_from_backend(driver)
        if not traces:
            return False

        trace_data = traces[-1]  # Take latest one

        # 8. Save in database
        site_idx = WEBSITES.index(website_url)
        database.db.save_trace(website_url, site_idx, trace_data)
        

        # Delete the most recent heatmap image (optional cleanup)
        try:
            filename = f"trace_{len(retrieve_traces_from_backend(driver))}.png"
            filepath = os.path.join("static/heatmaps", filename)
            if os.path.exists(filepath):
                os.remove(filepath)
        except Exception as e:
            print(f"[!] Failed to delete heatmap: {e}")



        return True

    except Exception as e:
        print(f"Error in trace collection: {e}")
        traceback.print_exc()
        return False
    


def collect_fingerprints(driver, target_counts=None):
    """ Implement the main logic to collect fingerprints.
    1. Calculate the number of traces remaining for each website
    2. Open the fingerprinting website
    3. Collect traces for each website until the target number is reached
    4. Save the traces to the database
    5. Return the total number of new traces collected
    """


    print("\n[+] Starting fingerprint collection")

    if target_counts is None:
        target_counts = {website: TRACES_PER_SITE for website in WEBSITES}

    # Get how many traces already exist
    collected = database.db.get_traces_collected()
    remaining = {
        site: max(0, target_counts[site] - collected.get(site, 0))
        for site in WEBSITES
    }

    total_new = 0
    wait = WebDriverWait(driver, 20)

    while sum(remaining.values()) > 0:
        for site in WEBSITES:
            if remaining[site] <= 0:
                continue

            success = collect_single_trace(driver, wait, site)
            if success:
                total_new += 1
                remaining[site] -= 1
            else:
                print(f"[-] Failed to collect trace for {site}. Retrying...")

            print(f"    Remaining for {site}: {remaining[site]}")

    print(f"[✓] Collected {total_new} new traces")
    return total_new



def main():
    """ Implement the main function to start the collection process.
    1. Check if the Flask server is running
    2. Initialize the database
    3. Set up the WebDriver
    4. Start the collection process, continuing until the target number of traces is reached
    5. Handle any exceptions and ensure the WebDriver is closed at the end
    6. Export the collected data to a JSON file
    7. Retry if the collection is not complete
    """


    print("[*] Starting automated data collection...")

    # 1. Check if Flask server is running
    if not is_server_running():
        print("[-] Flask server is not running at http://localhost:5000. Please start it first.")
        return

    # 2. Initialize the database
    clear_heatmaps_via_api()
    database.db.init_database()

    # 3. Set up the WebDriver
    driver = setup_webdriver()

    try:
        while not is_collection_complete():
            collect_fingerprints(driver)
            time.sleep(2)  # Short break between batches
    except KeyboardInterrupt:
        print("\n[!] Interrupted. Saving progress...")
    except Exception as e:
        print(f"[!] Unexpected error: {e}")
        traceback.print_exc()
    finally:
        # 4. Clean shutdown
        print("[*] Exporting collected dataset...")
        database.db.export_to_json(OUTPUT_PATH)
        driver.quit()
        print("[✓] Done. All traces collected and saved.")


if __name__ == "__main__":
    main()
