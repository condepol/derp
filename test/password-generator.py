#!/usr/bin/env python3
# coding: utf-8

import sys
import getpass
import hashlib

print("DO NOT USE.")

flist = [hashlib.md5,hashlib.sha1,hashlib.sha256]

def expand(k,m):
  r = bytes()
  b = str(m).encode('utf-8')
  for function_index in k*int(k[0])*7:
    b = flist[int(function_index)%len(flist)](b).digest()
    r += b
  return r

try:
  maxlen = int(sys.argv[1])
except:
  maxlen = None

print("{0}".format(str(expand(getpass.getpass("Computer keycode ?"),getpass.getpass("Passphrase ?")),'utf-16','ignore')[:maxlen]))
