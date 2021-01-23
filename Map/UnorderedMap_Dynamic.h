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


// Function Prototype
template <class Key>
inline int _getHash_Dynamic_Local_(const Key &key, int index);

template <class Key>
inline int _getHash_Dynamic_Global_(const Key &key, int index);


// Data Structure
template <class Key, class Value>
class _HashBucket_ {
// Data
public:
    int 				index_local;
    Pair<Key, Value>*	*container;
    int					size_container;

// Function
public:
    // init and del
    _HashBucket_(int index, int size_container):
			index_local(index),
			size_container(size_container)
	{
    	container = new Pair<Key, Value>* [size_container];
    	for (int i = 0; i < size_container; ++i) container[i] = nullptr;
    }

    ~_HashBucket_() {
    	// delete pair (inside container)
    	for (int i = 0; i < size_container; ++i) delete container[i];

    	// delete container
    	delete[] container;
    }

    // operation
    Bool insert(const Key &key, const Value &value) {
    	// check if insertion or replacement is available or not
    	int hash = getHash(key);
    	if (container[hash] != nullptr && container[hash]->first != key) return false;

    	// replace
    	// container[hash]->first != key already checked
    	if (container[hash]->first != nullptr) {
    		container[hash]->second = value;
    		return true;
    	}

    	// insert
    	auto pair_new 		= new Pair<Key, Value>();
    	pair_new->first		= key;
    	pair_new->second	= value;
    	container[hash]		= pair_new;

    	return true;
    }

    void erase(const Key &key) {
    	// find the box
    	int hash = getHash(key);
    	if (container[hash] == nullptr || container[hash]->first != key) return;

    	// delete
    	delete container[hash];
    	container[hash] = nullptr;
    }

    // assumed: key must be existed
    Value &at(const Key &key) {
    	// find the box
    	int hash = getHash(key);
    	if (container[hash] == nullptr || container[hash]->first != key) return 0;

    	// at
    	return container[hash]->second;
    }

protected:
	// operation
	int getHash(const Key &key) {
    	return _getHash_Dynamic_Local_(key, index_local);
    }
};


template <class Key, class Value>
class UnorderedMap_Dynamic: public UnorderedMap<Key, Value> {
// Data
protected:
	// size of bucket should a value of base 2
	// i.e. size_bucket = 1 << index_global
	//
	// size of container best to be a value of base 2
	_HashBucket_<Key, Value>*	*bucket_list;
    int 						index_global;
    int							size_container;
    int							size_allocated;

// Function
public:
    // init and del
    UnorderedMap_Dynamic(int size_container_):
    size_container(size_container_),
    size_allocated(0)
    {
    	// currently the initial global index_local is 1
    	// i.e. size_bucket_list = 2
    	index_global = 1;

    	// create bucket_list
    	int size_bucket_list = 1 << index_global;
    	bucket_list = new _HashBucket_<Key, Value>* [size_bucket_list];

    	// create bucket (inside bucket_list)
    	for (int i = 0; i < size_bucket_list; ++i) {
    		bucket_list[i] = new _HashBucket_<Key, Value>(index_global, size_container);
    	}
    }

    ~UnorderedMap_Dynamic() {
    	// compute size_bucket_list
    	int size_bucket_list = 1 << index_global;

    	// delete bucket (inside bucket_list)
    	for (int i = 0; i < size_bucket_list; ++i) delete bucket_list[i];

    	// delete bucket_list
    	delete[] bucket_list;
    }

