//
// Author: Jack Tse
// Date of creation: 27/1/2021
// Email: jacktsetcy@gmail.com
//

#ifndef ALGORITEMIMPLEMENTATION_UNIONTREE_H
#define ALGORITEMIMPLEMENTATION_UNIONTREE_H


// Import
#include "../List/List.h"


// Namespace-Begin - Algo
namespace Algo {


// Data Structure
class UnionTree {
// Data
public:
    Vector<int>		container;

// Function
public:
    // init and del
    UnionTree(int size_):
    container(Vector<int>(size, -1))
    {
    }

    ~UnionTree() {
    }

    // operation
    void join(int key_1, int key_2) {
    	int parent_1, parent_2;
    	int depth_1, depth_2;

    	_getParent_(key_1, parent_1, depth_1);
    	_getParent_(key_2, parent_2, depth_2);

    	// have the same parent
    	if (parent_1 == parent_2) {
    		_refreshSingle_(key_1, parent_1);
    		_refreshSingle_(key_2, parent_2);
    		return;
    	}

		if (depth_1 < depth_2) {
			container[parent_2] = parent_1;
			container[key_2]   = parent_1;
			_refreshSingle_(key_1, parent_1);
		}
		else {
			container[parent_1] = parent_2;
			container[key_1]   = parent_2;
			_refreshSingle_(key_2, parent_2);
		}
    }

	void refresh() {
		const int n = container.size();
		for (int i = 0; i < n; ++i) {
			const int parent = getParent(i);
			container[i] = parent == i ? -1 : parent;
		}
	}

	bool getIsConnected(int key_1, int key_2) {
		int parent_1 = getParent(key_1);
		int parent_2 = getParent(key_2);

		_refreshSingle_(key_1, parent_1);
		_refreshSingle_(key_2, parent_2);

		return parent_1 == parent_2;
	}

	int getParent(int key) {
		int parent, depth;
		_getParent_(key, parent, depth);
		return parent;
	}

protected:
	void _getParent_(int key, int &parent, int &depth) {
		parent = key;
		depth = 0;

		while (container[parent] != -1) {
			parent = container[parent];
			depth++;
		}
	}

	void _refreshSingle_(int key, int parent) {
    	if (key != parent) container[key] = parent;
    }

// Operator Overload
public:
	// ...
};


// Function
// ...


// Namespace-End - Algo
}


#endif //ALGORITEMIMPLEMENTATION_UNIONTREE_H
