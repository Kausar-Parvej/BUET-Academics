import random
from BitVector import *

def getPrime(bits):
    p = BitVector(intVal = 0)
    check = 0
    while check < 0.999:
        p = p.gen_random_bits(bits)  
        check = p.test_for_primality()
    return p

def lift(a,b,p):
    if(b==0):
        return 1
    k = lift(a,b>>1,p)
    k*=k
    k%=p
    if b%2==1:
        k*=a
        k%=p
    return k

def ei(n,p):
    return lift(n,p-2,p)

def ed(a,b,p):
    return (a*ei(b,p))%p

def ep(a,b,p):
    return (a+b)%p

def es(a,b,p):
    return (a+(p-b%p))%p

def em(a,b,p):
    return (a*b)%p


def getElipticCurve(bits, p, P):
    a = random.randint(-(1<<bits),(1<<bits))
    b = random.randint(0,10)
    u = 0
    while u==0:
        b = (P.y*P.y-P.x*P.x*P.x-a*P.x)%p
        if (4*a*a*a+27*b*b)%p==0 or a==0 or b==0:
            a = random.randint(-(1<<bits),(1<<bits))
        else:
            u = 1
    return EllipticCurve(p,a,b)

def getPoint(bits):
    x = random.randint(1,(1<<bits))
    y = random.randint(1,(1<<bits))
    while x==0 or y==0:
        x = random.randint(1,(1<<bits))
        y = random.randint(1,(1<<bits))
    return Point(x,y)

class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y
    
    def __str__(self):
        return f"Point({self.x}, {self.y})"


class EllipticCurve:
    def __init__(self, p, a, b):
        self.p = p
        self.a = a
        self.b = b
    
    def add(self,P,Q):
        s = 0
        if P.x==Q.x and P.y==Q.y:
            s = ed(ep(em(3,em(P.x,P.x,self.p),self.p),self.a,self.p),em(2,P.y,self.p),self.p)
        else:
            s = ed(es(Q.y,P.y,self.p),es(Q.x,P.x,self.p),self.p)
        x3 = es(em(s,s,self.p),ep(P.x,Q.x,self.p),self.p)
        y3 = es(em(s,es(P.x,x3,self.p),self.p),P.y,self.p)
        return Point(x3,y3)
    
    def mul(self,P,m):
        if m==1:
            return P
        Q = self.mul(P,m>>1)
        Q = self.add(Q,Q)
        if m%2==1:
            Q = self.add(Q,P)
        return Q
    
def binaryStringToAscii(binaryString):
    chunks = [binaryString[i:i+8] for i in range(0, len(binaryString), 8)]
    asciiString = ''.join(chr(int(chunk, 2)) for chunk in chunks)
    return asciiString

def intToString(keyInt,AES_LEN):
    keyBinary = bin(keyInt)[2:]
    while len(keyBinary)<AES_LEN:
        keyBinary+='1'
    keyString = binaryStringToAscii(keyBinary)
    return keyString

def main():
    bits=128
    p = getPrime(bits).int_val()
    P = getPoint(bits)
    E = getElipticCurve(bits,p,P)
    # p = 17
    # P = Point(5,1)
    # E = EllipticCurve(p,2,2)
    for i in range(1,100):
        print(i,": ",E.mul(P,i))

    return 

main()