#!/usr/bin/env python3
# coding: utf-8
import sys,time,struct,codecs
def S(t): return ''.join([['{} '.format(chr(byte)) if (byte % 0x80) > 0x1f else '\x1b[31m{:02x}\x1b[0m'.format(byte)][0] for byte in struct.pack('>I',t)])
def Z(t): return ''.join([(x if x != chr(0) else ' ') for x in str(struct.pack('>I',t),'cp437')])
def pr(t): print('{:30s} {:08x} {}  {:8s}'.format(time.strftime("%F %T %A",time.gmtime(t)),t,Z(t),S(t)))
def cases(s,t=0):
  if t == len(s):return [s]
  return [i for i in cases(s[:t]+s[t].upper()+s[t+1:],t+1)] + [i for i in cases(s[:t]+s[t].lower()+s[t+1:],t+1)]
def b(x):return [(ord(c)%256) for c in x]
for i in sys.argv[1:]:
  if len(i) == 4:
    for z in cases(i):
      pr(struct.unpack('>I',bytes(b(z)))[0])
  elif i =='now':
    pr(int(time.time()))
  elif i == 'today':
    now = time.gmtime()
    pr(int(time.mktime((now.tm_year,now.tm_mon,now.tm_mday,1,0,0,0,0,0))))
    pr(int(time.mktime((now.tm_year,now.tm_mon,now.tm_mday,24,59,59,0,0,0))))
  elif i[:5] == 'years':
    if len(i) == 8:
      for x in range(256):
        pr(struct.unpack('>I',bytes([x]+b(i[-3:])))[0])
    elif len(i) == 11:
      for x in range(256):
        pr(struct.unpack('>I',bytes([x])+codecs.decode(i[-6:],'hex'))[0])
    else:
      for z in range(256):
        pr(z<<24)
  elif i[:6] == 'months':
    p = int(time.time()) & 0xff000000 if len(i) == 6 else ord(i[-1])<<24
    for z in range(256):
      pr(p+(z<<16))
  elif len(i) == 1:
    for encoding in ['utf8','utf_16_le','utf_32_le']:
      z = bytes(i,encoding)
      pr(struct.unpack('>I',z+bytes([0]*(4-len(z))))[0])
  elif '-' in i and len(i.split('-')) == 3:
    y,m,d = (int(z) for z in i.split('-'))
    pr(int(time.mktime((y,m,d,1, 0, 0, 0,0,0))))
    pr(int(time.mktime((y,m,d,24,59,59,0,0,0))))
  elif len(i) == 8 or (len(i) == 10 and i[:2].lower() == '0x'):
    pr(struct.unpack('>I',codecs.decode(i[-8:],'hex'))[0])
