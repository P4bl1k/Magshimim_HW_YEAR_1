from scapy.all import *
import time
import socket

SEND_AMNT = 3

def get_ip(domain):
    """
    Function to resolve the domain name to an IP address.
    """
    try:
        return socket.gethostbyname(domain)
    except Exception:
        return None

def ping(domain):
    """
    Function to ping a domain name by resolving it to an IP address
    and sending ICMP echo requests.
    """
    ip = get_ip(domain)
    if ip is None:
        print(f"Could not resolve domain: {domain}")
        return

    print(f"Pinging {ip} with {SEND_AMNT} packets:")
    response_times = []

    for i in range(SEND_AMNT):
        try:
            packet = IP(dst=ip) / ICMP()
            send_time = time.time()
            reply = sr1(packet, timeout=3, verbose=0)
            receive_time = time.time()
            if reply:
                rtt_ms = int((receive_time - send_time) * 1000)
                print(f"Reply from {ip}: time={rtt_ms}ms")
                response_times.append(rtt_ms)
            else:
                print(f"Request {i+1} timed out.")
        except Exception:
            print(f"Error during ping.")

    if response_times:
        avg = sum(response_times) / len(response_times)
        print(f"Summary: Average={int(avg)}ms")
    else:
        print("Summary: No replies received.")

def main():
    """
    Main function Of the Program.
    """
    domain = input("Insert domain name: ")
    ping(domain)

if __name__ == "__main__":
    main()
