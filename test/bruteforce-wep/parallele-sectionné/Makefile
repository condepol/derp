m=main.c
e=executable
a=assembleur.asm
out=bin/

execute: compile
	./${out}${e}
	./${out}${e} 0x1453 0x4545

compile: main.c
	clear
	gcc -Werror -Wall ${m} -o ${out}${a} -lrt -pthread -O3 -S
	gcc -Werror -Wall ${m} -o ${out}${e} -lrt -pthread -O3 -ggdb
