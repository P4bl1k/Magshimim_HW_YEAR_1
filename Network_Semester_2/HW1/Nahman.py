import requests

def extract_password_from_files(): 
    base_url = "http://webisfun.cyber.org.il/nahman/files/"
    file_names = [f"file{i}.nfo" for i in range(11, 35)] 
    
    password_chars = []
    
    for file_name in file_names:
        url = base_url + file_name
        response = requests.get(url)
        response.raise_for_status()
        
        content = response.text
        password_chars.append(content[99])

    password = ''.join(password_chars)
    print("Password is:", password)
    return password
    
def find_most_common_words(url, num_words):
    response = requests.get(url)
    response.raise_for_status()
    words = response.text.split()
    
    word_counts = {}
    for word in words:
        word_counts[word] = word_counts.get(word, 0) + 1
    
    most_common = sorted(word_counts.items(), key=lambda x: x[1], reverse=True)[:num_words]
    
    result = ' '.join(word for word, count in most_common)
    return result


def main():
    userInput = int(input("Enter Your Choice For The Answer (1/2): "))
    if userInput == 1:
        extract_password_from_files()
    elif userInput == 2:
        url = "http://webisfun.cyber.org.il/nahman/final_phase/words.txt"
        num_words = 6
        sentence = find_most_common_words(url, num_words)
        print(sentence)
main()
