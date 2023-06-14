run: build
	./main

build: main.o
	gcc $^ -o main

main.o: main.c
	gcc -Wall -c main.c -o main.o

clear:
	rm main