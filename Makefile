exec:
	gcc -o main main.c
	./main

clean:
	rm -f main

.PHONY: exec clean
