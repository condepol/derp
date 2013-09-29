m="main.c"
e="executable"

execute: compile
	cat random | ./${e}
	python -c 'import sys;sys.stdout.write("".join([chr(i) for i in xrange(0x100)]));' | ./${e}

compile: main.c
	clear
	gcc -Wall -ansi -pedantic -std=c99 ${m} -o ${e}
