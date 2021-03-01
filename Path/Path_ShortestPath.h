//
// Author: Jack Tse
// Date of creation: 27/2/2021
// Email: jacktsetcy@gmail.com
//

#ifndef ALGORITEMIMPLEMENTATION_PATH_SHORTESTPATH_H
#define ALGORITEMIMPLEMENTATION_PATH_SHORTESTPATH_H


// Import
#include <Utility.h>
#include <Map.h>
#include <List.h>
#include <unordered_map>
#include <queue>


// Namespace-Begin - Algo
namespace Algo {


// Data Structure
struct _NodeRecord_ {
// Data
public:
	bool			is_visited;
	unsigned int	cost;
};


struct _PathRecord_ {
// Data
public:
	void			*target;
	unsigned int	cost;
};


struct _PathRecord_Compare_ {
// Operation
public:
	bool operator()(_PathRecord_ &a, _PathRecord_ &b) {
		return a.cost > b.cost;
	}
};


// Function - Prototype
bool getShortestPath_Dijkstra(
		const std::unordered_map<void*, std::vector<Pair<void*, unsigned int>>> &node_table,	// specify node and its neighbouring node, neighbouring: unidirectional edge from node to adj.
		void *begin, void *end,																	// begin: point to start, end: searching will end if once end point is reached
		std::unordered_map<void*, void*> &tree													// Map<Pair<start, end>>, toward begin point
);


// Function - Implementation
bool getShortestPath_Dijkstra(
		const std::unordered_map<void*, std::vector<Pair<void*, unsigned int>>> &node_table,	// specify node and its neighbouring node and the cost of edge, neighbouring: unidirectional edge from node to adj.
		void *begin, void *end,																	// begin: point to start, end: searching will end if once end point is reached
		std::unordered_map<void*, void*> &tree													// Map<Pair<start, end>>, toward begin point
		) {

	// CHECK
	// check if begin_point is inside the node_table
	//
	// end_point is not needed to check
	// (if end point is not in the table, then the algorithm will run through all node reachable from begin point)
	if (node_table.find(begin) == node_table.end()) return false;

	// CONFIG
	bool is_end_reached = false;
	std::unordered_map<void*, _NodeRecord_> record;

	// construct record table
	// record table is only applicable to single path_queue searching
	for (auto it = node_table.begin(); it != node_table.end(); ++it) {
		record[it->first] = { false, std::numeric_limits<unsigned int>::max() };
	}

	// CORE
	std::priority_queue<_PathRecord_, std::vector<_PathRecord_>, _PathRecord_Compare_> path_queue;
	path_queue.push({ begin, 0 } );

	tree[begin] = nullptr;

	while (!path_queue.empty()) {
		_PathRecord_ top = path_queue.top();
		path_queue.pop();

		// reach the end_point
		if (top.target == end) {
			is_end_reached = true;
			break;
		}

		// check if the node is visited or not
		// if visited, there exist an another path_queue that the cost is smaller than current path_queue
		auto it_node_top = node_table.find(top.target);
		auto it_record_top = record.find(top.target);

		if (it_record_top->second.is_visited) continue;
		it_record_top->second.is_visited = true;

		// to neighbouring node
		for (const Pair<void*, unsigned int> &neighbor : it_node_top->second) {

			// check if the node is visited before
			// prevent revisit the node and hence prevent cyclic path_queue
			auto it_record_neighbor = record.find(neighbor.first);
			if (it_record_neighbor->second.is_visited) continue;

			// only update if a new shortest path_queue occur
			const unsigned int cost = top.cost + neighbor.second;
			if (cost >= it_record_neighbor->second.cost) continue;

			it_record_neighbor->second.cost = cost;
			tree[neighbor.first] = top.target;

			// push new path_queue to queue
			path_queue.push({ neighbor.first, cost });
		}
	}

	// RET
	return is_end_reached;
}


// Namespace-End - Algo
}


#endif //ALGORITEMIMPLEMENTATION_PATH_SHORTESTPATH_H
