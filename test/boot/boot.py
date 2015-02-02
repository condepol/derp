#!/usr/bin/env python3

import socket
import struct

class Server:
  def __init__(self,interface_name):
    self.interface_name = interface_name
    self.socket = socket.socket(socket.AF_PACKET, socket.SOCK_RAW)
    self.socket.bind((self.interface_name,0))

  def loop(self):
    while True:
      frame, addr = self.socket.recvfrom(12)
      print(addr)
      print(repr(frame))


if __name__ == '__main__':
  iface = 'eth1'
  s = Server(iface)
  s.loop()
