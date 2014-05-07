#!/bin/bash
echo "quvi $1"
quvi $1 -f best --exec "wget %u -O %t.%e"
