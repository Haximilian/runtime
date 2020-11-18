CC=g++
CFLAGS=-O0 -g -std=c++11

all:
	$(CC) $(CFLAGS) queue.cpp user.cpp init.cpp yeild.cpp create.cpp dispatcher.cpp process.cpp contextSwitcher.cpp