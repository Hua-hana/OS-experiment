CC=gcc
CFLAGS=-Wall
PTHREADS=-lpthread

all: vm_manager.o driver.o
	$(CC) $(CFLAGS) -o s vm_manager.o driver.o $(PTHREADS)
vm_manager.o: vm_manager.c
	$(CC) $(CFLAGS) -c vm_manager.c $(PTHREADS)
driver.o: driver.c
	$(CC) $(CFLAGS) -c driver.c $(PTHREADS)
clean:
	rm -rf *.o
	rm -rf s
	rm -rf out.txt
