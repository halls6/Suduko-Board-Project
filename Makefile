all: 
	gcc -c main.c
	gcc -o main main.o -lpthread
	./main 1
	./main 2


clean:
	rm main.o
	rm main