    // operation
	void insert(const Key &key, const Value &value) override {
    	// ----- try to insert -----
    	// global hash
    	int hash_global = getHash(key);

    	// try to insert to bucket
    	if (bucket_list[hash_global]->insert(key, value)) {
    		size_allocated++;
    		return;
    	}

    	// ----- split bucket -----
    	// if not success, which mean overflow occur
    	// need to split the bucket

    	// create a new bucket, and record the old bucket
    	auto bucket_new = new _HashBucket_<Key, Value>(index_global + 1, size_container);
    	auto bucket_old = bucket_list[hash_global];

    	// actual split
    	// it is known that the bucket of bucket_old is full
    	//
    	// old bucket will be for key with smaller global_hash
    	// new bucket will be for key with larger global_hash
    	int hash_old = hash_global;
    	int hash_new = hash_global | (1 << index_global);

    	for (int i = 0; i < bucket_old.size_container; ++i) {
    		const Key 	&key_temp = bucket_old->container[i]->first;
    		const int	hash_temp = getHash(key_temp, index_global + 1);  // need to use the new hash function

    		if (hash_temp == hash_old) continue;

    		const Value &value_temp = bucket_old->container[i]->second;
    		bucket_old->erase(key_temp);
    		bucket_new->insert(key_temp, value_temp);
    	}

    	// increment local index of bucket_old
    	bucket_old->index_local++;

    	// ----- expand bucket_list -----
    	// create new bucket_list
    	int size_bucket_list_old	= 1 << index_global;
    	int size_bucket_list_new	= 1 << (index_global + 1);

    	auto bucket_list_old = bucket_old;
    	auto bucket_list_new = new _HashBucket_<Key, Value>* [size_bucket_list_new];

    	// move bucket from old to new bucket_list
    	for (int i = 0; i < size_bucket_list_old; ++i) {
    		const int hash_old_temp = getHash(i);
    		const int hash_new_temp = hash_old_temp | (1 << index_global);

    		bucket_list_new[hash_old_temp] = bucket_list_old[hash_old_temp];
    		bucket_list_new[hash_new_temp] = bucket_list_old[hash_old_temp];
    	}

    	// replace bucket_list by bucket_list_new, and
    	// delete the old one (do not delete the content inside the old one)
    	bucket_list = bucket_list_new;
    	delete bucket_list_old;

    	// add bucket_new into the bucket_list
    	bucket_list_new[hash_new] = bucket_new;

    	// finally increase global_index
		index_global++;

		// ----- update stat -----
		size_allocated++;
	}

	// TODO:
	void erase(const Key &key) override {

	}

	void clear() override {
    	// ----- delete all -----
    	// compute size of bucket_list
    	int size_bucket_list = 1 << index_global;

    	// delete bucket (inside bucket list)
    	for (int i = 0; i < size_bucket_list; ++i) delete bucket_list[i];

    	// delete bucket_list
    	delete[] bucket_list;
    	// bucket_list = nullptr;

    	// ----- create a new (default) one -----
    	index_global = 1;
    	size_bucket_list = 1 << index_global;

    	// new bucket_list
    	bucket_list = new _HashBucket_<Key,Value>* [size_bucket_list];

    	// new bucket (inside bucket_list)
    	for (int i = 0; i < size_bucket_list; ++i) {
    		bucket_list[i] = new _HashBucket_<Key, Value>(index_global, size_container);
    	}

    	// update stat
    	size_allocated = 0;
	}

	Value &at(const Key &key) override {
    	// get global_index and then the target bucket
    	int hash_global = getHash(key);
    	return bucket_list[hash_global]->at(key);
	}

	int size() override {
    	return size_allocated;
	}

	bool empty() override {
    	return size_allocated == 0;
	}

protected:
	// operation
	int getHash(const Key &key, int index = -1) {
    	if (index == -1) index = index_global;
    	return _getHash_Dynamic_Global_(key, index_global);
    }
};


// Function - Prototype
// ...


// Function - Implementation
template <class Key>
inline int _getHash_Dynamic_Local_(const Key &key, int index) {
	return key >> index;
}

template <class Key>
inline int _getHash_Dynamic_Global_(const Key &key, int index) {
	// (1 << index) - 1
	// fill ones, starting from lsb with number 1 == index
	//
	// e.g. index = 2
	// (1 << index): 		100
	// (1 << index) - 1:	011
	return key & ((1 << index) - 1);
}


// Namespace-End - Algo
}


#endif //ALGORITEMIMPLEMENTATION_UNORDEREDMAP_DYNAMIC_H
