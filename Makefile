CFLAGS = -std=gnu89 --pedantic-errors -Os -Wall
duckpass: duckpass.o
clean:; rm -f duckpass *.o
