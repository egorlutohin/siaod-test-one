#include <iostream>
using namespace std;
#include "mylist.h"

int main(int argc, char **argv){
	List<int> l;
	
	cout << "Empty list size: " <<l.get_size() << endl;
	cout << "Is list empty? " << l.is_empty() << endl;

	l.insert(10);
	l.insert(20);
	l.insert(30);
	l.insert(40);
	l.insert(50);
	l.insert(60);
	l.insert(70);
	cout << l;
	
	l.insert(0, 5);
	l.insert(2, 15);
	l.insert(7, 55);
	l.insert(8, 56);
	l.insert(11, 80);
	cout << l;
	try {
		l.insert(20, 0);
	} catch (const char *m) {
		cerr << "Error: " << m << endl;
	}
	l.insert(10, 65);
	l.insert(12, 75);
	
	cout << l;
	
	//~ cout << "Has value 80: " << l.has_value(80) << endl;
	//~ cout << "Has value 85: " << l.has_value(85) << endl;
	//~ cout << "Get value by number 3: " << l.get_value(3) << endl;
	//~ cout << "Get value by number 3 with operator `[]`: " << l[3] << endl;
	//~ try {
		//~ l[-1];
	//~ } catch (const char *m) {
		//~ cerr << "Error: " << m << endl;
	//~ }
	
	//~ (&l)->set_value(0, -1);
	//~ (&l)->get_value(0);
	//~ cout << l;
	
	//~ cout << "Get index of value 15: " << l.get_num_by_value(15) << endl;
	//~ cout << "Get index of value 115: " << l.get_num_by_value(115) << endl << endl;
	
	//~ cout << l;
	//~ cout << "Delete value -1: " <<  l.del_by_val(-1) << endl; // del by val
	//~ cout << "Delete value 15: " << l.del_by_val(15) << endl;
	//~ cout << "Delete value -1: " << l.del_by_val(-1) << endl;
	//~ cout << l;
	//~ cout << "Delete by index 2: " << l.del_by_num(2) << endl;
	//~ cout << l;
	
	//~ try {
		//~ l.del_by_num(21);
	//~ } catch (const char *m) {
		//~ cerr << "Error: " << m << endl;
	//~ }
	
	cout << "Iterator test" << endl;
	List<int>::Iterator i(&l);
	
	cout << "In boundary: " << i.in_boundary() << endl;
	while (i.in_boundary()) {
		cout << *i << " ";
		i++;
	}
	cout << endl;
	cout << i.end() << " ";
	i++;
	cout << *i << " ";
	i++;
	cout << *i << endl;
	
	i.end();
	while (i.in_boundary()) {
		cout << *i << " ";
		i--;
	}
	
	cout << endl;
	i--;
	cout << *i << " ";
	i--;
	cout << *i << endl;
	cout << "In boundary: " << i.in_boundary() << endl;

	
	return 0;
}
