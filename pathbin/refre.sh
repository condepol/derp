#!/bin/bash

maxtemp=$1;
cpu_marker='CPU Temperature'
temperature=`sensors | grep "${cpu_marker}" | awk -F ':' '{print $2}' | egrep "[0-9]*" -o | head -n 1`
while [ $temperature -gt $maxtemp ] ;
do
  temperature=`sensors | grep "${cpu_marker}" | awk -F ':' '{print $2}' | egrep "[0-9]*" -o | head -n 1`
  echo "Temperature : $temperature°C, > $maxtemp, waiting";
  sleep 1;
done;
# echo "Temperature : $temperature°C, ok :)";
