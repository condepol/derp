#!/usr/bin/python2.7
# -*- coding: utf-8 -*-

import getpass
import hashlib
import binascii


code = getpass.getpass('Computer keycode ? ')
code = code * int(code[0])
lisf = [[hashlib.md5,hashlib.sha1,hashlib.sha256][int(i)%3] for i in code]
key  = getpass.getpass('Key ?')
for f in lisf:
  key = binascii.b2a_uu(f(key).hexdigest()[:44])
print key,
