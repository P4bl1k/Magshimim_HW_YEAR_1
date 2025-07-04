"""
This script performs a DNS lookup for a given domain name using Scapy.
"""
from scapy.all import * 

user_input_domain = input("Insert domain name:")
dns_request = IP(dst="8.8.8.8") / UDP(dport=53) / DNS(rd=1, qd=DNSQR(qname=user_input_domain))
dns_response = sr1(dns_request, verbose=0, timeout=2)

if dns_response and DNS in dns_response and DNSRR in dns_response:
    ip_address = dns_response[DNSRR].rdata
    print(ip_address)
else:
    print("Couldnt find the domain.")