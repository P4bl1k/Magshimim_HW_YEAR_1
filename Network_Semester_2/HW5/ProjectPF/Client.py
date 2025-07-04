import socket
import hashlib

IP = '127.0.0.1'
PORT = 12345
BUFFER_SIZE = 4096

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

def get_user_input(choice):
    if choice == "2":
        return input("Enter album name: ")
    elif choice in ["3", "4", "5"]:
        return input("Enter song name: ")
    elif choice in ["6", "7"]:
        return input("Enter text: ")
    return ""

def User_Logged(client_socket):
    login_prompt = client_socket.recv(BUFFER_SIZE).decode()  
    print(login_prompt)
    while True:
        password = input()
        hashed = hashlib.sha256(password.encode()).hexdigest()
        client_socket.send(f"00{hashed}".encode()) 
        result = client_socket.recv(BUFFER_SIZE).decode()
        if result == "OK":
            print("Login successful!")
            return True
        else:
            print("Wrong password.")

def main():
    try:
        client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        client_socket.connect((IP, PORT))
        print(client_socket.recv(BUFFER_SIZE).decode())  

        if not User_Logged(client_socket):
            print("Authentication failed.")
            return

        while True:
            print_menu()
            choice = input("Enter number: ").strip()
            if choice not in [str(i) for i in range(1, 11)]:
                print("Invalid choice.")
                continue

            cmd_code = f"{int(choice):02d}"
            extra_data = get_user_input(choice)
            message = cmd_code + "-" + extra_data
            client_socket.send(message.encode())

            if cmd_code == "04":
                response_data = b""
                while True:
                    chunk = client_socket.recv(BUFFER_SIZE)
                    response_data += chunk
                    if b"<END>" in response_data:
                        break
                print(response_data.decode().replace("<END>", ""))
            else:
                response = client_socket.recv(BUFFER_SIZE).decode()
                print(response)

            if cmd_code == "08":
                break

        client_socket.close()

    except Exception as e:
        print(f"[!] Connection error: {e}")

if __name__ == "__main__":
    main()
