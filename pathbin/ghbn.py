#!/usr/bin/env python3

import sys
import socket
for hostname in sys.argv[1:]:
  try:
    h,a,i = socket.gethostbyname_ex(hostname)
    print('Hostname : {}'.format(h))
    if a != []:
      print('Aliases  : {}'.format(', '.join([str(al) for al in a])))
    print('Ips : {}'.format(' '.join([str(ip) for ip in i])))
  except socket.gaierror:
    print('\x1b[31m{}\x1b[0m'.format(hostname))

