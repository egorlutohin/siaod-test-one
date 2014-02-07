#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <limits>

#include "mylist.h"

using namespace std;

#if unix 
	#define CLEAR_SCREEN system("clear") // for linux
#else
	#define CLEAR_SCREEN system("cls") // for win32
#endif

namespace o {
	enum option {
		O_START, 
		O_PRINT, O_TELL_DIMENSION, O_SIMPLE_INSERT, O_INSERT_VALUE, O_CLEAN_LIST,  
		O_INSERT10, O_CHANGE_LIST_ELEMENT, O_GET_INDEX_BY_VALUE,
		O_GET_VALUE_BY_INDEX, O_DEL_BY_VALUE, O_DEL_BY_INDEX, O_ITERATOR_TEST,
		O_SET_ITERATOR_AT_BEGIN, O_SET_ITERATOR_AT_END, O_ITERATOR_NEXT, O_ITERATOR_PREV,
		O_ITERATOR_GET_CURRENT, O_ITERATOR_SET_CURRENT, O_ITERATOR_INFO,
		O_EXIT,
		O_END
	};
}

o::option menu(){
	int i = 0; // option number
menu_start:	
	CLEAR_SCREEN;
	
	cout << "Pleause select the option:" << endl;
	cout << o::O_PRINT << ". Print list" << endl;
	cout << o::O_TELL_DIMENSION << ". Tell dimension of list" << endl;
	cout << o::O_SIMPLE_INSERT << ". Insert value in list" << endl;
	cout << o::O_INSERT_VALUE << ". Insert value in list at position" << endl;
	cout << o::O_CLEAN_LIST << ". Clear list" << endl;
	cout << o::O_INSERT10 << ". Insert 10 elements" << endl;
	cout << o::O_CHANGE_LIST_ELEMENT <<". Change element of vector" << endl;
	cout << o::O_GET_INDEX_BY_VALUE << ". Get index by value" << endl;
	cout << o::O_GET_VALUE_BY_INDEX << ". Get value by index" << endl;
	cout << o::O_DEL_BY_VALUE << ". Delete by value" << endl;
	cout << o::O_DEL_BY_INDEX << ". Delete by index" << endl;
	cout << o::O_ITERATOR_TEST << ". Iterator test" << endl;
	
	cout << o::O_SET_ITERATOR_AT_BEGIN << ". Set iterator at begin" << endl;
	cout << o::O_SET_ITERATOR_AT_END << ". Set iterator at end" << endl;
	cout << o::O_ITERATOR_NEXT << ". Move iterator to next value" << endl;
	cout << o::O_ITERATOR_PREV << ". Move iterator to previous value" << endl;
	cout << o::O_ITERATOR_GET_CURRENT << ". Get current value of iterator" << endl;
	cout << o::O_ITERATOR_SET_CURRENT	<< ". Set current value of iterator" << endl;
	cout << o::O_ITERATOR_INFO << ". Tell iterator info" << endl;
	
	cout << o::O_EXIT << ". Exit from program" << endl;
	
	cout << ">> ";
	cin >> i;
	cin.clear();
	cin.ignore(256, '\n');
	
	if ((i <= o::O_START) || (i >= o::O_END)){
		goto menu_start;
	}
	
	return (o::option)i;
}


