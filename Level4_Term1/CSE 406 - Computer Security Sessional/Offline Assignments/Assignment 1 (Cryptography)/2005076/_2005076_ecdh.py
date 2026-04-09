import random
from sympy import isprime
import time

KEY_SIZE = [128, 192, 256]     #bits

class EC_point:
    def __init__(self, x_coord, y_coord):
        self.x = x_coord
        self.y = y_coord
    
    def __str__(self):
        return f"({self.x}, {self.y})"
    


class ECDH_cipher:
    def __init__(self, keyLevel=0, _curve=None):
        if _curve is None:
            self.bitlength = KEY_SIZE[keyLevel]
            self.curve = self._init_curve()
        else:
            self.curve = _curve
        self.a = self.curve["a"]
        self.b = self.curve["b"]
        self.p = self.curve["p"]
        self.base = EC_point(self.curve["gx"], self.curve["gy"])



    def _init_curve(self) -> dict:
        p = self._generate_prime(self.bitlength)
        while True:
            a = random.randint(1, p - 1)
            gx = random.randint(1, p - 1)
            gy = random.randint(1, p - 1)
            b = (gy**2 - gx**3 - a * gx) % p
            if (4 * a**3 + 27 * b**2) % p != 0:
                return {"a": a, "b": b, "p": p, "gx": gx, "gy": gy}
            
    
    def _generate_prime(self, bits):
        while True:
            candidate = random.randint(2**(bits - 1), 2**bits - 1)
            if isprime(candidate):
                return candidate
    
    def display_curve(self):
        print(f"Curve: y^2 = x^3 + {self.a}x + {self.b} mod {self.p}")
        print(f"Base Point: {self.base}")



    def ec_add(self, P: EC_point, Q: EC_point):
        if P.x == Q.x and P.y == Q.y:
            s = ((3 * P.x**2 + self.a) * pow(2 * P.y, -1, self.p)) % self.p
        else:
            s = ((Q.y - P.y) * pow(Q.x - P.x, -1, self.p)) % self.p
        rx = (s**2 - P.x - Q.x) % self.p
        ry = (s * (P.x - rx) - P.y) % self.p
        return EC_point(rx, ry)
    

    def ec_scalar_mult(self, scalar: int, point: EC_point):
        if scalar == 1:
            return point
        if scalar % 2 == 0:
            return self.ec_scalar_mult(scalar // 2, self.ec_add(point, point))
        else:
            return self.ec_add(point, self.ec_scalar_mult(scalar - 1, point))
        

    
    def generate_private(self):
        return random.randint(1, self.p - 1)
    



def time_operations(ecc: ECDH_cipher):
    priv_a = 2**ecc.bitlength - 1
    priv_b = 2**ecc.bitlength - 2

    t0 = time.time()
    pub_a = ecc.ec_scalar_mult(priv_a, ecc.base)
    t1 = time.time()

    t2 = time.time()
    pub_b = ecc.ec_scalar_mult(priv_b, ecc.base)
    t3 = time.time()

    t4 = time.time()
    shared_a = ecc.ec_scalar_mult(priv_a, pub_b)
    t5 = time.time()
    shared_b = ecc.ec_scalar_mult(priv_b, pub_a)

    print(f"Alice private and shared keys: {priv_a}, {shared_a.x}")
    print(f"Bob private and shared keys: {priv_b}, {shared_b.x}")

    return [(t1 - t0) * 1000, (t3 - t2) * 1000, (t5 - t4) * 1000]


def run():
    for key_level in range(3):
        ecc = ECDH_cipher(key_level)
        print(f"\n{ecc.bitlength}-bit ECC:")
        print("-----------------------------")
        #ecc.display_curve()
        t_pub_a, t_pub_b, t_shared = time_operations(ecc)
        
        print(f"\nAlice Public Key Time: {t_pub_a:.6f} ms")
        print(f"Bob Public Key Time:   {t_pub_b:.6f} ms")
        print(f"Shared Key Time:       {t_shared:.6f} ms")
        print("\n")

#run()

