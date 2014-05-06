#!/usr/bin/env python2.7
# coding: utf-8

import sys
from PIL import Image

if __name__ == '__main__':
  if len(sys.argv) < 2:
    print '{} <shades-of-grey-image.png> [invert]'.format(sys.argv[0])
  im = Image.open(sys.argv[1])
  w,h = im.size
  gradient='  ..,,--`::hh7788BBMM'
  gradient=' █████░██████▒▓███'
  if len(sys.argv) > 2:
    gradient = gradient.decode('utf-8')[::-1]
  print gradient
  output = ''
  monochrome=False
  try:
    print len(im.getpixel((0,0)))
  except:
    monochrome=True
  for c in xrange(h):
    output += '\n'
    for r in xrange(w):
      current_color = im.getpixel((r,c))
      if monochrome:
        color = current_color
      else:
        color = sum(current_color)/len(current_color)

      output += gradient.decode('utf-8')[int(len(gradient.decode('utf-8'))*color/256.)]
  print output
