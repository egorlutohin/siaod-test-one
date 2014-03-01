all: test-speed test-menu unittests
help:
	@echo "make test-menu|test-speed|unittests|clean"

test-speed: test-speed.cpp mylist.h
	g++ -g -o test-speed test-speed.cpp

test-menu: test-menu.cpp mylist.h
	g++ -g -o test-menu test-menu.cpp

unittests: unittests.cpp mylist.h
	g++ -g -Wall -o unittests unittests.cpp -lgtest -lpthread

clean-test-menu:
	rm -f test-menu

clean-test-speed:
	rm -f test-speed

clean-unittests:
	rm -f unittests

clean: clean-unittests clean-test-menu clean-test-speed

.PHONY: all help clean clean-test-menu clean-test-speed clean-unittests 
