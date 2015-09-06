CC     = gcc
CFLAGS = -Wall -c -g
LFLAGS = -Wall -lm

all: main

main: greedy.o main.o general.o sa.o
	$(CC) $(LFLAGS) $^ -o $@

greedy.o: greedy.c
	$(CC) $(CFLAGS) $<

general.o: general.c
	$(CC) $(CFLAGS) $<

sa.o: sa.c
	$(CC) $(CFLAGS) $<

main.o: main.c
	$(CC) $(CFLAGS) $<


clean:
	find . -name '*.o' -type f -delete
	rm -f main
