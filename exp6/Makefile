CC=gcc
CFLAGS=-Wall
PTHREADS=-lpthread

all: banker.o driver.o
	$(CC) $(CFLAGS) -o s banker.o driver.o $(PTHREADS)
banker.o: banker.c
	$(CC) $(CFLAGS) -c banker.c $(PTHREADS)
driver.o: driver.c
	$(CC) $(CFLAGS) -c driver.c $(PTHREADS)
clean:
	rm -rf *.o
	rm -rf s