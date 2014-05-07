#!/usr/bin/env python3

import sys
import socket
import struct
import random

def portmapper(host,port=111,program=100232,version=10):
  # pack data
  msg = struct.pack('6L16x4H',
    random.randrange(1<<32), # XID
    0,
    2,
    100000,
    2,
    3,
    program,
    version,
    0x11,
    1
  )
  # create socket
  s = socket.socket(socket.AF_INET,socket.SOCK_DGRAM | socket.NONBLOCK)
  # connect
  try:
    s.connect((host,port))
  except ConnectionRefusedError:
    print("Unable to connect to portmapper")
    sys.exit(0)

  # send data
  s.send(msg)
  # recieve data
  data = s.recv(28)
  print(data)
  # politely close socket
  s.close()
  # parse data
  wanted_port = struct.unpack('N',data[24:28])[0]
  # return port
  return wanted_port

if __name__ == '__main__':
  # parse args
  # find sadmind port
  print('Port : {}'.format(portmapper('localhost')))
  # find target hostname
  # execute command
