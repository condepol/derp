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

def s(x):
  if x % 0x80 > 0x20: return ' '+chr(x)
  return '{:02x}'.format(x)

def hash_password(password):
  A=1345345333
  add=7
  B=0x12345671
  i = 0
  for letter in password:
    # skip space in password
    if letter not in [ord(' '),ord('\t')]:
      bits = (A & 63)
      factor = bits + add
      key = letter * factor
      xor = (key + (A<<8)) % (1<<32)
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
  print("{:08x}{:08x}".format(*hash_password(i)))
