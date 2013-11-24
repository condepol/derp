tout: meta-galois galois
	./galois > gf256.ppm
meta-galois: meta-main.c
	rm -f gf256.c
	gcc -Werror -Wall -ansi -pedantic -std=c99 meta-main.c -o meta-galois
	./meta-galois > gf256.c
galois: gf256.c main.c
	gcc -Werror -Wall -ansi -pedantic -std=c99 main.c -o galois
color: gf256.c main.c
	gcc -Dusecolor -Werror -Wall -ansi -pedantic -std=c99 main.c -o galois
clean:
	rm -f gf256.c galois meta-galois gf256.ppm
wtf:
	gcc -Wall -Werror -ansi -pedantic -std=c99 wtfcolumn.c -o wtf
	./wtf
