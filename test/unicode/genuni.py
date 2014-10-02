#!/usr/bin/env python3
# coding: utf8

import unicodedata
for i in range(0x20000):
  try:
    print('U+{:04X} {} {}'.format(i,unicodedata.name(chr(i)),chr(i)))
  except UnicodeError:
    pass
  except ValueError:
    pass