int main(int argc, char **argv){
	
	List<int> l;
	List<int>::Iterator it(&l);
	o::option o;	
	
	while (true) {
		o = menu();
		CLEAR_SCREEN;

		try {switch (o) {
			case o::O_PRINT:
				cout << l;
				break;
			
			case o::O_TELL_DIMENSION:
				cout << l.get_size() << endl;
				break;
			
			case o::O_SIMPLE_INSERT:
				{
					cout << "Value: ";
					int v;
					cin >> v;
					l.insert(v);
					cout << l;
				}
				break;
	
			
			case o::O_INSERT_VALUE:
				{
				int i, j;
				cout << "Index: ";
				cin >> i;
				cout << "Value: ";
				cin >> j;
				l.insert(i, j);
				cout << l;
				}
				break;
			
			case o::O_CLEAN_LIST:
				l.clean();
				cout << l << endl;
				break;
			
			case o::O_INSERT10:
				{
					for (int i=10; i <= 100; i+=10)
						l.insert(i);
					cout << l;
				}
				break;
			
			case o::O_CHANGE_LIST_ELEMENT:
				{
				int i, j;
				cout << "Index: ";
				cin >> i;
				cout << "Value: ";
				cin >> j;
				l[i] = j;
				cout << l;
				}
				break;
			
			case o::O_GET_INDEX_BY_VALUE:
				{
				cout << "Value: ";
				int v, i;
				cin >> v;
				i = l.get_num_by_value(v);
				cout << l;
				cout << "Index: " << i << endl;
				cout << "Number of seeks: " << l.get_seek_num() << endl;
				}
				break;
				
			case o::O_DEL_BY_VALUE:
				{
					cout << l;
					cout << "Value: ";
					int v;
					cin >> v;
					cin.clear();
					cin.ignore(256, '\n');
					l.del_by_val(v);
					cout << l;
					cout << "Number of seeks: " << l.get_seek_num() << endl;
				}
				break;
				
			case o::O_DEL_BY_INDEX:
				{
					cout << l;
					cout << "Index: ";
					int i;
					cin >> i;
					l.del_by_num(i);
					cout << l;
					cout << "Number of seeks: " << l.get_seek_num() << endl;
				}
				break;
			case o::O_GET_VALUE_BY_INDEX:
				{
				int i;
				cout << "Index: ";
				cin >> i;
				cout << l;
				cout << "Value: " << l[i] << endl;
				}
				break;
			case o::O_ITERATOR_TEST:
				cout << l << endl;
				cout << "First three values: " << it.begin();
				it++;
				cout << " " << *it;
				it++;
				cout << " " << *it << endl;
				cout << "Last three values: " << it.end();
				it--;
				cout << " " << *it;
				it--;
				cout << " " << *it << endl;
				cout << endl;
				cout << "On boundary (bool)?: " << it.in_boundary() << endl;
				cout << "Last value: " << it.end() << endl;
				it++;
				cout << "Next three values: " << *it << " ";
				it++;
				cout << *it << " ";
				it++;
				cout << *it << endl;
				cout << "On boundary (bool)?: " << it.in_boundary() << endl;
				break;
			case o::O_SET_ITERATOR_AT_BEGIN:
				it.begin();
				cout << "Current index: " << it.tell_index() << endl;
				break;
			case o::O_SET_ITERATOR_AT_END:
				it.end();
				cout << "Current index: " << it.tell_index() << endl;
				break;
			case o::O_ITERATOR_NEXT:
				it++;
				cout << "Current index: " << it.tell_index() << endl;
				break;
			case o::O_ITERATOR_PREV:
				it--;
				cout << "Current index: " << it.tell_index() << endl;
				break;
			case o::O_ITERATOR_GET_CURRENT:
				cout << "Index: " << it.tell_index() << endl;
				cout << "Value: " << *it << endl;
				break;
			case o::O_ITERATOR_SET_CURRENT:
				cout << "Index: " << it.tell_index() << endl;
				{
					int v;
					cout << "Value: ";
					cin >> v;
					*it = v;
				}
				break;
				
			case o::O_ITERATOR_INFO:
				cout << "Current index: " << it.tell_index() << endl;
				cout << "Current counter: " << it.tell_counter() << endl;
				cout << "In boundary: " << it.in_boundary() << endl;
				break;
			
			case o::O_EXIT:
				cout << "Good bye!" << endl;
				exit(0);
				break;
			
		}} catch (const char *m) {
			cerr << "Error: " << m << endl;;
		}
		//getchar();
		cout << "Press enter to continue ... ";
		getchar();
	}
	
	return 0;
}
