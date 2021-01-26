//
// Author: Jack Tse
// Date of creation: 26/1/2021
// Email: jacktsetcy@gmail.com
//

#ifndef ALGORITEMIMPLEMENTATION_ITERATOR_H
#define ALGORITEMIMPLEMENTATION_ITERATOR_H


// Import
// ...


// Namespace-Begin - Algo
namespace Algo {


// Data Structure
template <class Value>
class _Iterator_ {
// Data
public:
    // ...

// Function
public:
    // init and del
	_Iterator_() {
    }

    ~_Iterator_() {
    }

    // operation
    // ...

// Operator Overload
public:
	// ++a
	virtual _Iterator_& operator++() {
    	return *this;
    }

    // --a
    virtual _Iterator_& operator--() {
    	return *this;
    }

    // a++
	virtual _Iterator_ operator++(int) {
    	return *this;
    }

    // a--
    virtual _Iterator_ operator--(int) {
    	return *this;
    }

    // a->
    virtual Value* operator->() const {
    	return nullptr;
    }

    // *a
    virtual Value* operator*() const {
    	return nullptr;
    }
};


// Function
// ...


// Namespace-End - Algo
}


#endif //ALGORITEMIMPLEMENTATION_ITERATOR_H
