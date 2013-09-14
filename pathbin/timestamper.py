#!/usr/bin/env python2.7
# coding: utf-8
import sys
import time
import struct
def iscool(b):
  return (sum(1*(0x1f<j and j<0x7f) for j in b) == len(b))
def issupercool(b):
  return (sum(1*(ord('A')<j and j<ord('z')) for j in b) == len(b))

if len(sys.argv) == 0:
  print(time.ctime(struct.unpack('>I',sys.stdin.read(4))[0]))
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
      
    
