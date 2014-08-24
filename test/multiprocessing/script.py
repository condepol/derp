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
  todo = range(15)
  wolks = [pool.apply_async(work,(todo[i],5,6)) for i in todo]
  results  = [wolk.get() for wolk in wolks]
  print(results)

