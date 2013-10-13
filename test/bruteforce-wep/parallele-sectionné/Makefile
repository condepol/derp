m=main.c
e=executable
a=assembleur.asm
out=bin/

execute: compile
	./${out}${e}
	./${out}${e} 0x1453 0x4545

compile: main.c
	clear
	gcc -Werror -Wall -ansi -pedantic -std=c99 ${m} -o ${out}${a} -pthread -O3 -S
	gcc -Werror -Wall -ansi -pedantic -std=c99 ${m} -o ${out}${e} -pthread -O3 -ggdb
