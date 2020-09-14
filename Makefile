main: main.c
	gcc -Wall -o main main.c

clean:
	rm -f main

.PHONY: clean
