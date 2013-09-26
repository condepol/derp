m="main.c"
e="executable"

execute: compile
	cat random | ./${e}

compile: main.c
	clear
	gcc -Wall -ansi -pedantic -std=c99 ${m} -o ${e}
