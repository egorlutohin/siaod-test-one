#ifndef mybsth
#define mybsth

template <typename Key, typename Value>
class MyBSTNode {
public:
	Value v;
	Key k;
	MyBSTNode<Key, Value> *l, *r;

//	MyBSTNode() {
//		l = NULL;
//		r = NULL;
//	}

	MyBSTNode(Key &k, Value &v){
		this->k = k;
		this->v = v;
		this->l = NULL;
		this->r = NULL;
	}
};

template <typename Key, typename Value>
class MyBST {
	MyBSTNode<Key, Value> *head;
	void to_string_rambler(MyBSTNode<Key, Value> *n, std::stringstream &ss) {

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

public:
	MyBST();
	MyBSTNode<Key, Value> *insert(Key, Value);
	MyBSTNode<Key, Value> *insert(Key, Value, MyBSTNode<Key, Value> *, bool&);

	std::string to_string() {
		std::stringstream ss;
		this->to_string_rambler(this->head, ss);

		return ss.str();
	}


	class Iterator {
		MyBST<Key, Value> *bst;
		MyBSTNode<Key, Value> *current_node;

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
}

template <typename Key, typename Value>
MyBSTNode<Key, Value> *MyBST<Key, Value>::insert(Key k, Value v) {
	bool flag;
	MyBSTNode<int, int> *node = this->insert(k, v, this->head, flag);
	if(this->head == NULL) {
		this->head = node;
	}
	return node;
}

template <typename Key, typename Value>
MyBSTNode<Key, Value> *MyBST<Key, Value>::insert(Key k, Value v, MyBSTNode<Key, Value> *root, bool &iflag) {

	if (root == NULL) {
		iflag = true;
		MyBSTNode<Key, Value> *node = new MyBSTNode<Key, Value>(k, v);
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

#endif
