all: build

build:
	$(MAKE) -C lib
	$(MAKE) -C cli
