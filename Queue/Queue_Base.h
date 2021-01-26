//
// Author: Jack Tse
// Date of creation: 26/1/2021
// Email: jacktsetcy@gmail.com
//

#ifndef ALGORITEMIMPLEMENTATION_QUEUE_BASE_H
#define ALGORITEMIMPLEMENTATION_QUEUE_BASE_H


// Import
// ...


// Namespace-Begin - Algo
namespace Algo {


// Data Structure
template <class Value>
class _Queue_ {
// Data
public:
    // ...

// Function
public:
    // init and del
    _Queue_() {
    }

    ~_Queue_() {
    }

    // operation
    // modifier
    virtual void push(Value &value) = 0;
    virtual void pop() = 0;
    virtual void clear() = 0;

    // data access
    virtual Value &top() = 0;

    // capacity
    virtual int size() = 0;
    virtual bool empty() = 0;

// Operator Overload
public:
	// ...
};


// Function
// ...

// Namespace-End - Algo
}


#endif //ALGORITEMIMPLEMENTATION_QUEUE_BASE_H
