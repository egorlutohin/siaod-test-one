#include <iostream>
#include <cstdlib>
#include "mylist.h"
using namespace std;

#define TAB "\t"

List<int>* make_list(int max_val, int size) {
	List<int> *l = new List<int>();
	for(int i = 0; i < size; i++){
		l->insert(rand() % max_val);
	}
	
	return l;
}

int main(int argc, char **argv){
	List<int> *l;
	
	cout << "Input MAX value: " ;
	int max_val;
	cin >> max_val;
	
	cout << "Input size of list: " ;
	int size;
	cin >> size;
	
	int repeats = size / 2;
	int num_search, num_insert, num_delete;
	cout << "Amount" TAB "Search" TAB "Insert" TAB "Delete" << endl; 
	
	l = make_list(max_val, size);
		
	
		num_search = num_insert = num_delete = 0;
		
		for(int j=0; j < repeats; j++) {
			l->has_value(rand()%max_val);
			num_search+= l->get_seek_num();
			
			l->insert(rand() % size, rand()%max_val);
			num_insert+= l->get_seek_num();
			
			l->del_by_num(rand() % size);
			num_delete+= l->get_seek_num();
		}
		
		num_search = num_search / repeats;
		num_insert = num_insert / repeats;
		num_delete = num_delete / repeats;
		
		cout << size << TAB << num_search << TAB << num_insert << TAB << num_delete << endl;
	
	return 0;
}
