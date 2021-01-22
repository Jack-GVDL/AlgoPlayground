//
// Author: Jack Tse
// Date of creation: 22/1/2021
// Email: jacktsetcy@gmail.com
//

#ifndef ALGORITEMIMPLEMENTATION_UNORDEREDMAP_DYNAMIC_H
#define ALGORITEMIMPLEMENTATION_UNORDEREDMAP_DYNAMIC_H


// Import
#include "UnorderedMap.h"


// Namespace-Begin - Algo
namespace Algo {


// Data Structure
template <class Key, class Value>
class _HashBucket_;


template<class Key, class Value>
union _HashBucket_Container_ {
	Pair<Key, Value>			*leaf;
	_HashBucket_<Key, Value>	*node;
};


template <class Key, class Value>
class _HashBucket_ {
// Typedef
	typedef _HashBucket_Container_<Key, Value> BC;  // BC standard for: bucket container

// Data
public:
    int					depth;
    Pair<Bool, BC*>		*bucket;
    int 				size_bucket;

// Function
public:
    // init and del
    _HashBucket_(int depth, int size_bucket):
    depth(depth),
    size_bucket(size_bucket)
    {
    	bucket = new Pair<Bool, BC*>[size_bucket];
    	for (int i = 0; i < size_bucket; ++i) {
    		bucket[i].first		= true;
    		bucket[i].second	= nullptr;
    	}
    }

    ~_HashBucket_() {
    	delete[] bucket;
    }

    // operation
    // insert
    // ...

    // erase
    // ...
};


template <class Key, class Value>
class UnorderedMap_Dynamic: public UnorderedMap<Key, Value> {
// Data
protected:
    // ...

// Function
public:
    // init and del
    UnorderedMap_Dynamic() {

    }

    ~UnorderedMap_Dynamic() {

    }

    // operation
	void insert(const Key &key, const Value &value) override {

	}

	void erase(const Key &key) override {

	}

	void clear() override {

	}

	Value &at(const Key &key) override {
	}

	int size() override {
	}

	bool empty() override {
	}
};


// Function
// ...


// Namespace-End - Algo
}


#endif //ALGORITEMIMPLEMENTATION_UNORDEREDMAP_DYNAMIC_H
