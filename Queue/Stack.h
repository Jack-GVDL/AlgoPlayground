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
template <class Value>
class Stack: public _Queue_<Value> {
// Data
public:
    _List_<Value> container;

// Function
public:
    // init and del
    Stack(_List_ container_ = Vector<Value>()):
    container(container_)
    {
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
