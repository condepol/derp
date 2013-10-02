#!/usr/bin/env python2.7
# coding: utf-8

import sys

dico = {
  "A" : """
00100
01010
11111
10001
10001""",
  "B" : """
11100
10010
11100
10010
11100""",
  "C" : """
01111
10000
10000
10000
01111""",
  "D" : """
11100
10010
10010
10010
11100""",
  "E" : """
11111
10000
11100
10000
11111""",
  "F" : """
11111
10000
11100
10000
10000""",
  "G" : """
01110
10000
10011
10001
01110""",
  "H" : """
10001
10001
11111
10001
10001""",
  "I" : """
01110
00100
00100
00100
01110""",
  "J" : """
00111
00010
00010
10010
01100""",
  "K" : """
10010
10100
11000
10100
10010""",
  "L" : """
10000
10000
10000
10000
11111""",
  "M" : """
10001
11011
10101
10001
10001""",
  "N" : """
10001
11001
10101
10011
10001""",
  "O" : """
11100
10010
11100
10000
10000""",
  "P" : """
11100
10010
11100
10000
10000""",
  "Q" : """
01110
10001
10001
10010
01101""",
  "R" : """
11100
10010
11100
10010
10001""",
  "S" : """
01111
10000
01110
00001
11110""",
  "T" : """
11111
00100
00100
00100
00100""",
  "U" : """
10001
10001
10001
10001
01110""",
  "V" : """
10001
10001
01010
01010
00100""",
  "W" : """
10101
10101
10101
10101
01010""",
  "X" : """
10001
01010
00100
01010
10001""",
  "Y" : """
10001
01010
00100
00100
00100""",
  "Z" : """
11111
00010
00100
01000
11111""",
  " " : """00000"""}

print ' '.join([''.join([chr(int('10'+u,2)) for u in dico[letter].strip().splitlines()]) for letter in ' '.join(sys.argv[1:]).upper()])
