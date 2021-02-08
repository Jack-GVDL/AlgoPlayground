//
// Author: Jack Tse
// Date of creation: 26/1/2021
// Email: jacktsetcy@gmail.com
//

#ifndef ALGORITEMIMPLEMENTATION_STACK_H
#define ALGORITEMIMPLEMENTATION_STACK_H


// Import
#include "../List/List.h"
#include "Queue_Base.h"


// Namespace-Begin - Algo
namespace Algo {


// Data Structure
//template <class Value, class Allocator = Vector<Value>>
template <class Value>
class Stack: public _Queue_<Value> {
// Data
public:
//    Allocator container;
	Vector<Value> container;

// Function
public:
    // init and del
    Stack()
    {
    }

    // assignment operator
    Stack& operator=(const Stack& other) {
    	this->container = other.container;
    	return *this;
    }

    ~Stack() {

    }

    // operation
	void push(const Value &value) override {
    	container.push_back(value);
	}

	void pop() override {
    	container.pop_back();
	}

	void clear() override {
		container.clear();
	}

	Value &top() override {
		return container.back();
	}

	const Value& top() const {
    	return container.back();
    }

	int size() const override {
		return container.size();
	}

	bool empty() const override {
		return container.empty();
	}
};


// Function
// ...


// Namespace-End - Algo
}


#endif //ALGORITEMIMPLEMENTATION_STACK_H
