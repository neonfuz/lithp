# Makefile

bin/main: *.c *.h
	$(CC) $(CFLAGS) -o $@ *.c

clean:
	rm -f bin/*

.PHONY: clean
