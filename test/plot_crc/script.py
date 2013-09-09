#!/usr/bin/env python2.7
# coding: utf-8

from PIL import Image

if __name__ == '__main__':
  image = Image.new('RGB',(1800,800),(0,0,0))
  for i in xrange(0x10000):
    image.putpixel((int(),b),(0xff,0xff,0xff))
  image.save('olol.png')
