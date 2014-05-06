#!/usr/bin/env python2.7
# coding: utf-8

import hashlib
import sys

ssid = sys.argv[1]

hexaend = ssid[-6:].lower()
hexvalues = ['{:02X}'.format(i) for i in range(ord('A'),ord('Z')+1)+range(ord('0'),ord('9')+1)]
print hexvalues

candidates = []
for y in xrange(6, 12):
  print "Year {}".format(y)
  for w in xrange(1, 52):
    snb = 'CP{:02d}{:02d}'.format(y,w)
    for X in hexvalues:
      snb2 = snb+X
      for Y in hexvalues:
       snb3 = snb2+Y
       for Z in hexvalues:
         sn_sha = hashlib.sha1(snb3+Z).hexdigest()
         if sn_sha[-6:] == hexaend:
           print "{} > {}".format(snb3+Z,sn_sha)
           candidates.append(sn_sha[:10].upper())

if len(candidates) == 0:
  print "No keys found."
else:
  print "Candidates:"
  for key in candidates:
    print '  '+key
