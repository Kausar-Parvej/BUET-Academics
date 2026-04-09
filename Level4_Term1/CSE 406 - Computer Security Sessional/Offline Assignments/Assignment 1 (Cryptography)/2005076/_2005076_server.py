import socket
import pickle

from _2005076_ecdh import ECDH_cipher, EC_point 
from _2005076_aes import decrypt_AES, hexToAscii, hexVecToAsciVec 

def send_data(conn, data):
    conn.sendall(pickle.dumps(data))     #send all as serialized bytes

def receive_data(conn):
    data = b''          #empty byte string
    while True:
        part = conn.recv(4096)
        if not part or len(part) < 4096:        
            data += part
            break
        data += part
    return pickle.loads(data)   #deserialize using pickle.loads()







server = socket.socket()
server.bind(('localhost', 12355))
server.listen(1)
print("Waiting for client...")

conn, addr = server.accept()
print("Connected to client:", addr)


params = receive_data(conn)
#print("Received curve parameters and A from Alice:", params)
ecc = ECDH_cipher(_curve=params['curve'])
A = EC_point(params['Ax'], params['Ay'])


b = ecc.generate_private()
B = ecc.ec_scalar_mult(b, ecc.base)
send_data(conn, {'Bx': B.x, 'By': B.y})


shared_point = ecc.ec_scalar_mult(b, A)
shared_key = str(shared_point.x)[:16]
print("server's shared key: ", shared_key)

# Receive ciphertext and IV
data = receive_data(conn)
iv = data['iv']
ciphertext = data['ciphertext']

print("received data: " , hexToAscii(''.join(ciphertext)))
plaintext, _ = decrypt_AES(ciphertext, iv, shared_key)
print("Decrypted message:", ''.join(hexVecToAsciVec(plaintext)))

conn.close()