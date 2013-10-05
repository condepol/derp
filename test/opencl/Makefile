m="main.c"
e="executable"

execute: compile
	./${e}

compile: main.c
	clear
	gcc -Wall -ansi -pedantic -std=c99 ${m} -o ${e} -I/opt/AMDAPP/include -L/opt/AMDAPP/lib/x86_64 -lOpenCL
