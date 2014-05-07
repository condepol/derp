#!/usr/bin/env python2.7
import os,select,socket,struct,sys,time
def checksum(source_string):
  return struct.unpack('<H',struct.pack('>H',65535^(
    (sum(struct.unpack('H',source_string[i:i+2])[0]for i in range(0,len(source_string),2))%0x10000) +
    (sum(struct.unpack('H',source_string[i:i+2])[0]for i in range(0,len(source_string),2)) >> 16))
    ))[0]

def receive_one_ping(my_socket, id, timeout):
  time_left = timeout
  while True:
    started_select = time.time()
    what_ready = select.select([my_socket], [], [], time_left)
    how_long_in_select = (time.time() - started_select)
    if what_ready[0] == []: # Timeout
      return

    time_received = time.time()
    received_packet, addr = my_socket.recvfrom(1024)
    icmpHeader = received_packet[20:28]
    type, code, checksum, packet_id, sequence = struct.unpack("bbHHh", icmpHeader)
    if packet_id == id:
      bytes = struct.calcsize("d")
      time_sent = struct.unpack("d", received_packet[28:28 + bytes])[0]
      return time_received - time_sent

    time_left = time_left - how_long_in_select
    if time_left <= 0:
      return


def send_one_ping(my_socket, dest_addr, id, psize):
  dest_addr  =  socket.gethostbyname(dest_addr)
  header = struct.pack("bbHHh",8,0,0,id,1)
  data = struct.pack("d",time.time())+(psize-16)*"Q"
  my_checksum = checksum(header + data)
  header = struct.pack("bbHHh", 8, 0, socket.htons(my_checksum), id, 1)
  my_socket.sendto(header + data, (dest_addr, 1)) # Don't know about the 1


def do_one(dest_addr, timeout, psize):
  try:
    my_socket = socket.socket(2,3,1)
  except socket.error, (errno, msg):
    if errno == 1:
      # Operation not permitted
      msg = msg + (
        " - Note that ICMP messages can only be sent from processes"
        " running as root."
      )
      raise socket.error(msg)
    raise # raise the original error

  my_id = os.getpid() & 0xFFFF

  send_one_ping(my_socket, dest_addr, my_id, psize)
  delay = receive_one_ping(my_socket, my_id, timeout)

  my_socket.close()
  return delay


def verbose_ping(dest_addr, timeout = 2, count = 4, psize = 64):
  """
  Send `count' ping with `psize' size to `dest_addr' with
  the given `timeout' and display the result.
  """
  for i in xrange(count):
    print "ping %s with ..." % dest_addr,
    try:
      delay  =  do_one(dest_addr, timeout, psize)
    except socket.gaierror, e:
      print "failed. (socket error: '%s')" % e[1]
      break

    if delay  ==  None:
      print "failed. (timeout within %ssec.)" % timeout
    else:
      delay  =  delay * 1000
      print "get ping in %0.4fms" % delay
  print

if __name__ == '__main__':
  verbose_ping("heise.de")
  verbose_ping("google.com")
  verbose_ping("a-test-url-taht-is-not-available.com")
  verbose_ping("192.168.1.1")
