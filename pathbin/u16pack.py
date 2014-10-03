#!/usr/bin/env python3
import sys
x = sys.stdin.buffer.read()
if len(x) % 2 != 0: x += bytes([0])
sys.stdout.write(str(x,'utf-16-le'))
