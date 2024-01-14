#!/usr/bin/python
# CS6250 Computer Networks Project 1
# Creates a datacenter topology based on command line parameters and starts the Mininet Command Line Interface.

from mininet.topo import Topo
from mininet.net import Mininet
from mininet.log import lg, output, setLogLevel
from mininet.node import CPULimitedHost
from mininet.link import TCLink
from mininet.cli import CLI
import argparse
import sys
import os

# Parse Command Line Arguments
parser = argparse.ArgumentParser(description="Datacenter Topologies")

parser.add_argument('--fi',
                    type=int,
                    help=("Number of Fan-in Switches to create."
                          "Must be >= 1"),
                    required=True)

parser.add_argument('--n',
                    type=int,
                    help=("Number of hosts to create in each lower level switch."
                          "Must be >= 1"),
                    required=True)

lg.setLogLevel('info')


# Topology to be instantiated in Mininet
class DataCenter(Topo):
    """DataCenter Topology"""

    def __init__(self, n=1, delay='0ms', fi=1,  cpu=.01, max_queue_size=None, **params):
        """Star Topology with fi fan-in  zones.
           n: number of hosts per low level switch
           cpu: system fraction for each host
           bw: link bandwidth in Mb/s
           delay: link latency (e.g. 10ms)"""
        self.cpu = 1 / ((n * fi * fi) * 1.5)

        # Initialize topo
        Topo.__init__(self, **params)

        hostConfig = {'cpu': cpu}
        #NOTE:  Switch to Switch links will be bw=10 delay=0
        #NOTE:  Hosts to Switch links will be bw=1 delay=1
        #NOTE:  Use the following configurations as appropriate when creating the links
        swlinkConfig = {'bw': 10, 'delay': '0ms', 'max_queue_size': max_queue_size}
        hostlinkConfig = {'bw': 1, 'delay': '1ms','max_queue_size': max_queue_size}
        tls = self.addSwitch('tls1')
        #TODO: Create your DataCenter Mininet Topology here!
        #NOTE: Top Level Switch is labled tls1 and is created for you
        #NOTE: You MUST label mid level switches as mls1, mls2, ... mlsfi
        mls_names = {}
        sx_names = {}
        hosts_names = {}

        for i in range(1, fi + 1):
            mls_name = 'mls' + str(i)
            mls_names[i] = self.addSwitch(mls_name)
            self.addLink(tls, mls_name, **swlinkConfig)

        for i in range(1, fi + 1):
            for j in range(1, fi + 1):
                sx_names[(i, j)] = self.addSwitch('s' + str(i) + 'x' + str(j))
                self.addLink(mls_names[i], sx_names[(i, j)], **swlinkConfig)

        for i in range(1, fi + 1):
            for j in range(1, fi + 1):
                for k in range(1, n + 1):
                    hosts_names[(i, j, k)] = self.addHost('h' + str(i) + 'x' + str(j) + 'x' + str(k), **hostConfig)
                    self.addLink(sx_names[(i, j)], hosts_names[(i, j, k)], **hostlinkConfig)

        #NOTE: You MUST label low level switches s1x1, s1x2...s1xfi... sfix1, sfix2,... sfixfi  
        #NOTE: You MUST label hosts as h1x1x1, h1x1x2, ... hfixfixn
        #NOTE: Remember to use n and fi, don't use args.n or args.fi!     
        #HINT: Use a loop to construct the topology in pieces. Don't forget the link configuration.


def main():
    """Create specified topology and launch the command line interface"""
    args = parser.parse_args()
    topo = DataCenter(n=args.n, fi=args.fi)
    net = Mininet(topo=topo, host=CPULimitedHost, link=TCLink)
    net.start()
    CLI(net)
    net.stop()
    
if __name__ == '__main__':
    setLogLevel('info')
    main()
