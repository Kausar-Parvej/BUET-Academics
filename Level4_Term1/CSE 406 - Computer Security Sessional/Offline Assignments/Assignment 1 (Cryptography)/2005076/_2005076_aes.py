import random
import string
import copy
import codecs
import time

from BitVector import *


"""Tables"""

Sbox = (
    0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,
    0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0,
    0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
    0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,
    0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,
    0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
    0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,
    0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,
    0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
    0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,
    0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
    0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
    0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,
    0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,
    0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
    0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16,
)


InvSbox = (
    0x52, 0x09, 0x6A, 0xD5, 0x30, 0x36, 0xA5, 0x38, 0xBF, 0x40, 0xA3, 0x9E, 0x81, 0xF3, 0xD7, 0xFB,
    0x7C, 0xE3, 0x39, 0x82, 0x9B, 0x2F, 0xFF, 0x87, 0x34, 0x8E, 0x43, 0x44, 0xC4, 0xDE, 0xE9, 0xCB,
    0x54, 0x7B, 0x94, 0x32, 0xA6, 0xC2, 0x23, 0x3D, 0xEE, 0x4C, 0x95, 0x0B, 0x42, 0xFA, 0xC3, 0x4E,
    0x08, 0x2E, 0xA1, 0x66, 0x28, 0xD9, 0x24, 0xB2, 0x76, 0x5B, 0xA2, 0x49, 0x6D, 0x8B, 0xD1, 0x25,
    0x72, 0xF8, 0xF6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xD4, 0xA4, 0x5C, 0xCC, 0x5D, 0x65, 0xB6, 0x92,
    0x6C, 0x70, 0x48, 0x50, 0xFD, 0xED, 0xB9, 0xDA, 0x5E, 0x15, 0x46, 0x57, 0xA7, 0x8D, 0x9D, 0x84,
    0x90, 0xD8, 0xAB, 0x00, 0x8C, 0xBC, 0xD3, 0x0A, 0xF7, 0xE4, 0x58, 0x05, 0xB8, 0xB3, 0x45, 0x06,
    0xD0, 0x2C, 0x1E, 0x8F, 0xCA, 0x3F, 0x0F, 0x02, 0xC1, 0xAF, 0xBD, 0x03, 0x01, 0x13, 0x8A, 0x6B,
    0x3A, 0x91, 0x11, 0x41, 0x4F, 0x67, 0xDC, 0xEA, 0x97, 0xF2, 0xCF, 0xCE, 0xF0, 0xB4, 0xE6, 0x73,
    0x96, 0xAC, 0x74, 0x22, 0xE7, 0xAD, 0x35, 0x85, 0xE2, 0xF9, 0x37, 0xE8, 0x1C, 0x75, 0xDF, 0x6E,
    0x47, 0xF1, 0x1A, 0x71, 0x1D, 0x29, 0xC5, 0x89, 0x6F, 0xB7, 0x62, 0x0E, 0xAA, 0x18, 0xBE, 0x1B,
    0xFC, 0x56, 0x3E, 0x4B, 0xC6, 0xD2, 0x79, 0x20, 0x9A, 0xDB, 0xC0, 0xFE, 0x78, 0xCD, 0x5A, 0xF4,
    0x1F, 0xDD, 0xA8, 0x33, 0x88, 0x07, 0xC7, 0x31, 0xB1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xEC, 0x5F,
    0x60, 0x51, 0x7F, 0xA9, 0x19, 0xB5, 0x4A, 0x0D, 0x2D, 0xE5, 0x7A, 0x9F, 0x93, 0xC9, 0x9C, 0xEF,
    0xA0, 0xE0, 0x3B, 0x4D, 0xAE, 0x2A, 0xF5, 0xB0, 0xC8, 0xEB, 0xBB, 0x3C, 0x83, 0x53, 0x99, 0x61,
    0x17, 0x2B, 0x04, 0x7E, 0xBA, 0x77, 0xD6, 0x26, 0xE1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0C, 0x7D,
)


Mixer = [
    [BitVector(hexstring="02"), BitVector(hexstring="03"), BitVector(hexstring="01"), BitVector(hexstring="01")],
    [BitVector(hexstring="01"), BitVector(hexstring="02"), BitVector(hexstring="03"), BitVector(hexstring="01")],
    [BitVector(hexstring="01"), BitVector(hexstring="01"), BitVector(hexstring="02"), BitVector(hexstring="03")],
    [BitVector(hexstring="03"), BitVector(hexstring="01"), BitVector(hexstring="01"), BitVector(hexstring="02")]
]


