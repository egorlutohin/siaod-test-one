#ifndef MYVECTOR_H
#define MYVECTOR_H

#ifndef IAMREMEMBER
	#warning "Don't remember to include `srand((unsigned) time(0))` in `main` function"
#endif

#include <iostream>
using namespace std;

#include <ctime>
#include <cstdlib>
#include <cmath>

template <typename T>
class Vector {
	T *arr;
	int cur_size; // current amount of objects in vector

	int comparison_num; // number of comparisons
	int exchange_num; // number of exchanges
	
	void _qsort(int l, int r);

	
	public:
	Vector(unsigned int size=10); // constructor, initial size of array = 10
	~Vector(); // destructor
	int size(); // current size of array
	T& operator[](int i);
	bool resize(int new_size); // change size of array
	void random_init(); // make random numbers in array values

	void bubble_sort();
	void lsd_sort(const int);
	void quick_recursion_sort();
	int get_comparison_num() { return comparison_num; }
	int get_exchange_num() {return exchange_num; }

	template <typename M> friend ostream& operator<< (ostream &O, const Vector<M> &v);

	class Iterator {
		Vector<T> *ptr;
		int current_index;
		
		public:
		Iterator(Vector<T> *); // constructor
		T& begin(); // set iterator to first element of vector
		T& end(); // set iterator to last element
		bool next(); 
		bool prev();
		bool on_end_boundary();
		bool on_start_boundary();
		T& operator*(); // access to data of current element
		T& operator++(int);
		T& operator--(int);
	};
	friend class Iterator;
};

// Iterator functions
template <typename T> Vector<T>::Iterator::Iterator(Vector<T> *v) {
	ptr = v;
	current_index = 0;
}

template <typename T> bool Vector<T>::Iterator::on_start_boundary() {
	return (current_index == 0);
}

template <typename T> bool Vector<T>::Iterator::on_end_boundary() {
	return (current_index == (ptr->cur_size - 1));
}

template <typename T> T& Vector<T>::Iterator::begin(){
	current_index = 0;
	
	return ptr->arr[current_index];
}

template <typename T> T& Vector<T>::Iterator::end(){
	current_index = ptr->cur_size - 1;
	
	return ptr->arr[current_index];
}

template <typename T> bool Vector<T>::Iterator::next() {
	if (current_index != (ptr->cur_size - 1)) {
		current_index++;
		return true;
	} else {
		return false;
	}
}

template <typename T> bool Vector<T>::Iterator::prev(){
	if (current_index != 0) {
		current_index--;
		return true;
	} else {
		return false;
	}
}

template <typename T> T& Vector<T>::Iterator::operator*(){
	return ptr->arr[current_index];
}

template <typename T> T& Vector<T>::Iterator::operator++(int i) {
	this->next();
	return **this;
}

template <typename T> T& Vector<T>::Iterator::operator--(int i) {
	this->prev();
	return **this;
}

// Vector functions
template <typename T> Vector<T>::Vector(unsigned int size){
	
	arr = new T[size];
	cur_size = size;
	
	comparison_num = exchange_num = 0;
}

template <typename T> Vector<T>::~Vector(){
	delete [] arr;
}

template <typename T> int Vector<T>::size(){
	return this->cur_size;
}

template <typename T> T& Vector<T>::operator[](int i){
	if (i < 0 || i >= cur_size) {
		throw "Bad array index";
	}

	return arr[i];
}

template <typename T> bool Vector<T>::resize(int new_size) {
	if (new_size <= 0) {
		throw "Wrong parameter of vector function `resize`";
	}

	T *tmp;
	tmp = new T[new_size];

	int min_size = cur_size < new_size ? cur_size : new_size; 

	for(int i = 0; i < min_size; i++) {
		tmp[i] = arr[i];
	}

	delete [] arr;
	arr = tmp;
	cur_size = new_size;

	return true;
}

template <typename T> void Vector<T>::random_init(){

	for(int i = 0; i < cur_size; i++){
		arr[i] = rand();
	}
}

template <typename T> void Vector<T>::bubble_sort(){

	T temp;
	
	comparison_num = exchange_num = 0;

	for(int i=0; i < this->cur_size - 1; i++) {
		for(int j = this->cur_size - 1; i < j; j--) {
			comparison_num++;
			if (arr[j-1] > arr[j]){ 
				temp = arr[j]; 
				arr[j] = arr[j-1]; 
				arr[j-1] = temp; exchange_num++;
			}
		}
	}
}

template <typename T> void Vector<T>::quick_recursion_sort(){
	comparison_num = exchange_num = 0;
	_qsort(0, this->size() - 1);
}

template <typename T> void Vector<T>::lsd_sort(const int R =16) {
	comparison_num = exchange_num = 0;
	
	// input param test
	double _ = log2(R);
	
	if ( (_ - (int)_ ) > 0) {
		throw "Radix is not a power of 2!!!";
	}
	
	// vars
	int d; // number of current digit
	T *C = new T[this->cur_size]; // helper array for buckets
	
	int k = sizeof(T) * 8 / log2(R); // maximum amount of digits in element
	
	// helper, extraction of digit no. d
	class H {
		public:
		static int digit(const T v, int d, int R) {
			d = -(d - (sizeof(T) * 8 / log2(R) - 1));
			return (v >> ((int)log2(R) * d)) % R;
		}
	};
	
	for(d = k - 1; d >= 0; d--) {
		
		T count[R]; // counter of each bucket size
		for(int i = 0; i < R; i++) {
			count[i] = 0;
		}
		
		int j = 0;
		for(int i = 0; i < this->cur_size; i++) {
			j = H::digit(arr[i], d, R);
			comparison_num++;
			count[j+1]++;
		}
		
		for(int r = 1; r < R; r++)
			count[r]+= count[r-1];
		
		j = 0;
		for(int i = 0; i < this->cur_size; i++) {
			j = H::digit(this->arr[i], d, R);
			comparison_num++;
			C[count[j]++] = this->arr[i];
			exchange_num++;
		}
		
		for (int i = 0; i < this->cur_size; i++) {
			this->arr[i] = C[i];
			exchange_num++;
		}
	}
	 
	delete [] C;
}

template <typename T> void Vector<T>::_qsort(int left, int right){

	int i, j;
	T x;
 
	i = left; j = right;
	x = arr[(left+right)/2];
 
	do {
		while((arr[i] < x) && (i < right)) {i++; comparison_num++;} comparison_num++;
		while((x < arr[j]) && (j > left)) {j--; comparison_num++;} comparison_num++;
 
		if(i <= j) {
			T tmp;
			tmp = arr[i]; 
			arr[i] = arr[j];
			arr[j] = tmp; exchange_num++;
			i++; j--;
		}
	} while(i <= j);
 
	if(left < j) _qsort(left, j);
	if(i < right) _qsort(i, right);
	
}

template <typename M> ostream& operator<< (ostream &o, const Vector<M> &v) {
	for (int i = 0 ; i < v.cur_size ; i++) {
                        o << v.arr[i] << " ";
	}

	o << endl;
	
	return o;
}
#endif
