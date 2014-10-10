#!/usr/bin/env python3
# coding: utf-8
import sys,math,struct
names = 'C C♯ D D♯ E F G G♯ A A♯ B B♯'.split()
sample_rate = 8000
chords = {'M':[0,4,8],'m':[0,3,8],'7':[0,4,8,10],'m7':[0,3,8,10],'Δ':[0,3,7]}
def tone(x): return 440*(math.exp(math.log(2)/12)**x)
def pc(x): return x[:2 if '♯' in x else 1],x[2 if '♯' in x else 1:] if len(x[2 if '♯' in x else 1:]) != 0 else 'M'
def wave(hz,n): return [int(((1<<29)-1)*math.sin(hz*i*math.pi/(sample_rate))) for i in range(n)]
def cool(t,n,spectrum):
  presum = [wave(tone(t+i),n) for i in range(len(spectrum))]
  output = [sum([spectrum[i]*presum[i][x] for i in range(len(spectrum))]) for x in range(len(presum[0]))]
  return output
def render(x): sys.stdout.buffer.write(struct.pack('<{:d}I'.format(len(x)),*[int(i%(1<<31)) for i in x]))
z = [0,0,0,2,4,4,2,0,4,2,2,0]
for i in z: render(cool(i,int(sample_rate/4),[1/x for x in [4,3,2,1]]))
