CC=gcc
CFLAG=-ansi -Wall

test2: test CLEAN


test: test.o ll.o fs.o
	$(CC) $(CFLAG) -o test test.o ll.o fs.o

test.o: test.c
	$(CC) $(CFLAG) -c test.c

ll.o: ll.c
	$(CC) $(CFLAG) -c ll.c

fs.o: fs.c
	$(CC) $(CFLAG) -c fs.c

run: test
	./test

CLEAN:
	rm *.o


