#!/usr/bin/env python3
import sys
import codecs
import struct
def crack(hash,charset):
  assert(len(hash) == 16)
  A,B = struct.unpack('>II',codecs.decode(hash,'hex'))
  print('{:08x}{:08x}'.format(A,B))
if __name__ == '__main__':
  charset = bytes(range(ord('A'),ord('Z')))
  crack('606707d16665cd42',charset)
