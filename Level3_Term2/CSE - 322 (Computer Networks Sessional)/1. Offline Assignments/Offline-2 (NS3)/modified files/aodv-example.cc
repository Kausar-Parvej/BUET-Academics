/*
 * Copyright (c) 2009 IITP RAS
 *
 * SPDX-License-Identifier: GPL-2.0-only
 *
 * This is an example script for AODV manet routing protocol.
 *
 * Authors: Pavel Boyko <boyko@iitp.ru>
 */
#include "ns3/raodv-helper.h"

#include "ns3/aodv-module.h"
#include "ns3/core-module.h"
#include "ns3/internet-module.h"
#include "ns3/mobility-module.h"
#include "ns3/network-module.h"
#include "ns3/ping-helper.h"
#include "ns3/point-to-point-module.h"
#include "ns3/yans-wifi-helper.h"

#include "ns3/wifi-module.h"
#include "ns3/flow-monitor-module.h"
#include "ns3/applications-module.h"






#include <cmath>
#include <iostream>

using namespace ns3;

/**
 * \defgroup aodv-examples AODV Examples
 * \ingroup aodv
 * \ingroup examples
 */

/**
 * \ingroup aodv-examples
 * \ingroup examples
 * \brief Test script.
 *
 * This script creates 1-dimensional grid topology and then ping last node from the first one:
 *
 * [10.0.0.1] <-- step --> [10.0.0.2] <-- step --> [10.0.0.3] <-- step --> [10.0.0.4]
 *
 * ping 10.0.0.4
 *
 * When 1/3 of simulation time has elapsed, one of the nodes is moved out of
 * range, thereby breaking the topology.  By default, this will result in
 * stopping ping replies reception after sequence number 33. If the step size is reduced
 * to cover the gap, then also the following pings can be received.
 */
class AodvExample
{
  public:
    AodvExample();
    /**
     * \brief Configure script parameters
     * \param argc is the command line argument count
     * \param argv is the command line arguments
     * \return true on successful configuration
     */
    bool Configure(int argc, char** argv);
    /// Run simulation
    void Run();
    /**
     * Report results
     * \param os the output stream
     */
    void Report(std::ostream& os);

  private:
    // parameters
    /// Number of nodes
    uint32_t size;
    /// Distance between nodes, meters
    double step;
    /// Simulation time, seconds
    double totalTime;
    /// Write per-device PCAP traces if true
    bool pcap;
    /// Print routes if true
    bool printRoutes;

    uint32_t packetRate = 10;
    double speed = 5.0;




    // network
    /// nodes used in the example
    NodeContainer nodes;
    /// devices used in the example
    NetDeviceContainer devices;
    /// interfaces used in the example
    Ipv4InterfaceContainer interfaces;

  private:
    /// Create the nodes
    void CreateNodes();
    /// Create the devices
    void CreateDevices();
    /// Create the network
    void InstallInternetStack();
    /// Create the simulation applications
    void InstallApplications();
};

int
main(int argc, char** argv)
{
    AodvExample test;
    if (!test.Configure(argc, argv))
    {
        NS_FATAL_ERROR("Configuration failed. Aborted.");
    }

    test.Run();
    test.Report(std::cout);
    return 0;
}

//-----------------------------------------------------------------------------
AodvExample::AodvExample()
    : size(10),
      step(50),
      totalTime(30),
      pcap(false),
      printRoutes(true)
{
}

bool
AodvExample::Configure(int argc, char** argv)
{
    // Enable AODV logs by default. Comment this if too noisy
    // LogComponentEnable("AodvRoutingProtocol", LOG_LEVEL_ALL);

    SeedManager::SetSeed(12345);
    CommandLine cmd(__FILE__);

    cmd.AddValue("pcap", "Write PCAP traces.", pcap);
    cmd.AddValue("printRoutes", "Print routing table dumps.", printRoutes);
    //cmd.AddValue("size", "Number of nodes.", size);
    cmd.AddValue("time", "Simulation time, s.", totalTime);
    //cmd.AddValue("step", "Grid step, m", step);

    cmd.AddValue("numNodes", "Number of nodes.", size);
    cmd.AddValue("speed", "speed of nodes in m/s", speed);
    cmd.AddValue("packetRate", "packet rate (packets per second)", packetRate);



    cmd.Parse(argc, argv);
    return true;
}

void
AodvExample::Run()
{
    //  Config::SetDefault ("ns3::WifiRemoteStationManager::RtsCtsThreshold", UintegerValue (1)); //
    //  enable rts cts all the time.
    CreateNodes();
    CreateDevices();
    InstallInternetStack();
    InstallApplications();

    std::cout << "Starting simulation for " << totalTime << " s ...\n";

    FlowMonitorHelper flowMonHelper;
    Ptr<FlowMonitor> monitor = flowMonHelper.InstallAll();

    Simulator::Stop(Seconds(totalTime));
    Simulator::Run();


    monitor->SerializeToXmlFile("aodv_flowmonResults.xml", true, true);


    Simulator::Destroy();
}

