#!/usr/bin/env python3
# coding: utf-8

import sys
from PIL import Image

def matrix_to_chars(matrix):
  # align columns 
  if len(matrix[0]) % 2 != 0:
    # suppose that every matrix line has same length
    for i in range(len(matrix)):
      matrix[i].append(0)
  # align lines
  while len(matrix)%4!=0:
    matrix.append([0]*len(matrix[0]))

  draw = ''
  for row in range(0,len(matrix),4):
    for column in range(0,len(matrix[0]),2):
      acc = 0
      # fuck poetry i iz gonna hardcode
      acc += matrix[row+0][column+0]<<0 
      acc += matrix[row+1][column+0]<<1
      acc += matrix[row+2][column+0]<<2
      acc += matrix[row+3][column+0]<<6
      acc += matrix[row+0][column+1]<<3
      acc += matrix[row+1][column+1]<<4
      acc += matrix[row+2][column+1]<<5
      acc += matrix[row+3][column+1]<<7
      draw += chr(0x2800+acc)
    draw += '\n'
  lines = draw.splitlines()
  nlines = []
  for line in lines:
    while line !=  '' and line[-1] == chr(0x2800):
      line = line[:-1]
    nlines.append(line)
  print('\n'.join(nlines))
  print(len('\n'.join(nlines)))

if __name__ == '__main__':
  if len(sys.argv) < 2:
    print('{} <two-colors-image.png> [invert]'.format(sys.argv[0]))
  im = Image.open(sys.argv[1])
  w,h = im.size
  matrix = []
  refcol = im.getpixel((0,0))
  if len(sys.argv) == 2:
    black,white=0,1
  else:
    black,white=1,0
  for c in range(h):
    matrix.append([])
    for r in range(w):
      if im.getpixel((r,c)) == refcol:
        matrix[-1].append(black)
      else:
        matrix[-1].append(white)
  matrix_to_chars(matrix)
