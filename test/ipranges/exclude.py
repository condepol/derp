#!/usr/bin/env python3

import sys
import struct

class Ip:
  def __init__(self,s,i=None):
    if i is None:
      self.s = s.strip()
      self.i = struct.unpack('>I',struct.pack('BBBB',*[int(i) for i in self.s.split('.')]))[0]
    else:
      self.i = i
      self.s = '.'.join([str(int(z)) for z in struct.unpack('BBBB',struct.pack('>I',i))])
  def __gt__(self,i):
    return self.i > i.i
  def __lt__(self,i):
    return self.i < i.i
  def __str__(self):
    return self.s

class Range:
  def __init__(self,i):
    start,bits = i.strip().split('/')
    self.start = Ip(start)
    self.bits = int(bits)
    self.end = Ip('',self.start.i | ((1<<(32-self.bits))-1))
  def contains(self,ip):
    if self.start < ip:
      if self.end > ip:
        return True
    if ip in [self.start,self.end]:
      return True
    return False
  def __str__(self):
    return '{}/{} : {}-{}'.format(self.start,self.bits,self.start,self.end)

class Rangefile:
  def __init__(self,fn):
    with open(fn,'r') as o:
      self.ranges = [Range(i) for i in o.readlines()]
class Ipfile:
  def __init__(self,fn):
    with open(fn,'r') as o:
      self.ips = [Ip(i) for i in o.readlines()]

if __name__ == '__main__':
  if len(sys.argv) != 3:
    print('Usage : {} ips ranges'.format(self.argv[0]))
  i = Ipfile(sys.argv[1])
  r = Rangefile(sys.argv[2])
  for ip in i.ips:
    in_scope = False
    for iprange in r.ranges:
      if iprange.contains(ip):
        in_scope = True
    if in_scope:
      sys.stdout.write('\x1b[32m{}\x1b[0m\n'.format(ip))
    else:
      sys.stderr.write('\x1b[31m{}\x1b[0m\n'.format(ip))
