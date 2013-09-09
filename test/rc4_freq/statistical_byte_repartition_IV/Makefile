m="main.c"
e="executable"

execute: compile
	./${e}
	display output.ppm

compile: main.c
	clear
	gcc -Wall -ansi -pedantic -std=c99 ${m} -o ${e}
