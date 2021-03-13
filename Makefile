
all:	compile

compile:main.c
	gcc main.c -o main
	./main

clean:	main.c
	rm main
