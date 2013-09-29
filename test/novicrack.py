#!/usr/bin/env python2.7
# coding: utf-8
# Top BL Spawn
# (some) Novell network default password generation

import sys

table = {
   8:[  4,  7], 
   9:[  5,  8], 
  10:[  2,  4,  6], 
  11:[  2,  4,  7], 
  12:[  3,  5,  8], 
  13:[  3,  5,  8], 
  14:[  3,  6,  9], 
  15:[  4,  6, 10], 
  16:[  4,  7, 11], 
  17:[  4,  7, 11], 
  18:[  5,  8, 12], 
  19:[  5,  8, 12], 
  20:[  5,  8, 13], 
  21:[  5,  9, 14], 
  22:[  6,  9, 14], 
  23:[  6,  9, 14], 
  24:[  6, 10, 15], 
  25:[  7, 11, 17], 
  26:[  7, 11, 17], 
  27:[  7, 12, 18], 
  28:[ 11, 12, 20],
}

def passfrom(prenom,nom):
  login = nom[:5]+prenom[:3]
  prefix = ''.join([str((nom+prenom)[i]) for i in table[len(prenom)+len(nom)]]).ljust(3,'P')
  number = str(len(prenom)*len(nom)).ljust(3,'0')
  return login,prefix+number

if __name__ == "__main__":
  if len(sys.argv) != 3:
    print "Usage :",sys.argv[0],"<prénom> <nom>"
    sys.exit(0)

  login,password = passfrom(sys.argv[1],sys.argv[2])

  print "login   : ",login
  print "password: ",password
