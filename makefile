CC=gcc
CFLAGS=-O0 -g

all: 
	$(CC) $(CFLAGS) main.c yeild.c create.c dispatcher.c process.c contextSwitcher.c