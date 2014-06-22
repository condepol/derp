#!/usr/bin/env python3
# coding: utf-8
# apt-get install python3-pil
# max of 40 symbols :/ 

import sys
from PIL import Image
from facebookdata import table

def nearest(color,table):
  result_index = 0
  min_dist = 256*256*256
  for index in range(len(table)):
    dist = distance(color,table[index][2])
    if dist < min_dist:
      min_dist = dist
      result_index = index
  return result_index

def distance(v1,v2):
  return sum([abs(v1[i]-v2[i]) for i in range(min(len(v1),len(v2)))])

def trigger(index,table):
  x = table[index][1]
  if type(x) is int:
    return chr(x)
  else:
    return x

if __name__ == '__main__':
  if len(sys.argv) not in [2,4]:
    print('Usage : {} <image> [<width> <height>]'.format(sys.argv[0]))
    sys.exit(0)

  # 1 : open file
  image_filename = sys.argv[1]
  try:
    image = Image.open(sys.argv[1])
  except Exception as e:
    print('Error while loading image {}'.format(image_filename))
    print(e)
    sys.exit(0)


  # 2 : resize
  if len(sys.argv) == 4:
    try:
      x,y=int(sys.argv[2]),int(sys.argv[3])
    except:
      print('Error while reading width and height from command line arguments')
      sys.exit(0)

    image = image.resize((x,y))
  else:
    # otherwise get dimensions
    (x,y) = image.size


  # 3 : convert to RGB colorspace
  image = image.convert("RGB")


  # print emojis !
  for i in range(y):
    for j in range(x):
      color = image.getpixel((j,i))
      nearest_color = nearest(color,table)
      print(trigger(nearest_color,table),end='')
    print('')
