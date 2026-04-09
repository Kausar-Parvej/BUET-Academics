import socket
import pickle

from _2005076_ecdh import ECDH_cipher, EC_point  
from _2005076_aes import encrypt_AES, getIV, hexToAscii 

def send_data(conn, data):
    conn.sendall(pickle.dumps(data))

def receive_data(conn):
    data = b''
    while True:
        part = conn.recv(4096)
        if not part or len(part) < 4096:  # Exit when end of message
            data += part
            break
        data += part
    return pickle.loads(data)





client = socket.socket()
print("Connecting to server...")
client.connect(('localhost', 12355))
print("Connected to server")


ecc = ECDH_cipher()
a = ecc.generate_private()
A = ecc.ec_scalar_mult(a, ecc.base)


send_data(client, {
    'curve': ecc.curve,
    'Ax': A.x,
    'Ay': A.y
})


B_data = receive_data(client)
B = EC_point(B_data['Bx'], B_data['By'])

# Compute shared key
shared_point = ecc.ec_scalar_mult(a, B)
shared_key = str(shared_point.x)[:16]
print("client's shared key: ", shared_key)


message = "Hello Bob!"
iv = getIV(128)
ciphertext, _, _ = encrypt_AES(message, iv, shared_key)


print("Sending message to server: ", message)
print("encrypted: ", hexToAscii(''.join(ciphertext)))
send_data(client, {'iv': iv, 'ciphertext': ciphertext})

client.close()