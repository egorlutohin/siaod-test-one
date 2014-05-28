#include <gtest/gtest.h> // wtf ??

#include <iostream>
#include <cstdlib>
#include <cmath>
#include "mybst.h"
using namespace std;

#define TAB "\t"

MyBST<int,int> *make_random_bst(const size_t s) {
	MyBST<int,int> *bst = new MyBST<int,int>();

	for(size_t i = 0; i < s; i++) {
		bst->insert(rand(), 0);
	}

	return bst;
}

MyBST<int,int> *make_worst_bst(const size_t s) {
	MyBST<int, int> *bst = new MyBST<int,int>();

	for(size_t i = 0; i < s; i++) {
		bst->insert(i * 10, 0);
	}

	return bst;
}

int main(int argc, char **argv){

	MyBST<int,int> *random_bst, *worst_bst;
	float random_num_search, random_num_insert, random_num_delete;
	float worst_num_search, worst_num_insert, worst_num_delete;
	int repeats;


	cout << "Количество" << TAB <<
			"Теория" << TAB <<
			"Поиск" << TAB <<
			"Вставка" << TAB <<
			"Удаление" << TAB <<
			"Поиск (худш.)" << TAB <<
			"Вставка (худш.)" << TAB <<
			"Удаление (худш.)" << endl;

	for(int amount = 1000; amount <= 100000; amount+=1000) {
		random_bst = make_random_bst(amount);
		worst_bst = make_worst_bst(amount);
		repeats = 100 + rand() % 100;

		random_num_search = random_num_insert = random_num_delete = 0;
		worst_num_search = worst_num_insert = worst_num_delete = 0;
		for(int j = 0; j < repeats; j++) {

			try {
				random_bst->get_value(rand());
			} catch(...) {}
			random_num_search+= random_bst->get_operation_counter();

			random_bst->insert(rand(), 0);
			random_num_insert+= random_bst->get_operation_counter();

			random_bst->remove(rand());
			random_num_delete+= random_bst->get_operation_counter();

			try {
				worst_bst->get_value(rand());
			} catch(...) {}
			worst_num_search+= worst_bst->get_operation_counter();

			worst_bst->insert(rand(), 0);
			worst_num_insert+= worst_bst->get_operation_counter();

			worst_bst->remove(rand());
			worst_num_delete+= worst_bst->get_operation_counter();

		}

		random_num_search = random_num_search / repeats;
		random_num_insert = random_num_insert / repeats;
		random_num_delete = random_num_delete / repeats;

		worst_num_search = worst_num_search / repeats;
		worst_num_insert = worst_num_insert / repeats;
		worst_num_delete = worst_num_delete / repeats;


		cout << setprecision(1) << std::fixed
			 << amount << TAB
			 << log2(amount) << TAB
			 << random_num_search << TAB
			 << random_num_insert << TAB
			 << random_num_delete << TAB
			 << worst_num_search << TAB
			 << worst_num_insert << TAB
			 << worst_num_delete << endl;
	}

	return 0;
}
