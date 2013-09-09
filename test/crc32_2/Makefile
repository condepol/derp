execution: compile
	./crc32 a4f8e6f4

compile: main.c
	clear
	gcc -g -Wall -ansi -pedantic main.c -o crc32 -O3 -fomit-frame-pointer -lpthread -lssl -std=c99
