#!/usr/bin/env python3

import os
import sys
import struct

class Service:
  def __init__(self,data,index):
    self.first_byte, self.serviceID, self.flags = struct.unpack('>BHH',data[index:index+5])
    # Not sure about this one, it could be a titleID trickery
    assert(self.first_byte == 0)
    # Check for new flag
    assert((0x32 | self.flags) == 0x32)

    self.length = 5
    # All the 6-packs of 0xff are prefixed by a byte having the bit 2 set.
    self.has_ff = (2 & self.flags) != 0
    if self.has_ff:
      # In this case, it means that the service length is 5 + 6
      self.length += 6

  def __str__(self):
    return '{:04x}-{:08b}'.format(self.serviceID,self.flags)

class ConsoleID:
  def __init__(self,data):
    self.integer = struct.unpack('>Q',data)[0]
  def __str__(self):
    return '{:016x}'.format(self.integer)

class StreetPass:
  def __init__(self,line):
    self.bytes = bytes([int(byte,16) for byte in line.split(':')])
    # parse properties
    self.oui_type, self.magic, self.service_length  = struct.unpack('>BBB',self.bytes[:3])
    self.foobar = struct.unpack('>H',self.bytes[-10:-8])[0]
    self.consoleID  = ConsoleID(self.bytes[-8:])
    # cut service data
    self.service_data = self.bytes[3:3+self.service_length]

    # checks for science
    assert(self.oui_type  ==    0x01  )
    assert(self.magic     ==    0x11  )
    assert(self.foobar    ==  0xf008  )
    
    # read services
    self.services = []
    index = 0
    while index < self.service_length:
      self.services.append(Service(self.service_data,index))
      # all services are not 5-byte long. c.f. Service class.
      index += self.services[-1].length
      

  def __str__(self):
    return '{}\n{}'.format(self.consoleID,
      '\n'.join(['  {}'.format(service) for service in self.services]))

if __name__ == '__main__':
  if len(sys.argv) == 1:
    lines = sys.stdin.readlines()
  else:
    if os.path.isfile(sys.argv[1]):
      with open(sys.argv[1],'r') as ofi:
        lines = ofi.readlines()
        ofi.close()
    else:
      print('Usage : {} [filename] (defaults to stdin)'.format(sys.argv[0]))
  
  print('\n'.join([str(StreetPass(line)) for line in lines]))
