#!/usr/bin/env python3
# coding: utf-8

import os,select,socket,struct,sys,time
import random

def check(somme,mine):
  try:
    assert(somme == mine)
  except AssertionError:
    print(' '.join(['{:04x}'.format(i) for i in [somme,mine]]))
    sys.exit(0)


def checksum_mini(data):
    # accumulate shorts
    mine=sum(data[i]+(data[i+1]<<8) for i in range(0,(len(data)|1)-1,2))
    # add last odd byte
    if len(data)&1: mine += data[-1]
    # shift carries
    while mine>>16: mine = (mine>>16) + (mine%65536)
    # swap bytes and xor
    return (((mine&255)<<8)+(mine>>8)) ^ 65535




def checksum_maxi(source_string):
    """
    I'm not too confident that this is right but testing seems
    to suggest that it gives the same answers as in_cksum in ping.c
    """
    sum = 0
    count_to = (len(source_string) // 2) * 2
    for count in range(0, count_to, 2):
        this = source_string[count + 1] * 256 + source_string[count]
        sum = sum + this
        sum = sum & 0xffffffff # Necessary?

    if count_to < len(source_string):
        sum = sum + source_string[len(source_string) - 1]
        sum = sum & 0xffffffff # Necessary?

    sum = (sum >> 16) + (sum & 0xffff)
    sum = sum + (sum >> 16)
    answer = ~sum
    answer = answer & 0xffff

    # Swap bytes. Bugger me if I know why.
    answer = answer >> 8 | (answer << 8 & 0xff00)

    return answer


if __name__ == '__main__':
  try:
    for i in range(2000):
      vector = bytes([random.randrange(256) for i in range(random.randrange(400))])
      assert(checksum_mini(vector) == checksum_maxi(vector))
    print('\x1b[32mOk\x1b[0m')
  except AssertionError:
    print('\x1b[31mFail\x1b[0m')
