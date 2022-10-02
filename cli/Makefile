include ../Makefile.am

CCFLAGS+=-Wall -Wextra --std=c99 -c $(shell pkg-config --cflags glib-2.0) -I../lib -DVERSION=\"$(VERSION)\"
LDFLAGS=$(shell pkg-config --libs glib-2.0) ../lib/todo_lib.so

SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)

BIN=todo

all: config build

help: # Print help 
	@grep '^[^.#]\+:\s\+.*#' Makefile | \
	sed "s/\(.\+\):\s*\(.*\) #\s*\(.*\)/`printf "\033[93m"`\1`printf "\033[0m"`	\3 [\2]/" | \
	expand -t20

config: # Output build config
	@echo "CC      = $(CC)"
	@echo "LD      = $(LD)"
	@echo "CCFLAGS = $(CCFLAGS)"
	@echo "LDFLAGS = $(LDFLAGS)"

.PHONY: clean

clean: # Clean object and binary files
	@rm -f $(BIN) $(OBJ)

%.o: %.c
	@$(CC) $(CCFLAGS) -o $@ $<
	@echo "CC $<"

build: $(OBJ) ../lib/todo_lib.so
	@$(LD) -o $(BIN) $^ $(LDFLAGS)
	@echo "LD $(BIN)"
