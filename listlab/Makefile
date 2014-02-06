all:
	@echo "make list-test|speed-test|test-menu"

list-test: test.exe
test.exe: mylist.h test.cpp
	g++ -o test.exe test.cpp

speed-test: test-speed.exe
test-speed.exe: test-speed.cpp mylist.h
	g++ -o test-speed.exe test-speed.cpp

speed-test2: test-speed2.exe
test-speed2.exe: test-speed2.cpp mylist.h
	g++ -o test-speed2.exe test-speed2.cpp

test-menu: test-menu.cpp mylist.h
	g++ -g -o test-menu test-menu.cpp
	
clean-test-menu:
	rm -f test-menu
