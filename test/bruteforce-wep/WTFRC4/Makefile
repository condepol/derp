m="main.c"
e="executable"

execute: compile
	./${e} | hd

compile: main.c
	clear
	gcc -Werror -Wall -ansi -pedantic -std=c99 ${m} -o ${e}
