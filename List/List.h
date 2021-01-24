//
// Author: Jack Tse
// Date of creation: 23/1/2021
// Email: jacktsetcy@gmail.com
//

#ifndef ALGORITEMIMPLEMENTATION_LIST_H
#define ALGORITEMIMPLEMENTATION_LIST_H


// Import
#include "List_Base.h"
#include "Linked.h"
#include "Vector.h"


// Data Structure
template <class Value>
class _ListNode_ {
// Data
public:
    Value 		&value;
    _ListNode_	*prev;
    _ListNode_	*next;

// Function
public:
    // init and del
    explicit _ListNode_(Value &value):
    value(value),
    prev(nullptr),
    next(nullptr)
    {
    }

    ~_ListNode_() {
    }

    // operation
    // ...
};


template <class Value>
class List: public _List_<Value> {
// Data
public:
    _ListNode_<Value>	root;
    int					size_node;
    Value				default_none;

// Function
public:
    // init and del
    List():
    size_node(0),
    default_none(0)
    {
    	// set root
    	root.value	= default_none;
    	root.prev	= &root;
    	root.next	= &root;
    }

    ~List() {
    	// while the reconnect part in clear() function will be useless
    	clear();
    }

	// operation
    // modifier
	void push_back(Value &value) override {
    	// create node
    	auto target = new _ListNode_<Value>();
    	target.value = value;

    	// reconnect
    	auto prev_old = root.prev;
    	prev_old->next 	= target;
    	root->prev		= target;
    	target->prev	= prev_old;
    	target->next	= &root;

    	// update stat
    	size_node++;
	}

	void pop_back() override {
    	if (size_node == 0) return;

    	// CONFIG
    	auto target			= root.prev;
		auto target_prev 	= target->prev;

		// reconnect
		target_prev->next 	= &root;
		root.prev			= target_prev;

		// delete target
		delete target;

		// update stat
		size_node--;
	}

	void clear() override {
    	auto cur = root.next;
    	while (cur != root) {

    		// get current node
    		auto temp = cur;
    		cur = cur->next;

    		// delete cur (i.e. stored in temp)
    		delete temp;
    	}

    	// reconnect
    	root.next = &root;
    	root.prev = &root;
	}

	// data access
	Value &at(int index) override {
    	if (index < 0 || index >= size_node) return default_none;

    	auto cur = root.next;
    	while (index != 0) {
    		cur = cur->next;
    		index--;
    	}

    	return cur->value;
	}

	Value &front() override {
    	return root.next->value;
	}

	Value &back() override {
    	return root.prev->value;
	}

	// capacity
	int size() override {
		return size_node;
	}

	bool empty() override {
		return size_node == 0;
	}
};


// Function
// ...


#endif //ALGORITEMIMPLEMENTATION_LIST_H
