#include <iostream>
#include "Map/Map.h"


// Namespace
using namespace Algo;


// Function - Prototype
bool testHash();


// Operation
int main() {
	testHash();
    return 0;
}


// Function - Implementation
bool testHash() {

	// CONFIG
	const int size_container = 100;

	// ----- lambda -----
	std::function<void(const std::string&)> func_log 				= [](const std::string &content) 	-> void 		{ std::cout << content << std::endl; };
	std::function<std::string(const int)>	func_key_to_string		= [](const int key) 				-> std::string 	{ return std::to_string(key); };
	std::function<std::string(const int)>	func_value_to_string	= [](const int value) 				-> std::string 	{ return std::to_string(value); };

	// ----- operation_list list -----
	Pair<HashOperation, Pair<int, int>> operation_list[] = {
		makeHashOperation(HashOperation::INSERT,	0, 0),
		makeHashOperation(HashOperation::INSERT,	-1, -1),
		makeHashOperation(HashOperation::INSERT,	size_container, size_container),
		makeHashOperation(HashOperation::INSERT, 	size_container + 1, size_container + 1),
		makeHashOperation(HashOperation::ERASE, 	size_container + 2, 0),
		makeHashOperation(HashOperation::ERASE, 	size_container + 1, 0),
		makeHashOperation(HashOperation::INSERT,	size_container * 2 + 1, size_container * 2 + 1),
		makeHashOperation(HashOperation::AT, 		size_container, size_container),
		makeHashOperation(HashOperation::CLEAR, 	0, 0)
	};

	// ----- hash table list -----
	// hash table list
	UnorderedMap<int, int>* hash_list[] = {
			new UnorderedMap_Simple<int, int>(size_container)
	};

	// ----- get list size -----
	int size_operation	= sizeof(operation_list) / sizeof(Pair<int, Pair<int, int>>);
	int size_table		= sizeof(hash_list) / sizeof(UnorderedMap<int, int>*);

	// ----- testing -----
	// actual testing
	for (int i = 0; i < size_table; ++i) {
		int result = runHash(
						*hash_list[i],
						operation_list,
						size_operation,
						&func_log,
						&func_key_to_string,
						&func_value_to_string
					);

		if (result == 0) continue;
		return false;
	}

	return true;
}
