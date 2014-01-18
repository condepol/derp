#!/usr/bin/env python3
# coding: utf-8

class A():
  def __init__(self,par='azer'):
    print ('Initializing a A with parameter {}'.format(par))

class B(A):
  def __init__(self,par='tyui'):
    super().__init__(par)
    print ('Initializing a E with parameter {}'.format(par))

if __name__ == ('__main__'):
  print(B('derp'))
