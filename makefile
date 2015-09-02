CC     = gcc
CFLAGS = -Wall -c
LFLAGS = -Wall

all: main

main: greedy.o main.o general.o
	$(CC) $(LFLAGS) $^ -o $@

greedy.o: greedy.c
	$(CC) $(CFLAGS) $<

general.o: general.c
	$(CC) $(CFLAGS) $<

main.o: main.c
	$(CC) $(CFLAGS) $<


clean:
	find . -name '*.o' -type f -delete
	rm -f main
