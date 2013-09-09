#!/usr/bin/python2.7
# -*- coding: utf-8 -*-


no='�'
print no
if 't' in no:
  print 'ol'
start = 0
stop = 0x20000
step = 0x1000

for section in xrange(start,stop,step):
  a = [unichr(code) for code in xrange(section, section+step)]
  if no not in a:
    print "Section "+hex(section)+" is ok."
  else:
    print "Section "+hex(section)+" is NOT ok."
