#!/usr/bin/env python2.7
# coding: utf-8

# if len(data) is not even, a null byte will be added.

import sys

def pack(data):
  if (len(data)%2) == 1:
    data += chr(0x00)
  r = ''
  for i in xrange(0,len(data),2):
    r += unichr((1<<16)+(ord(data[i])<<8)+ord(data[i+1]))
  return r

if __name__ == "__main__":
  if len(sys.argv) == 1:
    data = sys.stdin.read()
  else:
    with open(sys.argv[1]) as ofi:
      data = ofi.read()
      ofi.close()
  sys.stdout.write(pack(data))
