# Makefile

bin/main: *.c
	$(CC) $(CFLAGS) -o $@ *.c

clean:
	rm -f main

.PHONY: clean
