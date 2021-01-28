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
	class ConstIterator {
	// Data
	public:
		Value 	*container;
		int		index;
		int 	forward;

	// Function
	public:
		// init and del
		ConstIterator(Value *container_, int index_, int forward_ = 1):
		container(container_),
		index(index_),
		forward(forward_)
		{
		}

		~ConstIterator() {

		}

		// operation
		// ...

	// Operator Overload
	public:
		// increment / decrement
		// ++a
		ConstIterator &operator++() {
			index += forward;
			return *this;
		}

		// --a
		ConstIterator &operator--() {
			index -= forward;
			return *this;
		}

		// a++
		ConstIterator operator++(int i) {
			Iterator temp = *this;
			index += forward;
			return temp;
		}

		// --a
		ConstIterator operator--(int i) {
			Iterator temp = *this;
			index -= forward;
			return temp;
		}

		// arithmetic
		// a+b
		ConstIterator operator+(const unsigned int i) {
			index += i;
			return *this;
		}

		// a-b
		ConstIterator operator-(const unsigned int i) {
			index -= i;
			return *this;
		}

		// comparison
		// a==b
		bool operator==(const ConstIterator &other) const {
			return this->index == other.index;
		}

		// a!=b
		bool operator!=(const ConstIterator &other) const {
			return this->index != other.index;
		}

		// a<b
		bool operator<(const ConstIterator &other) const {
			return this->index < other.index;
		}

		// a>b
		bool operator>(const ConstIterator &other) const {
			return this->index > other.index;
		}

		// a<=b
		bool operator<=(const ConstIterator &other) const {
			return this->index <= other.index;
		}

		// a>=b
		bool operator>=(const ConstIterator &other) const {
			return this->index >= other.index;
		}

		// member access
		// a->
		const Value& operator->() const {
			return container[index];
		}

		// *a
		const Value& operator*() const {
			return container[index];
		}
	};


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
		// increment / decrement
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

		// arithmetic
		// a+b
		Iterator operator+(const unsigned int i) {
			index += i;
			return *this;
		}

		// a-b
		Iterator operator-(const unsigned int i) {
			index -= i;
			return *this;
		}

		// comparison
		// a==b
		bool operator==(const Iterator &other) const {
			return this->index == other.index;
		}

		// a!=b
		bool operator!=(const Iterator &other) const {
			return this->index != other.index;
		}

		// a<b
		bool operator<(const Iterator &other) const {
			return this->index < other.index;
		}

		// a>b
		bool operator>(const Iterator &other) const {
			return this->index > other.index;
		}

		// a<=b
		bool operator<=(const Iterator &other) const {
			return this->index <= other.index;
		}

		// a>=b
		bool operator>=(const Iterator &other) const {
			return this->index >= other.index;
		}

		// member access
		// a->
		Value& operator->() const {
	    	return container[index];
	    }

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

    Vector(unsigned int size_):
    ratio_expansion(2),
    ratio_retraction(0.5),
    size_allocated(0),
    default_none(0)
    {
    	// get the size needed
    	size_container = ratio_expansion;
    	while (size_container < size_) size_container *= ratio_expansion;

    	// allocate space for container
    	container = new Value[size_container];
    }

    Vector(unsigned int size_, Value value_fill):
    ratio_expansion(2),
    ratio_retraction(0.5),
    size_allocated(0),
    default_none(0)
    {
    	// get the size needed
    	size_container = ratio_expansion;
    	while (size_container < size_) size_container *= ratio_expansion;

    	// allocate space for container
    	container = new Value[size_container];

    	// fill container
    	for (int i = 0; i < size_; ++i) container[i] = value_fill;
    	size_allocated = size_;
    }

    ~Vector() {
    	delete[] container;
    }

    // operation
    // modifier
	void push_back(Value &value) override {
    	// check if need to expand or not
    	_expand_(size_allocated + 1);

    	// add to back
    	container[size_allocated] = value;
    	size_allocated++;
	}

	void pop_back() override {
    	// rm from back
    	size_allocated--;

    	// check if need to retract or not
    	_retract_(size_allocated);
	}

	void clear() override {
    	delete[] container;

    	size_allocated = 0;
    	size_container = 1 * ratio_expansion;
    	container = new Value[size_container];
	}

	// data access
	Value &at(unsigned int index) override {
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

	Value* data() {
    	return container;
    }

	// capacity
	unsigned int size() override {
		return size_allocated;
	}

	// TODO
	unsigned int max_size() override {
    	return 0;
    }

    unsigned int capacity() {
    	return size_container;
    }

	bool empty() override {
		return size_allocated == 0;
	}

	void resize(unsigned int n, Value value) {
		// no change
		if (n == size_allocated) return;

		// retract
		if (n < size_allocated) {
			_retract_(n);
			size_allocated = n;
			return;
		}

		// expand (n > size_allocated)
		_expand_(n);
		for (int i = size_allocated; i < n; ++i) container[i] = value;
		size_allocated = n;
	}

	void resize(unsigned int n) {
    	resize(n, default_none);
    }

	// only effective if n > size_container
	void reserve(unsigned int n) {
    	if (n <= size_container) return;
    	_expand_(n);
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

	ConstIterator cbegin() const {
		return ConstIterator(container, 0);
	}

	ConstIterator cend() const {
		return ConstIterator(container, size_allocated);
	}

	ConstIterator crbegin() const {
		return ConstIterator(container, size_allocated - 1, -1);
	}

	ConstIterator crend() const {
		return ConstIterator(container, -1, -1);
	}

protected:
	void _expand_(unsigned int size_demand) {
    	// expand the array if the current size of container is lower than the demand
    	unsigned int size_container_new = size_container;
    	while (size_container_new < size_demand) size_container_new *= ratio_expansion;

    	// check if need to actually expand the array
    	if (size_container_new == size_container) return;

    	// allocate new array space and move data to the new container
    	auto container_new = new Value[size_container_new];
		memcpy(container_new, container, min(size_container_new, size_allocated) * sizeof(Value));

		// destroy old container
		delete[] container;

		// put new size_container and container
		size_container	= size_container_new;
		container		= container_new;
    }

    void _retract_(unsigned int size_demand) {
    	// retract the array while the array can hold the size of demand
    	unsigned int size_container_new = size_container;
    	while ((unsigned int)((float)size_container_new * ratio_retraction) > size_demand) {
    		size_container_new = (unsigned int)((float)size_container_new * ratio_retraction);
    	}

    	// check if need to actually retract the array
    	if (size_container_new == size_container) return;

    	// allocate new array space and move data to the new container
    	auto container_new = new Value[size_container_new];
		memcpy(container_new, container, min(size_container_new, size_allocated) * sizeof(Value));

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
