import socket
from datetime import datetime, timedelta

def calculate_checksum(city, date):
    letters = [c.lower() for c in city if c.isalpha()]
    alpha_sum = sum(ord(c) - ord('a') + 1 for c in letters)
    digit_sum = sum(int(d) for d in date if d.isdigit())
    return float(f"{alpha_sum}.{digit_sum:02d}")

def check_forecast(city, date, host="34.218.16.79", port=77):
    try:
        checksum = calculate_checksum(city, date)
        message = f"100:REQUEST:city={city}&date={date}&checksum={checksum}"

        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            s.connect((host, port))

            s.recv(1024)  # welcome message

            s.sendall(message.encode())

            response = s.recv(1024).decode()

        if response.startswith("200:ANSWER:"):
            content = response[len("200:ANSWER:"):]
            parts = content.split("&")
            data_dict = dict(part.split("=") for part in parts)

            temp = float(data_dict["temp"])
            desc = data_dict["text"]
            return (temp, desc)

        elif response.startswith("500:ERROR:"):
            error_msg = response[len("500:ERROR:"):]
            return (999.0, error_msg)

        else:
            return (999.0, "Invalid response format")

    except Exception as e:
        return (999.0, str(e))


def main():
    city = input("What is your city? (e.g., Eilat, Israel): ")

    print("\nMenu:")
    print("1. What is the weather today?")
    print("2. Weather forecast for the next three days")

    choice = input("Select an option (1/2): ")

    if choice == "1":
        today = datetime.now().strftime("%d/%m/%Y")
        temp, desc = check_forecast(city, today)
        print(f"\n{today}, Temperature: {temp}, {desc}.")

    elif choice == "2":
        print()
        for i in range(4):
            date = (datetime.now() + timedelta(days=i)).strftime("%d/%m/%Y")
            temp, desc = check_forecast(city, date)
            print(f"{date}, Temperature: {temp}, {desc}.")
    else:
        print("Invalid choice.")

if __name__ == "__main__":
    main()
