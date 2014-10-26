#!/usr/bin/env python3
# coding: utf-8
# 
# from mysql source code, see their gplv2 license.
# 
# Generate binary hash from raw text string 
# Used for Pre-4.1 password handling
# SYNOPSIS
# hash_password()
# result       OUT store hash in this location
# password     IN  plain text password to build hash
# password_len IN  password length (password may be not null-terminated)
# 

def s(x): return chr(x) if x % 0x80 > 0x20 else '.'
def hash_password(password):
  A=1345345333
  add=7
  B=0x12345671
  i = 0
  print('\x1b[32m{:8s} \x1b[34m{:8s} \x1b[31m{:>8s} \x1b[0m{:8s}'.format('A','B','add','letter'))
  for letter in password:
    print('\x1b[32m{:08x} \x1b[34m{:08x}\x1b[31m {:8x}\x1b[0m {:6x} {}'.format(A,B,add,letter,s(letter)))
    # skip space in password
    if letter not in [ord(' '),ord('\t')]:
      bits = (A & 63)
      factor = bits + add
      key = letter * factor
      xor = (key + (A<<8)) % (1<<32)
      print('{:8x} {:17x} {:6x}'.format(bits,factor,key))
      print('{:08x} + {:6x}\n{:08x} ^ A'.format((A<<8)%(1<<32),key,xor))
      A = A ^ xor
      B = ((B<<8)^A) + B
      A = A % (1<<32)
      B = B % (1<<32)
      add += letter
      i += 1

  # Don't use sign bit (str2int) 
  return A & (( 1 << 31) -1), B & (( 1 << 31) -1)

if __name__ == '__main__':
  import sys
  if len(sys.argv) == 1:
    i = sys.stdin.buffer.read()
  else:
    i = bytes(sys.argv[1],'utf8')
  o = "{:08x}{:08x}".format(*hash_password(i))
  # whatthehell
  if o == "0a6ffbf026b9eb69":
    print('\x1b[32mOK\x1b[0m')
  else:
    print('\x1b[31mfail\x1b[0m')
  print(o)

