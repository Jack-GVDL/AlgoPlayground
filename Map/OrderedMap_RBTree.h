//
// Author: Jack Tse
// Date of creation: 31/1/2021
// Email: jacktsetcy@gmail.com
//

#ifndef ALGORITEMIMPLEMENTATION_ORDEREDMAP_RBTREE_H
#define ALGORITEMIMPLEMENTATION_ORDEREDMAP_RBTREE_H


// Import
#include "OrderedMap_Base.h"
#include <Queue.h>


// Namespace-Begin - Algo
namespace Algo {


// Data Structure
template <class Key, class Value>
class _RBNode_ {
// Data
public:
    _RBNode_	*left;
    _RBNode_	*right;
    Key			key;
    Value		value;
    Bool		is_black;

// Function
public:
    // init and del
    _RBNode_():
    left(nullptr),
    right(nullptr),
    value(0),
    is_black(true)
	{
	}

    _RBNode_(const Key &key_, const Value &value_):
    left(nullptr),
    right(nullptr),
    key(key_),
    value(value_),
    is_black(true)
    {
    }

    _RBNode_(const _RBNode_ &left_, const _RBNode_ &right_, const Key &key_, const Value &value_):
    left(left_),
    right(right_),
    key(key_),
    value(value),
    is_black(true)
	{}

    ~_RBNode_() {

    }

    // operation
    // ...

// Operator Overload
public:
	// ...
};


template <class Key, class Value>
class OrderedMap_RBTree: public _OrderedMap_<Key, Value> {
// Class
public:
	class ConstIterator {
	// Data
	public:
	    // ...

	// Function
	public:
	    // init and del
	    ConstIterator() {

	    }

	    ~ConstIterator() {

	    }

	    // operation
	    // ...

	// Operator Overload
	public:
		// ...
	};

	class Iterator {
	// Data
	public:
	    // ...

	// Function
	public:
	    // init and del
	    Iterator() {

	    }

	    ~Iterator() {

	    }

	    // operation
	    // ...

	// Operator Overload
	public:
		// ...
	};

// Data
public:
	_RBNode_<Key, Value>	_root_;
	_RBNode_<Key, Value>	*root;
    unsigned int			size_allocated;

// Function
public:
    // init and del
    OrderedMap_RBTree():
    root(&_root_),
    size_allocated(0)
    {
    }

    ~OrderedMap_RBTree() {
    	// iterative method
    	Stack<_RBNode_<Key, Value>*> stack;
    	if (root->left != nullptr)	stack.push(root->left);
    	if (root->right != nullptr)	stack.push(root->right);

    	while (!stack.empty()) {
    		_RBNode_<Key, Value>* top = stack.top();
    		stack.pop();

    		if (root->left != nullptr)	stack.push(top->left);
    		if (root->right != nullptr)	stack.push(top->right);

    		delete top;
    	}
    }

    // modifier
	void insert(const Key &key, const Value &value) override {

	}

	void erase(const Key &key) override {

	}

	void clear() override {

	}

	void swap(_OrderedMap_ <Key, Value> &other) override {

	}

	// element access
	Value &at(const Key &key) override {
	}

	// capacity
	unsigned int size() override {
		return size_allocated;
	}

	bool empty() override {
		return size_allocated == 0;
	}

	// TODO
	unsigned int max_size() override {
		return 0;
	}

	// operation
	Iterator begin() {

    }

	Iterator end() {

    }

	Iterator rbegin() {

    }

	Iterator rend() {

    }

	ConstIterator cbegin() const {

    }

	ConstIterator cend() const {

    }

	ConstIterator crbegin() const {

    }

	ConstIterator crend() const {

    }

// Operator Overload
public:
	// ...
};


// Function
// ...


// Namespace-End - Algo
}


#endif //ALGORITEMIMPLEMENTATION_ORDEREDMAP_RBTREE_H
