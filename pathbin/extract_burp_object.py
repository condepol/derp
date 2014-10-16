#!/usr/bin/env python3
# coding: utf-8

import sys
import codecs

with open(sys.argv[1]) as ofi: lines = ofi.readlines()
line = [i for i in lines if '<response base64="true"><![CDATA[' in i][0]
base64 = bytes(line.split('<![CDATA[')[1].split(']]><')[0],'ascii')
sys.stdout.buffer.write(codecs.decode(base64,'base64'))

