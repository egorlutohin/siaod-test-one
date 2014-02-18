#ifndef MYLIST_H
#define MYLIST_H
#include <string>
#include <sstream>

template <typename T>
class List {

	int current_size; // list elements count
	int storage_size; // storage array size
	int head_index;
	int free_index;
	T *arr;
	int *index_arr;

	T& _get_value_by_number(int);
	void _validate_index(int n, bool set_operation = false) {
		if(n < 0)
			throw "Индекс не может быть отрицательным";

		if (!set_operation) { // validate get...
			if (n >= get_size())
				throw "Индекс больше чем размер списка";
		} else { // validate set operation
			if (n > get_size())
				throw "Индекс больше чем размер списка";
		}
	};
	void _have_more_one_place() {
		if (free_index == -1) {
			throw "В массиве больше нет места, не могу вставить еще одно значение";
		}

	};

public:
	List(int); // конструктор
	~List(); // деструктор
	int get_size(); // + опрос размера списка
	void clean(); // + очистка списка
	bool is_empty(); // + проверка списка на пустоту
	void insert(const T &); // + включение нового значения
	int get_storage_size(); // максимальный размер списка
	T get_value_by_number(int n){
		return _get_value_by_number(n);
	} // + получение значения с заданным номером в списке
	T operator[](int i) {
		return this->get_value_by_number(i);
	}
	bool has_value(const T&, int*); // + опрос наличия заданного значения
	void change_value_by_number(const int n, const T& v){
		_get_value_by_number(n) = v;
	}

	int get_value_position(const T& v){
		int p;
		bool hv = has_value(v, &p);

		if (hv)
			return p;
		else
			return -1;
	}

	void insert_by_number(int, const T&); // + включение нового значения в позицию с заданным номером
	void delete_element_by_value(const T&); // + удаление заданного значения из списка
	std::string to_string() {
		std::stringstream ss;

		List<T>::Iterator i(this);

		for(i.begin(); i.in_boundary(); i.next()) {
			if (i.in_end())
				ss << *i;
			else
				ss << *i << " ";
		}

		return ss.str();
	}


	class Iterator {
		List<T> *l;
		int current_index;
		int position_counter;
	public:
		Iterator(List<T> *);
		void begin(); // установка итератора на первый элемент списка
		void next(); // перевод итератора на конец списка
		T& get_current_value(); // доступ к данным текущего элемента
		T& operator*(); // доступ к данным текукщего элемента
		bool in_begin(); // итератор в начале
		bool in_end();
		bool in_boundary(); //
		int get_current_position() {
			return position_counter;
		}
		int get_current_index() {
			return current_index;
		}
	};
	friend class Iterator;
};

// Определение методов класса Iterator
template <typename T> List<T>::Iterator::Iterator(List<T> *ptr):
	l(ptr){
	this->begin();
}

template <typename T> void List<T>::Iterator::begin(){
	current_index = l->head_index;
	position_counter = 0;
}

template <typename T> void List<T>::Iterator::next(){
	position_counter++;
	if (in_boundary()) {
		current_index = l->index_arr[current_index];
	} else {
		current_index = l->current_size - 1;
		return;
	}
}

template <typename T> T& List<T>::Iterator::get_current_value(){
	if (l->is_empty())
		throw "Список пуст";
	return l->arr[current_index];
}

template <typename T> T& List<T>::Iterator::operator*(){
	return get_current_value();
}

template <typename T> bool List<T>::Iterator::in_begin(){
	if (current_index == l->head_index)
		return true;
	else
		return false;
}

template <typename T> bool List<T>::Iterator::in_end(){
	if (l->index_arr[current_index] == -1)
		return true;
	else
		return false;
}

template <typename T> bool List<T>::Iterator::in_boundary(){
	if (position_counter < l->current_size)
		return true;
	else
		return false;
}

// Определение методов класса List
template <typename T> List<T>::List(int init_size) {
	storage_size = init_size;
	arr = new T[storage_size];
	index_arr = new int[storage_size];

	clean();
}

template <typename T> List<T>::~List() {
	delete [] arr;
	delete [] index_arr;
}

template <typename T> int List<T>::get_size() {
	return this->current_size;
}

template <typename T> void List<T>::clean(){
	head_index = -1;
	free_index = 0;

	/* Размечаем индексы свободных элементов */
	for(int i = 0; i < storage_size - 1; i++) {
		index_arr[i] = i + 1;
	}
	index_arr[storage_size - 1] = -1; // последний элемент не имеет ссылку на свободный индекс

	current_size = 0;

}

template <typename T> bool List<T>::is_empty(){
	return this->current_size == 0 ? true : false;
}

template <typename T> void List<T>::insert(const T &v){

	_have_more_one_place();

	arr[free_index] = v;
	current_size++;

	int next_free_index = index_arr[free_index];

	if (head_index == -1) {
		head_index = 0;
		index_arr[0] = -1;
	} else {
		int last_index = head_index;
		while (index_arr[last_index] != -1) {
			last_index = index_arr[last_index];
		}
		index_arr[last_index] = free_index; // устанавливаем конец списка
		index_arr[free_index] = -1;
	}

	free_index = next_free_index;
}

template <typename T> int List<T>::get_storage_size(){
	return storage_size;
}

template <typename T> T& List<T>::_get_value_by_number(int n){

	_validate_index(n);

	int result_index = head_index;
	List<T>::Iterator iterator(this);
	for(int i = 0; i < n; i++){
		iterator.next();
	}

	return *iterator;
}

template <typename T> bool List<T>::has_value(const T& v, int *p = NULL){
	List<T>::Iterator i(this);

	for(i.begin(); i.in_boundary(); i.next())
		if (*i == v) {
			if(p != NULL) {
				*p = i.get_current_position();
			}
			return true;
		}

	return false;
}

template <typename T> void List<T>::insert_by_number(int p, const T& v) {

	_have_more_one_place(); // имеет еще одно место в хранилище для добавления элемента?
	_validate_index(p, true); // индекс нормальный?

	if (is_empty()) {
		insert(v);
		return;
	}

	if(p == 0) { // insert to begin
		int current_insert_index = free_index;
		free_index = index_arr[free_index];

		arr[current_insert_index] = v;
		index_arr[current_insert_index] = head_index;
		head_index = current_insert_index;

		current_size++;
		return;
	} else {
		List<int>::Iterator i(this);
		i.begin();
		for(int j = 0; j < p - 1; j++, i.next());

		int current_insert_index = free_index;
		free_index = index_arr[free_index];
		arr[current_insert_index] = v;

		int old_next_index = index_arr[i.get_current_index()];
		index_arr[i.get_current_index()] = current_insert_index;
		index_arr[current_insert_index] = old_next_index;
		current_size++;

		return;
	}
}

template <typename T> void List<T>::delete_element_by_value(const T& v) {
	if (get_size() == 0)
		return;

	List<T>::Iterator i(this);

	int previous_value_index = -1;

	for (i.begin(); i.in_boundary(); i.next()) {
		if(*i == v){
			if (i.in_begin()) {
				head_index = index_arr[i.get_current_index()];
				index_arr[i.get_current_index()] = free_index;
				free_index = i.get_current_index();
				current_size--;

//			} else if (i.in_end()) {
//				return;
			} else {
				index_arr[previous_value_index] = index_arr[i.get_current_index()];
				index_arr[i.get_current_index()] = free_index;
				free_index = i.get_current_index();
				current_size--;
			}

			break;
		}

		previous_value_index = i.get_current_index();

	}

	return;
}

#endif
