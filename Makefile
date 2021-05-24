CC = gcc -std=gnu89 --pedantic-errors
CFLAGS = -Os -Wall

duckpass: duckpass.o
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)
clean:
	rm -f duckpass duckpass.o
