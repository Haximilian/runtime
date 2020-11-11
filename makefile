CC=gcc
CFLAGS=-O0

all: 
	$(CC) $(CFLAGS) main.c yeild.c create.c dispatcher.c process.c contextSwitcher.c