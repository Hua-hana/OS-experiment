# makefile for thread pool
#

CC=gcc
CFLAGS=-Wall
PTHREADS=-lpthread

all: client.o threadpool.o
	$(CC) $(CFLAGS) -o s client.o threadpool.o $(PTHREADS)
cp: consumer_producer.o buffer.o
	$(CC) $(CFLAGS) -o cp consumer_producer.o buffer.o $(PTHREADS)
consumer_producer.o: consumer_producer.c
	$(CC) $(CFLAGS) -c consumer_producer.c $(PTHREADS)
buffer.o: buffer.c
	$(CC) $(CFLAGS) -c buffer.c $(PTHREADS)
client.o: client.c
	$(CC) $(CFLAGS) -c client.c $(PTHREADS)

threadpool.o: threadpool.c threadpool.h
	$(CC) $(CFLAGS) -c threadpool.c $(PTHREADS)

clean:
	rm -rf *.o
	rm -rf s
	rm -rf cp

