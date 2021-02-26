//
// Author: Jack Tse
// Date of creation: 26/2/2021
// Email: jacktsetcy@gmail.com
//

#ifndef ALGORITEMIMPLEMENTATION_SELECT_H
#define ALGORITEMIMPLEMENTATION_SELECT_H


// Import
#include "Debug.h"
#include "Address.h"
#include "Random.h"
#include "UtilInt.h"


// Namespace-Begin - Algo
namespace Algo {


// Data Structure
// ...


// Function - Prototype
void* select_QuickSelect(
		void *data, unsigned int offset, unsigned int size, int8(*compare)(void*, void*),
		unsigned int index);

// should be used internal
void* _select_QuickSelect_(
		void *data, unsigned int offset, unsigned int size, int8(*compare)(void*, void*),
		unsigned int index, void *buffer);

unsigned int _select_QuickSelect_Partition_(
		void *data, unsigned int offset, unsigned int size, int8(*compare)(void*, void*),
		unsigned int pivot, void *buffer, int8 *is_front_continue);


// Function - Implementation
void* select_QuickSelect(
		void *data, unsigned int offset, unsigned int size, int8(*compare)(void*, void*),
		unsigned int index) {

	// check
	if (data == nullptr) 		return nullptr;
	if (offset == 0) 			return nullptr;
	if (size == 0) 				return nullptr;
	if (size <= offset) 		return nullptr;
	if (index >= size / offset) return nullptr;

	// allocate space for buffer
	// first part is for swap
	// second part is for compare
	void *buffer = malloc(offset * 2);

	// actual sorting routine
	void *ret = _select_QuickSelect_(data, offset, size, compare, index, buffer);

	// free buffer
	free(buffer);

	// RET
	return ret;
}


void* _select_QuickSelect_(
		void *data, unsigned int offset, unsigned int size, int8(*compare)(void*, void*),
		unsigned int index, void *buffer) {

	// base condition
	const unsigned int n = size / offset;
	if (n <= 1) return data;

	// ----- partition -----
	// get point of pivot
	unsigned int pivot = getRandomInt() % n;

	// partition
	int8 is_front_continue = 0;
	unsigned int mid = _select_QuickSelect_Partition_(data, offset, size, compare, pivot, buffer, &is_front_continue);

	// ----- special case -----
	// check if can early stop or needed to redo the partition
	if (mid == n) {

		// early stopping: list contain only one value
		if (!is_front_continue) return data;

		// redo partition: previous partition cannot split the list into front and end
		// as the list must contain more than one value
		// therefore the loop must break at some point
		for (int i = 0; i < n; ++i) {
			if (compare(getTargetPtr(data, void, i * offset), getTargetPtr(buffer, void, offset)) == 0) continue;
			pivot = i;
			break;
		}

		// do the partition again
		mid = _select_QuickSelect_Partition_(data, offset, size, compare, pivot, buffer, &is_front_continue);
	}

	// ----- recursion -----
	// front
	if (index < mid) {
		if (!is_front_continue) return data;  // early stopping
		return _select_QuickSelect_(data, offset, mid * offset, compare, index, buffer);
	}

	// back
	return _select_QuickSelect_(
			getTargetPtr(data, void, mid * offset), offset, size - mid * offset, compare,
			index - mid, buffer);
}


unsigned int _select_QuickSelect_Partition_(
		void *data, unsigned int offset, unsigned int size, int8(*compare)(void*, void*),
		unsigned int pivot, void *buffer, int8 *is_front_continue) {

	// CONFIG
	const unsigned int n = size / offset;
	memcpy(getTargetPtr(buffer, void, offset), getTargetPtr(data, void, pivot * offset), offset);

	// CORE
	unsigned int index = 0;
	for (unsigned int i = 0; i < n; ++i) {

		// compare function
		// 1: a before b
		// 0: a same as b (no specific order)
		// -1: a after b
		int8 ret = compare(getTargetPtr(data, void, i * offset), getTargetPtr(buffer, int, offset));
		if (ret == -1) continue;

		if (i != index) {
			memcpy(buffer, getTargetPtr(data, void, i * offset), offset);
			memcpy(getTargetPtr(data, void, i * offset), getTargetPtr(data, void, index * offset), offset);
			memcpy(getTargetPtr(data, void, index * offset), buffer, offset);
		}

		// only when front contain more than one value
		// front part is needed to go deep
		//
		// example of "more than one value"
		// one value:			1, 1, 1, 1
		// more than one value:	1, 2, 1, 1
		*is_front_continue |= ret;

		// set the new position of the end of the front
		index++;
	}

	// RET
	return index;
}


// Namespace-End - Algo
}


#endif //ALGORITEMIMPLEMENTATION_SELECT_H
