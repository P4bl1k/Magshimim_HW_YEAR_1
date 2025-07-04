import socket

REAL_SERVER_IP = '54.71.128.194'
REAL_SERVER_PORT = 92
LOCAL_PORT = 9090

def handle_client(client_socket):
    try:
        # Receive request from client
        request = client_socket.recv(4096)
        print("=== Request from client ===")
        print(request.decode(errors='ignore'))

        # Connect to real server
        server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        server_socket.connect((REAL_SERVER_IP, REAL_SERVER_PORT))

        # Forward request to server
        server_socket.sendall(request)

        # Receive response from server
        response = server_socket.recv(4096)
        print("=== Response from server (before modification) ===")
        print(response.decode(errors='ignore'))

        if b'France' in response:
            print("France detected! Sending error")
            error_message = b'ERROR#France is banned!'
            client_socket.sendall(error_message)
        else:
            # Modify the response - add "proxy" to name field
            modified_response = response.replace(b'name:"', b'name:"proxy')

            print("=== Modified response to client ===")
            print(modified_response.decode(errors='ignore'))

            # Send modified response back to client
            client_socket.sendall(modified_response)

        server_socket.close()
        client_socket.close()

    except Exception as e:
        print(f"Error: {e}")
        client_socket.close()

def main():
    proxy_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    proxy_socket.bind(('127.0.0.1', LOCAL_PORT))
    proxy_socket.listen(5)

    print(f"Proxy is listening on port {LOCAL_PORT}...")

    while True:
        client_socket, addr = proxy_socket.accept()
        print(f"Accepted connection from {addr}")
        handle_client(client_socket)

if __name__ == "__main__":
    main()
