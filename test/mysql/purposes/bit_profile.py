#!/usr/bin/env python3
# coding: utf-8
import struct
def s(x): return chr(x) if x % 0x80 > 0x20 else '.'
def hash_password(password):
  A,B,add=1345345333,0x12345671,7
  i = 0
  for letter in password:
    # skip space in password
    A = (A ^ (letter*((A&63)+add))+ (A<<8)) % (1<<32)
    B = (((B<<8)^A)+B) % (1<<32)
    add += letter
    i += 1
  return A & (( 1 << 31) -1), B & (( 1 << 31) -1)

def profile(gen):
  bits = [0]*64
  for a,b in gen:
    for i in range(32):
      bits[i]     += (a>>(31-i))&1
      bits[i+32]  += (b>>(31-i))&1
  print(' '.join(['{:3x}'.format(i) for i in bits[:32]]))
  print(' '.join(['{:3x}'.format(i) for i in bits[32:]]))

if __name__ == '__main__':
  profile(hash_password(struct.pack('B',b)) for b in range(256))
  #profile(hash_password(struct.pack('H',b)) for b in range(65536))
  #one_byte = [0, 256, 254, 2, 0, 0, 0, 0, 0, 254, 256, 2, 0, 254, 254, 254, 0, 47, 117, 139, 135, 125, 129, 129, 127, 128, 128, 129, 127, 129, 0, 256, 0, 254, 254, 2, 0, 254, 256, 0, 0, 254, 256, 2, 0, 256, 0, 254, 209, 141, 120, 139, 121, 130, 129, 126, 127, 130, 129, 129, 127, 127, 254, 2]
  #two_bytes = [0, 1020, 1016, 4, 0, 64516, 64516, 64516, 0, 53535, 36215, 34611, 34402, 34815, 32744, 32795, 32233, 32530, 33016, 32674, 32771, 32708, 32775, 32815, 32637, 32512, 32254, 31745, 30719, 36865, 24320, 49407, 0, 65532, 1016, 4, 64516, 1016, 1020, 52349, 12167, 20744, 42811, 23615, 14560, 34428, 35772, 37310, 34269, 29461, 34445, 32786, 32768, 32728, 32647, 32797, 32639, 32998, 33282, 33793, 34814, 28797, 41212, 48391]
  #passwd = 'whatthehellꊀ𐌈ܗꢋ'
  #print('{} : {:08x}{:08x}'.format(passwd,*hash_password(bytes(passwd,'utf8'))))
  #print(' '.join(['{:d}'.format(i) for i in one_byte]))
  #print(' '.join(['{:d}'.format(i) for i in two_bytes]))
  #profile(hash_password(struct.pack('I',b)) for b in range(1<<32))
