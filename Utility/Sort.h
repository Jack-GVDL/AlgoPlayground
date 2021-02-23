//
// Author: Jack Tse
// Date of creation: 23/2/2021
// Email: jacktsetcy@gmail.com
//

#ifndef ALGORITEMIMPLEMENTATION_SORT_H
#define ALGORITEMIMPLEMENTATION_SORT_H


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
// public
void sort_QuickSort(void *data, unsigned int offset, unsigned int size, int8(*compare)(void*, void*));
void sort_MergeSort(void *data, unsigned int offset, unsigned int size, int8(*compare)(void*, void*));

// should only be used internal
void _sort_QuickSort_(
		void *data, unsigned int offset, unsigned int size, int8(*compare)(void*, void*),
		void *buffer);

unsigned int _partition_(
		void *data, unsigned int offset, unsigned int size, int8(*compare)(void*, void*),
		unsigned int pivot, void *buffer, int8 *is_front_continue);


// Function - Implementation
void sort_QuickSort(void *data, unsigned int offset, unsigned int size, int8(*compare)(void*, void*)) {
	// check
	if (data == nullptr)	return;
	if (offset == 0)		return;
	if (size == 0)			return;
	if (size <= offset)		return;

	// allocate space for buffer
	// first part is for swap
	// second part is for compare
	void *buffer = malloc(offset * 2);

	// actual sorting routine
	_sort_QuickSort_(data, offset, size, compare, buffer);

	// free buffer
	free(buffer);
}


void sort_MergeSort(void *data, unsigned int offset, unsigned int size, int8(*compare)(void*, void*)) {
	// check
	if (data == nullptr)	return;
	if (offset == 0)		return;
	if (size == 0)			return;
	if (size <= offset)		return;

	// TODO
}


// assumed: buffer must be large enough
void _sort_QuickSort_(
		void *data, unsigned int offset, unsigned int size, int8(*compare)(void*, void*),
		void *buffer) {

	// base condition
	const unsigned int n = size / offset;
	if (n <= 1) return;

	// partition
	int8 is_front_continue = 0;
	unsigned int pivot	= getRandomInt() % n;
	unsigned int mid	= _partition_(data, offset, size, compare, pivot, buffer, &is_front_continue);

	// mid point correction
	// already make the back part has at least one item to handle
	if (mid * offset == size) mid--;

	// D&C
	// part   | start | end (exclusive)   | size
	// front  | 0	  | mid 			  | mid
	// back	  | mid	  | size			  | size - mid
	if (is_front_continue) _sort_QuickSort_(data, offset, mid * offset, compare, buffer);
	_sort_QuickSort_(getTargetPtr(data, void, mid * offset), offset, size - mid * offset, compare, buffer);
}


// assumed: buffer must be large enough
unsigned int _partition_(
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
		// 0: a after b
		int8 ret = compare(getTargetPtr(data, void, i * offset), getTargetPtr(buffer, int, offset));
		if (ret == -1) continue;

		if (i != index) {
			memcpy(buffer, getTargetPtr(data, void, i * offset), offset);
			memcpy(getTargetPtr(data, void, i * offset), getTargetPtr(data, void, index * offset), offset);
			memcpy(getTargetPtr(data, void, index * offset), buffer, offset);
		}

		// only when front contain more than one value
		// front part is needed to sort
		//
		// example of of "more than one value"
		// one value:			1, 1, 1, 1
		// more than one value:	1, 2, 1, 1
		*is_front_continue |= ret;

		index++;
	}

	// RET
	return index;
}


// Namespace-End - Algo
}


#endif //ALGORITEMIMPLEMENTATION_SORT_H
