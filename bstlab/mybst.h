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
	size_t change_counter;
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

		this->change_counter++;
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

		this->change_counter++;
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

			this->change_counter++;
			delete t;
			this->size--;
			return NULL;
		}

		if(t->l == NULL) {
			MyBSTNode *x = t->r;
			if (t == this->head) {
				this->head = t->r;
			}

			this->change_counter++;
			delete t;
			this->size--;

			return x;
		}

		if(t->r == NULL) {
			MyBSTNode *x = t->l;
			if (t == this->head) {
				this->head = t->l;
			}

			this->change_counter++;
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
		size_t bst_create_counter;

		void check_changes_in_bst() {
			if (this->bst->change_counter != this->bst_create_counter) {
				throw "Изменилось дерево";
			}
		}

		void goto_min(MyBSTNode *n) {
			if (n == NULL) {
				return;
			}

			this->current_node = n;
			goto_min(n->l);
		}

		void goto_max(MyBSTNode *n) {
			if (n == NULL) {
				return;
			}

			this->current_node = n;
			goto_max(n->r);
		}

		MyBSTNode *max(MyBSTNode *t) {
			if (t == NULL) {
				return NULL;
			}

			while (t->r != NULL) {
				t = t->r;
			}

			return t;
		}

		MyBSTNode *min(MyBSTNode *t) {
			if (t == NULL) {
				return NULL;
			}

			while (t->l != NULL) {
				t = t->l;
			}

			return t;
		}

		MyBSTNode *r_parent(MyBSTNode *t, MyBSTNode *x) {
			if (t == x) {
				return NULL;
			}

			if (x->k > t->k) {
				MyBSTNode *rp;
				rp = r_parent(t->r, x);
				if(rp != NULL) {
					return rp;
				} else {
					return t;
				}
			} else {
				return r_parent(t->l, x);
			}
		}

		MyBSTNode *predcessor(MyBSTNode *r, MyBSTNode *x) {
			if (x->l != NULL) {
				return max(x->l);
			} else {
				return r_parent(r, x);
			}
		}

		MyBSTNode *l_parent(MyBSTNode *t, MyBSTNode *x) {
			if (t == x) {
				return NULL;
			}

			if (x->k < t->k) {
				MyBSTNode *rp;
				rp = l_parent(t->l, x);
				if(rp != NULL) {
					return rp;
				} else {
					return t;
				}
			} else {
				return l_parent(t->r, x);
			}
		}


		MyBSTNode *successor(MyBSTNode *r, MyBSTNode *x) {
			if(x->r != NULL) {
				return min(x->r);
			} else {
				return l_parent(r, x);
			}
		}

	public:
		Iterator(MyBST<Key, Value> *t) {
			this->bst = t;
			this->current_node = this->bst->head;
			this->bst_create_counter = this->bst->change_counter;
		}

		bool not_null() {
			return !(this->current_node == NULL);
		}

		//доступ по чтению и записи к данным текущего узла в дереве
		Value& current_value() {
			check_changes_in_bst();

			if (this->bst->get_size() == 0) {
				throw "Дерево пустое";
			}

			if (this->current_node == NULL) {
				throw "Текущий элемент пустой";
			}

			return this->current_node->v;
		}

		// установка на первый узел в дереве с минимальным ключом
		void goto_min() {
			check_changes_in_bst();
			goto_min(this->bst->head);
		}

		//установка на последний узел в дереве с максимальным ключом
		void goto_max() {
			check_changes_in_bst();
			goto_max(this->bst->head);
		}

		void previous() {
			check_changes_in_bst();

			if (this->current_node == NULL) {
				return;
			}

			this->current_node = this->predcessor(this->bst->head, this->current_node);
			return;
		}

		void next() {
			check_changes_in_bst();

			if(this->current_node == NULL) {
				return;
			}

			this->current_node = this->successor(this->bst->head, this->current_node);
			return;
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
		this->change_counter++;
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
