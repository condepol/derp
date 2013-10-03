m=main.c
e=executable
a=assembleur.asm
out=bin/

execute: compile
	./${out}${e}

compile: main.c
	clear
	gcc -Werror -Wall -ansi -pedantic -std=c99 ${m} -o ${out}${a} -O3 -S
	gcc -Werror -Wall -ansi -pedantic -std=c99 ${m} -o ${out}${e} -O3
