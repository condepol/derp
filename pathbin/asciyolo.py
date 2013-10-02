#!/usr/bin/env python2.7
# coding: utf-8

import sys
import string
print string.replace(string.replace("\n".join([bin(ord(i))[2:] for i in ''.join(sys.argv[1:])]),'0',' '),'1','█')

