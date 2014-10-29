#!/usr/bin/env python3
def pack(*k):
  x = 0
  for i in k:
    x = (x<<8) + i
  return x


for a in range(256):
  for b in range(256):
    c = (a + b)%256
    A = (c - b)%256
    if a != A:
      print('{} != {}'.format(A,a))

a=0x74
b=0x99
c=0x22
print('{:x}'.format(pack(a,b,c)))
