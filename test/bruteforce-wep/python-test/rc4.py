#!/usr/bin/env python2.7
# coding: utf-8

import sys
import zlib
import struct
import binascii
from Crypto.Cipher import ARC4

key = "\xab\x71\x59"+"\x61\x61\x10\x14\x53"

cipher = ARC4.new(key)

if (len(sys.argv) == 1):
  msg = cipher.encrypt("\x00"*515)
  print msg
  sys.exit(0)


data = binascii.unhexlify("6887201858b728c7d06ac37da94b06abd76a09a34a0d96774914a15cfd2cb45cf100f8a56feb499d08d51236e96f890cedf0a7376997caab1b8a1fef33ff489a221bfa360c2c6f293e0aae552c6fc73bc2145185586526d1337d52606c3ffe2192436bbf7b2a894b5afc5cbdf6ea1eb138d29d0f34660532a03398fcbe84500a2ecadab968b14f3bea78b7b3264f0511e84779fd6c4891913a08a0943e4946504e726f350cbccd1045e61a2de21651dee0c94404b241e416d03b770985ed597fb77640965246a9b8b82136959bd21d757ac4c26234619feaa78a9b13db7fa9e93b6c7c8b221eb391d95707f96f4a0ee88b950e843b96a42e73c2e739b0b0b24d512713e93d33fa19ab78f9e5a385184ab19f4d444fbd0e7900a8c66cd824c75af7252bff682bc1eee2be183ad1240feb461ec678b0b182fc682563beeabfa6f20cc34fac73db804c26381fb2aa996cf6d2211179ddddbcab3340a1cc3899a91516d2cb169596b8c9001a3e37929dc6ed6dba3e2abdff17f361844d560ef2406511afa3525d13d337289c46af576ce038351327d6fc1f4cc38efe064c12a52972950094b649fb3ce6cd3e94758a756a11f7b639047dbf63ee89ffdc18bbfc"+"4e418db3")

cipher = ARC4.new(key)
deciphered = cipher.decrypt(data)

crc = deciphered[-4:]
clear = deciphered[:-4]
print len(clear),"bytes of cleartext"
print len(crc),"bytes of crc"
print len(deciphered),len(data),"bytes of data (cipered & deciphered"
print "computed crc       :  ",binascii.hexlify(struct.pack('<I',zlib.crc32(clear)%(1<<32)))
print "hex(int(crc))      :",hex(zlib.crc32(clear)%(1<<32))
print "raw deciphered crc :  ", binascii.hexlify(crc)


print "Data : "
print deciphered
