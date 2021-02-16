//
// Author: Jack Tse
// Date of creation: 26/1/2021
// Email: jacktsetcy@gmail.com
//

#ifndef ALGORITEMIMPLEMENTATION_QUEUE_H
#define ALGORITEMIMPLEMENTATION_QUEUE_H


// Import
#include "Queue_Base.h"
#include "Stack.h"


// Namespace-Begin - Algo
namespace Algo {


// Data Structure
template <class Value>
class Queue: public _Queue_<Value> {
// Data
public:
    Vector<Value> container;

// Function
public:
    // init and del
    Queue()
    {
    }

    // assignment operator
    Queue& operator=(const Queue& other) {
    	this->container = other.container;
    	return *this;
    }

    ~Queue() {
    }

    // operation
	void push(const Value &value) override {
		container.push_back(value);
	}

	// TODO
	void pop() override {
//		container.pop_front();
	}

	void clear() override {
    	container.clear();
    }


	Value &top() override {
		return container.front();
	}

	const Value &top() const override {
		return container.front();
	}

	int size() const override {
		return container.size();
	}

	bool empty() const override {
		return container.empty();
	}

// Operator Overload
public:
	// ...
};


// Function
// ...


// Namespace-End - Algo
}


#endif //ALGORITEMIMPLEMENTATION_QUEUE_H
