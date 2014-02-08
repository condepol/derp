#!/usr/bin/env python3
# coding: utf-8

import sys
import random
from PIL import Image

dist = 20
destinations = []
def near(col):
  z = list(col)[:3]
  for i in range(3):
    z[i] = z[i] + random.randrange(-dist,dist)
    if z[i] < 0:
      z[i] = 0
    elif z[i] > 255:
      z[i] = 255
  return z

def walk(orig,img):
  order = [[0,-1],[0,1],[1,-1],[1,1]]
  #random.shuffle(order)

  refcol = img.getpixel(orig)
  for i in order:
    nc = list(orig)
    nc[i[0]] += i[1]
    nc = tuple(nc)
    try:
      color = img.getpixel(nc)
      if color[3] == 0:
        img.putpixel(nc,tuple(near(refcol))+(255,))
        destinations.append(nc)
    except IndexError:
      pass

if __name__ == '__main__':
  filename = sys.argv[1]    if len(sys.argv) > 1 else 'wp.png'
  width = int(sys.argv[2])  if len(sys.argv) > 2 else 1600
  height = int(sys.argv[3]) if len(sys.argv) > 3 else 900

  # add extension
  filename = '.'.join([filename,'png']) if '.' not in filename else filename

  print('{} will be {}x{}'.format(filename,width,height))
  dimension=(width,height)

  img=Image.new('RGBA',dimension,color=(0x80,0x80,0x80,0))
  
  coords = (random.randrange(width),random.randrange(height))
  walk(coords,img)
  done=0
  while destinations != []:
    if done % 10000 == 0:
      print(done/(width*height))
    walk(destinations.pop(random.randrange(len(destinations))),img)
    done+=1
  img.save(filename) 
