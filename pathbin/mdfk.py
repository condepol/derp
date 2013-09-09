#!/usr/bin/python2.7
# -*- coding: utf-8 -*-
# madafaka.

from hashlib import *
from binascii import *

def mdd(x):
    return md5(x).hexdigest()

def shh(x):
    return sha1(x).hexdigest()

def shg(x):
    return sha256(x).hexdigest()

code = raw_input("Computer keycode ? ")

code = code * int(code[0])
lisf = []
for i in code:
    if int(i)%3==0:
        lisf.append(mdd)
    elif int(i)%3==1:
        lisf.append(shh)
    elif int(i)%3==2:
        lisf.append(shg)


key = raw_input("Key ? ")
for f in lisf:
    key = b2a_uu(f(key)[:44])
print key
