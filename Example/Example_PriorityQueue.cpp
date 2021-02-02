//
// Author: Jack Tse
// Date of creation: 25/1/2021
// Email: jacktsetcy@gmail.com
//
// LeetCode
// 23: Merge k Sorted Lists


// Import
#include <vector>
#include <queue>
#include <stdio.h>
#include <stdint.h>


// Namespace
using namespace std;


// Data Structure
struct ListNode {
	int val;
	ListNode *next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode *next) : val(x), next(next) {}

	ListNode* push(int value) {
		auto temp = new ListNode(value);
		next = temp;
		return temp;
	}
};


struct CompareNode {
	bool operator()(const ListNode *node_1, const ListNode *node_2) {
		return node_1->val > node_2->val;
	}
};


class Solution {
public:
	ListNode* mergeKLists(vector<ListNode*>& lists) {
		// CONFIG
		// queue (smallest at the front)
		priority_queue<ListNode*, vector<ListNode*>, CompareNode> table;

		for (auto list : lists) {
			if (list == nullptr) continue;
			table.push(list);
		}

		// result
		ListNode fake_head;
		ListNode *cur = &fake_head;

		// CORE
		while (!table.empty()) {
			auto top = table.top();
			table.pop();

			cur->next = top;
			cur = top;

			if (top->next != nullptr) {
				table.push(top->next);
			}
		}

		// RET
		cur->next = nullptr;
		return fake_head.next;
	}
};


// Operation
int main() {
	// CONFIG
	ListNode node_1;
	ListNode node_2;
	ListNode node_3;

	node_1.push(1)->push(4)->push(5);
	node_2.push(1)->push(3)->push(4);
	node_3.push(2)->push(6);

	vector<ListNode*> node_list;
	node_list.push_back(node_1.next);
	node_list.push_back(node_2.next);
	node_list.push_back(node_3.next);

	// CORE
	Solution solution;
	auto node = solution.mergeKLists(node_list);

	int count = 0;
	while (node != nullptr) {
		if (count != 0) printf("->");
		printf("%i", node->val);
		node = node->next;
		count++;
	}

	return 0;
}
