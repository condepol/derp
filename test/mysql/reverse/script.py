#!/usr/bin/env python3
import sys
import codecs
import struct

class State:
  def __init__(self,a,b,c,k,charset):
    self.a = a
    self.b = b
    self.c = c
    self.k = k
    self.charset = charset

  def is_initial(self):
    if self.c == 7:
      if self.a == 0x50305735:
        if self.b == 0x12345671:
          return True
    return False
  
  def __eq__(self,x):
    if self.a == x.a:
      if self.b == x.b:
        if self.c == x.c:
          if self.k == x.k:
            return True
    return False

  def child(self,k):
    # one round of mysql323
    a, b, c = self.a, self.b, self.c
    a = ((a ^ (k* ((a&63) + c)) + (a<<8)) %(1<<32)) & 0x7fffffff
    b = ((((b<<8) ^ a) + b) %(1<<32)) & 0x7fffffff
    c += k
    return State(a,b,c,k,self.charset)

  def parents(self):
    for key in self.charset:
      for ancient in self.ancients(key):
        yield x

  def ancients(self,k):
    'return possible states'
    # cut the bytes of A
    α,β,γ,δ = struct.unpack('<4B',struct.pack('<I',self.a))
    # get the previous accumulator state
    acc = self.c - k
    # if we are below 7, the key is too big
    if acc < 7: return
    # identify the possible d values
    def possible_d():
      for d in bytes(range(256)):
        z = k * (acc + (d&63))
        if (z % 256) ^ δ == d:
          yield d
    # deduce entire c,b,a from d
    for d in possible_d():
      # recover the 'z' factor
      z = key * (acc - k + (d&63))
      # recover c
      # γδ = (d0)*z ^ cd
      # cd = γδ ^ (d0)*z
      cd = ((γ<<8)+δ) ^ ((d<<8)*z)
      c = (cd>>8)%256
      # recover b
      # βγδ = bcd ^ (cd0 * z)
      # bcd = βγδ ^ (cd0 * z)
      βγδ = (β<<16)+(γ<<8)+δ
      bcd = βγδ ^ (((c<<16)+(d<<8))*z)
      b = (bcd>>16)%256
      # αβγδ = abcd ^ (bcd0 * z)
      # abcd = αβγδ ^ (bcd0 * z)
      αβγδ = struct.unpack('<I',struct.pack('<B',α,β,γ,δ)) & 0x7fffffff
      abcd = αβγδ ^ (((b<<24)+(c<<16)+(d<<8))*z) & 0x7fffffff
      a = (abcd>>24)%256
      na = struct.unpack('<I',struct.pack('<B',a,b,c,d)) & 0x7fffffff
      # TODO I STOPPED HERE
      # once we have recovered A, we have to recover B
      ε,ζ,η,θ = struct.unpack('<4B',struct.pack('<I',self.b))
      h = ( θ -      δ)   % 256
      g = ( η - (h ^ γ) -1) % 256 # i have no idea why the -1 helps
      f = ( ζ - (g ^ β) -1) % 256 # i have no idea why the -1 helps
      e = ( ε - (f ^ α) -1) % 256 # i have no idea why the -1 helps
      nb = struct.unpack('<I',struct.pack('<B',e,f,g,h)) & 0x7fffffff
      # check correctness of reverse
      s = State(na,nb,acc,key,self.charset)
      if self == s.child(k)
        yield State(na,nb,acc,key)
      else:
        print('Noes !')

def crack(hash,charset,lenmax):
  assert(len(hash) == 16)
  b,a = struct.unpack('<II',struct.pack('<Q',int(hash,16)))
  print('Cracking hash «{:08x}{:08x}»'.format(a,b))
  print('Charset : {}'.format(charset))
  print('Max acc : {}'.format(lenmax))

  for last_acc in range(7,lenmax):
    for key in charset:
      s = State(a,b,last_acc,key,charset)

if __name__ == '__main__':
  import sys
  # ABCD
  hash = '086fecf00b799509' if len(sys.argv) < 2 else sys.argv[1]
  # protip : use « ÿ» for 0x20->0xff «\ ÿ» in a shell
  charset = 'AD' if len(sys.argv) < 3 else sys.argv[2][:2]
  charset = bytes(range(ord(charset[0]),ord(charset[1])+1))
  # Number of characters max in the password to recover
  # This defines the size of the tree
  lenmax  = 6 if len(sys.argv) < 4 else int(sys.argv[3])
  # final acc = 7 + sum(ord(letter) for letter in password)
  # thus, taking the max value of the charset give us the max bound :
  lenmax  = 7 + (max(charset) * lenmax)
  crack(hash,charset,lenmax)
