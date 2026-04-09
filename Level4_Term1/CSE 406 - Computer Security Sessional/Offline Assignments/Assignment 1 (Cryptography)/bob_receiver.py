import threading
import socket
import ast

import _2005076_aes as _AES
import _2005076_ecdh


key_length = 128

def ecdh_key_exchange(b_socket):
    curve = b_socket.recv(1024).decode()
    ecdh  = _2005076_ecdh.ECDH_cipher(_curve= eval(curve))

    b_privateKey = ecdh.generate_private()
    b_publicKey = ecdh.ec_scalar_mult(b_privateKey, ecdh.base)
    b_socket.send(str(b_publicKey).encode())

    a_publicKey = b_socket.recv(1024).decode()
    a_publicKey = _2005076_ecdh.EC_point(int(a_publicKey.split(",")[0][1:]), int(a_publicKey.split(",")[1][:-1]))
    shared_key = ecdh.ec_scalar_mult(b_privateKey, a_publicKey)
    return shared_key.x


def initiate_connection(host, port):
    b_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    b_socket.bind((host, port))
    b_socket.listen()
    return b_socket


def send_message(b_socket, shared_key, message):
    IV = _AES.getIV(key_length)
    b_socket.send(IV.encode())
    cipher_msg = _AES.encrypt_AES(message, IV, shared_key)
    cipher_msg = str(cipher_msg)
    b_socket.send(cipher_msg.encode())


def receive_message(b_socket, shared_key):
    while True:
        IV = b_socket.recv(1024).decode()
        cipher_msg = b_socket.recv(1024).decode()
        cipher_tuple = ast.literal_eval(cipher_msg)
        message = _AES.decrypt_AES(cipher_tuple, IV, shared_key)
        print(f"Received message(cipher): {cipher_msg}")
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
    host = ""
    port = 12345
    socket = initiate_connection(host, port)
    a_socket, a_addr = socket.accept()
    print(f"Connected to {a_addr}")
    shared_key = ecdh_key_exchange(a_socket)
    chatting(a_socket, shared_key)

