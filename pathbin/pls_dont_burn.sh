#!/bin/bash
target_pid=$1
temp_max=75
work_time=0.1

echo "Seeking process ${target_pid}"
result=`kill -0 ${target_pid}`
while ${result};
do
  #echo "Stopping process ${target_pid} .."
  for fpid in $(ps -o pid --ppid=${target_pid} | tail -n +2) ; do kill -STOP $fpid ; done
  kill -STOP ${target_pid}
  #echo "Refreshing .."
  refre.sh $temp_max
  #echo "Working for ${work_time}s";
  kill -CONT ${target_pid}
  for fpid in $(ps -o pid --ppid=${target_pid} | tail -n +2) ; do kill -CONT $fpid ; done
  sleep ${work_time}
  result=`kill -0 ${target_pid}`
done
echo "Process ${target_pid} terminated"
