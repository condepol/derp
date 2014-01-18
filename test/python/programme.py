#!/usr/bin/env python3
# coding: utf-8

class A():
  def __init__(self,*par):

    try:
      self.forA = par[0]['forA']
    except Exception as e:
      print(e)
      self.forA = 'default A :/'

    print('Initializing a A with parameter {}'.format(self.forA))

class B(A):
  def __init__(self,*par):
    super().__init__(*par)

    try:
      self.forB = par[0]['forB']
    except Exception as e:
      print(e)
      self.forB = 'default B :/'

    print('Initializing a E with parameter {}'.format(self.forB))

if __name__ == ('__main__'):
  b = B({
    'forB':'thisisforB',
    'forA':'information_for_A'})

  print('Initialized in B.__init__ : {}'.format(b.forB))
  print('Initialized in A.__init__ : {}'.format(b.forA))
