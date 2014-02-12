#!/usr/bin/env python2.7
# coding: utf-8

import sys
import struct
import random
from PIL import Image

dist = 20
destinations = []

def write_gif_header(fp,width,height):
  fp.write(''.join([
    'GIF89a',
    struct.pack('<HH',width,height),
    '\x70\x00\x00\x21\xff\x0bNETSCAPE2.0\x03\x01\x01\x00\x00']))

def wpixel(fp,coord,color):
  fp.write(''.join([
    '\x21\xf9\x04\x00\x01\x00\x00\x00\x2c',
    struct.pack('<HH',coord[0],coord[1]),
    '\x01\x00\x01\x00\x80',
    struct.pack('<BBB',color[0],color[1],color[2]),
    '\x00\x00\x00\x02\x02\x44\x01\x00']))

 

def near(col):
  z = list(col)[:3]
  for i in range(3):
    z[i] = z[i] + random.randrange(-dist,dist)
    if z[i] < 0:
      z[i] = 0
    elif z[i] > 255:
      z[i] = 255
  return z

def walk(orig,img,fp):
  order = [[0,-1],[0,1],[1,-1],[1,1]]
  refcol = img.getpixel(orig)
  for i in order:
    nc = list(orig)
    nc[i[0]] += i[1]
    nc = tuple(nc)
    try:
      color = img.getpixel(nc)
      if color[3] == 0:
        ncoul = tuple(near(refcol))
        img.putpixel(nc,ncoul+(255,))
        wpixel(fp,nc,ncoul)
        destinations.append(nc)
    except IndexError:
      pass

if __name__ == '__main__':
  filename = sys.argv[1]    if len(sys.argv) > 1 else 'wp.gif'
  width = int(sys.argv[2])  if len(sys.argv) > 2 else 500
  height = int(sys.argv[3]) if len(sys.argv) > 3 else 500

  # add extension
  filename = '.'.join([filename,'gif']) if '.' not in filename else filename

  print('{} will be {}x{}'.format(filename,width,height))
  dimension=(width,height)
  
  fp = open(filename,'wb')

  write_gif_header(fp,width,height)
  
  img=Image.new('RGBA',dimension,color=(0x80,0x80,0x80,0))
  coords = (random.randrange(width),random.randrange(height))

  walk(coords,img,fp)
  done=0
  while destinations != []:
    if done % (width) == 0:
      print(float(done)/(width*height))
    walk(destinations.pop(random.randrange(len(destinations))),img,fp)
    done+=1
  fp.write(';')
  fp.close()
