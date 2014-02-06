#ifndef MYLIST_H
#define MYLIST_H

#ifndef NULL 
	#define NULL 0
#endif

#include <cstdio>

using namespace std;

static char err_msg[256];

template <typename T>
class Node {
	public:
	T value;
	Node *next, *prev;
	Node(const T &v, Node *n=NULL, Node *p=NULL);
};

template <typename T>
class List {
	
	int current_size;
	Node<T> *head_first, *head_last;
	int seek_num; // for testing purpose
	
	void _insert_first(const T &v);
	void _insert_last(const T &v);
	void _insert_between(Node<T> *before_node, const T &v);
	Node<T>* _get_node_by_num(int index);
	Node<T>* _get_node_by_value(const T &v, int *index=NULL);
	void _del_node(Node<T> *n);

	public:
	List(); // constructor
	~List(); // destructor
	int get_size(); // get size of list
	bool is_empty() const; // to check emptiness of list
	void insert(const T &v); // insert value
	void insert(int num, const T &v); // insert value by number
	void clean(); // clean list
	bool has_value(const T &v);
	T& get_value(int num); // get value by index
	T& operator[](int num); // get value by index (shortcut)
	void set_value(int num, const T &v); //set value by num
	int get_num_by_value(const T &v); // get index in list with this value
	bool del_by_val(const T &v); // delete by value
	bool del_by_num(int num); // delete by number
	int get_seek_num() { return seek_num; }

	template <typename M> friend ostream& operator<< (ostream &o, const List<M> &l);
	
	class Iterator {
		List<T> *l;
		Node<T> *current_node;
		int index_counter;
		
		public:
		Iterator(List<T> *); // constructor
		T& begin(); // set iterator to first element of vector
		T& end(); // set iterator to last element
		T& next(); 
		T& prev();
		bool in_boundary(); // index in boundary
		T& operator*(); // access to data of current element
		T& operator++(int);
		T& operator--(int);
		
		int tell_index() {
			if(!l->is_empty()) {
				return ((index_counter % l->current_size) + l->current_size) % l->current_size;
			} else return 0;
		}
		int tell_counter() { return index_counter; }
	};
	friend class Iterator;
};

template <typename T> List<T>::Iterator::Iterator(List<T> *lp) {
	l = lp;
	current_node = l->head_first;
	index_counter = 0;
}

template <typename T> T& List<T>::Iterator::begin() {
	
	if (l->is_empty()) {
		throw "List is empty!";
	}
	
	index_counter = 0;
	current_node = l->head_first;
	return current_node->value;
}

template <typename T> T& List<T>::Iterator::end() {

	if (l->is_empty()) {
		throw "List is empty!";
	}
	
	index_counter = l->current_size - 1;
	current_node = l->head_last;
	return current_node->value;
}

template <typename T> T& List<T>::Iterator::next() {

	if (l->is_empty()) {
		throw "List is empty!";
	}
	
	current_node = current_node->next;
	index_counter++;
	return current_node->value;
}

template <typename T> T& List<T>::Iterator::prev() {
	
	if (l->is_empty()) {
		throw "List is empty!";
	}

	current_node = current_node->prev;
	index_counter--;
}

template <typename T> bool List<T>::Iterator::in_boundary() {
	
	if (l->is_empty()) {
		throw "List is empty!";
	}
	
	if((index_counter >= l->current_size) || (index_counter < 0)) {
		return false;
	} else {
		return true;
	}
}

template <typename T> T& List<T>::Iterator::operator*() {
	
	if (l->is_empty()) {
		throw "List is empty!";
	}
	
	return current_node->value;
}

template <typename T> T& List<T>::Iterator::operator++(int i) {

	if (l->is_empty()) {
		throw "List is empty!";
	}

	return this->next();
}

template <typename T> T& List<T>::Iterator::operator--(int j) {
	
	if (l->is_empty()) {
		throw "List is empty!";
	}
	
	return this->prev();
}

template <typename T> Node<T>::Node(const T &v, Node<T> *n, Node<T> *p) {
	this->value = v;
	this->next = n;
	this->prev = p;
}

template <typename T> List<T>::List() {
	this->current_size = 0;
	this->head_first = this->head_last = NULL;
	this->seek_num = 0;
}

template <typename T> Node<T>* List<T>::_get_node_by_value(const T &v, int *index){
	Node<T> *n;
	seek_num = 0;
	
	n = this->head_first;
	
	int i;
	for(i = 0; i < this->current_size; i++){
		seek_num++;
		if (n->value == v) {
			if(index != NULL){
				*index = i;
			}
			
			return n;
			break;
		}
		n = n->next;
	}
	
	if(index != NULL){
		*index = -1;
	}
	return NULL;
}

