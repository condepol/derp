#!/usr/bin/env python3
import sys
import codecs
import struct

def pack(*k):
  x = 0
  for i in k: x = (x<<8) + i
  return x & 0x7fffffff

class State:
  def __init__(self,a,b,c,k,charset):
    self.a = a
    self.b = b
    self.c = c
    self.k = k
    self.charset = charset
  def __str__(self):
    return '{:>8s} \x1b[32m{:08x}\x1b[34m{:08x} \x1b[31m{:4x}\x1b[0m{}'.format(
        self.k,
        self.a,
        self.b,
        self.c,
        'OMG' if self.is_initial() else '')

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
          return True
    return False

  def child(self,k):
    # one round of mysql323
    a, b, c = self.a, self.b, self.c
    a = ((a ^ (k* ((a&63) + c)) + (a<<8)) %(1<<32)) & 0x7fffffff
    b = ((((b<<8) ^ a) + b) %(1<<32)) & 0x7fffffff
    c += k
    return State(a,b,c,self.k,self.charset)

  def parents(self):
    for key in self.charset:
      for ancient in self.ancients(key):
        yield ancient

  def ancients(self,k):
    'return possible states'
    # cut the bytes of A
    α,β,γ,δ = struct.unpack('4B',struct.pack('>I',self.a))
    assert(pack(α,β,γ,δ) == self.a)
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
      # i think this whole step could be done more elegantly
      # recover the 'z' factor
      z = k * (acc + (d&63))
      # recover c
      # γδ = (d0)+z ^ cd
      # cd = γδ ^ (d0)+z
      cd = (pack(γ,δ) ^ (pack(d,0)+z)) % 0x10000
      assert(cd % 256 == d)
      c = (cd>>8)%256
      # recover b
      # βγδ = bcd ^ (cd0 + z)
      # bcd = βγδ ^ (cd0 + z)
      bcd = (pack(β,γ,δ) ^ (pack(c,d,0)+z))%0x1000000
      assert(bcd % 0x10000 == cd)
      b = (bcd>>16)%256
      # αβγδ = abcd ^ (bcd0 + z)
      # abcd = αβγδ ^ (bcd0 + z)
      abcd = pack(α,β,γ,δ) ^ (pack(b,c,d,0)+z) & 0x7fffffff
      a = (abcd>>24)%256
      # this is not optimal, but i won't optimize yet
      na = pack(a,b,c,d)
      try:
        assert(abcd == na)
      except Exception as e:
        print('{:08x} != {:08x} {:02x}{:02x}{:02x}{:02x}'.format(abcd,na,a,b,c,d))
        raise e

      # once we have recovered A, we have to recover B
      ε,ζ,η,θ = struct.unpack('4B',struct.pack('>I',self.b))
      # θ = h + δ
      # h = θ - δ
      h = ( θ - δ ) % 256
      # ηθ = gh + (γδ ^ h0)
      # gh = ηθ - (γδ ^ h0)
      gh = (pack(η,θ) - (pack(h,0) ^ pack(γ,δ)))%0x10000
      g = (gh >> 8) % 256
      assert( gh % 0x100 == h )
      # ζηθ = (gh0 ^ βγδ) + fgh
      # fgh = ζηθ - (gh0 ^ βγδ)
      fgh = (pack(ζ,η,θ) - (pack(g,h,0) ^ pack(β,γ,δ)))%0x1000000
      f = (fgh >> 16)%256
      assert( fgh % 0x10000 == gh)
      
      # εζηθ = efgh + (fgh0 ^ αβγδ)
      # efgh = εζηθ - (fgh0 ^ αβγδ)
      # efgh = (fgh0 ^ αβγδ) - εζηθ
      efgh = (pack(ε,ζ,η,θ) - (pack(f,g,h,0) ^ pack(α,β,γ,δ))) & 0x7fffffff
      e = (efgh >> 24)%256
      try:
        assert(efgh % 0x1000000 == fgh)
      except Exception as ex:
        print('{:08x}'.format(abcd))
        print('{:08x} {:06x}'.format(efgh,fgh))
        raise ex
      nb = pack(e,f,g,h)
      assert(efgh == nb)

      # check correctness of reverse
      s = State(na,nb,acc,chr(k)+self.k,self.charset)
      #print('\n'.join([
      #  '{:18s} {}'.format(i,j)
      #  for i,j in (
      #    ('Self',self),
      #    ('Parent',s),
      #    ('Recovered',s.child(k)),
      #    )
      #  ]))
      if self == s.child(k):
        yield State(na,nb,acc,chr(k)+self.k,self.charset)
      else:
        print('Noes !')
  def salmon(self):
    for i in self.parents():
      print(i)
      i.salmon()

def crack(hash,charset,lenmax):
  assert(len(hash) == 16)
  b,a = struct.unpack('<II',struct.pack('<Q',int(hash,16)))
  print('Cracking hash «{:08x}{:08x}»'.format(a,b))
  print('Charset : {}'.format(charset))
  print('Max acc : {}'.format(lenmax))

  for last_acc in range(7+min(charset),lenmax):
    for key in charset:
      s = State(a,b,last_acc,chr(key),charset)
      s.salmon()

if __name__ == '__main__':
  import sys
  # ABCD
  hash = '086fecf00b799509' if len(sys.argv) < 2 else sys.argv[1]
  # protip : use « ÿ» for 0x20->0xff «\ ÿ» in a shell
  charset = 'AB' if len(sys.argv) < 3 else sys.argv[2][:2]
  charset = bytes(range(ord(charset[0]),ord(charset[1])+1))
  # Number of characters max in the password to recover
  # This defines the size of the tree
  lenmax  = 2 if len(sys.argv) < 4 else int(sys.argv[3])
  # final acc = 7 + sum(ord(letter) for letter in password)
  # thus, taking the max value of the charset give us the max bound :
  lenmax  = 7 + (max(charset) * lenmax)
  crack(hash,charset,lenmax)
