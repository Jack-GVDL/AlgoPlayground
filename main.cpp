#include <iostream>
#include <Utility.h>
#include "Map/Map.h"
#include "List/List.h"
#include <Path.h>


// Namespace
using namespace Algo;


// Function - Prototype
bool Test_testUnorderedMap();
bool Test_testList();
bool Test_testVector();  // test the iterator
bool Test_testLinked();  // test the iterator
bool Test_testMap();
bool Test_testSort_QuickSort();
bool Test_testSelect_QuickSelect();
bool Test_testShortestPath_Dijkstra();


// Operation
int main() {
//	Test_testUnorderedMap();
//	Test_testList();
//	Test_testVector();
//	Test_testLinked();
//	Test_testMap();
//	Test_testSort_QuickSort();
//	Test_testSelect_QuickSelect();
	Test_testShortestPath_Dijkstra();
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

	TestCluster cluster;
	cluster.addOperation(&ops_insert_1);
	cluster.addOperation(&ops_insert_2);
	cluster.addOperation(&ops_insert_3);
	cluster.addOperation(&ops_insert_4);
	cluster.addOperation(&ops_insert_5);
	cluster.addOperation(&ops_erase_1);
	cluster.addOperation(&ops_erase_2);
	cluster.addOperation(&ops_at_1);
	cluster.addOperation(&ops_at_2);
	cluster.addOperation(&ops_at_3);
	cluster.addOperation(&ops_at_4);
	cluster.addOperation(&ops_clear_1);

	// lambda function
	std::function<std::string(const int)> func_int_to_string =
			[](const int value) -> std::string { return std::to_string(value); };

	ops_insert_1.func_value_to_string	= ops_insert_1.func_key_to_string	= &func_int_to_string;
	ops_insert_2.func_value_to_string	= ops_insert_2.func_key_to_string	= &func_int_to_string;
	ops_insert_3.func_value_to_string	= ops_insert_3.func_key_to_string	= &func_int_to_string;
	ops_insert_4.func_value_to_string	= ops_insert_4.func_key_to_string	= &func_int_to_string;
	ops_insert_5.func_value_to_string	= ops_insert_5.func_key_to_string	= &func_int_to_string;
	ops_erase_1.func_value_to_string	= ops_erase_1.func_key_to_string	= &func_int_to_string;
	ops_erase_2.func_value_to_string	= ops_erase_2.func_key_to_string	= &func_int_to_string;
	ops_at_1.func_value_to_string		= ops_at_1.func_key_to_string		= &func_int_to_string;
	ops_at_2.func_value_to_string		= ops_at_2.func_key_to_string		= &func_int_to_string;
	ops_at_3.func_value_to_string		= ops_at_3.func_key_to_string		= &func_int_to_string;
	ops_at_4.func_value_to_string		= ops_at_4.func_key_to_string		= &func_int_to_string;
	ops_clear_1.func_value_to_string 	= ops_clear_1.func_key_to_string 	= &func_int_to_string;

	// CORE
	cluster.execute(&parameter);

	for (std::string &s : cluster.log_list) printf("%s", s.c_str());
	return true;
}


bool Test_testList() {
	// CONFIG
	Vector<int> list_vector;

	// parameter
	TestOperation_List_Base<int>::Parameter parameter = {&list_vector};

	// operation
	TestOperation_List_PushBack<int> ops_push_back_1(0);
	TestOperation_List_PushBack<int> ops_push_back_2(1);
	TestOperation_List_PushBack<int> ops_push_back_3(2);
	TestOperation_List_PushBack<int> ops_push_back_4(3);

	TestOperation_List_PopBack<int> ops_pop_back_1;

	TestOperation_List_Clear<int> ops_clear_1;

	TestOperation_List_At<int> ops_at_1(2, 2, true);
	TestOperation_List_At<int> ops_at_2(3, 0, true);
	TestOperation_List_At<int> ops_at_3(3, -1, false);

	TestCluster cluster;
	cluster.addOperation(&ops_push_back_1);
	cluster.addOperation(&ops_push_back_2);
	cluster.addOperation(&ops_push_back_3);
	cluster.addOperation(&ops_push_back_4);
	cluster.addOperation(&ops_pop_back_1);
	cluster.addOperation(&ops_push_back_1);
	cluster.addOperation(&ops_at_1);
	cluster.addOperation(&ops_at_2);
	cluster.addOperation(&ops_at_3);
	cluster.addOperation(&ops_clear_1);

	// lambda function
	std::function<std::string(const int)> func_int_to_string =
			[](const int value) -> std::string { return std::to_string(value); };

	ops_push_back_1.func_value_to_string	= &func_int_to_string;
	ops_push_back_2.func_value_to_string	= &func_int_to_string;
	ops_push_back_3.func_value_to_string	= &func_int_to_string;
	ops_push_back_4.func_value_to_string	= &func_int_to_string;
	ops_pop_back_1.func_value_to_string		= &func_int_to_string;
	ops_clear_1.func_value_to_string		= &func_int_to_string;
	ops_at_1.func_value_to_string			= &func_int_to_string;
	ops_at_2.func_value_to_string			= &func_int_to_string;
	ops_at_3.func_value_to_string			= &func_int_to_string;

	// CORE
	cluster.execute(&parameter);

	for (std::string &s : cluster.log_list) printf("%s", s.c_str());
	return true;
}


