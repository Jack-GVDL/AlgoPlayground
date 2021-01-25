#include <iostream>
#include "Map/Map.h"
#include "List/List.h"


// Namespace
using namespace Algo;


// Function - Prototype
bool testHash();
bool testList();


// Operation
int main() {
	testHash();
	testList();
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
		makeHashOperation(HashOperation::AT,		0, 0),
		makeHashOperation(HashOperation::AT,		-1, -1),
		makeHashOperation(HashOperation::AT, 		size_container, size_container),
		makeHashOperation(HashOperation::AT,		size_container * 2 + 1, size_container * 2 + 1),
		makeHashOperation(HashOperation::NOT_AT, 	size_container + 2,	-1),
		makeHashOperation(HashOperation::CLEAR, 	0, 0)
	};

	// ----- hash table list -----
	// hash table list
	_UnorderedMap_<int, int>* hash_list[] = {
			new UnorderedMap_Simple<int, int>(size_container),
			new UnorderedMap_Dynamic<int, int>(4)
	};

	// ----- get list size -----
	int size_operation	= sizeof(operation_list) / sizeof(Pair<int, Pair<int, int>>);
	int size_table		= sizeof(hash_list) / sizeof(_UnorderedMap_<int, int>*);

	// ----- testing -----
	// actual testing
	for (int i = 0; i < size_table; ++i) {

		// separation
		func_log(std::string("\n----- test -----\n"));

		int result = runOperation_Hash(
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


bool testList() {
	// CONFIG
	// ...

	// ----- lambda -----
	std::function<void(const std::string&)> func_log 				= [](const std::string &content) 	-> void 		{ std::cout << content << std::endl; };
	std::function<std::string(const int)>	func_key_to_string		= [](const int key) 				-> std::string 	{ return std::to_string(key); };
	std::function<std::string(const int)>	func_value_to_string	= [](const int value) 				-> std::string 	{ return std::to_string(value); };

	// ----- operation_list list -----
	Pair<ListOperation, Pair<int, int>> operation_list[] = {
			makeListOperation(ListOperation::PUSH_BACK, 0, 0),
			makeListOperation(ListOperation::PUSH_BACK, 0, 1),
			makeListOperation(ListOperation::PUSH_BACK, 0, 2),
			makeListOperation(ListOperation::PUSH_BACK, 0, 3),
			makeListOperation(ListOperation::POP_BACK, 0, 0),
			makeListOperation(ListOperation::AT, 2, 2),
			makeListOperation(ListOperation::AT, 3, 0),
			makeListOperation(ListOperation::NOT_AT, 3, -1),
			makeListOperation(ListOperation::CLEAR, 0, 0)
	};

	// ----- list list -----
	// list of list
	_List_<int>* list_list[] = {
			new Linked<int>(),
			new Vector<int>()
	};

	// ----- get list size -----
	int	size_operation	= sizeof(operation_list) / sizeof(Pair<ListOperation, Pair<int, int>>);
	int size_list		= sizeof(list_list) /sizeof(_List_<int>*);

	// ----- actual testing -----
	for (int i = 0; i < size_list; ++i) {

		// separation
		func_log(std::string("\n----- test -----\n"));

		int result = runOperation_List(
				*list_list[i],
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
