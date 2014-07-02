#!/bin/bash

IFS='
'

for image in `ls images/*.png`;
do
  color=`convert ${image} -scale 1x1\! -format '%[pixel:u]' info:-`;
  echo ${image} ${color};
done;
