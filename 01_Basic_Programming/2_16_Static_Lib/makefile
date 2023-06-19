all: build
	./main

build: main.o func.o
	ar rcs libfunc.a func.o
	gcc main.o -L. -lfunc -o main

%.o: %.c
	gcc -c $< -o $@

clean:
	rm *.o *.a main

.PHONY: all build clean