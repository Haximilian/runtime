CC=g++
CFLAGS=-O0 -g -std=c++11
INCLUDE := /Users/maximilian/Desktop/Language/VClock

all:
	$(CC) $(CFLAGS) -I $(INCLUDE) -L $(INCLUDE) queue.cpp user.cpp init.cpp yeild.cpp create.cpp dispatcher.cpp contextSwitcher.cpp
