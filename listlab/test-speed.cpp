#include <iostream>
#include <cstdlib>
#include "mylist.h"
using namespace std;

#define TAB "\t"

List<int>* make_list(int amount) {
	List<int> *l = new List<int>();
	for(int i = 0; i < amount; i++){
		l->insert(rand());
	}
	
	return l;
}

int main(int argc, char **argv){
	List<int> *l;
	
	int repeats;
	int num_search, num_insert, num_delete;
	cout << "Amount" TAB "Search" TAB "Insert" TAB "Delete" << endl; 
	for (int i = 100; i <= 10000; i+=100) {
		
		l = make_list(i);
		
		repeats = 100 + rand() % 100;
		num_search = num_insert = num_delete = 0;
		
		for(int j=0; j < repeats; j++) {
			l->has_value(rand());
			num_search+= l->get_seek_num();
			
			l->insert(rand() % i, 0);
			num_insert+= l->get_seek_num();
			
			l->del_by_num(rand() % i);
			num_delete+= l->get_seek_num();
		}
		
		num_search = num_search / repeats;
		num_insert = num_insert / repeats;
		num_delete = num_delete / repeats;
		
		cout << i << TAB << num_search << TAB << num_insert << TAB << num_delete << endl;
	}
	
	return 0;
}
