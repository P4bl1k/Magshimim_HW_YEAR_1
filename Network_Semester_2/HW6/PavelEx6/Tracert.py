from scapy.all import *
import time
import socket

MAX_HOPS = 30
TIMEOUT = 2
def tracert(dest_name):
    """
    Function to perform a traceroute to a given destination.
    input: dest_name,max_hops,timeout.
    output: Traceroute results.
    """
    max_hops = MAX_HOPS
    timeout = TIMEOUT
    
    print(f"Tracing route to {dest_name} with max {max_hops} hops:\n")
    dest_ip = dest_name
    try:
        dest_ip = socket.gethostbyname(dest_name)
    except Exception:
        pass

    for ttl in range(1, max_hops + 1):
        packet = IP(dst=dest_ip, ttl=ttl) / ICMP()
        start_time = time.time()
        reply = sr1(packet, verbose=0, timeout=timeout)
        rtt = (time.time() - start_time) * 1000
        if reply is None:
            print(f"{ttl:2}  *")
        else:
            try:
                host = reply.src
            except Exception:
                host = "Unknown"
            print(f"{ttl:2}  {host:15}  {rtt:.2f} ms")
            if reply.src == dest_ip:
                print("Trace complete.")
                break

if __name__ == "__main__":
    
    dest = input("Enter destination: ")
    tracert(dest)
