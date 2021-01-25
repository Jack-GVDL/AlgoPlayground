//
// Author: Jack Tse
// Date of creation: 23/1/2021
// Email: jacktsetcy@gmail.com
//

#ifndef ALGORITEMIMPLEMENTATION_VECTOR_H
#define ALGORITEMIMPLEMENTATION_VECTOR_H


// Import
#include "List_Base.h"
#include <string>
#include <algorithm>


// Data Structure
template <class Value>
class Vector: public _List_<Value> {
// Data
public:
    Value			*container;
    unsigned int	size_container;
    unsigned int	size_allocated;
    float			ratio_expansion;
    float			ratio_retraction;
    Value			default_none;

// Function
public:
    // init and del
    Vector():
    	ratio_expansion(2),
    	ratio_retraction(0.5),
    	size_allocated(0),
    	default_none(0)
    {
		size_container	= 1 * ratio_expansion;
		container		= new Value[size_container];
    }

    ~Vector() {
    	delete[] container;
    }

    // operation
	void push_back(Value &value) override {
    	// check if need to expand or not
    	_expand_();

    	// add to back
    	container[size_allocated] = value;
    	size_allocated++;
	}

	void pop_back() override {
    	// rm from back
    	size_allocated--;

    	// check if need to retract or not
    	_retract_();
	}

	void clear() override {
    	delete[] container;

    	size_allocated = 0;
    	size_container = 1 * ratio_expansion;
    	container = new Value[size_container];
	}

	Value &at(int index) override {
    	if (index < 0 || index >= size_allocated) return default_none;
    	return container[index];
	}

	Value &front() override {
    	if (size_allocated == 0) return default_none;
    	return container[0];
	}

	Value &back() override {
    	if (size_allocated == 0) return default_none;
    	return container[size_allocated - 1];
	}

	int size() override {
		return size_allocated;
	}

	bool empty() override {
		return size_allocated == 0;
	}

protected:
	void _expand_() {
    	// CHECK
    	// expand the array if it is full
    	if (size_allocated < size_container) return;

    	// CORE
    	// create new container
    	int		size_container_new	= size_container * ratio_expansion;
    	auto	container_new		= new Value[size_container_new];

		// move data from old to new container
		memcpy(container_new, container, size_allocated * sizeof(Value));

		// destroy old container
		delete[] container;

		// put new size_container and container
		size_container	= size_container_new;
		container		= container_new;
    }

    void _retract_() {
    	// CHECK
    	// extract the array if it is
    	// - below half-full (TODO: need to consider ratio_retraction), AND
    	// - above min size of container (1 * ratio_expansion)
    	if (size_allocated < size_container / 2) return;

    	// CORE
    	// create new container
    	int		size_container_new	= std::max<int>(1 * ratio_expansion, size_container / 2);
    	auto	container_new		= new Value[size_container_new];

    	// move data from old to new container
		memcpy(container_new, container, size_allocated * sizeof(Value));

		// destroy old container
		delete[] container;

		// put new size_container and container
		size_container	= size_container_new;
		container		= container_new;
    }
};


// Function
// ...


#endif //ALGORITEMIMPLEMENTATION_VECTOR_H
