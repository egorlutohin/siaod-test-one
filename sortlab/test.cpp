#include <iostream>

#include "myvector.h"

using namespace std;

int main(){
	Vector<int> v;
	v.random_init();
	cout << v;
	
	Vector<int>::Iterator it(&v);
	cout << "Let's simplify values in vector:" << endl;
	it.begin();
	do {
		*it%=1000;
	} while(it.next());
	cout << v << endl;

	
	//~ v.lsd_sort();
	//~ try {
		//~ v.lsd_sort(10);
	//~ } catch (char const *s) {
		//~ cout << "Error: " << s << endl;
	//~ }
	
	v.lsd_sort();
	cout << v;
	
	return 0;
}
