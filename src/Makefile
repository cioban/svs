CC = gcc
CFLAGS = -Wall -g -O2 `mysql_config --cflags` `pkg-config glib-2.0 --cflags` `pkg-config gthread-2.0 --cflags` `pkg-config gtk+-2.0 --cflags`
LIBS = $(PWD)/../lib/obj/lib/libconfuse.a `mysql_config --libs` `pkg-config glib-2.0 --libs` `pkg-config gthread-2.0 --libs` `pkg-config gtk+-2.0 --libs`

BINDIR = ../build

BIN = $(BINDIR)/svs
OBJS = database.o config.o pport.o main.o info.o gui.o
HEADERS = database.h config.h pport.h info.h gui.h

all: $(BIN)

$(BIN): $(HEADERS) $(OBJS) Makefile
	(mkdir -p $(BINDIR))
	$(CC) $(OBJS) -o $@ $(CFLAGS) $(LIBS)

clean:
	rm -f $(BINDIR)/* *.o

