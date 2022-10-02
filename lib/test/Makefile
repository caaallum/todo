include ../../Makefile.am

CCFLAGS+=$(shell pkg-config --cflags check)
LDFLAGS=$(shell pkg-config --libs check) ../todo_lib.so

TESTS=test_item test_group test_group_list

BIN=$(addsuffix .test, $(TESTS))
 
all: run
.PHONY: clean

clean:
	@echo $(BIN)
	@rm -f $(BIN)

%.test: %.c
	@$(CC) -o $@ $< $(CCFLAGS) $(LDFLAGS)

run: $(BIN)
	@for test in $(BIN); do ./$$test; done
