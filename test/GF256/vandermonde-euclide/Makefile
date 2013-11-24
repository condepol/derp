tout: euclide
	./euclide > euclide.ppm
euclide: main.c
	gcc -Werror -Wall -ansi -pedantic -std=c99 main.c -o euclide -lm
clean:
	rm -f euclide euclide.ppm
