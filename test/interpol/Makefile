m="main.c"
e="executable"

execute: compile
	./${e} 5

compile: main.c
	clear
	gcc -Wall -ansi -pedantic -std=c99 ${m} -o ${e}
