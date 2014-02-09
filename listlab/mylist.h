#ifndef MYLIST_H
#define MYLIST_H

template <typename T>
class List {

	int current_size; // list elements count
	int storage_size; // storage array size
	int head_index;
	int free_index;
	T *arr;
	int *index_arr;

public:
	List(int); // конструктор
	~List(); // деструктор
	int get_size(); // + опрос размера списка
	void clean(); // + очистка списка
	bool is_empty(); // + проверка списка на пустоту
	void insert(const T &); // + включение нового значения
	int get_storage_size(); // максимальный размер списка
	T get_value_by_number(int); // + получение значения с заданным номером в списке
	T operator[](int i) {
		return this->get_value_by_number(i);
	}
	bool has_value(const T&); // + опрос наличия заданного значения

	class Iterator {
		List<T> *l;
		int current_index;
	public:
		Iterator(List<T> *);
		void begin(); // установка итератора на первый элемент списка
		//void end(); // установка итератора на конец списка
		void next(); // перевод итератора на конец списка
		T& get_current_value(); // доступ к данным текущего элемента
		T& operator*(); // доступ к данным текукщего элемента
		bool is_begin(); // итератор в начале
		bool is_end(); // итератор в конце
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
}

template <typename T> void List<T>::Iterator::next(){
	if (is_end()) {
		return;
	} else {
		current_index = l->index_arr[current_index];
	}
}

template <typename T> T& List<T>::Iterator::get_current_value(){
	return l->arr[current_index];
}

template <typename T> T& List<T>::Iterator::operator*(){
	return get_current_value();
}

template <typename T> bool List<T>::Iterator::is_begin(){
	if (current_index == l->head_index)
		return true;
	else
		return false;
}

template <typename T> bool List<T>::Iterator::is_end(){
	if (l->index_arr[current_index] == -1)
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

	if (free_index == -1) {
		throw "В массиве больше нет места, не могу вставить еще одно значение";
	}

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

template <typename T> T List<T>::get_value_by_number(int n){
	if(n < 0)
		throw "Индекс не может быть отрицательным";

	if (n >= get_size())
		throw "Индекс больше чем размер списка";

	int result_index = head_index;
	List<T>::Iterator iterator(this);
	for(int i = 0; i < n; i++){
		iterator.next();
	}

	return *iterator;
}

template <typename T> bool List<T>::has_value(const T& v){
	List<T>::Iterator i(this);

	for(i.begin(); !i.is_end(); i.next())
		if (*i == v) {
			return true;
		}
	if (*i == v) {
		return true;
	}

}
#endif
