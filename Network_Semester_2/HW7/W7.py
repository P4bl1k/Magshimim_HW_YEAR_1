from scapy.all import *
from scapy.layers.dns import DNS, DNSRR
from scapy.layers.http import HTTPRequest
from scapy.layers.inet import IP

IPforc = "34.218.16.79"

def main():
    options = {
        "1": dns_sniff,
        "2": forecast_sniff,
        "3": http_sniff
    }

    welcome = (
        "Welcome to Magshishark!\n"
        "Please select sniffing state:\n"
        "1. DNS\n"
        "2. Forecast\n"
        "3. HTTP\n"
        "Or select 0 to Exit:"
    )

    while True:
        print(welcome)
        choice = input().strip()
        if choice == "0":
            print("Bye!")
            break
        sniff_function = options.get(choice)
        if sniff_function:
            try:
                sniff_function()
            except KeyboardInterrupt:
                print("\nReturning to menu...")
        else:
            print("Invalid choice!")

# ---------- DNS ----------
# Check if the packet is a DNS response with answers
def is_dns_response(packet):
    return DNS in packet and packet[DNS].qr == 1 and packet[DNS].ancount > 0

# Sniff DNS responses and print the domain and IP address
def dns_sniff():
    print("Sniffing DNS responses...")
    sniff(lfilter=is_dns_response, prn=print_dns_info)

# Print the DNS response information from the packet
def print_dns_info(packet):
    dns_layer = packet[DNS]
    domain = dns_layer.qd.qname.decode() if dns_layer.qd else "Unknown"
    for i in range(dns_layer.ancount):
        rr = dns_layer.an[i]
        if rr.type == 1:  # A record
            print(f"{domain} ===> {rr.rdata}")

# ---------- Forecast ----------
# Check if the packet is a forecast response
def is_forecast(packet):
    return (IP in packet and
            packet[IP].src == IPforc and
            Raw in packet and
            "200:ANSWER" in packet[Raw].load.decode(errors="ignore"))

# Sniff forecast packets and print the information
def forecast_sniff():
    print("Sniffing Forecast...")
    sniff(lfilter=is_forecast, prn=print_forecast_info)

# Print the forecast information from the packet
def print_forecast_info(packet):
    print(packet[Raw].load.decode(errors="ignore"))

# ---------- HTTP ----------
# Check if the packet is an HTTP GET request
def is_http_get(packet):
    return packet.haslayer(HTTPRequest) and packet[HTTPRequest].Method == b'GET'

# Sniff HTTP GET requests and print the host and path
def http_sniff():
    print("Sniffing HTTP GET requests...")
    sniff(lfilter=is_http_get, prn=print_http_get)

# Print the host and path from the HTTP GET request
def print_http_get(packet):
    if packet.haslayer(HTTPRequest):
        req = packet[HTTPRequest]
        host = req.Host.decode() if req.Host else ""
        path = req.Path.decode() if req.Path else ""
        print(f"{host}{path}")
    else:
        print("Unknown HTTP packet")

# ---------- Run ----------
if __name__ == '__main__':
    main()
