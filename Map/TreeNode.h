//
// Author: Jack Tse
// Date of creation: 16/2/2021
// Email: jacktsetcy@gmail.com
//

#ifndef ALGORITEMIMPLEMENTATION_TREENODE_H
#define ALGORITEMIMPLEMENTATION_TREENODE_H


// Import
#include <Utility.h>


// Namespace-Begin - Algo
namespace Algo {


// Data Structure
class _BaseBinaryNode_ {
// Data
public:
	_BaseBinaryNode_	*left;
	_BaseBinaryNode_	*right;
};


template <class Key, class Value>
class _UniDirBinaryNode_ {
// Data
public:
	_UniDirBinaryNode_	*left;
	_UniDirBinaryNode_	*right;

	Key					key;
	Value				value;
};


template <class Key, class Value>
class _BiDirBinaryNode_ {
// Data
public:
	_BiDirBinaryNode_	*parent;
	_BiDirBinaryNode_	*left;
	_BiDirBinaryNode_	*right;

	Key					key;
	Value				value;
};


// Function
// height
uint32 getTreeHeight(_BaseBinaryNode_ *node) {
	if (node == nullptr) return 0;
	return max(getTreeHeight(node->left) + 1, getTreeHeight(node->right) + 1);
}


template<class Key, class Value>
inline uint32 getTreeHeight(_UniDirBinaryNode_<Key, Value> *node) {
	return getTreeHeight((_BaseBinaryNode_*)node);
}


template<class Key, class Value>
inline uint32 getTreeHeight(_BiDirBinaryNode_<Key, Value> *node) {
	typedef _BiDirBinaryNode_<Key, Value> Node;
	return getTreeHeight(casting(node, _BaseBinaryNode_, Node, left));
}


// size - number of node in the tree
uint32 getTreeSize(_BaseBinaryNode_ *node) {
	if (node == nullptr) return 0;
	return getTreeSize(node->left) + getTreeSize(node->right) + 1;
}


template<class Key, class Value>
inline uint32 getTreeSize(_UniDirBinaryNode_<Key, Value> *node) {
	return getTreeSize((_BaseBinaryNode_*)node);
}


template<class Key, class Value>
inline uint32 getTreeSize(_BiDirBinaryNode_<Key, Value> *node) {
	typedef _BiDirBinaryNode_<Key, Value> Node;
	return getTreeSize(casting(node, _BaseBinaryNode_, Node, left));
}


// print node (key + value)
// TODO


// Namespace-End - Algo
}


#endif //ALGORITEMIMPLEMENTATION_TREENODE_H
