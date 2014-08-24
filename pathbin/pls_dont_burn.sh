#!/bin/bash
target_pid=$1
temp_max=58

echo "Seeking process ${target_pid}"
result=`kill -0 ${target_pid}`
while ${result};
do
  echo "Stopping process ${target_pid} .."
  kill -STOP ${target_pid}
  echo "Refreshing .."
  refre.sh $temp_max
  echo "Working for 30s";
  kill -CONT ${target_pid}
  sleep 20
  result=`kill -0 ${target_pid}`
done
echo "Process ${target_pid} terminated"
