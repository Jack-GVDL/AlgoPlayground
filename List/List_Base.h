//
// Author: Jack Tse
// Date of creation: 23/1/2021
// Email: jacktsetcy@gmail.com
//

#ifndef ALGORITEMIMPLEMENTATION_LIST_BASE_H
#define ALGORITEMIMPLEMENTATION_LIST_BASE_H


// Import
// ...


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

// Operator Overload
public:
	Value& operator[](int index) {
		return at(index);
	}
};


// Function
// ...


#endif //ALGORITEMIMPLEMENTATION_LIST_BASE_H
