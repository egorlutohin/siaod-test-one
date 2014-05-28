all: unittests test-speed
help:
	@echo "make unittests|test-speed|test-menu|pdf|clean"

test-speed: test-speed.cpp mybst.h
	g++ -g -Wall -o test-speed test-speed.cpp

test-menu: test-menu.cpp mylist.h
	g++ -g -o test-menu test-menu.cpp

unittests: unittests.cpp mybst.h
	g++ -g -Wall -o unittests unittests.cpp -lgtest -lgtest_main -lpthread

pdf:
	libreoffice --headless --convert-to pdf report-bstlab.odt 

clean-test-menu:
	rm -f test-menu

clean-test-speed:
	rm -f test-speed

clean-unittests:
	rm -f unittests

clean-pdf:
	rm -rf *.pdf

clean: clean-unittests clean-test-menu clean-test-speed clean-pdf

.PHONY: all help clean clean-test-menu clean-test-speed clean-unittests pdf clean-pdf
