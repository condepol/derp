#!/usr/bin/env python3
# coding: utf-8

from Crypto.Cipher import ARC4

key = bytes('ㄙ𐰳ꏒㄊ','utf8')
msg = bytes('𐠕𐊸ࡂꨃ','utf8')
cipher = ARC4.new(key)
for x in key,msg,cipher.encrypt(msg):
  print(''.join(['{:02x}'.format(c) for c in x]))
