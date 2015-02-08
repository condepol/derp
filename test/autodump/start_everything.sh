#!/bin/bash

# 0. Get boot count
# (lol no internal clock on rpi)
boot_count=$(cat /home/pi/.boot_count)
echo -n $(( ${boot_count} + 1 )) > /home/pi/.boot_count
chown pi:pi /home/pi/.boot_count
echo "Boot n° ${boot_count}"

# 1. make a work folder
now=$(date +"%F:%T")
prefix=$(printf "%08x" ${boot_count})
root_suffix="${prefix}_${now}"
root_folder="/mnt/usb/data_dumps/${root_suffix}/"
if [ ! -d /mnt/usb/data_dumps/ ]
then
  echo "No USB key."
  exit 0
fi
mkdir -p $root_folder
cd $root_folder
echo "Initialized /mnt/usb/data_dumps/${root_suffix}/"
# todo : check root folder mount status

# 2. diagnose stuff
mkdir metadata
lsusb > metadata/lsusb.txt
airmon-zc > metadata/airmon-zc.txt
df > metadata/df.txt
df -h > metadata/df-h.txt
ip link show | grep wlan | awk '{print substr($2,0,length($2))}' > interfaces.txt
echo "Metadata done"

# 3. Assign channels
interfaces_count=$(wc -l interfaces.txt | awk '{print $1}')
if [ ${interfaces_count} -lt 1 ]
then
  echo "No interface, abort."
  exit 0
fi

echo "Detected ${interfaces_count} interfaces :"
cat interfaces.txt

tmux new-session -s dump -d
if [ ${interfaces_count} -ge 1 ]
then
  interface=$(head -n 1 interfaces.txt | tail -n 1)
  channel=1
  tmux new-window -P -t "dump:1" -n "c${channel}_${interface}" "/home/pi/autodump/dump.sh ${interface} ${channel} ${root_folder}/chan${channel}"
fi

if [ ${interfaces_count} -ge 2 ]
then
  interface=$(head -n 2 interfaces.txt | tail -n 1)
  channel=6
  tmux new-window -P -t "dump:2" -n "c${channel}_${interface}" "/home/pi/autodump/dump.sh ${interface} ${channel} ${root_folder}/chan${channel}"
fi

if [ ${interfaces_count} -ge 3 ]
then
  interface=$(head -n 3 interfaces.txt | tail -n 1)
  channel=12
  tmux new-window -P -t "dump:3" -n "c${channel}_${interface}" "/home/pi/autodump/dump.sh ${interface} ${channel} ${root_folder}/chan${channel}"
fi




