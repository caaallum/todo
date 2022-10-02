include ../Makefile.am

CCFLAGS+=-c -fPIC $(shell pkg-config --cflags libxml-2.0) -DVERSION=\"${VERSION}\"
LDFLAGS=$(shell pkg-config --libs libxml-2.0)

SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)

LIB=todo_lib.so

all: config $(LIB)

help: # Print help on Makefile
	@grep '^[^.#]\+:\s\+.*#' Makefile | \
	sed "s/\(.\+\):\s*\(.*\) #\s*\(.*\)/`printf "\033[93m"`\1`printf "\033[0m"`	\3 [\2]/" | \
	expand -t20

config: # Output current build config
	@echo "CC      = $(CC)"
	@echo "LD      = $(LD)"
	@echo "CCFLAGS = $(CCFLAGS)"
	@echo "LDFLAGS = $(LDFLAGS)"

.PHONY: clean
clean: # Clean object and lib files
	@rm -f $(LIB) $(OBJ)

%.o: %.c
	@$(CC) $(CCFLAGS) -o $@ $< 
	@echo "CC $<"

$(LIB): $(OBJ)
	@$(LD) --shared -o $(LIB) $^ $(LDFLAGS)
	@echo "LD $(LIB)"

.PHONY: test
test: $(LIB) # Test library functionality
	$(MAKE) -C test