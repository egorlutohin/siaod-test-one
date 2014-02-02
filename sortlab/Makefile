all:
	@echo "Type target please: test-menu simple-speed-test advanced-speed-test"

test: test.cpp myvector.h
	g++ -o test -g -DIAMREMEMBER test.cpp
menu-test: menu-test.cpp myvector.h
	g++ -g -DIAMREMEMBER -Dunix menu-test.cpp -o  menu-test
	
# bla-bla
speed-test-simple-sort: speed-test-simple-sort.cpp myvector.h
	g++ -g -DIAMREMEMBER -o speed-test-simple-sort speed-test-simple-sort.cpp
	
# bla-bla
speed-test-advanced-sort-2: speed-test-advanced-sort.cpp myvector.h
	g++ -DIAMREMEMBER -DDIMENSION=2 -o speed-test-advanced-sort-2 speed-test-advanced-sort.cpp

speed-test-advanced-sort-256: speed-test-advanced-sort.cpp myvector.h
	g++ -DIAMREMEMBER -DDIMENSION=256 -o speed-test-advanced-sort-256 speed-test-advanced-sort.cpp
