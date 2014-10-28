#!/usr/bin/env python3
import sys
import codecs
import struct

def step(a,b,c,k):
  a = (a ^ (k*((a&63)+c))+ (a<<8)) % (1<<32)
  b = (((b<<8)^a)+b) % (1<<32)
  return a & (( 1 << 31) -1), b & (( 1 << 31) -1)

def ancient(A,B,last_acc,key):
  # check that this acc and this key lead to valid reverse
  δ =  A      % 256
  γ = (A>>8 ) % 256
  β = (A>>16) % 256
  α = (A>>24) % 256

  # this may or may not be ugly
  for six_bits in range(1<<7):
    Z = key * (last_acc - key + six_bits)
    z0, z1, z2 = Z % 256, (Z >> 8) % 256, (Z >> 16) % 256
    d = δ ^ z0
    if d & 0b111111 == six_bits:
      break

  new_acc = last_acc - key
  # original acc was 7, we shouldn't go below
  if new_acc < 7: return
  two_bytes = ((d << 8) + Z) % 0x10000
  c = ((two_bytes >> 8) % 256) ^ γ
  three_bytes = (((c<<16)+(d<<8)) + Z) % 0x1000000
  b = ((three_bytes >> 16) % 256) ^ β
  a = b ^ α
  nA = ((a<<24) + (b<<16) + (c<<8) + d) & 0x7fffffff
  # once we have recovered A, we have to recover B
  θ =  B      % 256
  η = (B>>8 ) % 256
  ζ = (B>>16) % 256
  ε = (B>>24) % 256
  h = ( θ -      δ)   % 256
  g = ( η - (h ^ γ) -1) % 256 # i have no idea why the -1 helps
  f = ( ζ - (g ^ β) -1) % 256 # i have no idea why the -1 helps
  e = ( ε - (f ^ α) -1) % 256 # i have no idea why the -1 helps
  nB = ((e<<24) + (f<<16) + (g<<8) + h) & 0x7fffffff
  # now we have A, B and key plus new_acc,
  # we have to check
  xA,xB = step(nA,nB,new_acc,key)
  if (xA == A) and (xB == B):
    return nA,nB,new_acc,key

  #print(' '.join(
  #  ['{:08x}'.format(i) for i in [A,B,nA,nB,xA,xB,xA^A]] + 
  #  ['{}'.format(i) for i in [last_acc,new_acc,key]]
  #  ))

def salmon(stuff,charset,level=0):
  for A,B,acc,key in stuff:
    if acc < 7:
      pass
    elif A == 0x50305735 and B == 0x12345671:
      print('Won. {} {}'.format(acc,key))
    else:
      print((" "*level)+'{:08x} {:08x} {:x} {:x} {}'.format(A,B,acc,key,chr(key)))
      this = []
      for k in charset:
        new = ancient(A,B,acc,k)
        if new is not None:
          this.append(new)
      salmon(this,charset,level+1)


def crack(hash,charset,max_sum=0x1000):
  assert(len(hash) == 16)
  A,B = struct.unpack('>II',codecs.decode(hash,'hex'))
  print('{:08x}{:08x}'.format(A,B))
  # 1. find starting points
  starting_points = []
  skipped = 0
  for last_acc in range(max_sum):
    for key in charset:
      new = ancient(A,B,last_acc,key)
      if new is not None:
        starting_points.append(new)
      else:
        skipped += 1
  print('Found {} starting points, skipped {}.'.format(len(starting_points),skipped))
  salmon(starting_points,charset)

if __name__ == '__main__':
  import sys
  charset = bytes(range(ord('A'),ord('Z')))
  # crack('606707d16665cd42',charset)
  #crack('086fecf00b799509',bytes(range(ord('A'),ord('D')+1)),400)
  crack(sys.argv[1],bytes(range(ord('A'),ord('D')+1)),400)
