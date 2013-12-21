all:hello-world

CC=g++
CPPFLAGS=-Wall -std=c++11 -ggdb
LDFLAGS=-pthread

hello-world:hello-world.o
	$(CC) $(LDFLAGS) -o $@ $^

hello-world.o:hello-world.cc
	$(CC) $(CPPFLAGS) -o $@ -c $^

.PHONY:
	clean

clean:
	rm hello-world.o hello-world
