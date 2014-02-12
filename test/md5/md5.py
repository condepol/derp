#!/usr/bin/env python2.7
# coding: utf-8

def isuint32(x):
  if type(x) != int:
    return False
  if x > 0x100000000:
    return False
  if x < 0:
    return False

class basic_functions():
  def __init__(self):
    pass

  def apply(self,a,b,c,method):
    assert sum([isuint32(z) for z in (a,b,c)])
    if method == 'f':
      return ((c) ^ ((a) & ((b) ^ (c))))
    elif method == 'g':
      return ((b) ^ ((c) & ((a) ^ (b))))
    elif method == 'h':
      return (a^b^c)
    elif method == 'i':
      return ((b) ^ ((a) | ~(c)))


