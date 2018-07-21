# Makefile

bin/main: *.c
	$(CC) $(CFLAGS) -o $@ *.c

clean:
	rm -f bin/*

.PHONY: clean
