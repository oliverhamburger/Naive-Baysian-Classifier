CFLAGS = -std=c99 -Wall
CC = gcc

naive_bayesian_classifier: main.o functions.o
	$(CC) $(CFLAGS) main.o functions.o -o naive_bayesian_classifier

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

functions.o: functions.c functions.h
	$(CC) $(CFLAGS) -c functions.c

clean:
	rm -f naive_bayesian_classifier *.o
