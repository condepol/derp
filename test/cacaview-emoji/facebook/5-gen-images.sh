#!/bin/sh
# usage : ./a.sh name x y

big_image='spAcfMfpPL-.png'
input_filename='6-names-coordinates-for-script.txt'

IFS="
"

for i in `cat ${input_filename}`;
do
  echo $i;
  fn=`echo $i | awk '{print $1}';`.png;
  x=`echo $i | awk '{print $2}';`;
  y=`echo $i | awk '{print $3}';`;
  convert ${big_image} -crop 16x16+$x+$y +repage $fn ;
done;

