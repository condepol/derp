#!/bin/bash
username='americ'
echo -n "password[$username @ SERVER_NAS.local]:"
read -s password;
echo

echo "Folder"
mount -t cifs //SERVER_NAS.local/Folder /mount/point/ -o username=$username,password=$password,uid=1000,gid=1000,file_mode=0640,dir_mode=0750,dynperm;
