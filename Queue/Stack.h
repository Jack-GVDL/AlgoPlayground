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
template <class Value, class Allocator = Vector<Value>>
class Stack: public _Queue_<Value> {
// Data
public:
    Allocator container;

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
	void push(Value &value) override {
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

	int size() override {
		return container.size();
	}

	bool empty() override {
		return container.empty();
	}
};


// Function
// ...


// Namespace-End - Algo
}


#endif //ALGORITEMIMPLEMENTATION_STACK_H
