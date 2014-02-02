#include <iostream>
#include <cstring>
#include "myvector.h"

using namespace std;

#define TAB "\t"

#ifndef DIMENSION
	# error "Put DIMENSION (power of 2) in -D flag!!!"
#endif

void middle_case_init(Vector<int> &v) {
	v.random_init();
}

void worst_case_init(Vector<int> &v) {
	
	Vector<int>::Iterator iter(&v);
	iter.begin();
	for(int i=(v.size() - 1); i >=0; i--){
		*iter = i;
		iter.next();
	}
}

void (*vector_init)(Vector<int> &v);

int main(int argc, char **argv){
	
	if (argc >= 2 && strcmp("middle", argv[1]) == 0) {
		vector_init = &middle_case_init;
	
	} else if (argc >= 2 && strcmp("worst", argv[1]) == 0) {
		vector_init = &worst_case_init;
		
	} else {
		cerr << "Compiled dimension: " << DIMENSION << endl;
		cerr << "error: bad argument" << endl;
		cerr << "help: " << argv[0] << " middle|worst" << endl;
		return 0;
	}
	
	Vector<int> v;
	Vector<int>::Iterator iter(&v);
	int c, e, //comparisons and exchanges
	    da; // amount increment
	

	cout << "Amount" TAB "Comp." TAB "Exch." TAB "Total"  TAB "Theory"<< endl;
	for(int amount=1000; amount <= 8000; amount+=1000){
		
		v.resize(amount);
		
		(*vector_init)(v);
		
		
		v.lsd_sort(DIMENSION);
		
		c = v.get_comparison_num();
		e = v.get_exchange_num();
		
		int m;
		if (DIMENSION == 2)
			m = 32;
		else if (DIMENSION == 256)
			m = 4;
		else m = 0;
		
		cout << v.size() << TAB << c << TAB << e << TAB << c+e << TAB <<  m*v.size() << endl;
		
	}
	
	return 0;
}
