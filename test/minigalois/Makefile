all: exec count
count: gf.c gf.py
	wc -c gf.* | sort -n
build: gf.c gf.py
	gcc gf.c
exec: build
	./a.out | validator.py
	python gf.py | validator.py
	perl gf.pl | validator.py

