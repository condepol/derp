#!/usr/bin/env python2.7
# coding: utf-8

import os,select,socket,struct,sys,time
import random

def checksum_mini(source_string):
  return struct.unpack('<H',struct.pack('>H',65535^(
    (sum(struct.unpack('H',source_string[i:i+2])[0]for i in range(0,len(source_string),2))%0x10000) +
    (sum(struct.unpack('H',source_string[i:i+2])[0]for i in range(0,len(source_string),2)) >> 16))
    ))[0]


def checksum_maxi(source_string):
    """
    I'm not too confident that this is right but testing seems
    to suggest that it gives the same answers as in_cksum in ping.c
    """
    sum = 0
    count_to = (len(source_string) / 2) * 2
    for count in xrange(0, count_to, 2):
        this = ord(source_string[count + 1]) * 256 + ord(source_string[count])
        sum = sum + this
        sum = sum & 0xffffffff # Necessary?

    if count_to < len(source_string):
        sum = sum + ord(source_string[len(source_string) - 1])
        sum = sum & 0xffffffff # Necessary?

    sum = (sum >> 16) + (sum & 0xffff)
    sum = sum + (sum >> 16)
    answer = ~sum
    answer = answer & 0xffff

    # Swap bytes. Bugger me if I know why.
    answer = answer >> 8 | (answer << 8 & 0xff00)

    return answer


if __name__ == '__main__':
  for i in xrange(555):
    vector = ''.join([chr(random.randrange(256)) for i in xrange((random.randrange(400)|1)+1)])
    assert(checksum_mini(vector) == checksum_maxi(vector))
