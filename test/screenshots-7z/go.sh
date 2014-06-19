#!/bin/sh

timeout=1
archive_name="screenshots.7z"

take_screenshot () {
  echo $RANDOM > $1;
}

while true;
do
  filename=$(date "+%Y-%m-%d_%H-%M-%S.png");
  take_screenshot ${filename};
  7z a ${archive_name} -p7z ${filename};
  rm ${filename};
  sleep ${timeout};
done  
