#!/usr/bin/env python3
# coding: utf-8

import sys
import zlib

def suffix(i):
  x = '_'
  while i != 0:
    x += chr(0x20 + i % 0x5f)
    i //= 0x5f
  return x

if __name__ == '__main__':
  wa = sys.argv[1]  if len(sys.argv) > 1 else None
  wb = sys.argv[2]  if len(sys.argv) > 2 else None
  stop = False      if len(sys.argv) > 3 else True

  if wa is None:
    print('Usage : {} <word_A> [word_B]'.format(sys.argv[0]))
    sys.exit(0)

  if wb is None:
    print('crc32(«\x1b[32m{}\x1b[0m») : {:08x}'.format(wa,zlib.crc32(bytes(wa,'utf-8'))))
    sys.exit(0)

  sa = 0
  sb = 0

  da = {}
  db = {}

  step = 1<<32
  step = 155

  while True:
    na = zlib.crc32(bytes(wa+suffix(sa),'utf-8'))
    if da.get(na):
      print('crc32(«\x1b[32m{}\x1b[0m») == crc32(«\x1b[32m{}\x1b[0m») == {:08x}'.format(
        wa+suffix(sa),
        wb+suffix(da.get(na)),
        na))
      if stop:
        sys.exit(0)
    else:
      db[na] = sa

    sa += step

    nb = zlib.crc32(bytes(wb+suffix(sb),'utf-8'))
    if db.get(nb):
      print('crc32(«\x1b[32m{}\x1b[0m») == crc32(«\x1b[32m{}\x1b[0m») == {:08x}'.format(
        wa+suffix(db.get(nb)),
        wb+suffix(sb),
        nb))
      if stop:
        sys.exit(0)
    else:
      da[nb] = sb

    sb += step
