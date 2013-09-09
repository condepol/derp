#!/usr/bin/python2.7
# coding: utf-8
#

import sys

def main():
  if len(sys.argv) == 1:
    print 'usage : '+sys.argv[0]+' good-times.srt good-text.srt [clean] [switch]'
    sys.exit(0)

  options = ''
  if len(sys.argv) > 3:
    options = ' '.join(sys.argv[3:])

  nif = Srt(sys.argv[1])
  nof = Srt(sys.argv[2])

  if 'clean' in options:
    nif.load('clean')
    nof.load('clean')
  else:
    nif.load()
    nof.load()

  if 'switch' in options:
    nof.copytimes(nif)
    nof.save(nof.filename+'retimed.srt')
    

class Srt():
  def __init__(self,filename):
    self.filename = filename
    self.loaded = False
    self.entries = []
  
  def load(self,clean=''):
    data = readfile(self.filename)
    tmp_lines = data.splitlines()
    # read all lines 
    while len(tmp_lines) != 0:
      skip_this_one = False
      tmp_entry = Entry()
      # read index
      tmp_entry.index = int(tmp_lines[0])
      # read time 
      tmp_entry.time = tmp_lines[1]
      # read text
      tmp_lines = tmp_lines[2:]
      # read all lines of text
      while len(tmp_lines) != 0 and tmp_lines[0] != '':
        tmp_entry.text.append(tmp_lines[0])
        if clean == 'clean':
          if "subtitles" in tmp_entry.text[-1].lower(): # skip every subtitle subtitle
            skip_this_one = True
        tmp_lines = tmp_lines[1:]

      # skip newline
      if len(tmp_lines) != 0 and tmp_lines[0] == '' :
        tmp_lines = tmp_lines[1:]
      # append if not junk
      if not skip_this_one:
        self.entries.append(tmp_entry)

    # reorder indexes
    for i in xrange(len(self.entries)):
      self.entries[i].index = i + 1

    self.loaded = True
    print str(self)

  def copytimes(self,srt):
    for i in xrange(min(len(self.entries),len(srt.entries))):
      self.entries[i].time = srt.entries[i].time

  def save(self,filename):
    with open(filename,'w') as o:
      o.write('\n\n'.join([str(u) for u in self.entries]))
      o.close()
    
  def __str__(self):
    r = 'srt file \''+self.filename+'\'\n'
    if self.loaded:
      r += 'Loaded, '+str(len(self.entries))+' entries\n'
    else:
      r += 'Not loaded.\n'
    return r


class Entry():
  def __init__(self):
    self.index = 0
    self.time = ''
    self.text = []
  def __str__(self):
    return '\n'.join([str(self.index),self.time,'\n'.join(self.text)])


def readfile(f):
  with open(f,'r') as o:
    d = o.read()
    o.close()
  return d

if __name__ == '__main__':
  main()
