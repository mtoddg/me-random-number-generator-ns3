/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
#include <iostream>
#include <./Eigen/Eigen>
#include <./unsupported/Eigen/MatrixFunctions>
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/random-variable-stream.h"

#include "rnd_analysis.h"
#include "test_rnd_var.h"

//using Eigen::MatrixXd;
using namespace Eigen;
using namespace std;

// Default Network Topology
//
//       10.1.1.0
// n0 -------------- n1
//    point-to-point
//
 
using namespace ns3;    


class dog
{
 public:
   int a;
   Matrix3d aa;

  dog()
  {
    a = 6;
    //aa(2,2) = 1,1,1,1;
  }
};

NS_LOG_COMPONENT_DEFINE ("FirstScriptExample");

int main (int argc, char *argv[])
{
  double rnd;
  RngSeedManager::SetSeed(4);


  CommandLine cmd (__FILE__);
  cmd.Parse (argc, argv);
  
  Time::SetResolution (Time::NS);
  LogComponentEnable ("UdpEchoClientApplication", LOG_LEVEL_INFO);
  LogComponentEnable ("UdpEchoServerApplication", LOG_LEVEL_INFO);

  NodeContainer nodes;
  nodes.Create (2);

  PointToPointHelper pointToPoint;
  pointToPoint.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
  pointToPoint.SetChannelAttribute ("Delay", StringValue ("2ms"));

  NetDeviceContainer devices;
  devices = pointToPoint.Install (nodes);

  InternetStackHelper stack;
  stack.Install (nodes);

  Ipv4AddressHelper address;
  address.SetBase ("10.1.1.0", "255.255.255.0");

  Ipv4InterfaceContainer interfaces = address.Assign (devices);

  UdpEchoServerHelper echoServer (9);

  ApplicationContainer serverApps = echoServer.Install (nodes.Get (1));
  serverApps.Start (Seconds (1.0));
  serverApps.Stop (Seconds (10.0));

  UdpEchoClientHelper echoClient (interfaces.GetAddress (1), 9);
  echoClient.SetAttribute ("MaxPackets", UintegerValue (1));
  echoClient.SetAttribute ("Interval", TimeValue (Seconds (1.0)));
  echoClient.SetAttribute ("PacketSize", UintegerValue (1024));

  ApplicationContainer clientApps = echoClient.Install (nodes.Get (0));
  clientApps.Start (Seconds (2.0));
  clientApps.Stop (Seconds (10.0));

  cout << "test" << "\n";
  
  //Ptr<UniformRandomVariable> x = CreateObject<UniformRandomVariable> ();
  Ptr<ExponentialRandomVariable> x = CreateObject<ExponentialRandomVariable> ();
  x->SetAttribute ("Mean", DoubleValue(5));
  x->SetAttribute ("Bound", DoubleValue(100));
  rnd_a test_rnd;
  test_rnd.init();
  //test_rnd.nums = 9;
  //test_rnd.print_nums();

  //test_rnd.get_sample(5.6);
  //test_rnd.print_res();

  int i;
  for (i=0; i<1000000; i++) {
    rnd = x->GetValue();
    test_rnd.get_sample(rnd);
    test_rnd.get_sample_online(rnd);
  }
  test_rnd.analyze_rnds();
  test_rnd.print_res();

  Ptr<ToddRandomVariable> y = CreateObject<ToddRandomVariable> ();
  y->SetAttribute ("Max", DoubleValue(500));
  y->SetAttribute ("Min", DoubleValue(10));
  cout << y->GetMin()<< " " << y->GetMax() << endl;
  cout << y->GetValue(4,5) << endl;
  rnd = y->GetValue();
  cout << rnd << "it" << endl;
  
  Matrix2d testB(2,2);
  testB << 1,2,3,4;
  y->LoadB(testB);
  
  //ToddRandomVariable arnd;
  //arnd.a = 4;
  //cout << arnd.a << endl;

  Simulator::Run ();
  Simulator::Destroy ();

 

  MatrixXd m(2,2);
  m(0,0) = 3;
  m(1,0) = 2.5;
  m(0,1) = -1;
  m(1,1) = m(1,0) + m(0,1);
  std::cout << m << std::endl; 
  cout << m.exp() << endl;

  MatrixXd e(1,3), p(3,1), B(3,3);
  e << 1,2,3;
  p << 1,2,3;
  B << 1,1,1,2,2,2,3,3,3;
  
  Vector3d v;
  v << 3,4,5;
  RowVector3d w;
  w << 5,6,7;

  cout << v << endl;
  cout << w << endl;
  cout << B << endl;
  cout << "---" << endl;
  cout << w*B << endl;
  
 
  
  


  cout << e << endl;
  cout << p << endl;
  
  dog Finn;
  Finn.a = 5;
  cout << Finn.a << endl;


  return 0;
}
