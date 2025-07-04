from Glitter import *
import requests 
import json
import datetime
import sys

def main():
    display_welcome()
    
    try:
        user_info = authenticate_user()
        if not user_info:
            print("Authentication failed. Exiting...")
            return
    except KeyboardInterrupt:
        print("\n\nGoodbye!")
        return
    
    try:
        while True:
            display_menu()
            
            try:
                choice = int(input("\nEnter your choice: "))
                if not handle_menu_choice(choice):
                    break 
                    
            except ValueError:
                print("Please enter a valid number")
            except KeyboardInterrupt:
                print("\nExiting...")
                break
            
            input("\nPress Enter to continue...")
    
    except Exception as e:
        print(f"An unexpected error occurred: {str(e)}")
    
    if current_user_info:
        print("\nLogging out...")
        logout(current_user_info["user"]["id"])
    
    print("\nThank you for using Glitter Client!")
    print("="*60)

if __name__ == "__main__":
    main()