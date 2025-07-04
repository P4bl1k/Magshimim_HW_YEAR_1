import socket

SERVER_IP = '127.0.0.1'
SERVER_PORT = 12345
BUFFER_SIZE = 1024

def print_menu():
    print("""
1 Get Albums
2 Get Album Songs
3 Get Song Length
4 Get Song Lyrics
5 Get Song Album
6 Search Song by Name
7 Search Song by Lyrics
8 Quit
""")


def main():
    try:
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as client_socket:
            client_socket.connect((SERVER_IP, SERVER_PORT))
            welcome = client_socket.recv(BUFFER_SIZE).decode()
            print(welcome)

            while True:
                print_menu()
                choice = input("Enter number: ").strip()
                if choice not in [str(i) for i in range(1, 9)]:
                    print("Invalid option.")
                    continue

                code = f"{int(choice):02}"  # 1 -> '01'
                param = ""

                if code in ["02"]:
                    param = input("Enter album name: ").strip()
                elif code in ["03", "04", "05"]:
                    param = input("Enter song name: ").strip()
                elif code in ["06", "07"]:
                    param = input("Enter text: ").strip()

                message = f"{code}|{param}"
                client_socket.send(message.encode())

                response = client_socket.recv(BUFFER_SIZE).decode()
                print(response)

                if code == "08":
                    break

    except ConnectionRefusedError:
        print("[!] Cannot connect to server. Is it running?")
    except Exception as e:
        print(f"[!] Connection error: {e}")


if __name__ == "__main__":
    main()