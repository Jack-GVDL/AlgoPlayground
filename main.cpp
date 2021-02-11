#include <iostream>
#include "Map/Map.h"
#include "List/List.h"


// Namespace
using namespace Algo;


// Function - Prototype
bool testHash();
bool testList();
bool testList_Vector();  // test the iterator
bool testList_Linked();  // test the iterator
bool testMap_RBTree();


// Operation
int main() {
//	testHash();
//	testList();
//	testList_Vector();
//	testList_Linked();
	testMap_RBTree();
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


bool testList_Vector() {
	printf("----- Vector -----\n");

	// create a container
	Vector<int> vector;
	Vector<int> vector_2;
//	vector.resize(20);
//	vector.reserve(20);

	vector_2.resize(20, 3);

	// push some item into it
	for (int i = 0; i < 30; ++i) {
		vector.push_back(i);
		printf("%i ", vector[i]);
	}
	printf("\n");

	vector.assign(vector_2.begin(), vector_2.end());

	vector.insert(vector.begin() + 5, 100);
	vector.erase(vector.begin() + 10);

	// stat
	printf("Size: %i\n", vector.size());
	printf("Capacity: %i\n", vector.capacity());

	// use iterator to get the item one by one
	// const iterator: begin
	for (Vector<int>::ConstIterator it = vector.cbegin(); it < vector.cend(); it = it + 3) {
		printf("%i ", *(it));
	}
	printf("\n");

	// iterator: begin
	for (Vector<int>::Iterator it = vector.begin(); it != vector.end(); ++it) {
		printf("%i ", *(it));
	}
	printf("\n");

	// const iterator: rbegin
	for (Vector<int>::ConstIterator it = vector.crbegin(); it != vector.crend(); ++it) {
		printf("%i ", *(it));
	}
	printf("\n");

	// iterator: rbegin
	for (Vector<int>::Iterator it = vector.rbegin(); it != vector.rend(); ++it) {
		printf("%i ", *(it));
	}
	printf("\n");

	printf("\n");
	return true;
}


bool testList_Linked() {
	printf("----- Linked -----\n");

	// create a container
	Linked<int> vector;

	// push some item into it
	for (int i = 0; i < 30; ++i) {
		vector.push_back(i);
		printf("%i ", vector[i]);
	}
	printf("\n");

	// use iterator to get the item one by one
	for (Linked<int>::Iterator it = vector.begin(); it != vector.end(); ++it) {
		printf("%i ", *(it));
	}
	printf("\n");

	for (Linked<int>::Iterator it = vector.rbegin(); it != vector.rend(); ++it) {
		printf("%i ", *(it));
	}
	printf("\n");

	printf("\n");
	return true;
}


bool testMap_RBTree() {
	// CONFIG
	OrderedMap_RBTree<int, int> table;

	std::function<std::string(const int)>	func_key_to_string		= [](const int key)		-> std::string 	{ return std::to_string(key); };
	std::function<std::string(const int)>	func_value_to_string	= [](const int value) 	-> std::string 	{ return std::to_string(value); };

	// insert
	for (int i = 0; i < 15; ++i) table.insert(i, i);

	printf("Insertion completed\n");
	if (!checkRBTree_IsBalance(table.root->left, table.root)) printf("Imbalance\n");
	printf("%s \n", getString_RBTree(table.root->left, table.root, &func_key_to_string, &func_value_to_string).c_str());

	// erase
	table.erase(18);
	table.erase(14);
	table.erase(9);

	printf("Deletion completed\n");
	if (!checkRBTree_IsBalance(table.root->left, table.root)) printf("Imbalance\n");
	printf("%s \n", getString_RBTree(table.root->left, table.root, &func_key_to_string, &func_value_to_string).c_str());

	// iterator
	printf("cbegin\n");
	for (auto it = table.cbegin(); it != table.cend(); ++it) printf("%i ", *it);
	printf("\n");

	printf("crbegin\n");
	for (auto it = table.crbegin(); it != table.crend(); ++it) printf("%i ", *it);
	printf("\n");

	// check --it
	auto const_iterator = table.cbegin();
	for (int i = 0; i < 3; ++i) {
		++const_iterator;
		++const_iterator;
		++const_iterator;
		--const_iterator;
		printf("%i ", *const_iterator);
	}
	printf("\n");

//	printf("begin\n");
//	for (auto it = table.begin(); it != table.end(); ++it) printf("%i ", *it);
//	printf("\n");

//	printf("end\n");
//	for (auto it = table.rbegin(); it != table.rend(); ++it) printf("%i ", *it);
//	printf("\n");

	return true;
}
