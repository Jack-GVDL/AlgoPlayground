//
// Author: Jack Tse
// Date of creation: 20/1/2021
// Email: jacktsetcy@gmail.com
//

#ifndef ALGORITEMIMPLEMENTATION_UNORDEREDMAP_SIMPLE_H
#define ALGORITEMIMPLEMENTATION_UNORDEREDMAP_SIMPLE_H


// Import
#include "UnorderedMap_Base.h"


// Namespace
namespace Algo {


// Function Prototype
template<class Key>
inline int _getHash_Simple_(const Key &key, int size_container);
inline int _getHash_Simple_(const int &key, int size_container);


// Data Structure
template<class Key, class Value>
class UnorderedMap_Simple : public _UnorderedMap_<Key, Value> {
// Data
protected:
	Pair<Key, Value> **container;
	int size_container;
	int size_allocated;

// Function
public:
	// init and del
	explicit UnorderedMap_Simple(int size_container_) :
	size_container(size_container_),
	size_allocated(0)
	{
		// the actual size of container is size_container + 1
		// the extra space if for storing nullptr for end marker used in searching
		size_container = size_container + 1;

		container = new Pair<Key, Value> *[size_container];
		for (int i = 0; i < size_container; ++i) container[i] = nullptr;
	}

	~UnorderedMap_Simple() {
		// delete pair (insider container)
		for (int i = 0; i < size_container; ++i) delete container[i];

		// delete container
		delete[] container;
	}

	// operation
	void insert(const Key &key, const Value &value) override {
		// get the box
		int hash = getHash(key);
		while (container[hash] != nullptr && container[hash]->first != key) {
			hash = getHash(hash + 1);
		}

		// check if key is already inside the map or not
		// if is inside, then replace the value
		if (container[hash] != nullptr) {
			container[hash]->second = value;
			return;
		}

		// check if insertion is available or not
		// remember there always one box for storing end marker
		if (size_allocated + 1 == size_container) return;

		// actual insertion
		auto pair_new 		= new Pair<Key, Value>();
		pair_new->first 	= key;
		pair_new->second 	= value;
		container[hash] 	= pair_new;

		// update stat
		size_allocated++;
	}

	void erase(const Key &key) override {
		// early stop
		if (size_allocated == 0) return;

		// get the box
		int hash = getHash(key);
		while (container[hash] != nullptr && container[hash]->first != key) {
			hash = getHash(hash + 1);
		}

		// check if box exist or not
		if (container[hash] == nullptr) return;

		// remove the box
		delete container[hash];
		container[hash] = nullptr;
		size_allocated = 0;
	}

	void clear() override {
		// remove (delete) the Pair* in every box
		for (int i = 0; i < size_container; ++i) {
			delete container[i];
			container[i] = nullptr;
		}

		// update stat
		size_allocated = 0;
	}

	Value &at(const Key &key) override {
		// find the box
		int hash = getHash(key);
		while (container[hash] != nullptr && container[hash]->first != key) {
			hash = getHash(hash + 1);
		}

		// if box not exist
		// then create a new one (with value unknown, TODO: should be default)
		if (container[hash] == nullptr) {
			auto *pair_new = new Pair<Key, Value>;
			pair_new->first = key;
			container[hash] = pair_new;
		}

		// now the box should exist for all the case
		return container[hash]->second;
	}

	int size() override {
		return size_allocated;
	}

	bool empty() override {
		return size_allocated == 0;
	}

protected:
	// operation
	int getHash(const Key &key) {
		return _getHash_Simple_(key, size_container);
	}

// Operator Overload
public:
	// ...
};


// Function - Prototype
// ...


// Function - Implementation
template<class Key>
inline int _getHash_Simple_(const Key &key, int size_container) {
	return key % size_container;
}

inline int _getHash_Simple_(const int &key, int size_container) {
	return abs(key) % size_container;
}


// Namespace: Algo
}


#endif //ALGORITEMIMPLEMENTATION_UNORDEREDMAP_SIMPLE_H
