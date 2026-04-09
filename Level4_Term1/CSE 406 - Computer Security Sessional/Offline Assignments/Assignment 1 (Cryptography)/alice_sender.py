import threading
import socket
import ast

import _2005076_aes as _AES
import _2005076_ecdh 

key_length = 128

def ecdh_key_exchange(a_socket, key_level):
    _ecdh = _2005076_ecdh.ECDH_cipher(key_level)
    curve = _ecdh._init_curve()

    a_socket.send(str(curve).encode())

    b_publicKey = a_socket.recv(1024).decode()
    b_publicKey = _2005076_ecdh.EC_point(int(b_publicKey.split(",")[0][1:]), int(b_publicKey.split(",")[1][:-1]))

    a_privateKey = _ecdh.generate_private()
    a_publicKey = _ecdh.ec_scalar_mult(a_privateKey, _ecdh.base)
    a_socket.send(str(a_publicKey).encode())

    shared_key = _ecdh.ec_scalar_mult(a_privateKey, b_publicKey)
    return shared_key.x


def initiate_connection(host, port):
    a_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    a_socket.connect((host, port))
    print("Connected to the server.")
    return a_socket


def send_message(a_socket, shared_key, message):
    IV = _AES.getIV(key_length)
    a_socket.send(IV.encode())
    cipher_tuple = _AES.encrypt_AES(message,IV, shared_key)
    cipher = str(cipher_tuple)
    a_socket.send(cipher.encode())


def receive_message(a_socket, shared_key):
    while True:
        IV = a_socket.recv(1024).decode()
        cipher = a_socket.recv(1024).decode()
        cipher = ast.literal_eval(cipher)
        message = _AES.decrypt_AES(cipher, IV, shared_key)
        print(f"Received message(cipher): {cipher}")
        print(f"Received message: {message}")
        if message == "exit":
            print("Connection closed by the sender.")
            break
def chatting(socket, shared_key):
    receiveThread = threading.Thread(target=receive_message, args=(socket, shared_key))
    receiveThread.start()
    while True:
        message = input()
        send_message(socket, shared_key, message)
        if message == "exit":
            print("closing connection")
            receiveThread.join()
            break
    socket.close()


if __name__ == "__main__":
    host = "localhost"
    port = 12345
    keyLevel = 0
    socket = initiate_connection(host, port)
    shared_key = ecdh_key_exchange(socket, keyLevel)
    chatting(socket, shared_key)

        

    
