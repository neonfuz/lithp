main: *.c
	$(CC) -o $@ *.c

clean:
	rm -f main

.PHONY: clean
