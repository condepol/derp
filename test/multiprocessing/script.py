#!/usr/bin/env python3
# coding: utf8

import time
import multiprocessing

def work(*params):
  print(params)
  time.sleep(2)
  print('fini')
  return params[0]

if __name__ == '__main__':
  pool = multiprocessing.Pool()
  wolk = pool.apply_async(work,(4,5,6))
  a = wolk.get()
  print(a)