void
AodvExample::Report(std::ostream&)
{
}

void
AodvExample::CreateNodes()
{
    std::cout << "Creating " << size << " nodes with random mobility.\n";
    nodes.Create(size);

    // Create and configure the PositionAllocator
    Ptr<RandomRectanglePositionAllocator> positionAlloc = CreateObject<RandomRectanglePositionAllocator>();
    positionAlloc->SetAttribute("X", StringValue("ns3::UniformRandomVariable[Min=0.0|Max=250.0]"));
    positionAlloc->SetAttribute("Y", StringValue("ns3::UniformRandomVariable[Min=0.0|Max=250.0]"));

    // Set up the MobilityHelper
    MobilityHelper mobility;
    mobility.SetPositionAllocator(positionAlloc);

    // Explicitly bind the PositionAllocator to RandomWaypointMobilityModel
    mobility.SetMobilityModel("ns3::RandomWaypointMobilityModel",
                              "Speed", StringValue("ns3::UniformRandomVariable[Min=5.0|Max=" + std::to_string(speed*2) + "]"),
                              "Pause", StringValue("ns3::ConstantRandomVariable[Constant=0.0]"),
                              "PositionAllocator", PointerValue(positionAlloc));

    // Install the mobility model on nodes
    mobility.Install(nodes);

    // Debugging: Print initial positions
    // for (uint32_t i = 0; i < nodes.GetN(); ++i)
    // {
    //     Ptr<MobilityModel> mobilityModel = nodes.Get(i)->GetObject<MobilityModel>();
    //     Vector pos = mobilityModel->GetPosition();
    //     std::cout << "Node " << i << " initial position: (" << pos.x << ", " << pos.y << ")\n";
    // }
}



void
AodvExample::CreateDevices()
{
    WifiMacHelper wifiMac;
    wifiMac.SetType("ns3::AdhocWifiMac");

    YansWifiPhyHelper wifiPhy;
    YansWifiChannelHelper wifiChannel = YansWifiChannelHelper::Default();
    wifiPhy.SetChannel(wifiChannel.Create());

    // Adjust the transmit power to increase the communication range
    wifiPhy.Set("TxPowerStart", DoubleValue(22.0));
    wifiPhy.Set("TxPowerEnd", DoubleValue(22.0));

    WifiHelper wifi;
    wifi.SetRemoteStationManager("ns3::ConstantRateWifiManager",
                                 "DataMode", StringValue("OfdmRate6Mbps"),
                                 "RtsCtsThreshold", UintegerValue(0)); // Enable RTS/CTS for all packets

    devices = wifi.Install(wifiPhy, wifiMac, nodes);

    if (pcap)
    {
        wifiPhy.EnablePcapAll("aodv");
    }
}


void
AodvExample::InstallInternetStack()
{
    //RAodvHelper aodv;
    AodvHelper aodv;

    InternetStackHelper stack;
    stack.SetRoutingHelper(aodv);
    stack.Install(nodes);
    Ipv4AddressHelper address;
    address.SetBase("10.0.0.0", "255.0.0.0");
    interfaces = address.Assign(devices);

    if (printRoutes)
    {
        Ptr<OutputStreamWrapper> routingStream =
            Create<OutputStreamWrapper>("aodv.routes", std::ios::out);
        Ipv4RoutingHelper::PrintRoutingTableAllAt(Seconds(8), routingStream);
    }
}

void
AodvExample::InstallApplications()
{
    ApplicationContainer serverApps, clientApps;
    uint16_t basePort = 8000; // Base port to ensure uniqueness

    Ptr<UniformRandomVariable> randomNode = CreateObject<UniformRandomVariable>();

    for (uint32_t i = 0; i < size; ++i)
    {
        uint32_t destNodeIndex;
        do
        {
            destNodeIndex = randomNode->GetValue(0, size); // Pick a random destination node
        } while (destNodeIndex == i); // Avoid self-communication

        uint16_t serverPort = basePort + i; // Assign unique port for each server

        // Install server on destination node
        UdpServerHelper server(serverPort);
        serverApps.Add(server.Install(nodes.Get(destNodeIndex)));

        // Configure and install client on source node
        UdpClientHelper client(interfaces.GetAddress(destNodeIndex), serverPort);
        client.SetAttribute("MaxPackets", UintegerValue(512));
        client.SetAttribute("Interval", TimeValue(Seconds(1.0 / packetRate)));
        client.SetAttribute("PacketSize", UintegerValue(512));
        clientApps.Add(client.Install(nodes.Get(i)));
    }

    serverApps.Start(Seconds(1.1));
    clientApps.Start(Seconds(1.5));
    serverApps.Stop(Seconds(totalTime));
    clientApps.Stop(Seconds(totalTime));
}
