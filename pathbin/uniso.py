#!/usr/bin/env python3
# coding: utf-8

import sys
i = 'utf8'    if len(sys.argv) < 2 else sys.argv[1]
o = 'iso8859' if len(sys.argv) < 3 else sys.argv[2]

sys.stdout.write(str(bytes(str(sys.stdin.buffer.read(),'utf8'),i),o))
