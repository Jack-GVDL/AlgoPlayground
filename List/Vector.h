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


// Namespace-Begin - Algo
namespace Algo {


// Data Structure
template <class Value>
class Vector: public _List_<Value> {
// Class
public:
	class Iterator {
	// Data
	public:
		Value 	*container;
		int		index;
		int 	forward;

	// Function
	public:
		// init and del
		Iterator(Value *container_, int index_, int forward_ = 1):
		container(container_),
		index(index_),
		forward(forward_)
		{
		}

		~Iterator() {

		}

		// operation
		// ...

	// Operator Overload
	public:
		// ++a
		Iterator &operator++() {
			index += forward;
			return *this;
		}

		// --a
		Iterator &operator--() {
			index -= forward;
			return *this;
		}

		// a++
		Iterator operator++(int i) {
			Iterator temp = *this;
			index += forward;
			return temp;
		}

		// --a
		Iterator operator--(int i) {
			Iterator temp = *this;
			index -= forward;
			return temp;
		}

		// a==
		bool operator==(const Iterator &other) const {
			return this->index == other.index;
		}

		// a!=
		bool operator!=(const Iterator &other) const {
			return this->index != other.index;
		}

		// a->
		Value& operator->() const {
			return container[index];
		}

		// *a
		Value& operator*() const {
			return container[index];
		}
	};

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
    // modifier
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

	// data access
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

	// capacity
	int size() override {
		return size_allocated;
	}

	bool empty() override {
		return size_allocated == 0;
	}

	// iterator
	Iterator begin() const {
		return Iterator(container, 0);
	}

	Iterator end() const {
		return Iterator(container, size_allocated);
	}

	Iterator rbegin() const {
    	return Iterator(container, size_allocated - 1, -1);
    }

    Iterator rend() const {
    	return Iterator(container, -1, -1);
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
//


// Namespace-End - Algo
}


#endif //ALGORITEMIMPLEMENTATION_VECTOR_H
