#!/usr/bin/env python3
# coding: utf-8

class A():
  def __init__(self,**kwargs):

    self.forA = kwargs.get('forA')

    if self.forA == None:
      self.forA = 'default A :/'

    print('Initializing a A with parameter {}'.format(self.forA))

class B(A):
  def __init__(self,**kwargs):
    super().__init__(**kwargs)
    
    self.forB = kwargs.get('forB')

    if self.forB == None:
      self.forB = 'default B :/'

    print('Initializing a E with parameter {}'.format(self.forB))

if __name__ == ('__main__'):
  dico = {
    'forB':'thisisforB',
    'forA':'information_for_A'}
  b = B(**dico)

  print('Initialized in B.__init__ : {}'.format(b.forB))
  print('Initialized in A.__init__ : {}'.format(b.forA))
