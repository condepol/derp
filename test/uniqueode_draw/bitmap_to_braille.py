#!/usr/bin/env python3
# coding: utf-8

import sys
from PIL import Image

def stripline(line):
  while len(line)!=0 and line[-1] == chr(0x2800):line=line[:-1]
  return line.strip()

def matrix_to_chars(matrix):
  # remove first empty lines
  while sum(matrix[0]) == 0:matrix = matrix[1:]
  # remove first empty columns
  while sum([line[0] for line in matrix]) == 0:
    matrix = [l[1:] for l in matrix]
  # align columns to a multiple of 2
  if len(matrix[0]) % 2 != 0:
    for i in range(len(matrix)):
      matrix[i].append(0)
  # align lines to a multiple of 4
  while len(matrix)%4!=0:
    matrix.append([0]*len(matrix[0]))
  draw = ''
  for row in range(0,len(matrix),4):
    for column in range(0,len(matrix[0]),2):
      acc = 0
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
  draw = '\n'.join([stripline(line) for line in draw.splitlines()])
  while draw[-1] == '\n':draw=draw[:-1]
  print(draw)
  print(len(draw))

def bitmap_to_matrix(filename):
  im = Image.open(filename)
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
  return matrix

if __name__ == '__main__':
  if len(sys.argv) < 2:
    print('{} <two-colors-image.png> [invert]'.format(sys.argv[0]))
    sys.exit(0)
  matrix = bitmap_to_matrix(sys.argv[1])
  matrix_to_chars(matrix)
