#!/usr/bin/env python3
# coding: utf-8
import sys
class Line:
  def __init__(self,line):
    self.values = line.strip().split(';')
    self.codepoint = int(self.values[0],16)
    self.name = self.values[1]
    self.altname = self.values[10]
    self.invalid = False
    if self.name in ['<control>']:
      self.name = self.altname
      self.altname = ''
    if self.name == self.altname: self.altname = ''
    try:
      bytes(chr(self.codepoint),'utf8')
    except:
      self.invalid = True
  def __str__(self):
    if not self.invalid:
      return 'U+{:04X} {} {}'.format(self.codepoint,self.name,chr(self.codepoint))
    else:
      return 'U+{:04X} {} {}'.format(self.codepoint,self.name,chr(0xfffd))
with open(sys.argv[1]) as o: lines = o.readlines()
for i in lines:
  z = Line(i)
  print(z)
