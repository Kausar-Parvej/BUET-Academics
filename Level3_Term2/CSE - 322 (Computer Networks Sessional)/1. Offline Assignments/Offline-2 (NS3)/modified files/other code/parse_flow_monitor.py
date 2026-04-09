import xml.etree.ElementTree as ET

# Total simulation time (in seconds)
total_time = 30

def parse_flow_monitor_results(xml_file):
    tree = ET.parse(xml_file)
    root = tree.getroot()

    # Metrics to calculate
    total_tx_packets = 0
    total_rx_packets = 0
    total_lost_packets = 0
    total_rx_bytes = 0
    total_delay = 0.0
    total_flows = 0
    i=0

    for flow in root.findall(".//Flow"):
        try:
            tx_packets = int(flow.get("txPackets", 0))
            rx_packets = int(flow.get("rxPackets", 0))
            lost_packets = int(flow.get("lostPackets", 0))
            rx_bytes = int(flow.get("rxBytes", 0))
            delay_sum_ns = flow.get("delaySum", "0ns").replace("ns", "")
            delay_sum = float(delay_sum_ns) / 1e9  # Convert nanoseconds to seconds
            i+=1
            # print(f"Flow{i}: tx={tx_packets}, rx={rx_packets}, lost={lost_packets}, rx_bytes={rx_bytes}, delay={delay_sum}")
        except ValueError:
            # Skip flows with invalid or missing data
            continue

        # Update totals
        if tx_packets == 0 and rx_packets == 0 and rx_bytes == 0:
            #print(f"total_flows: {total_flows}")
            continue
        total_tx_packets += tx_packets
        total_rx_packets += rx_packets
        total_lost_packets += lost_packets
        total_rx_bytes += rx_bytes
        total_delay += delay_sum
        total_flows += 1

    if total_flows == 0:
        print("No valid flows found in the XML file.")
        return

    # Metrics calculations
    throughput = (total_rx_bytes * 8) / (total_time)/1024  # kilo bits/sec (assuming simTime = 20s)
    end_to_end_delay = total_delay / total_rx_packets if total_rx_packets > 0 else 0
    packet_delivery_ratio = (total_rx_packets / total_tx_packets) * 100 if total_tx_packets > 0 else 0
    packet_drop_ratio = (total_lost_packets / total_tx_packets) * 100 if total_tx_packets > 0 else 0

    print(f"Throughput: {throughput:.2f} kbps")
    print(f"End-to-End Delay: {end_to_end_delay:.6f} s")
    print(f"Packet Delivery Ratio: {packet_delivery_ratio:.2f}%")
    print(f"Packet Drop Ratio: {packet_drop_ratio:.2f}%")

if __name__ == "__main__":
    xml_file = "aodv_flowmonResults.xml"
    parse_flow_monitor_results(xml_file)
