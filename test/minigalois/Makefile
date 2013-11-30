all: exec count
count: gf.c gf.py
	wc -c gf.*
build: gf.c gf.py
	gcc gf.c
exec: build
	./a.out | hd
	python gf.py

