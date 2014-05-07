# coding: utf-8
import socket,sys
c=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
c.bind(('localhost',50888))
s,a=c.accept()
print("Connected by {}:{}".format(a[0],a[1]))
x=4
while x:
  x=s.recv(1024)
  sys.stdout.write(x)

