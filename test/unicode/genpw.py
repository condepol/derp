#!/usr/bin/env python3
# coding: utf-8
import sys
import random
length = int(sys.argv[1]) if len(sys.argv) > 1 else 30
pool   = int(sys.argv[2]) if len(sys.argv) > 2 else 1
dico = ''.join([
  ''.join([chr(i) for i in range(*z)])
  for z in [
    (0x41,0x5b),
    (0x20,0x7f),
    (0x120,0x200),
  ][:pool]
])
print("".join([random.choice(dico) for i in range(length)]))
