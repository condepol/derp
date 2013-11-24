#!/usr/bin/env python2.7
# coding: utf-8

# if len(data) is not even, a null byte will be added.

import sys

def unpack(data):
  r = ''
  for i in data.decode('utf-8'):
    z=ord(i)
    r += chr((z>>8)%256)
    r += chr((z)%256)
  return r

if __name__ == "__main__":
  if len(sys.argv) == 1:
    data = sys.stdin.read()
  else:
    with open(sys.argv[1]) as ofi:
      data = ofi.read()
      ofi.close()
  sys.stdout.write(unpack(data))
