#ifndef mybsth
#define mybsth

template <typename Key, typename Value>
class MyBST {

	class MyBSTNode {
	public:
		Value v;
		Key k;
		MyBSTNode *l, *r;

		MyBSTNode(Key &k, Value &v){
			this->k = k;
			this->v = v;
			this->l = NULL;
			this->r = NULL;
		}
	};

	MyBSTNode *head;
	size_t size;
	size_t operation_counter;

	Value &get_value(MyBSTNode *t, const Key &k) {
		this->operation_counter++;
		if (t == NULL) {
			throw "Нет элемента с таким ключом в дереве";
		}

		if (k == t->k) {
			return t->v;
		}

		if (k < t->k) {
			return get_value(t->l, k);
		} else {
			return get_value(t->r, k);
		}

	}

	void get_inner_path_value(MyBSTNode *n, size_t level, size_t &sum) {
		if(n == NULL) {
			return;
		}

		get_inner_path_value(n->l, level + 1, sum);
		get_inner_path_value(n->r, level + 1, sum);

		if ((n->l != NULL) && (n->r != NULL)) {
			sum+= level;
		}
	}

	void clean(MyBSTNode *n) {
		if (n == NULL) {
			return;
		}

		clean(n->l);
		clean(n->r);

		delete n;
		this->size--;
	}
	void to_string_rambler(MyBSTNode *n, std::stringstream &ss) {

		if (n == NULL) {
			return;
		}

		to_string_rambler(n->l, ss);
		to_string_rambler(n->r, ss);

		if (!ss.str().empty()) { // dirty hack
			ss << " ";
		}
		ss << n->v;
	}

	MyBSTNode *remove2(MyBSTNode *t, MyBSTNode *t0) {
		this->operation_counter++;
		if(t->l != NULL) {
			t->l = this->remove2(t->l, t0);
			return t;
		}

		t0->k = t->k;
		t0->v = t->v;

		MyBSTNode *x = t->r;
		delete t;
		this->size--;

		return x;
	}

	MyBSTNode *remove(MyBSTNode *t, Key k, bool &deleted) {
		this->operation_counter++;
		if (t == NULL) {
			deleted = false;
			return t;
		}

		if (k < t->k) {
			bool del;
			t->l = this->remove(t->l, k, del);
			deleted = del;
			return t;
		}

		if (k > t->k) {
			bool del;
			t->r = this->remove(t->r, k, del);
			deleted = del;
			return t;
		}

		deleted = true;
		if ((t->l == NULL) && (t->r == NULL)) {
			if(t == this->head) {
				this->head = NULL;
			}
			delete t;
			this->size--;
			return NULL;
		}

		if(t->l == NULL) {
			MyBSTNode *x = t->r;
			if (t == this->head) {
				this->head = t->r;
			}
			delete t;
			this->size--;
			return x;
		}

		if(t->r == NULL) {
			MyBSTNode *x = t->l;
			if (t == this->head) {
				this->head = t->l;
			}
			delete t;
			this->size--;
			return x;
		}

		t->r = this->remove2(t->r, t);
		return t;
	}

	void print(MyBSTNode *n, size_t level) {
		if (n == NULL) {
			return;
		}

		print(n->r, level + 1);

		for(int i=0; i <= 3*level; i++) {
			std::cout << " ";
		}
		std::cout << n->k << std::endl;

		print(n->l, level + 1);
	}

	MyBSTNode *insert(Key, Value, MyBSTNode *, bool&);

public:
	MyBST();
	~MyBST() {
		this->clean();
	};
	bool insert(Key, Value);
	void clean();
	bool remove(Key k) {
		bool deleted;
		this->operation_counter = 0;
		this->remove(this->head, k, deleted);
		return deleted;
	};

	size_t get_operation_counter() {
		return this->operation_counter;
	}

	size_t get_inner_path_value() {
		size_t sum = 0;
		this->get_inner_path_value(this->head, 0, sum);
		return sum;
	}

	Value &get_value(const Key &k) {
		this->operation_counter = 0;
		return get_value(this->head, k);
	}

	Value &get_head_value() {
		if (this->head == NULL) {
			throw "Дерево пусто";
		}

		return this->head->v;
	}

	size_t get_size() {
		return size;
	}

	bool is_empty() {
		return (this->get_size() == 0);
	}

	void print() {
		std::cout << std::endl;
		this->print(this->head, 0);
		std::cout << std::endl;
	}

	std::string to_string() {
		std::stringstream ss;
		this->to_string_rambler(this->head, ss);

		return ss.str();
	}


	class Iterator {
		MyBST<Key, Value> *bst;
		MyBSTNode *current_node;

	public:
		//next();
		Value& operator*() {
			if (current_node = NULL) {
				return (Value)0;
			}
			else {
				return current_node->v;
			}
		}
	};
	friend Iterator;
};


template <typename Key, typename Value>
MyBST<Key, Value>::MyBST() {
	this->head = NULL;
	this->size = 0;
	this->operation_counter = 0;
}

template <typename Key, typename Value>
bool MyBST<Key, Value>::insert(Key k, Value v) {
	bool flag = false;
	this->operation_counter = 0;
	MyBSTNode *node = this->insert(k, v, this->head, flag);
	if(this->head == NULL) {
		this->head = node;
	}

	if (flag == true) {
		this->size++;
	}

	return flag;
}

template <typename Key, typename Value>
typename MyBST<Key, Value>::MyBSTNode *MyBST<Key, Value>::insert(Key k, Value v, MyBST<Key, Value>::MyBSTNode *root, bool &iflag) {

	this->operation_counter++;

	if (root == NULL) {
		iflag = true;
		MyBSTNode *node = new MyBSTNode(k, v);
		return node;
	}

	if (k == root->k) {
		iflag = false;
		return root;
	}

	bool iresult;
	if (k < root->k) {
		root->l = this->insert(k, v, root->l, iresult);
	} else {
		root->r = this->insert(k, v, root->r, iresult);
	}

	iflag = iresult;
	return root;
}

template <typename Key, typename Value>
void MyBST<Key, Value>::clean() {
	this->clean(this->head);
	this->head = NULL;
}
#endif
