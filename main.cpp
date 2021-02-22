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
	Test_testUnorderedMap();
//	testList();
//	testList_Vector();
//	testList_Linked();
//	testMap_RBTree();
    return 0;
}


// Function - Implementation
bool Test_testUnorderedMap() {
	// CONFIG
	const int size_container = 100;
	UnorderedMap_Simple<int, int> unordered_map_simple(size_container);

	// parameter
	TestOperation_UnorderedMap_Base<int, int>::Parameter parameter = {&unordered_map_simple};

	// operation
	TestOperation_UnorderedMap_Insert<int, int> ops_insert_1(1, 1);
	TestOperation_UnorderedMap_Insert<int, int> ops_insert_2(-1, -1);
	TestOperation_UnorderedMap_Insert<int, int> ops_insert_3(size_container, size_container);
	TestOperation_UnorderedMap_Insert<int, int> ops_insert_4(size_container + 1, size_container + 1);
	TestOperation_UnorderedMap_Insert<int, int> ops_insert_5(size_container * 2 + 1, size_container * 2 + 1);

	TestOperation_UnorderedMap_Erase<int, int> ops_erase_1(size_container + 2);
	TestOperation_UnorderedMap_Erase<int, int> ops_erase_2(size_container + 1);

	TestOperation_UnorderedMap_At<int, int> ops_at_1(0, 0, true);
	TestOperation_UnorderedMap_At<int, int> ops_at_2(-1, -1, true);
	TestOperation_UnorderedMap_At<int, int> ops_at_3(size_container * 2 + 1, size_container * 2 + 1, true);
	TestOperation_UnorderedMap_At<int, int> ops_at_4(1, -1, false);

	TestOperation_UnorderedMap_Clear<int, int> ops_clear_1;

	// lambda function
	std::function<std::string(const int)> func_int_to_string =
			[](const int value) -> std::string { return std::to_string(value); };

	std::function<void(const std::string&)> func_output =
			[](const std::string& s) -> void { printf("%s", s.c_str()); };

	ops_insert_1.func_value_to_string = ops_insert_1.func_key_to_string = &func_int_to_string;
	ops_insert_2.func_value_to_string = ops_insert_2.func_key_to_string = &func_int_to_string;
	ops_insert_3.func_value_to_string = ops_insert_3.func_key_to_string = &func_int_to_string;
	ops_insert_4.func_value_to_string = ops_insert_4.func_key_to_string = &func_int_to_string;
	ops_insert_5.func_value_to_string = ops_insert_5.func_key_to_string = &func_int_to_string;

	ops_erase_1.func_value_to_string = ops_erase_1.func_key_to_string = &func_int_to_string;
	ops_erase_2.func_value_to_string = ops_erase_2.func_key_to_string = &func_int_to_string;

	ops_at_1.func_value_to_string = ops_at_1.func_key_to_string = &func_int_to_string;
	ops_at_2.func_value_to_string = ops_at_2.func_key_to_string = &func_int_to_string;
	ops_at_3.func_value_to_string = ops_at_3.func_key_to_string = &func_int_to_string;
	ops_at_4.func_value_to_string = ops_at_4.func_key_to_string = &func_int_to_string;

	ops_clear_1.func_value_to_string = ops_clear_1.func_key_to_string = &func_int_to_string;

	// CORE
	ops_insert_1.execute(&parameter, &func_output);
	ops_insert_2.execute(&parameter, &func_output);
	ops_insert_3.execute(&parameter, &func_output);
	ops_insert_4.execute(&parameter, &func_output);
	ops_erase_1.execute(&parameter, &func_output);
	ops_erase_2.execute(&parameter, &func_output);
	ops_insert_5.execute(&parameter, &func_output);
	ops_at_1.execute(&parameter, &func_output);
	ops_at_2.execute(&parameter, &func_output);
	ops_at_3.execute(&parameter, &func_output);
	ops_at_4.execute(&parameter, &func_output);
	ops_clear_1.execute(&parameter, &func_output);

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
	Vector<int> vector_1;
	Vector<int> vector_2;
//	vector_1.resize(20);
//	vector_1.reserve(20);

	vector_2.resize(20, 3);

	// push some item into it
	for (int i = 0; i < 30; ++i) {
		vector_1.push_back(getRandomInt());
		printf("%i ", vector_1[i]);
	}
	printf("\n");

//	vector_1.assign(vector_2.begin(), vector_2.end());
//
//	vector_1.insert(vector_1.begin() + 5, 100);
//	vector_1.erase(vector_1.begin() + 10);

	// stat
	printf("Size: %i\n", vector_1.size());
	printf("Capacity: %i\n", vector_1.capacity());

	// sort
//	sortList(vector_1.begin(), vector_1.end());

	// use iterator to get the item one by one
	// const iterator: begin
	printf("cbegin\n");
	for (Vector<int>::ConstIterator it = vector_1.cbegin(); it < vector_1.cend(); it = it + 3) {
		printf("%i ", *(it));
	}
	printf("\n");

	// iterator: begin
	printf("begin\n");
	for (Vector<int>::Iterator it = vector_1.begin(); it != vector_1.end(); ++it) {
		printf("%i ", *(it));
	}
	printf("\n");

	// const iterator: rbegin
	printf("crbegin\n");
	for (Vector<int>::ConstIterator it = vector_1.crbegin(); it != vector_1.crend(); ++it) {
		printf("%i ", *(it));
	}
	printf("\n");

	// iterator: rbegin
	printf("rbegin\n");
	for (Vector<int>::Iterator it = vector_1.rbegin(); it != vector_1.rend(); ++it) {
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
	printf("Tree: height: %i; size: %i; diff: %i\n",
		getTreeHeight((_BiDirBinaryNode_*)table.root->left, table.root),
		getTreeSize((_BiDirBinaryNode_*)table.root->left, table.root),
		getTreeHeightDiff((_BiDirBinaryNode_*)table.root->left, table.root));

	if (!checkRBTree_IsBalance(table.root->left, table.root)) printf("Imbalance\n");
	printf("%s \n", getString_RBTree(table.root->left, table.root, &func_key_to_string, &func_value_to_string).c_str());

	// erase
	table.erase(18);
	table.erase(14);
	table.erase(9);

	printf("Deletion completed\n");
	printf("Tree height: %i; Tree size: %i \n",
		   getTreeHeight((_BiDirBinaryNode_*)table.root->left, table.root),
		   getTreeSize((_BiDirBinaryNode_*)table.root->left, table.root));

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

	printf("begin\n");
	for (auto it = table.begin(); it != table.end(); ++it) printf("%i ", *it);
	printf("\n");

	printf("rbegin\n");
	for (auto it = table.rbegin(); it != table.rend(); ++it) printf("%i ", *it);
	printf("\n");

	return true;
}
