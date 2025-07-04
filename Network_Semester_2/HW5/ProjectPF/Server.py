import socket
import hashlib
from Data import *

# Constants
IP = '127.0.0.1'
PORT = 12345
BUFFER_SIZE = 16384
WELCOME_MSG = "Welcome to the Pink-Floyd Server!"
LOGIN_MSG = "Please enter the password: "
HASHED_PASSWORD = "57431ecd7699fc01db4739a427c6f6350d4ae626b9c93d5df56ec1f95e0c012b"  # SHA256 for "#Magsh1m!m"

def hash_password(password):
    return hashlib.sha256(password.encode()).hexdigest()

def authenticate_client(client_socket):
    try:
        client_socket.settimeout(10.0)
        client_socket.send(LOGIN_MSG.encode())
        password_hash = client_socket.recv(BUFFER_SIZE).decode()

        is_alt_client = password_hash.startswith("00")
        if is_alt_client:
            password_hash = password_hash[2:]

        if password_hash == HASHED_PASSWORD:
            msg = "OK" if is_alt_client else "Authentication successful..."
            client_socket.send(msg.encode())
            return True
        else:
            msg = "Wrong password." if is_alt_client else "Authentication failed..."
            client_socket.send(msg.encode())
            return False
    except Exception:
        return False
    finally:
        client_socket.settimeout(None)

def format_response(data_list):
    if not data_list:
        return "No results were found..."
    elif isinstance(data_list, list):
        return ", ".join(data_list)
    else:
        return str(data_list)

def handle_client(client_socket, client_address):
    print(f"Connected to: {client_address}")
    try:
        albums, songs = parse_database()
        if not albums or not songs:
            client_socket.send("Server database error...".encode())
            return

        client_socket.send(WELCOME_MSG.encode())
        if not authenticate_client(client_socket):
            print(f"Authentication failed for: {client_address}")
            return

        connection_active = True
        while connection_active:
            data = client_socket.recv(BUFFER_SIZE).decode()
            if not data:
                break

            message_parts = data.split("-", 1)
            command_code = message_parts[0]
            parameter = message_parts[1].strip() if len(message_parts) > 1 else ""

            print(f"{client_address}: Command: {command_code}, Parameter: {parameter}")
            if command_code == "01":
                response = format_response(get_all_albums(albums, songs))
            elif command_code == "02":
                response = format_response(get_songs_in_album(albums, songs, parameter))
            elif command_code == "03":
                response = get_song_length(albums, songs, parameter)
            elif command_code == "04":
                response = get_song_lyrics(albums, songs, parameter)
            elif command_code == "05":
                response = get_album_by_song(albums, songs, parameter)
            elif command_code == "06":
                response = format_response(search_songs_by_title(albums, songs, parameter))
            elif command_code == "07":
                response = format_response(search_songs_by_lyrics(albums, songs, parameter))
            elif command_code == "08":
                response = "Thank you for using us, Goodbye!"
                connection_active = False
            else:
                response = "Unknown command..."

            if command_code == "04":
                client_socket.sendall((response + "<END>").encode())
            else:
                client_socket.send(response.encode())
    except Exception as e:
        print(f"[!] Error with {client_address}: {e}")
    finally:
        client_socket.close()
        print(f"Disconnected from: {client_address}")

def main():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as server_socket:
        server_socket.bind((IP, PORT))
        server_socket.listen()
        print(f"Server is listening on {IP}:{PORT}")
        while True:
            try:
                client_socket, client_address = server_socket.accept()
                handle_client(client_socket, client_address)
            except Exception as e:
                print(f"Server error: {e}")

if __name__ == "__main__":
    main()
