# coding: utf-8
import socket,sys
c=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
c.connect(('localhost',8888))
print(c)
c.sendall(sys.stdin.read())
c.close()
