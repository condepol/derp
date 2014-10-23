#!/usr/bin/env python3
# coding: utf-8

import codecs

key = bytes('ㄙ𐰳ꏒㄊ','utf8')
msg = bytes('𐠕𐊸ࡂꨃ','utf8')
cipher = bytes()

# 1 init buffer
i = 0
j = 0
S = bytearray(range(256))
for i in range(256):
  j = ( j + S[i] + key[i%len(key)] ) % 256
  S[i], S[j] = S[j], S[i]

# 2 generate keystream
i = 0
j = 0
for c in msg:
  i = ( i + 1 ) % 256
  j = ( j + S[i] ) % 256
  S[i], S[j] = S[j], S[i]
  cipher += bytes([c ^ S[(S[i]+S[j])%256]])
print(codecs.encode(key,'hex'))
print(codecs.encode(msg,'hex'))
print(codecs.encode(cipher,'hex'))
