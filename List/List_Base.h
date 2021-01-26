//
// Author: Jack Tse
// Date of creation: 23/1/2021
// Email: jacktsetcy@gmail.com
//

#ifndef ALGORITEMIMPLEMENTATION_LIST_BASE_H
#define ALGORITEMIMPLEMENTATION_LIST_BASE_H


// Import
#include "../Utility/Utility.h"


// Namespace-Begin - Algo
namespace Algo {


// Data Structure
template <class Value>
class _List_ {
// Data
public:
    // ...

// Function
public:
    // init and del
	_List_() {
    }

    ~_List_() {
    }

    // operation
    // modifier
	virtual void push_back(Value &value) = 0;
    virtual void pop_back() = 0;
    virtual void clear() = 0;

    // data access
    virtual Value& at(int index) = 0;
    virtual Value& front() = 0;
    virtual Value& back() = 0;

    // capacity
	virtual int size() = 0;
	virtual bool empty() = 0;

	// iterator
//	virtual _Iterator_<Value>& begin() = 0;
//	virtual _Iterator_<Value>& end() = 0;

// Operator Overload
public:
	Value& operator[](int index) {
		return at(index);
	}
};


// Function
// ...


// Namespace-End - Algo
}


#endif //ALGORITEMIMPLEMENTATION_LIST_BASE_H