template <typename T> T& List<T>::get_value(int num) {
	return this->_get_node_by_num(num)->value;	
}

template <typename T> void List<T>::set_value(int num, const T &v) {
	this->_get_node_by_num(num)->value = v;
}

template <typename T> T& List<T>::operator[](int num){
	return this->get_value(num);
}

template <typename T> bool List<T>::has_value(const T &v){
	return (this->_get_node_by_value(v) != NULL);
}

template <typename T> void List<T>::clean(){
	seek_num = 0;
	if (!this->is_empty()) {
		Node<T> *n;

		while(head_first != head_last) {
			seek_num++;
			n = head_last;
			head_last = head_last->prev;
			delete n;
		}
		delete head_first;
	}
	this->current_size = 0;
	this->head_first = this->head_last = NULL;
}

template <typename T> List<T>::~List() {
	this->clean();
}

template <typename T> int List<T>::get_size() {
	return this->current_size;
}

template <typename T> bool List<T>::is_empty() const {
	return !this->current_size;
}

template <typename T> void List<T>::_insert_first(const T &v) {
	Node<T> *n = new Node<T>(v);
	
	seek_num = 0;
	
	if (this->is_empty()) {
		n->prev = n;
		n->next = n;
		this->head_first = n;
		this->head_last = n;
	} else {
		n->next = head_first;
		n->prev = head_last;
		head_first->prev = n;
		head_first = n;
	}
	
	current_size++;
}

template <typename T> void List<T>::_insert_last(const T &v) {
	
	if (this->is_empty()) {
		_insert_first(v);
	} else {
		Node<T> *n = new Node<T>(v);

		head_last->next = n;
		head_first->prev = n;
		
		n->next = this->head_first;
		n->prev = this->head_last;
		
		head_last = n;
		current_size++;
	}
}


template <typename T> void List<T>::_insert_between(Node<T> *before_node, const T &v) {
	
	Node<T> *n = new Node<T>(v);
	
	n->next = before_node;
	n->prev = before_node->prev;
	before_node->prev->next = n;
	before_node->prev = n;
	
	current_size++;
	
}

template <typename T> Node<T>* List<T>::_get_node_by_num(int index){
	
	if(index < 0 || index > (this->current_size-1)) {
		sprintf(err_msg, "Incorrect index - `%d` (list size - %d)", index, this->current_size);
		throw err_msg;
	}
	
	Node<T> *result;
	seek_num = 0;
	
	bool move_forward = (index < (current_size / 2));
	
	if (move_forward) {
		result = this->head_first;
		for(int i = 0; i < index; i++){
			seek_num++;
			result = result->next;
		}
		
	} else {
		result = this->head_last;
		for(int i = (current_size - 1); i > index; i--){
			seek_num++;
			result = result->prev;
		} 
		
	}
	
	return result;
}

template <typename T> void List<T>::insert(const T &v) {
		_insert_last(v);
}

template <typename T> void List<T>::insert(int num, const T &v) {
	
	seek_num = 0;

	if(num == 0) { //first
		_insert_first(v);
	} else if(num == this->current_size) { //last
		_insert_last(v);
	}
	else {
		_insert_between(_get_node_by_num(num), v);
	}
}

template <typename T> int List<T>::get_num_by_value(const T &v) {
	int i;
	_get_node_by_value(v, &i);
	
	return i;
}

template <typename T> void List<T>::_del_node(Node<T> *n) {

	if (n == head_first) {
		head_first = n->next;
		head_first->prev = head_last;
	} else if (n == head_last) {
		head_last = n->prev;
		head_last->next = head_first;
	} else {
		n->prev->next = n->next;
		n->next->prev = n->prev;
	}
	
	delete n;
	current_size--;
}

template <typename T> bool List<T>::del_by_val(const T &v) {
	Node<T> *n;
	n = _get_node_by_value(v);
	
	if(n != NULL) {
		_del_node(n);
		return true;
	} else {
		return false;
	}
}

template <typename T> bool List<T>::del_by_num(int num) {
	Node<T> *n;
	n = _get_node_by_num(num);
	_del_node(n);
	return true;
}

template <typename M> ostream& operator<< (ostream &o, const List<M> &l) {
	Node<M> *n;
	
	if (!l.is_empty()) {
		
		for(n = l.head_first; n != l.head_last; n = n->next) {
			cout << n->value << " ";
		} 
		cout << n->value;
		
	} else {
		cout << "<empty list>";
	}
	
	cout << endl;
}

#endif
