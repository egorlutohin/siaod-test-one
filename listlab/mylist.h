#ifndef MYLIST_H
#define MYLIST_H
#include <string>
#include <sstream>
#include <cstddef>

template <typename T>
class List {

	size_t current_size; // list elements count
	size_t storage_size; // storage array size
	size_t head_index;
	size_t free_index;
	T *arr;
	size_t *index_arr;

	T& _get_value_by_number(size_t);
	void _validate_index(size_t n, bool inclusive = false) {
		if(n < 0)
			throw "Индекс не может быть отрицательным";

		if (!inclusive) { // validate get for example
			if (n >= get_size())
				throw "Индекс больше чем размер списка";
		} else { // validate set operation for example
			if (n > get_size())
				throw "Индекс больше чем размер списка";
		}
	};
	void _have_more_one_place() {
		if (current_size == storage_size) {
			throw "В массиве больше нет места, не могу вставить еще одно значение";
		}

	};

public:
	List(size_t); // конструктор
	~List(); // деструктор
	size_t get_size(); // + опрос размера списка
	void clean(); // + очистка списка
	bool is_empty(); // + проверка списка на пустоту
	void insert(const T &); // + включение нового значения
	size_t get_storage_size(); // максимальный размер списка
	T get_value_by_number(size_t n){
		return _get_value_by_number(n);
	} // + получение значения с заданным номером в списке
	T operator[](size_t i) {
		return this->get_value_by_number(i);
	}
	bool has_value(const T& v, size_t *p = NULL); // + опрос наличия заданного значения
	void change_value_by_number(const size_t n, const T& v){ // + изменение значения с заданным номером в списке
		_get_value_by_number(n) = v;
	}

	size_t get_value_position(const T& v){ // + получение позиции в списке с заданным значением
		size_t p;
		bool hv = has_value(v, &p);

		if (hv)
			return p;
		else
			throw "Нет такого значения";
	}

	void insert_by_number(size_t, const T&); // + включение нового значения в позицию с заданным номером
	void delete_by_value(const T&); // + удаление заданного значения из списка
	std::string to_string();
	void delete_by_number(size_t); // +  удаление значения из позиции с заданным номером


	class Iterator {
		List<T> *l;
		size_t current_index;
		size_t position_counter;
	public:
		Iterator(List<T> *);
		void begin(); // + установка итератора на первый элемент списка
		void next(); // + переход к следующему значению в списке
		T& get_current_value(); // доступ к данным текущего элемента
		T& operator*(); // + доступ к данным текущего элемента
		bool in_begin(); // итератор в начале
		bool in_end();
		bool in_boundary(); // + проверка состояния итератора
		size_t get_current_position() {
			return position_counter;
		}
		size_t get_current_index() {
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
	if ((l->get_size() - 1) == this->position_counter)
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
template <typename T> List<T>::List(size_t init_size) {
	storage_size = init_size;
	arr = new T[storage_size];
	index_arr = new size_t[storage_size];

	clean();
}

template <typename T> List<T>::~List() {
	delete [] arr;
	delete [] index_arr;
}

template <typename T> size_t List<T>::get_size() {
	return this->current_size;
}

template <typename T> void List<T>::clean(){
	free_index = 0;

	/* Размечаем индексы свободных элементов */
	for(size_t i = 0; i < storage_size - 1; i++) {
		index_arr[i] = i + 1;
	}

	current_size = 0;
}

template <typename T> bool List<T>::is_empty(){
	return this->current_size == 0 ? true : false;
}

template <typename T> void List<T>::insert(const T &v){

	_have_more_one_place();

	size_t next_free_index = index_arr[free_index];

	if (is_empty()) {
		head_index = 0;
	} else {

		List<T>::Iterator i(this);
		for(i.begin(); !i.in_end(); i.next());

		index_arr[i.get_current_index()] = free_index;
	}

	arr[free_index] = v;
	current_size++;

	free_index = next_free_index;
}

template <typename T> size_t List<T>::get_storage_size(){
	return storage_size;
}

template <typename T> T& List<T>::_get_value_by_number(size_t n){

	_validate_index(n);

	List<T>::Iterator iterator(this);
	for(size_t i = 0; i < n; i++){ // Сделать рефакторинг без переменной i
		iterator.next();
	}

	return *iterator;
}

template <typename T> bool List<T>::has_value(const T& v, size_t *p){ // by default p = NULL
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

template <typename T> void List<T>::insert_by_number(size_t p, const T& v) {

	_have_more_one_place(); // имеет еще одно место в хранилище для добавления элемента?
	_validate_index(p, true); // индекс нормальный?

	if (is_empty()) {
		insert(v);
		return;
	}

	if(p == 0) { // insert to begin
		size_t current_insert_index = free_index;
		free_index = index_arr[free_index];

		arr[current_insert_index] = v;
		index_arr[current_insert_index] = head_index;
		head_index = current_insert_index;

		current_size++;
		return;
	} else {
		List<T>::Iterator i(this);
		i.begin();
		for(size_t j = 0; j < p - 1; j++, i.next()); // можно перерделать без буквы j

		size_t current_insert_index = free_index;
		free_index = index_arr[free_index];
		arr[current_insert_index] = v;

		size_t old_next_index = index_arr[i.get_current_index()];
		index_arr[i.get_current_index()] = current_insert_index;
		index_arr[current_insert_index] = old_next_index;
		current_size++;

		return;
	}
}

template <typename T> std::string List<T>::to_string() {
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


template <typename T> void List<T>::delete_by_value(const T& v) {
	if (get_size() == 0)
		return;

	List<T>::Iterator i(this);

	size_t previous_value_index;

	for (i.begin(); i.in_boundary(); i.next()) {

		if(*i == v){

			if (i.in_begin()) {
				head_index = index_arr[i.get_current_index()];
			} else {
				index_arr[previous_value_index] = index_arr[i.get_current_index()];
			}

			index_arr[i.get_current_index()] = free_index;
			free_index = i.get_current_index();
			current_size--;

			break;
		}

		previous_value_index = i.get_current_index();

	}

	return;
}

template <typename T> void List<T>::delete_by_number(size_t p) {

	_validate_index(p);

	List<T>::Iterator i(this);

	i.begin();
	if (p == 0) {
		head_index = index_arr[i.get_current_index()];
	} else {
		size_t previous_value_index;
		for (int j = 0; j < p; j++) { // переделать без буквы j
			previous_value_index = i.get_current_index();
			i.next();
		}
		index_arr[previous_value_index] = index_arr[i.get_current_index()];
	}

	index_arr[i.get_current_index()] = free_index;
	free_index = i.get_current_index();
	current_size--;

	return;
}

#endif
