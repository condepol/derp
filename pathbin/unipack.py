#!/usr/bin/env python3
# coding: utf-8

# if len(data) is not even, a null byte will be added.

import sys,struct

def pack(data):
  if (len(data)%2) == 1: data += bytes([0])
  return ''.join([chr((1<<16)+struct.unpack('>H',data[i:i+2])[0]) for i in range(0,len(data),2)])

if __name__ == "__main__":
  if len(sys.argv) == 1:
    data = sys.stdin.buffer.read()
  else:
    with open(sys.argv[1],'rb') as ofi: data = ofi.read()
  sys.stdout.buffer.write(bytes(pack(data),'utf8'))
