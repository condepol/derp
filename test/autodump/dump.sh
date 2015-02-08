#!/bin/bash
interface=$1
channel=$2
filename=$3
echo "will dump on ${interface} - channel ${channel}"
airmon-zc start ${interface}
airodump-ng -c ${channel} -w ${filename} ${interface}mon
