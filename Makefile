CC=gcc
CFLAGS=$(shell /usr/xenomai/bin/xeno-config --alchemy --cflags)
LDFLAGS=$(shell /usr/xenomai/bin/xeno-config --alchemy --ldflags)


all:
	$(CC) -o app1 $(CFLAGS) $(LDFLAGS) app1.c
	$(CC) -o app2 $(CFLAGS) $(LDFLAGS) app2.c