InvMixer = [
    [BitVector(hexstring="0E"), BitVector(hexstring="0B"), BitVector(hexstring="0D"), BitVector(hexstring="09")],
    [BitVector(hexstring="09"), BitVector(hexstring="0E"), BitVector(hexstring="0B"), BitVector(hexstring="0D")],
    [BitVector(hexstring="0D"), BitVector(hexstring="09"), BitVector(hexstring="0E"), BitVector(hexstring="0B")],
    [BitVector(hexstring="0B"), BitVector(hexstring="0D"), BitVector(hexstring="09"), BitVector(hexstring="0E")]
]


keyLength = 128
keyRounds = {128 : 10, 192 : 12, 256 : 14}
AES_modulus = BitVector(bitstring='100011011')


padded_textHexVec = []
unpadded_textHexVector = []


def getIV(keyLength):
    all_chars = string.ascii_letters + string.digits + string.punctuation
    return ''.join(random.choice(all_chars) for _ in range(keyLength//8))

def printMatrix(matrix):
    for i in range(4):
        for j in range(len(matrix[i])):
            print(hex(matrix[i][j]), end=" ")
        print()
    print()

def getHex(hex_string):             #4e6f7720697320 -> 4e 6f 77 20 69 73 20
    str = ""
    for i in range(0, len(hex_string), 2):
        str += hex_string[i:i + 2] + " "
    return str



#
def matrixToVector(matrix):         # [1,2], [3,4], [5,6] -> [1,3,5,2,4,6]
    vector = []
    for i in range(len(matrix[0])):
        for j in range(len(matrix)):
            vector.append(matrix[j][i])
    return vector


def stringToHexVector(s):  # "hello\n" -> ["68", "65", "6c", "6c", "6f", "0a"]
    hex_vector = []
    for ch in s:
        hex_num = hex(ord(ch))[2:]
        hex_vector.append(hex_num.zfill(2))  # pad with 0 if needed
    return hex_vector



def hexVectorToHexString(hex_vector):       ###
    retr = []
    for hex_num in hex_vector:
        retr.append(hex_num.get_bitvector_in_hex())
    return retr

def hexVectorToHexMatrix(hex_vector):        # [1,2,3,4,5,6,7,8] -> [[1,5],[2,6],[3,7],[4,8]] (A 4-row matrix) in bits
    hex_matrix = []
    for i in range(4):
        vector = []
        for j in range(i, len(hex_vector), 4):
            vector.append(BitVector(hexstring=hex_vector[j]))
        hex_matrix.append(vector)

    return hex_matrix




#
def hexMatVecToHexStrVec(cipherHexMatVec):      #[["61", "62"],["63", "64"]], [["65", "66"],["67", "68"]] -> ["61626364", "65666768"]
    hexStrVec = []
    for cipherHexMat in cipherHexMatVec:
        cipher_blockVec = matrixToVector(cipherHexMat)
        strBlock = hexVectorToHexString(cipher_blockVec)
        strBlock = ''.join(strBlock)
        hexStrVec.append(strBlock)  
    return hexStrVec

def hexStrVecToHexMatVec(hexStrVec):        # ["61626364", "65666768"] -> [["61", "62"],["63", "64"]], [["65", "66"],["67", "68"]]
    hexMatVec = []
    for hexStr in hexStrVec:
        hexVec = []
        for i in range(0, len(hexStr), 2):
            hexVec.append(hexStr[i:i + 2])
        hexMat = hexVectorToHexMatrix(hexVec)
        hexMatVec.append(hexMat)
    return hexMatVec


def hexVecToAsciVec(hexVec):        # ["61", "62"],["63", "64"] -> ["a", "b"],["c", "d"]
    asciiVec = []
    for hexNum in hexVec:
        asciiVec.append(hexNum.get_bitvector_in_ascii())
    return asciiVec

def hexToAscii(hexStr):         # "61626364" -> "abcd"
    binaryStr = codecs.decode(hexStr, 'hex')
    asciiStr = str(binaryStr, "ISO-8859-1")
    return asciiStr


#
def resizeKey(key):
    keyBytes = keyLength // 8
    key = key[:keyBytes]
    key = key.ljust(keyBytes, '%')
    return key;


def addPadding(textHexVec):   #PKCS#7
    block_size = keyLength // 8
    text_size = len(textHexVec)
    padding_size = text_size % block_size

    if padding_size == 0:
        for _ in range(block_size):
            textHexVec.append('00')
    else:
        padding_size = block_size - padding_size
        pad = hex(padding_size)[2:]
        while len(pad) < 2:
            pad = '0' + pad
        
        for _ in range(padding_size):
            textHexVec.append(pad)

    return textHexVec


def removePadding(textHexVector):   #PKCS#7
    block_size = keyLength // 8
    text_size = len(textHexVector)
    padding_count = int(textHexVector[text_size-1])

    if padding_count == 0:
        padding_count = block_size
    textHexVector = textHexVector[:text_size - padding_count]
    return textHexVector




    
##
def subByteVec(vector):
    subbed_vector = []
    for item in vector:
        subbed_vector.append(BitVector(intVal=Sbox[item.intValue()], size=8))
    return subbed_vector

def subByteMAtix(matrix):
    subbed_matrix = matrix[:][:]
    for i in range(len(subbed_matrix)):
        subbed_matrix[i] = subByteVec(matrix[i])
    return subbed_matrix

def invSubByteVec(vector):
    invSub_vector = []
    for item in vector:
        invSub_vector.append(BitVector(intVal=InvSbox[item.intValue()], size=8))
    return invSub_vector

def invSubByteMatrix(matrix):
    invSub_matrix = matrix[:][:]
    for i in range(len(invSub_matrix)):
        invSub_matrix[i] = invSubByteVec(matrix[i])
    return invSub_matrix



def shiftVector(vector, shift):
    shifted_vector = vector[:]
    ln = len(vector)
    for i in range(0, ln):
        shifted_vector[i] = vector[(i + shift + ln) % ln]
    return shifted_vector

def shiftMatrix(matrix, leftShift=True):
    for i in range(4):
        if leftShift:
            matrix[i] = shiftVector(matrix[i], i)
        else:
            matrix[i] = shiftVector(matrix[i], -i)
    return matrix



def xorVector(vector1, vector2):
    xor_vector = []
    for i in range(len(vector1)):
        xor_vector.append(vector1[i] ^ vector2[i])
    return xor_vector

def xorMatrix(matrix1, matrix2):
    xor_matrix = matrix1[:][:]
    for i in range(len(xor_matrix)):
        xor_matrix[i] = xorVector(matrix1[i], matrix2[i])
    return xor_matrix






##
def g(vector, round_constant):
    returned_vector = shiftVector(vector, 1)
    returned_vector = subByteVec(returned_vector)
    k0 = BitVector(hexstring="00")
    returned_vector = xorVector(returned_vector, [round_constant, k0, k0, k0])
    return returned_vector


def keyExpansion(key):
    column_num = keyLength // (4 * 8)
    keys = []
    key = resizeKey(key)
    key = stringToHexVector(key)
    
    keys.append(hexVectorToHexMatrix(key))
    #print(keys)

    round_constant = BitVector(hexstring="01")
    for round in range(1, keyRounds[keyLength] + 1):
        last_vector = []
        for i in range(4):
            last_vector.append(keys[round - 1][i][column_num - 1])      #selects the last column of the previous round key
        last_vector = g(last_vector, round_constant)
        current_key = copy.deepcopy(keys[round - 1])
        for j in range(column_num):
            for i in range(4):
                if j == 0:
                    current_key[i][j] = current_key[i][j] ^ last_vector[i]
                else:
                    current_key[i][j] = current_key[i][j] ^ current_key[i][j - 1]
        keys.append(current_key)

        k2 = BitVector(hexstring="02")
        round_constant = k2.gf_multiply_modular(round_constant, AES_modulus, 8)  # round_constant = round_constant * 2 mod AES_modulus

    return keys


def mixColumns(matrix):
    column_num = keyLength // (4*8)
    mixed_matrix = []
    for i in range(4):
        mixed_matrix.append([BitVector(intVal=0, size=8) for _ in range(column_num)])

    for i in range(4):
        for j in range(column_num):
            for k in range(4):
                mixed_matrix[i][j] ^= Mixer[i][k].gf_multiply_modular(matrix[k][j], AES_modulus, 8)
    return mixed_matrix


def invMixColumns(matrix):
    column_num = keyLength // (4*8)
    mixed_matrix = []
    for i in range(4):
        mixed_matrix.append([BitVector(intVal=0, size=8) for _ in range(column_num)])

    for i in range(4):
        for j in range(column_num):
            for k in range(4):
                mixed_matrix[i][j] ^= InvMixer[i][k].gf_multiply_modular(matrix[k][j], AES_modulus, 8)
    return mixed_matrix





###
def encryptBlock(textHexVec, iv, keys):
    text_matrix = hexVectorToHexMatrix(textHexVec)
    text_matrix = xorMatrix(text_matrix, iv)
    text_matrix = xorMatrix(text_matrix, keys[0])

    for round in range(1, keyRounds[keyLength]+1):
        text_matrix = subByteMAtix(text_matrix)
        text_matrix = shiftMatrix(text_matrix, True)
        if round != keyRounds[keyLength]:
            text_matrix = mixColumns(text_matrix)
        text_matrix = xorMatrix(text_matrix, keys[round])

    return text_matrix


def encryptText(textHexVec, iv, keys):
    textHexVec = addPadding(textHexVec)
    global padded_textHexVec
    padded_textHexVec = textHexVec[:]
    blockSize = keyLength // 8
    textLength = len(textHexVec)
    iv = hexVectorToHexMatrix(stringToHexVector(iv))

    cipherHexMatVec = []   #vector of martices
    for i in range(0, textLength, blockSize):
        text_matrix = encryptBlock(textHexVec[i:i + blockSize], iv, keys)
        iv = text_matrix
        cipherHexMatVec.append(text_matrix)
    return cipherHexMatVec




def decryptBlock(cipherHexMat, iv, keys):
    text_matrix = xorMatrix(cipherHexMat, keys[0])
    for round in range(1, keyRounds[keyLength]+1):
        text_matrix = invSubByteMatrix(text_matrix)
        text_matrix = shiftMatrix(text_matrix, False)
        text_matrix = xorMatrix(text_matrix, keys[round])
        if round != keyRounds[keyLength]:
            text_matrix = invMixColumns(text_matrix)
    
    text_matrix = xorMatrix(text_matrix, iv)
    text_matrix = matrixToVector(text_matrix)
    return text_matrix


def decryptText(cipherHexMatVec, iv, keys):
    decrypted = []
    iv = hexVectorToHexMatrix(stringToHexVector(iv))
    keys.reverse()
    for cipherHexMat in cipherHexMatVec:
        text_matrix = decryptBlock(cipherHexMat, iv, keys)
        iv = cipherHexMat
        decrypted.extend(text_matrix)
    
    keys.reverse()
    return decrypted
    






####
def encrypt_AES(text, iv, key):
    key = str(key)
    start_time = time.time()
    textHexVec = stringToHexVector(text)
    keys = keyExpansion(key)
    key_scheduleTime = time.time() - start_time

    start_time = time.time()
    cipherHexMatVec = encryptText(textHexVec, iv, keys)
    cipherHexStrVec = hexMatVecToHexStrVec(cipherHexMatVec)
    encryption_time = time.time() - start_time

    return cipherHexStrVec, key_scheduleTime, encryption_time


def decrypt_AES(hexStrVec, iv, key):
    keys = keyExpansion(key)

    strt_time = time.time()
    hexMatVector = hexStrVecToHexMatVec(hexStrVec)
    decrypted_hexVec = decryptText(hexMatVector, iv, keys)

    global unpadded_textHexVector
    unpadded_textHexVector = decrypted_hexVec[:]
    decrypted_hexVec = removePadding(decrypted_hexVec)
    decrypt_time = time.time() - strt_time

    return decrypted_hexVec, decrypt_time





#######
def main():
    print("\nin AES.py\n")

    global keyLength
    keyLength = 128
    key = "BUET CSE20 Batch!"
    text = "We need Picnic!"
    iv = getIV(keyLength)

    cipher_hexStrVec, key_Time, encryption_time = encrypt_AES(text, iv, key)
    decipher_hexVector, decrypt_time = decrypt_AES(cipher_hexStrVec, iv, key)


    print("Key: ")
    print("In ASCII: ", key)
    print("In Hex: ", getHex(''.join(stringToHexVector(key))))
    print("")

    print("Plain Text: ")
    print("In ASCII: ", text)
    print("In Hex: ", getHex(''.join(stringToHexVector(text))))
    print("In ASCII (after padding): ", hexToAscii(''.join(padded_textHexVec)))
    print("In Hex (after padding): ", getHex(''.join(padded_textHexVec)))
    print("")

    #print("IV: ", iv)
    print("")

    print("Ciphered Text:")
    print("In Hex: ", getHex(''.join(cipher_hexStrVec)))
    print("In ASCII: ", hexToAscii(''.join(cipher_hexStrVec)))
    print("")

    print("Decrypted Text")
    print("Before Unpadding:")
    print("In Hex: ", getHex(''.join(hexVectorToHexString(unpadded_textHexVector))))
    print("In ASCII: ", ''.join(hexVecToAsciVec(unpadded_textHexVector)))

    print("After Unpadding:")
    #print(unpadded_textHexVector)
    print("In Hex: ", getHex(''.join(hexVectorToHexString(decipher_hexVector))))
    print("In ASCII: ", ''.join(hexVecToAsciVec(decipher_hexVector)))
    print("\n")


    print("Execution Time Details: ")
    print("Key Schedule Time : ",round(key_Time*1000,7),"ms")
    print("Encryption Time : ",round(encryption_time*1000,7),"ms")
    print("Decryption Time : ",round(decrypt_time*1000,7),"ms")
    print("\n")



#main()