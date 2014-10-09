#!/usr/bin/env python3
import sys
import codecs
import struct
# hardcoded tables
table = "944626378ace9bdf"
order = [5,1,2,7,4,0,6,3]
# read mac address
mac = "08863B053A41" if len(sys.argv) == 1 else sys.argv[1]
# convert to bytes
code = codecs.decode(mac[-8:],'hex')
# add 1
code = struct.pack('>I',1+struct.unpack('>I',code)[0])
# transform to hex
code = str(codecs.encode(code,'hex'),'ascii')
# extract positions
code = [int(code[u],16) for u in order]
# extract code letters
code = [table[u] for u in code]
print(''.join(code))
