//
// Author: Jack Tse
// Date of creation: 31/1/2021
// Email: jacktsetcy@gmail.com
//

#ifndef ALGORITEMIMPLEMENTATION_ORDEREDMAP_BASE_H
#define ALGORITEMIMPLEMENTATION_ORDEREDMAP_BASE_H


// Import
#include <Utility.h>


// Namespace-Begin - Algo
namespace Algo {


// Data Structure
template <class Key, class Value>
class _OrderedMap_ {
// Class
public:
	// ...

// Data
public:
    // ...

// Function
public:
    // init and del
    _OrderedMap_() {
    }

    ~_OrderedMap_() {
    }

    // operation
    // modifier
    virtual void insert(const Key &key, const Value &value) = 0;
    virtual void erase(const Key &key) = 0;
    virtual void clear() = 0;
    virtual void swap(_OrderedMap_& other) = 0;

    // element access
    virtual Value& at(const Key &key) = 0;

    // capacity
    virtual unsigned int size() = 0;
    virtual bool empty() = 0;
    virtual unsigned int max_size() = 0;

    // iterator
    // ...

// Operator Overload
public:
	Value& operator[](const Key &key) {
		return at(key);
	}
};


// Function
// ...


// Namespace-End - Algo
}


#endif //ALGORITEMIMPLEMENTATION_ORDEREDMAP_BASE_H
