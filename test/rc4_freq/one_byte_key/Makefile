m="main.c"
e="executable"

execute: compile
	./${e}
	avconv -f image2 -i output-%03d.ppm -r 10 video.mkv

compile: main.c
	clear
	gcc -Wall -ansi -pedantic -std=c99 ${m} -o ${e}
