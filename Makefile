exec:
	gcc -o hello hello.c
	./hello

clean:
	rm -f hello

.PHONY: exec clean
