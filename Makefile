CC=gcc


CFLAGS =-c -Wall



all: server
all: client

client: major2cli.o
	$(CC) major2cli.o -o client


server: major2srv.o 
	$(CC) -pthread major2srv.o -o server 

major2cli.o: major2cli.c
	$(CC) $(CFLAGS) major2cli.c

major2srv.o: major2srv.c
	$(CC) $(CFLAGS) -pthread major2srv.c 


clean:
	rm -rf *o server client
