#!/bin/sh

timeout=10
archive_name="screenshots.7z"
hashes_filename=".screenshots_hashs.txt"

take_screenshot () {
  scrot $1;
}

touch ${hashes_filename}
while true;
do
  filename=`date "+%Y-%m-%d_%H-%M-%S.png"`;
  take_screenshot ${filename};
  this_file_sum=`md5sum ${filename} | awk '{print $1}'`;
  if grep -Fxq "${this_file_sum}" "${hashes_filename}";
  then
    echo "\033[31mNot adding duplicate screenshot\033[0m";
  else
    echo ${this_file_sum} >> ${hashes_filename};
    echo "\033[32mAdding ${filename}\033[0m";
    7z a ${archive_name} -m0=lzma -mx=9 -mfb=64 -md=32m -ms=on -p7z ${filename} >/dev/null;
  fi

  rm ${filename};
  sleep ${timeout};
done  

