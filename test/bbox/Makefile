az:
	gcc -Wall -ansi -pedantic -std=c99 -Werror -O3 -march=native -funroll-all-loops pwn.c sha1.c -o pwn
	echo "Should find 8716FEBAD3 because of the following:"
	python -c 'import hashlib;h=hashlib.sha1("CP084642394D").hexdigest().upper();print "\x1b[31m{}\x1b[0m{}\x1b[32m{}\x1b[0m".format(h[:10],h[10:-6],h[-6:])'
	./pwn 12345a
