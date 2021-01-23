//
// Author: Jack Tse
// Date of creation: 22/1/2021
// Email: jacktsetcy@gmail.com
//
// reference
// https://stackoverflow.com/questions/4897844/is-sizeofbool-defined-in-the-c-language-standard
//
// the main problem of original type bool is that
// sizeof(bool) is implementation defined
// i.e. not required to be 1
//
// but it is also noticed that
// sizeof(char) is 1 by standard
//
// so the below Bool class will use char as value type
//


#ifndef ALGORITEMIMPLEMENTATION_BOOL_H
#define ALGORITEMIMPLEMENTATION_BOOL_H


// Import
// ...


// Namespace-Begin - Algo
namespace Algo {


// Data Structure
struct Bool {
// Data
protected:
	char _value;

// Function
public:
	// init and del
	Bool(bool value) {
		*this = value;
	}

	template <class T>
	Bool(T other) {
		*this = other;
	}

// Operator Overload
public:
	Bool& operator= (bool other) {
		_value = other ? 1 : 0;
		return *this;
	}

	Bool& operator= (Bool other) {
		_value = other._value;
		return *this;
	}

	bool operator== (bool other) const {
		return (other ? 1 : 0) == _value;
	}

	bool operator== (Bool other) const {
		return _value == other._value;
	}

	bool operator!= (bool other) const {
		return (other ? 1 : 0) != _value;
	}

	bool operator!= (Bool other) const {
		return _value != other._value;
	}

	template <class T>
	T operator| (T other) const {
		return _value | other;
	}

	template <class T>
	T operator& (T other) const {
		return _value & other;
	}

	template <class T>
	unsigned char operator<< (T shift) const {
		return _value << shift;
	}

	template <class T>
	unsigned char operator>> (T shift) const {
		return _value >> shift;
	}
};


// Function
// ...


// Namespace-End - Algo
}


#endif //ALGORITEMIMPLEMENTATION_BOOL_H