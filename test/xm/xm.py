#!/usr/bin/env python3

import sys
import struct

def unpacker(names,data):
  format = ''.join(name[1] for name in names)
  objects = struct.unpack(format,data)
  props = {}
  for i in range(len(objects)):
    props[names[i][0]] = objects[i]
  return props

class Instrument_Header:
  def __init__(self,parent,instrument_index,offset):
    self.parent = parent
    self.instrument_index = instrument_index
    self.offset = offset

class Sample:
  def __init__(self,parent,sample_index,offset):
    self.parent = parent
    self.sample_index = sample_index
    self.offset = offset

class Pattern:
  def __init__(self,parent,pattern_index,offset):
    self.parent = parent
    self.pattern_index = pattern_index
    self.offset = offset

class XM_Header:
  def __init__(self,parent):
    self.parent = parent
    self.offset = 0
    self.elements = [
      ['ID text','17s'],
      ['Module name','20s'],
      ['0x1A','B'],
      ['Tracker name','20s'],
      ['Version number','H'],
      ['Header size','I'],
      ['Song length','H'],
      ['Restart position','H'],
      ['Number of channels','H'],
      ['Number of patterns','H'],
      ['Number of instruments','H'],
      ['Flags','H'],
      ['Default tempo','H'],
      ['Default BPM','H'],
    ]
    self.length = struct.calcsize(''.join([x[1] for x in self.elements]))
    data = self.parent.get(self.offset,self.length)
    self.props = unpacker(self.elements,data)
    self.elements.append(['Pattern order table','{:d}B'.format(self.props['Song length'])])
    self.props['Pattern order table'] = struct.unpack(
      self.elements[-1][1],
      self.parent.get(
        self.offset + self.length,
        self.props['Song length'],
      )
    )

  def table(self):
    return ((i[0],i[1],self.props[i[0]]) for i in self.elements)

  def __str__(self):
    return '\n'.join([self.table()])

class XM:
  def __init__(self,filename):
    self.filename = filename
    self.fileopen = False
    self.header = XM_Header(self)

  def get(self,offset,length):
    if not self.fileopen:
      self.openfile()
    self.file.seek(offset)
    return self.file.read(length)

  def openfile(self):
    self.file = open(filename,'rb')
    self.fileopen = True

  def close(self):
    if self.fileopen:
      self.file.close()

  def __str__(self):
    return '\n'.join([
      'XM file «{}»'.format(self.filename),
      '\n'.join([
        '  {:30s} {:4s} {}'.format(*line) for line in self.header.table()
      ])
    ])

if __name__ == '__main__':
  if len(sys.argv) == 1:
    filenames = [z.strip() for z in sys.stdin.readlines() if len(z.strip()) != 0]
  else:
    filenames = sys.argv[1:]

  for filename in filenames:
    xm = XM(filename)
    xm.close()
    print(xm)
