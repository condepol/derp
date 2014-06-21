#!/bin/bash

input_filename='8-list-found-formulas.txt'

IFS='
'

for line in `cat ${input_filename}`;
do
  root=${line%% *}
  code=${line##* }

  if [ ${root:0:1} == 2 ] || [ ${root:0:1} == 4 ];
  then
    img="images/${root}.png";
  else
    img="images/emoticon_${root}.png";
  fi

  color=`convert ${img} -scale 1x1\! -format '%[pixel:u]' info:-`;
  echo $root ${color##*a};
  
done;
