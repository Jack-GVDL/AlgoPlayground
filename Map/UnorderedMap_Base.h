// Author: Jack Tse
// Date of creation: 2021-01-20
// Email: jacktsetcy@gmail.com
//
#ifndef ALGORITEMIMPLEMENTATION_UNORDEREDMAP_BASE_H
#define ALGORITEMIMPLEMENTATION_UNORDEREDMAP_BASE_H


// Import
//#include <utility>
#include <Utility.h>


// Namespace
namespace Algo {


// Class
// TODO: change name to _UnorderedMap_ or UnorderedMap_Base
template <class Key, class Value>
class _UnorderedMap_ {
// Data
public:
    // ...

// Function
public:
    // init and del
//    _UnorderedMap_(){
//    }

//    ~_UnorderedMap_(){
//    }

    // operation
    virtual void insert(const Key &key, const Value &value) = 0;
    virtual void erase(const Key &key) = 0;
    virtual void clear() = 0;
    virtual Value& at(const Key &key) = 0;

    virtual int size() = 0;
    virtual bool empty() = 0;

// Operator Overload
public:
	Value& operator[](const Key &key) {
		return at(key);
	}
};


// Namespace: Algo
};


#endif //ALGORITEMIMPLEMENTATION_UNORDEREDMAP_BASE_H
