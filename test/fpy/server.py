#!/usr/bin/env python3
import sys,socket,struct
port = int(sys.argv[1]) if len(sys.argv) > 1 else 8888

data = sys.stdin.buffer.read()
print('{} data bytes'.format(len(data)))

c=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
c.bind(('localhost',port))
c.listen(5)
localinfo = c.getsockname()
print('Listening on {}:{}'.format(*localinfo))
fd, addr = c.accept()
print('Connected by {}:{}'.format(*addr))

print('Sending data.')
fd.sendall(data)

print('Closing socket')
fd.close()
c.shutdown(socket.SHUT_RDWR)
c.close()
