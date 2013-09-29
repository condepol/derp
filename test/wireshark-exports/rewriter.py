#!/usr/bin/env python2.7

import sys

id = 0
def main():
  if len(sys.argv) < 3:
    print "{0} <inputs>... <output>".format(sys.argv[0])
    sys.exit(0)
  else:
    input_filenames = sys.argv[1:-1]
    output_filename = sys.argv[-1]

  print "Reading packets from {0}.".format(", ".join(input_filenames))
  print "Writing output in {0}.".format(output_filename)

  loader = Loader()
  for input_filename in input_filenames:
    with open(input_filename,'r') as ofi:
      data = ofi.read() # not safe for binary files on Microsoft Windows
      ofi.close()
    blocks = data.strip().split("\n\n");
    for block in blocks:
      loader.packets.append(Packet(block))
  
  with open(output_filename,'w') as ofi:
    ofi.write(loader.render())
    ofi.close()
  print "Done."

class Packet():
  def __init__(self,raw):
    global id
    self.raw = raw.splitlines()
    self.id = id
    id += 1
    
    self.name = "pkt{0}".format(self.id)

    self.data = ''
    for dataline in self.raw[2:-1]:
      self.data += ''.join([chr(int(i,16)) for i in dataline[:dataline.index("/")-2].strip().split(", ")])
    

  def __len__(self):
    return len(self.data)
  
  def get_data(self):
    return '"'+''.join(["\\x%02x"%(ord(i)) for i in self.data])+'"'
    
  def __str__(self):
    return "Packet {0}, {1} chars".format(self.id,len(self.raw))

class Loader():
  def __init__(self):
    self.packets = []
    
  def render(self):
    r =  'typedef struct {unsigned int length;unsigned char * data;} wireshark_packet;\n'
    r += 'typedef struct {unsigned int length;wireshark_packet * packets;} wireshark_dico;\n'
    r += 'wireshark_dico load_packets ( void ) {\n'
    r += '  wireshark_dico output;\n'
    r += '  output.length = %d;\n'%(len(self.packets))
    r += '  output.packets = malloc(%d*sizeof(wireshark_packet));\n'%(len(self.packets))
    for packet in self.packets:
      r += '  output.packets[%d].length = %d;\n'%(packet.id,len(packet))
      r += '  output.packets[%d].data = malloc(%d*sizeof(unsigned char));\n'%(packet.id,len(packet))
      r += '  memcpy(output.packets[%d].data,(unsigned char *)%s,%d);\n'%(packet.id,packet.get_data(),len(packet))
    r += '  return output;\n'
    r += '}\n'
    return r
 

if __name__ == "__main__":
  main()