bool Test_testVector() {
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


bool Test_testLinked() {
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


bool Test_testMap() {
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


int8 compare(void *a, void *b) {
	if ( *((int*)a) == *((int*)b) ) return 0;
	if ( *((int*)a) < *((int*)b) )	return 1;
	return -1;
}


bool Test_testSort_QuickSort() {
	// CONFIG
	int number_list[] = {10, 23, 23, 23, 23, 23, 23, 23, 23, 38, 29, 383, 348, 201, 383, 128, 163};

	// CORE
	sort_QuickSort(number_list, sizeof(int), sizeof(number_list), compare);

	for (int i = 0; i < sizeof(number_list) / sizeof(int); ++i) {
		printf("%i ", number_list[i]);
	}

	return true;
}


bool Test_testSelect_QuickSelect() {
	// CONFIG
	Vector<int> vector;
	for (int i = 0; i < 30; ++i) vector.push_back(getRandomInt() % 100);

	Vector<int> vector_sorted(vector);
	sort_QuickSort(vector_sorted.data(), sizeof(int), vector_sorted.size() * sizeof(int), compare);

	// CORE
	// show the sorted result
	for (int i = 0; i < vector_sorted.size(); ++i)  printf("%i ", vector_sorted[i]);
	printf("\n");

	// do selection
	unsigned int index;
	void *target;

	index = 6;
	target = select_QuickSelect(vector.data(), sizeof(int), vector.size() * sizeof(int), compare, index);
	printf("Target: index: %i, value: %i\n", index, *(reinterpret_cast<int*>(target)));

	index = 15;
	target = select_QuickSelect(vector.data(), sizeof(int), vector.size() * sizeof(int), compare, index);
	printf("Target: index: %i, value: %i\n", index, *(reinterpret_cast<int*>(target)));

	index = 2;
	target = select_QuickSelect(vector.data(), sizeof(int), vector.size() * sizeof(int), compare, index);
	printf("Target: index: %i, value: %i\n", index, *(reinterpret_cast<int*>(target)));

	// RET
	return true;
}


// node for testing
struct NodeTest {
	int value;
};


bool Test_testShortestPath_Dijkstra() {
	// create node
	NodeTest node_list[10];
	for (int i = 0; i < 10; ++i) {
		node_list[i] = { i };
	}

	std::unordered_map<void*, std::vector<Pair<void*, unsigned int>>> node_table;
	for (int i = 0; i < 10; ++i) {
		node_table.insert(make_pair( (void*)(node_list + i), std::vector<Pair<void*, unsigned int>>() ));
	}

	// create connection
	node_table[(void*)(node_list + 0)].push_back(makePair((void*)(node_list + 1), (unsigned int)1));
	node_table[(void*)(node_list + 0)].push_back(makePair((void*)(node_list + 2), (unsigned int)2));
	node_table[(void*)(node_list + 1)].push_back(makePair((void*)(node_list + 3), (unsigned int)3));
	node_table[(void*)(node_list + 2)].push_back(makePair((void*)(node_list + 3), (unsigned int)5));

	// tree
	std::unordered_map<void*, void*> tree;

	// dijkstra
	bool ret = getShortestPath_Dijkstra(node_table, (void*)(node_list + 0), (void*)(node_list + 3), tree);
	printf("Path is %s\n", ret ? "found" : "not found");

	// print tree
	for (auto& it : tree) {
		if (it.second == nullptr) {
			printf("%i %s \n", ((NodeTest*)(it.first))->value, "end" );
			continue;
		}
		printf("%i %i \n", ((NodeTest*)(it.first))->value, ((NodeTest*)(it.second))->value );
	}

	return true;
}
