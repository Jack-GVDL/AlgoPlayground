//
// Author: Jack Tse
// Date of creation: 20/1/2021
// Email: jacktsetcy@gmail.com
//

#ifndef ALGORITEMIMPLEMENTATION_UNORDEREDMAP_SIMPLE_H
#define ALGORITEMIMPLEMENTATION_UNORDEREDMAP_SIMPLE_H


// Import
#include "UnorderedMap.h"


// Namespace
namespace Algo {


// Function Prototype
template<class Key>
inline int _getHash_(const Key &key, int size_container);

inline int _getHash_(const int &key, int size_container);


// Data Structure
template<class Key, class Value>
class UnorderedMap_Simple : public UnorderedMap<Key, Value> {
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
			size_allocated(0) {
		container = new Pair<Key, Value> *[size_container];
		for (int i = 0; i < size_container; ++i) container[i] = nullptr;
	}

	~UnorderedMap_Simple() {
		delete[] container;
	}

	// operation
	void insert(const Key &key, const Value &value) override {
		// check if insertion is available or not
		if (size_allocated == size_container) return;

		// get the box
		int hash = getHash(key);
		while (container[hash] != nullptr && container[hash]->first != key) {
			hash = getHash(hash + 1);
		}

		// if box not exist,	create new pair
		// else,				set value
		if (container[hash] == nullptr) {
			auto pair_new = new Pair<Key, Value>();
			pair_new->first = key;
			pair_new->second = value;
			container[hash] = pair_new;
			return;
		} else {
			container[hash]->second = value;
		}

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

// protected:
public:
	// operation
	int getHash(const Key &key) {
		return _getHash_(key, size_container);
	}

// Operator Overload
public:
	Value &operator[](const Key &key) {
		return at(key);
	}
};


// Function - Prototype
// ...


// Function - Implementation
template<class Key>
inline int _getHash_(const Key &key, int size_container) {
	return key % size_container;
}

inline int _getHash_(const int &key, int size_container) {
	return abs(key) % size_container;
}


// Namespace: Algo
}


#endif //ALGORITEMIMPLEMENTATION_UNORDEREDMAP_SIMPLE_H
