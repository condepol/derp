#!/usr/bin/env python2.7
# coding: utf-8
import sys
d = sys.stdin.read()
ok = [0x01, 0xd6, 0xd7]
if len(d) != 256:
  print 'Invalid length {}.'.format(len(d));
  sys.exit(0)
for i in xrange(len(d)):
  if ord(d[i]) != ok[i%3]:
    print 'Byte {:d} is {:02x} (should have been {:02x}'.format(i,ord(d[i]),ok[i%3])
    sys.exit(0)
print '{}Ok.{}'.format("\x1b[32m","\x1b[0m")
