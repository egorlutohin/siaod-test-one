#ifndef mybsth
#define mybsth

//template <typename Key, typename Value>

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

	MyBSTNode *insert(Key, Value, MyBSTNode *, bool&);

public:
	MyBST();
	bool insert(Key, Value);
	void clean();

	size_t get_size() {
		return size;
	}

	bool is_empty() {
		return (this->get_size() == 0);
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
}

template <typename Key, typename Value>
bool MyBST<Key, Value>::insert(Key k, Value v) {
	bool flag = false;
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
