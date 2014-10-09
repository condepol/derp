m=main.c
e=executable
b="bin/"

execute: compile
	./${b}/${e}
	./${b}/${e} 0x1453 0x4545

compile: main.c
	mkdir -p ${b}/
	gcc -Werror -Wall ${m} -o ${b}/${e} -lrt -pthread -O3 -march=native -fno-stack-protector
