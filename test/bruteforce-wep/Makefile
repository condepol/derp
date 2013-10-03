m="main.c"
e="executable"
a="assembleur.asm"

execute: compile
	./${e}

compile: main.c
	clear
	gcc -Werror -Wall -ansi -pedantic -std=c99 ${m} -o ${e} -O3
	gcc -Werror -Wall -ansi -pedantic -std=c99 ${m} -S -o ${a} -O3
