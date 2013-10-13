#!/usr/bin/env python2.7
# coding: utf-8
import sys
import time
import struct
import binascii

def iscool(c):
  return (0x1f<c and c<0x7f)
def issupercool(b):
  return (sum(1*(ord('A')<j and j<ord('z')) for j in b) == len(b))

def safe(d):
  r = ''
  for i in d:
    if iscool(ord(i)):
      r += ' '+i
    else:
      r += binascii.hexlify(i)
  return r

if len(sys.argv) == 1:
  data = sys.stdin.read(5)
  while len(data) == 5:
    print safe(data[:4]),':',time.ctime(struct.unpack('>I',data[:4])[0])
    data = sys.stdin.read(5)

else:
  t = time.time()
  if sys.argv[1] == "now":
    print(time.ctime(t))
    print(struct.pack('>I',t))
  elif sys.argv[1] == "next":
    t = time.time()
    # FUCKING BRUTEFORCE I HAVE NO BRAIN
    while not issupercool([ord(i) for i in struct.pack('>I',t)]):
      t += 1
    print(time.ctime(t))
    print(struct.pack('>I',t))
      
    
