all: 
	gcc -c main.c
	gcc -o main main.o
	./main

clean:
	rm main.o
	rm main