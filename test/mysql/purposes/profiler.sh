#!/bin/bash
gcc -Wall -Wextra -std=c99 -pedantic -ansi -O3 -march=native -fno-stack-protector bit_profile.c -o profiler &&
  ./bit_profile.py &&
  ./profiler 1 &&
  gcc -Wall -Wextra -std=c99 -pedantic -ansi -ggdb -fno-stack-protector bit_profile.c -o profiler_asm
