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
class _ConstIterator_ {
// Data
public:
    // ...

// Function
public:
    // init and del
	_ConstIterator_() {
    }

    ~_ConstIterator_() {
    }

    // operation
    // ...

// Operator Overload
public:
	// increment / decrement
	virtual _ConstIterator_& operator++() = 0;							// ++a
	virtual _ConstIterator_& operator--() = 0;							// --a
//	virtual _ConstIterator_& operator++(int i) = 0;						// a++
//	virtual _ConstIterator_& operator--(int i) = 0;						// a--

//	virtual bool operator==(const _ConstIterator_ &other) const = 0;	// a == b
//	virtual bool operator!=(const _ConstIterator_ &other) const = 0;	// a != b

    virtual const Value& operator->() const = 0;  						// *a
    virtual const Value& operator*() const = 0; 						// *a
};


// Function
template <class Value>
class _Iterator_: public _ConstIterator_<Value> {
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
	// increment / decrement
	virtual _Iterator_& operator++() = 0;			// ++a
	virtual _Iterator_& operator--() = 0;			// --a
//	virtual _Iterator_& operator++(int i) = 0;		// a++
//	virtual _Iterator_& operator--(int i) = 0;		// a--

	virtual Value& operator->() const = 0;  		// *a
	virtual Value& operator*() const = 0; 			// *a
};


// Namespace-End - Algo
}


#endif //ALGORITEMIMPLEMENTATION_ITERATOR_H
