import os
import xml.etree.ElementTree as ET
import csv

total_time = 30

def parse_flow_monitor_results(xml_file):
    tree = ET.parse(xml_file)
    root = tree.getroot()

    total_tx_packets = 0
    total_rx_packets = 0
    total_lost_packets = 0
    total_rx_bytes = 0
    total_delay = 0.0
    total_flows = 0

    for flow in root.findall(".//Flow"):
        try:
            tx_packets = int(flow.get("txPackets", 0))
            rx_packets = int(flow.get("rxPackets", 0))
            lost_packets = int(flow.get("lostPackets", 0))
            rx_bytes = int(flow.get("rxBytes", 0))
            delay_sum_ns = flow.get("delaySum", "0ns").replace("ns", "")
            delay_sum = float(delay_sum_ns) / 1e9  # Convert nanoseconds to seconds
        except ValueError:
            continue

        total_tx_packets += tx_packets
        total_rx_packets += rx_packets
        total_lost_packets += lost_packets
        total_rx_bytes += rx_bytes
        total_delay += delay_sum
        total_flows += 1

    throughput = (total_rx_bytes * 8) / (total_time)/1024 if total_flows > 0 else 0  # kilo bits/sec
    end_to_end_delay = total_delay / total_rx_packets if total_rx_packets > 0 else 0
    packet_delivery_ratio = (total_rx_packets / total_tx_packets) * 100 if total_tx_packets > 0 else 0
    packet_drop_ratio = (total_lost_packets / total_tx_packets) * 100 if total_tx_packets > 0 else 0

    return throughput, end_to_end_delay, packet_delivery_ratio, packet_drop_ratio

# Directory containing XML files
input_dir = "simulation_results"
output_csv = "metrics.csv"

with open(output_csv, "w", newline="") as csvfile:
    csvwriter = csv.writer(csvfile)
    csvwriter.writerow(["numNodes", "speed", "packetRate", "Throughput (kbps)", "End-to-End Delay (s)", "PDR (%)", "Packet Drop Ratio (%)"])

    for filename in os.listdir(input_dir):
        if filename.endswith(".xml"):
            # Extract parameters from filename
            parts = filename.replace("results_", "").replace(".xml", "").split("_")
            num_nodes = parts[0].replace("nodes", "")
            speed = parts[1].replace("speed", "")
            packet_rate = parts[2].replace("rate", "")

            # Parse metrics from XML file
            xml_path = os.path.join(input_dir, filename)
            throughput, delay, pdr, drop_ratio = parse_flow_monitor_results(xml_path)

            # Write metrics to CSV
            csvwriter.writerow([num_nodes, speed, packet_rate, throughput, delay, pdr, drop_ratio])

print(f"Metrics saved to {output_csv}")
