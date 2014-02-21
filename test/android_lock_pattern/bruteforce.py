#!/usr/bin/env python2.7
# coding: utf-8

import sys
import hashlib

k = hashlib.sha1(''.join([chr(int(i)) for i in '145263780'])).hexdigest()
assert ( k == '2c3422d33fb9dd9cde87657408e48f4e635713cb')

def pwn(degre,pwd,bar=False):
  if degre == 0:
    if hashlib.sha1(''.join([chr(i) for i in pwd])).hexdigest() == k:
      print '\x1b[0GFound : {}'.format(''.join(['{}'.format(i) for i in pwd]))
      sys.exit(0)
  else:
    for noct in xrange(10):
      if noct not in pwd:
        if bar:
          sys.stdout.write("\x1b[0G[{:<9s}]".format(noct*'='))
          sys.stdout.flush()
        pwn(degre-1,pwd+[noct])
    if bar:
      print degre

if __name__ == '__main__':
  for degre in xrange(4,10):
    pwn(degre,[],bar=True)
