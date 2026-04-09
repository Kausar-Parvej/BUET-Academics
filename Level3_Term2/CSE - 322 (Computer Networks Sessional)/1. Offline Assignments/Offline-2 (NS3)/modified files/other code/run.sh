#!/bin/bash

# Create directory for simulation results
output_dir="simulation_results"
mkdir -p $output_dir

# Fixed values for parameters
fix_speed=16
fix_packet_rate=150
fix_node_num=50

# Parameter combinations
num_nodes_list=(20 40 70 90)
speed_list=(5 10 15 20)
packet_rate_list=(100 200 250 300)

for num_nodes in "${num_nodes_list[@]}"; do
    output_file="${output_dir}/results_nodes${num_nodes}_speed${fix_speed}_rate${fix_packet_rate}.xml"

    echo "Running simulation for Nodes=$num_nodes, Speed=$fix_speed, PacketRate=$fix_packet_rate..."
    ./ns3 run "aodv-example --numNodes=$num_nodes --speed=$fix_speed --packetRate=$fix_packet_rate"

    mv aodv_flowmonResults.xml "$output_file"
    echo "Saved results to $output_file"
done

for packet_rate in "${packet_rate_list[@]}"; do
    output_file="${output_dir}/results_nodes${fix_node_num}_speed${fix_speed}_rate${packet_rate}.xml"

    echo "Running simulation for Nodes=$fix_node_num, Speed=$fix_speed, PacketRate=$packet_rate..."
    ./ns3 run "aodv-example --numNodes=$fix_node_num --speed=$fix_speed --packetRate=$packet_rate"

    mv aodv_flowmonResults.xml "$output_file"
    echo "Saved results to $output_file"
done

for speed in "${speed_list[@]}"; do
    output_file="${output_dir}/results_nodes${fix_node_num}_speed${speed}_rate${fix_packet_rate}.xml"

    echo "Running simulation for Nodes=$fix_node_num, Speed=$speed, PacketRate=$fix_packet_rate..."
    ./ns3 run "aodv-example --numNodes=$fix_node_num --speed=$speed --packetRate=$fix_packet_rate"

    mv aodv_flowmonResults.xml "$output_file"
    echo "Saved results to $output_file"
done

echo "Simulation runs completed!"
