#include <iostream>
#include <cstdlib>
#include <cstdio>

#include "myvector.h"

using namespace std;

#if unix 
	#define CLEAR_SCREEN system("clear") // for linux
#else
	#define CLEAR_SCREEN system("cls") // for win32
#endif

namespace o {
	enum option {
		O_START, 
		O_PRINT, O_TELL_DIMENSION, O_CHANGE_DIMENSION, 
		O_RANDOM_INIT, O_CHANGE_VECTOR_ELEMENT, O_ELEMENTARY_SORT,
		O_ADVANCED_SORT, O_ITERATOR_TEST, O_EXIT,
		O_END
	};
}

o::option menu(){
menu_start:	
	CLEAR_SCREEN;
	
	cout << "Pleause select the option:" << endl;
	cout << o::O_PRINT << ". Print vector" << endl;
	cout << o::O_TELL_DIMENSION << ". Tell dimension of vector" << endl;
	cout << o::O_CHANGE_DIMENSION << ". Change dimension of vector" << endl;
	cout << o::O_RANDOM_INIT << ". Fill vector values by random numbers" << endl;
	cout << o::O_CHANGE_VECTOR_ELEMENT <<". Change element of vector" << endl;
	cout << o::O_ELEMENTARY_SORT << ". Elementary sort of vector" << endl;
	cout << o::O_ADVANCED_SORT << ". Advanced sort of vector" << endl;
	cout << o::O_ITERATOR_TEST << ". Iterator test" << endl;
	cout << o::O_EXIT << ". Exit from program" << endl;
	
	
	char c;
	int i;
	cout << ">> ";
	cin >> c;
	i = c - '0';

	
	if ((i <= o::O_START) || (i >= o::O_END)){
		goto menu_start;
	}
	
	return (o::option)i;
}


int main(int argc, char **argv){
	
	Vector<int> v;
	Vector<int>::Iterator it(&v);
	o::option o;	
	
	while (true) {
		o = menu();
		CLEAR_SCREEN;

		try {switch (o) {
			case o::O_PRINT:
				cout << v;
				break;
			
			case o::O_TELL_DIMENSION:
				cout << v.size() << endl;
				break;
			
			case o::O_CHANGE_DIMENSION:
				int i;
				cout << "Print new size: ";
				cin.ignore();
				cin >> i;
				v.resize(i);
				cout << v;
				break;
			
			case o::O_RANDOM_INIT:
				v.random_init();
				cout << v << endl;
				
				cout << "Let's simplify values in vector:" << endl;
				it.begin();
				do {
					*it%=100;
				} while(it.next());
				cout << v << endl;
				break;
			
			case o::O_CHANGE_VECTOR_ELEMENT:
				{
					int j, k;
					cout << "Vector index: ";
					cin.ignore();
					cin >> j;
					cout << "Value: ";
					cin.ignore();
					cin >> k;
					v[j] = k;
					cout << v;
				}
				break;
			
			case o::O_ELEMENTARY_SORT:
				v.bubble_sort();
				cout << v;
				cout << "Comparisons number: " << v.get_comparison_num() << endl;
				cout << "Exchanges number: " << v.get_exchange_num() << endl;
				break;
			
			case o::O_ADVANCED_SORT:
				v.quick_recursion_sort();
				cout << v;
				cout << "Comparisons number: " << v.get_comparison_num() << endl;
				cout << "Exchanges number: " << v.get_exchange_num() << endl;
				break;
			
			case o::O_ITERATOR_TEST:
				cout << v << endl;
				cout << "First three values: " << it.begin();
				cout << " " << it++;
				cout << " " << it++ << endl;
				cout << "Last three values: " << it.end();
				cout << " " << it--;
				cout << " " << it-- << endl;
				cout << endl;
				cout << "On end boundary (bool): " << it.on_end_boundary() << endl;
				cout << "Last value: " << it.end() << endl;
				cout << "On end boundary (bool): " << it.on_end_boundary() << endl;
				cout << "Next three value: " << it++ << " ";
				cout << it++ << " ";
				cout << it++ << endl;
				break;

			case o::O_EXIT:
				cout << "Good bye!" << endl;
				exit(0);
				break;
			
		}} catch (const char *m) {
			cerr << "Error: " << m << endl;;
		}
		getchar();
		cout << "Press enter to continue ... ";
		getchar();
	}
	
	return 0;
}
