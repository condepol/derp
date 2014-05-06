#!/usr/bin/env python2.7
# coding: utf-8

import sys
import struct
import random

class Gif():
  def __init__(self,width=500,height=500,color=(0,0,0)):
    self.width = width
    self.height = height
    self.canvas_color = color
    self.frames = []
    
  def write(self):
    #with open(self.filename,'w') as ofi:
    #  ofi.write(self.get_header())
    #  ofi.write('lol')
    #  ofi.close()
    sys.stdout.write(self.header())
    for f in self.frames:
      sys.stdout.write(f.get())
    sys.stdout.write(';')


  def header(self):
    scr = struct.pack('<6sHHBBB',
      'GIF89a',
      self.width,
      self.height,
      0b01110000, # no global color palette, 0b111 = 7 +1= 8bit color depth, 0b0000 = no palette -> no information on palette
      0,          # background color index
      0)          # pixel aspect ratio (0 = no information)

    # http://odur.let.rug.nl/~kleiweg/gif/netscape.html
    ext = struct.pack('<3s11s2sHB','\x21\xff\x0b','NETSCAPE2.0','\x03\x01',1,0)

    return scr+ext

class Frame():
  def __init__(self,x,y,color,w=1,h=1):
    self.x = x
    self.y = y
    self.h = h
    self.w = w
    self.color = color

  def get(self):
    #header = struct.pack('<BHHHHB',0x2c,self.position.x,self.position.y,1,1,0x87)
    #graphics = struct.pack('<3sBHBB','\x21\xf9\x04',0,duration,0,0)
    return ''.join([
      '\x21\xf9\x04\x00\x01\x00\x00\x00\x2c',
      struct.pack('<HH',self.x,self.y),
      struct.pack('<HH',self.w,self.h),
      '\x80',
      ''.join([chr(i) for i in self.color]),
      '\x00\x00\x00\x02\x02\x44\x01\x00'])


def randomcolor():
  return (random.randrange(256),random.randrange(256),random.randrange(256))

if __name__ == '__main__':
  width   = 40
  height  = 40
  a = Gif(width,height)
  a.frames.append(Frame(width,height,(0,0,0),True))
  for i in xrange(width*height):
    a.frames.append(Frame(random.randrange(width),
                          random.randrange(height),
                          randomcolor(),
                          ))
  a.write()
