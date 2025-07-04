import socket

IP = '127.0.0.1'
PORT = 12345
BUFFER_SIZE = 1024
WELCOME_MSG = "Welcome to the Pink-Floyd Server!"

DUMMY_RESPONSES = {
    "01": "Album1, Album2, Album3",
    "02": "Song1, Song2, Song3",
    "03": "03:33",
    "04": "Here are the lyrics...",
    "05": "The Wall",
    "06": "Time, Money, Us and Them",
    "07": "Mother, The Trial, Run Like Hell",
    "08": "Goodbye!"
}


def handle_client(conn, addr):
    print(f"[+] Connected to {addr}")
    try:
        conn.send(WELCOME_MSG.encode())

        while True:
            data = conn.recv(BUFFER_SIZE).decode()
            if not data:
                break

            parts = data.split("|", 1)
            code = parts[0]
            param = parts[1] if len(parts) > 1 else ""
            print(f"[{addr}] Command: {code}, Data: {param}")

            response = DUMMY_RESPONSES.get(code, "Unknown command")
            conn.send(response.encode())

            if code == "08":
                break

    except ConnectionResetError:
        print(f"[!] Client {addr} disconnected unexpectedly")
    finally:
        conn.close()
        print(f"[-] Connection with {addr} closed")


def main():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as server_socket:
        server_socket.bind((IP, PORT))
        server_socket.listen()
        print(f"[*] Server listening on {IP}:{PORT}")

        while True:
            try:
                conn, addr = server_socket.accept()
                handle_client(conn, addr)
            except Exception as e:
                print(f"[!] Error: {e}")


if __name__ == "__main__":
    main()
