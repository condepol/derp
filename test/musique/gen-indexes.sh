#!/bin/bash

IFS='
'

# enumerate subfolders
for root_folder in `find $1 -type d `;
do
  echo $root_folder
  target=${root_folder}/index.html
  # put header
  cat header.html > ${target};
  # title
  echo ${root_folder##data/} >> ${target}
  # mid header
  cat header2.html >> ${target}
  # fill playlist
  for file in `find ${root_folder} -type f -name \*.mp3 | sort `;
  do
    sed -i -e 's/LASTVIRGULE/,/g' ${target}
    #track_name=`exiftool ${file} | grep Title | sed -e 's/.* : //g' `
    track_name=`basename ${file%%.mp3}`
    poster=`dirname ${file}`/cover.jpg
    echo "  {" >> ${target}
    echo "    title:\"${track_name}\"," >> ${target}
    echo "    mp3:\"/musique/${file}\"," >> ${target}
    echo "    oga:\"/musique/${file%%mp3}ogg\"," >> ${target}
    echo "    free: true," >> ${target}
    echo "    poster: \"/musique/${poster}\"," >> ${target}
    echo "  }LASTVIRGULE" >> ${target}
  done;
  sed -i -e 's/LASTVIRGULE//g' ${target}
  # put page header
  cat end_header.html >> ${target}
  echo "<h2>♫ ♬ 🎜 🎝 🎶</h2>" >> ${target};
  echo "<h3>${root_folder##data/}</h3>" >> ${target};
  parent=`dirname ${root_folder%%/}`
  echo "Parent : <a href=\"/musique/${parent}\">${parent}</a><br>" >> ${target};
  # put subfolder list
  for subfolder in `find ${root_folder} -type d`;
  do
    echo "<a href=\"/musique/${subfolder}\">${subfolder##data/}</a><br>" >> ${target};
  done
  # put player 
  cat player.html >> ${target}

  echo "</body></html>" >> ${target};
done;
