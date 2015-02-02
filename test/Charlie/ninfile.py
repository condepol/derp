#!/usr/bin/env python3

import struct
def unpack(spec,data):
  fmt = '<{}'.format(''.join([s[1] for s in spec]))
  o = struct.unpack(fmt,data)
  d = {}
  for i in range(len(spec))
    d[spec[i]] = o[i]
  return d

class Generic_Header:
  def __init__(self,parent):
    self.parent = parent
    self.props = {}
    
  def parse(self):
    # 0x00  ID  char[4] 
    # 0x04  Endianess           ushort  If = 0xFFFE the Magic ID must be reversed
    # 0x06  Constant            ushort  Unknown
    # 0x08  File size           uint  
    # 0x0C  Header size         ushort  Always 0x10
    # 0x0E  Number of sections  ushort  It can be 0x01, 0x02 or 0x03
    x = self.parent.read(0,0x10)
    self.props = x. #TODO
    pass
  def get_props(self):
    r = []
    r.append(['dummy',45])
    return r
  def __str__(self):
    return '\n'.join(['{:20s}{}'.format(z[0],z[1]) for z in self.get_props()])

class Master:
  def __init__(self,filename):
    self.filename = filename
    self.filesize = 0
    self.isopen = False
    self.file = None
    self.header = None
    self.props['Filename'] = self.filename

  def parse(self):
    self.header = Generic_Header(self)
    self.header.parse()

  def read(self,offset,length):
    if not self.isopen:
      self.file = open(self.filename,'rb')
      self.file.seek(0,2)
      self.filesize = self.file.tell()
      self.file.seek(0)
    assert(offset + length < self.filesize)
    if self.file.tell() != offset:
      self.file.seek(offset)
    return self.file.read(length)

  def get_props(self):
    result = []
    for k in ['Filename','File size']:
      result.append([k,self.props.get(k)])
    return result

  def __str__(self):
    return '\n'.join(['{:20s}{}'.format(z[0],z[1]) for z in self.get_props()])

if __name__ == '__main__':
  for fn in sys.argv[1:]:
    x = Master(fn)
    x.parse()
    print(x)
