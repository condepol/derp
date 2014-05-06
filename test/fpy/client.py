#!/usr/bin/env python3
# coding: utf-8

import sys,socket

host = sys.argv[1]      if len(sys.argv) > 1 else 'localhost'
port = int(sys.argv[2]) if len(sys.argv) > 2 else 8888

s=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
print('Connecting to {}:{}'.format(host,port))
s.connect((host,port))
print('Connected from {}:{}'.format(*s.getsockname()))

new = s.recv(1024)
while len(new) != 0:
  sys.stdout.buffer.write(new)
  new = s.recv(1024)

s.shutdown(socket.SHUT_RDWR)
s.close()
