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
		O_PRINT=1, O_TELL_DIMENSION, O_SIMPLE_INSERT, O_INSERT_VALUE, O_CLEAN_LIST,
		O_INSERT10, O_CHANGE_LIST_ELEMENT, O_GET_INDEX_BY_VALUE,
		O_GET_VALUE_BY_INDEX, O_DEL_BY_VALUE, O_DEL_BY_INDEX,
		O_SET_ITERATOR_AT_BEGIN, O_ITERATOR_NEXT,
		O_ITERATOR_GET_CURRENT, O_ITERATOR_SET_CURRENT, O_ITERATOR_INFO,
		O_EXIT,
	};
}

int get_int() {
	int i;
	cin >> i;
	cin.clear();
	cin.ignore(256, '\n');
	return i;
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
	cout << o::O_CHANGE_LIST_ELEMENT <<". Change list element" << endl;
	cout << o::O_GET_INDEX_BY_VALUE << ". Get index by value" << endl;
	cout << o::O_GET_VALUE_BY_INDEX << ". Get value by index" << endl;
	cout << o::O_DEL_BY_VALUE << ". Delete by value" << endl;
	cout << o::O_DEL_BY_INDEX << ". Delete by index" << endl;
	cout << o::O_SET_ITERATOR_AT_BEGIN << ". Set iterator at begin" << endl;
	cout << o::O_ITERATOR_NEXT << ". Move iterator to next value" << endl;
	cout << o::O_ITERATOR_GET_CURRENT << ". Get current value of iterator" << endl;
	cout << o::O_ITERATOR_SET_CURRENT	<< ". Set current value of iterator" << endl;
	cout << o::O_ITERATOR_INFO << ". Tell iterator info" << endl;
	
	cout << o::O_EXIT << ". Exit from program" << endl;
	
	cout << ">> ";

	i = get_int();
	
	return (o::option)i;
}


int main(int argc, char **argv){
	
	List<int> l(100);
	List<int>::Iterator it(&l);
	it.begin();
	o::option o;	
	
	while (true) {
		o = menu();
		CLEAR_SCREEN;

		try {switch (o) {
			case o::O_PRINT:
				cout << l.to_string() << endl;
				break;
			case o::O_TELL_DIMENSION:
				cout << l.get_size() << endl;
				break;
			case o::O_SIMPLE_INSERT:
				{
					cout << "Value: ";
					int v = get_int();
					l.insert(v);
					cout << l.to_string() << endl;
					cout << "Number of seeks: " << l.get_seek_num() << endl;
				}
				break;
			case o::O_INSERT_VALUE:
				{
				int i, j;
				cout << "Index: ";
				i = get_int();
				cout << "Value: ";
				j = get_int();
				l.insert(i, j);
				cout << l.to_string() << endl;
				cout << "Number of seeks: " << l.get_seek_num() << endl;
				}
				break;
			case o::O_CLEAN_LIST:
				l.clean();
				cout << l.to_string() << endl;
				break;
			case o::O_INSERT10:
				{
					for (int i=10; i <= 100; i+=10)
						l.insert(i);
					cout << l.to_string() << endl;
				}
				break;
			case o::O_CHANGE_LIST_ELEMENT:
				{
				cout << l.to_string() << endl;
				int i, j;
				cout << "Index: ";
				i = get_int();
				cout << "Value: ";
				j = get_int();
				l.change_value_by_number(i, j);
				cout << l.to_string() << endl;
				cout << "Number of seeks: " << l.get_seek_num() << endl;
				}
				break;
			case o::O_GET_INDEX_BY_VALUE:
				{
				cout << l.to_string() << endl;
				cout << "Value: ";
				int v, i;
				v = get_int();
				i = l.get_value_position(v);
				cout << "Index: " << i << endl;
				cout << "Number of seeks: " << l.get_seek_num() << endl;
				}
				break;
			case o::O_DEL_BY_VALUE:
				{
					cout << l.to_string() << endl;
					cout << "Value: ";
					int v = get_int();
					l.delete_by_value(v);
					cout << l.to_string() << endl;
					cout << "Number of seeks: " << l.get_seek_num() << endl;
				}
				break;
			case o::O_DEL_BY_INDEX:
				{
					cout << l.to_string() << endl;
					cout << "Index: ";
					int i = get_int();
					l.delete_by_number(i);
					cout << l.to_string() << endl;
					cout << "Number of seeks: " << l.get_seek_num() << endl;
				}
				break;
			case o::O_GET_VALUE_BY_INDEX:
				{
				cout << l.to_string() << endl;
				cout << "Index: ";
				int i = get_int();
				cout << "Value: " << l[i] << endl;
				cout << "Number of seeks: " << l.get_seek_num() << endl;
				}
				break;
			case o::O_SET_ITERATOR_AT_BEGIN:
				it.begin();
				cout << l.to_string() << endl;
				cout << "Current index: " << it.get_current_position() << endl;
				break;
			case o::O_ITERATOR_NEXT:
				cout << l.to_string() << endl;
				it.next();
				cout << "Current index: " << it.get_current_position() << endl;
				break;
			case o::O_ITERATOR_GET_CURRENT:
				cout << l.to_string() << endl;
				cout << "Index: " << it.get_current_position() << endl;
				cout << "Value: " << *it << endl;
				break;
			case o::O_ITERATOR_SET_CURRENT:
				cout << l.to_string() << endl;
				cout << "Index: " << it.get_current_position() << endl;
				{
					cout << "Value: ";
					int v = get_int();
					*it = v;
				}
				cout << l.to_string() << endl;
				break;
			case o::O_ITERATOR_INFO:
				cout << l.to_string() << endl;
				cout << "Current index: " << it.get_current_position() << endl;
				cout << "In boundary: " << it.in_boundary() << endl;
				cout << "In begin (bool): " << it.in_begin() << endl;
				cout << "In end (bool): " << it.in_end() << endl;
				break;
			case o::O_EXIT:
				cout << "Good bye!" << endl;
				exit(0);
				break;
			default:
				cerr << "Error: Invalid option number" << endl;
				break;
		}} catch (const char *m) {
			cerr << "Error: " << m << endl;;
		}
		cout << "Press enter to continue ... ";
		getchar();
	}
	
	return 0;
}
