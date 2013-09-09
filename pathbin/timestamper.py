#!/usr/bin/env python2.7
# coding: utf-8
import sys
import time
import struct
print(time.ctime(struct.unpack('>I',sys.stdin.read(4))[0]))
