//
// Author: Jack Tse
// Date of creation: 22/1/2021
// Email: jacktsetcy@gmail.com
//

#ifndef ALGORITEMIMPLEMENTATION_PAIR_H
#define ALGORITEMIMPLEMENTATION_PAIR_H


// Import
// ...


// Namespace - Algo
namespace Algo {


// Data Structure
template<class First, class Second>
class Pair {

// Data
public:
	First first;
	Second second;

// Function
public:
	// init and del
	Pair():
	first(0),
	second(0)
	{
	}

	Pair(First first, Second second):
	first(first),
	second(second)
	{
	}

	~Pair() {
	}

	// operation
	// ...
};


// Namespace - Algo
}


// Function
// ...


#endif //ALGORITEMIMPLEMENTATION_PAIR_H
