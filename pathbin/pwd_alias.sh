#!/bin/bash

logical=`pwd -L`
physical=`pwd -P`

if [ "$logical" == "$physical" ];
then
  echo $logical;
else
  echo -e "\x1b[0;36mlogical  :\x1b[0;36m" $logical;
  echo -e "\x1b[0;33mphysical :" $physical "\x1b[0m";
fi
