CC=gcc
CFLAGS=-O0 -g

all:
	$(CC) $(CFLAGS) user.c init.c yeild.c create.c dispatcher.c process.c contextSwitcher.c