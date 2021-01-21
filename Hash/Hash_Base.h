// Author: Jack Tse
// Date of creation: 2021-01-20
// Email: jacktsetcy@gmail.com
//
#ifndef ALGORITEMIMPLEMENTATION_HASH_BASE_H
#define ALGORITEMIMPLEMENTATION_HASH_BASE_H


// Import
#include <utility>


// Namespace
namespace Algo {


// Class
template <class Key, class Value>
class Hash_Base {
// Data
public:
    // ...

// Function
public:
    // init and del
//    Hash_Base(){
//    }

//    ~Hash_Base(){
//    }

    // operation
    virtual void insert(const Key &key, const Value &value) = 0;
    virtual void erase(const Key &key) = 0;
    virtual void clear() = 0;
    virtual Value& at(const Key &key) = 0;

    virtual int size() = 0;
    virtual bool empty() = 0;
};


// Namespace: Algo
};


#endif //ALGORITEMIMPLEMENTATION_HASH_BASE_H
