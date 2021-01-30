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
// Enum
protected:
	enum class ResizeResult {
		NO_CHANGE,
		EXPANDED,
		RETRACTED,
		SIZE_ENUM
	};

// Class
public:

	class Iterator;

//	class ConstIterator: public _ConstIterator_<Value> {
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

		ConstIterator(const ConstIterator &it) {
			this->container = it.container;
			this->index		= it.index;
			this->forward	= it.forward;
		}

		~ConstIterator() {

		}

		// operation
		// ...

	// Operator Overload
	public:
		// increment / decrement
		// ++a
		ConstIterator& operator++() {
			index += forward;
			return *this;
		}

		// --a
		ConstIterator& operator--() {
			index -= forward;
			return *this;
		}

		// a++
		ConstIterator operator++(int i) {
			ConstIterator temp(*this);
			index += forward;
			return temp;
		}

		// a--
		ConstIterator operator--(int i) {
			ConstIterator temp(*this);
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
		// a == b
		bool operator==(const ConstIterator &other) const {
			return this->index == other.index;
		}

		// a != b
		bool operator!=(const ConstIterator &other) const {
			return this->index != other.index;
		}

		// a < b
		bool operator<(const ConstIterator &other) const {
			return this->index < other.index;
		}

		// a > b
		bool operator>(const ConstIterator &other) const {
			return this->index > other.index;
		}

		// a <= b
		bool operator<=(const ConstIterator &other) const {
			return this->index <= other.index;
		}

		// a >= b
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


	//	class Iterator: public _Iterator_<Value> {
	// class Iterator: public Vector<Value>::ConstIterator {
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

		// copy constructor
		Iterator(const Iterator &it) {
	    	this->container	= it.container;
	    	this->index		= it.index;
	    	this->forward	= it.forward;
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
		// a + b
		Iterator operator+(const unsigned int i) {
			index += i;
			return *this;
		}

		// a - b
		Iterator operator-(const unsigned int i) {
			index -= i;
			return *this;
		}

		// comparison
		// a == b
		bool operator==(const Iterator &other) const {
			return this->index == other.index;
		}

		// a != b
		bool operator!=(const Iterator &other) const {
			return this->index != other.index;
		}

		// a < b
		bool operator<(const Iterator &other) const {
			return this->index < other.index;
		}

		// a > b
		bool operator>(const Iterator &other) const {
			return this->index > other.index;
		}

		// a <= b
		bool operator<=(const Iterator &other) const {
			return this->index <= other.index;
		}

		// a >= b
		bool operator>=(const Iterator &other) const {
			return this->index >= other.index;
		}

		// member access
		// a->
		Value& operator->() const {
	    	return container[index];
	    }

	    // *a
	    Value& operator*() const {
	    	return container[index];
	    }

	    // casting
	    operator ConstIterator() const {
	    	return ConstIterator(container, index, forward);
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

    // copy constructor
    Vector(const Vector& other):
    ratio_expansion(other.ratio_expansion),
    ratio_retraction(other.ratio_retraction),
    size_allocated(other.size_allocated),
    default_none(other.default_none) {
    	// copy the container
    	container = new Value[size_container];
    	memcpy(container, other.container, other.size_allocated);
    	this->size_allocated = other.size_allocated;
    }

	// assignment constructor
	Vector& operator=(const Vector &other) {
    	this->container 	 	= other.container;
    	this->size_container 	= other.size_container;
    	this->size_allocated 	= other.size_allocated;
    	this->ratio_retraction	= other.ratio_retraction;
    	this->ratio_expansion	= other.ratio_expansion;

    	return *this;
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

	void assign(unsigned int n, const Value &value) {
    	_resize_(n, false);
    	for (unsigned int i = n; i < n; ++i) container[i] = value;
    }

    void assign(ConstIterator begin, ConstIterator end) {
    	// get length
    	ConstIterator 	it 	= begin;
    	unsigned int	n	= 0;
    	while (it != end) {
    		n++;
    		it++;
    	}

    	// resize
    	_resize_(n, false);

    	// memcpy
    	for (unsigned int i = 0; i < n; ++i) {
    		container[i] = *begin;
    		begin++;
    	}
    }

//    void assign(Iterator begin, Iterator end) {
//    	// casting: Iterator -> ConstIterator
//    	assign( *((ConstIterator*)(&begin)), *((ConstIterator*)(&end)) );
//    }

    // a new element is inserted before the element at the specified position
    Iterator insert(Iterator position, const Value &value) {
    	// CONFIG
    	const unsigned int	index			= position.index;
		Value 				*container_old  = nullptr;

    	// expand
    	ResizeResult ret = _resize_(size_allocated + 1, false, &container_old);

    	// no change
    	if (ret == ResizeResult::NO_CHANGE) {
    		for (unsigned int i = size_allocated - 1; i >= index + 1; --i) container[i] = container[i - 1];
    		container[index] = value;
    	}

    	// resized
    	else {
    		memcpy(container, 				container_old,			sizeof(Value) * index);
    		memcpy(container + index + 1,	container_old + index,	sizeof(Value) * size_allocated - index);
    		container[index] = value;
    		delete container_old;
    	}

    	// new iterator
    	return position;
    }

    Iterator erase(Iterator position) {
    	// CONFIG
    	const unsigned int	index			= position.index;
    	Value				*container_old	= nullptr;

    	// retract
    	ResizeResult ret = _resize_(size_allocated - 1, false, &container_old);

    	// no change
    	if (ret == ResizeResult::NO_CHANGE) {
    		for (unsigned int i = index; i < size_allocated - 2; ++i) container[i] = container[i + 1];
    	}

    	// resized
    	else {
    		memcpy(container,			container_old, 				sizeof(Value) * index);
    		memcpy(container + index,	container_old + index + 1,	sizeof(Value) * size_allocated - index - 1);
    		delete container_old;
    	}

    	return position;
    }

    void swap(Vector<Value> &other) {
    	// assignment operator
    	Vector<Value> temp;
    	temp = other;

    	// assignment operator
    	other = *this;

    	// data from other to this
    	*this = temp;
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
    	// CONFIG
    	const unsigned int size_allocated_old = size_allocated;

    	// CORE
    	// resize, and the size_allocated will be updated
    	_resize_(n);

    	// fill the unfilled space
    	for (int i = size_allocated_old; i < n; ++i) container[i] = value;
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
	// if container is not nullptr
	// which means the function itself should do nothing to old container and leave upper to handle it
	ResizeResult _resize_(unsigned int n, Bool is_memcpy = true, Value* *container_old = nullptr) {
    	// CONFIG
    	ResizeResult ret;

    	// no change
    	if (n == size_allocated) return ResizeResult::NO_CHANGE;

    	// retract
    	if (n < size_allocated) {
    		ret = _retract_(n, is_memcpy, container_old);
    		size_allocated = n;
    		return ret;
    	}

		// expand (n > size_allocated)
		ret = _expand_(n, is_memcpy, container_old);
    	size_allocated = n;
    	return ret;
    }

	ResizeResult _expand_(unsigned int size_demand, Bool is_memcpy = true, Value* *container_old = nullptr) {
    	// expand the array if the current size of container is lower than the demand
    	unsigned int size_container_new = size_container;
    	while (size_container_new < size_demand) size_container_new *= ratio_expansion;

    	// check if need to actually expand the array
    	if (size_container_new == size_container) return ResizeResult::NO_CHANGE;

    	// allocate new array space and move data to the new container
    	auto container_new = new Value[size_container_new];
		if (is_memcpy) memcpy(container_new, container, min(size_container_new, size_allocated) * sizeof(Value));

		// destroy old container
		if (container_old == nullptr)	delete[] container;
		else							*container_old = container;

		// put new size_container and container
		size_container	= size_container_new;
		container		= container_new;

		return ResizeResult::EXPANDED;
    }

    ResizeResult _retract_(unsigned int size_demand, Bool is_memcpy = true, Value* *container_old = nullptr) {
    	// retract the array while the array can hold the size of demand
    	unsigned int size_container_new = size_container;
    	while ((unsigned int)((float)size_container_new * ratio_retraction) > size_demand) {
    		size_container_new = (unsigned int)((float)size_container_new * ratio_retraction);
    	}

    	// check if need to actually retract the array
    	if (size_container_new == size_container) return ResizeResult::NO_CHANGE;

    	// allocate new array space and move data to the new container
    	auto container_new = new Value[size_container_new];
		if (is_memcpy) memcpy(container_new, container, min(size_container_new, size_allocated) * sizeof(Value));

		// destroy old container
		if (container_old == nullptr)	delete[] container;
		else							*container_old = container;

		// put new size_container and container
		size_container	= size_container_new;
		container		= container_new;

		return ResizeResult::RETRACTED;
    }
};


// Function
//


// Namespace-End - Algo
}


#endif //ALGORITEMIMPLEMENTATION_VECTOR_H
