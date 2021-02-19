//
// Author: Jack Tse
// Date of creation: 16/2/2021
// Email: jacktsetcy@gmail.com
//

#ifndef ALGORITEMIMPLEMENTATION_TREENODE_H
#define ALGORITEMIMPLEMENTATION_TREENODE_H


// Import
#include <Utility.h>
#include <List.h>


// Namespace-Begin - Algo
namespace Algo {


// Enum
enum class TraversalOrder {
	INORDER,
	PREORDER,
	POSTORDER,
	SIZE_ENUM
};


// Data Structure
class _UniDirBinaryNode_ {
// Data
public:
	_UniDirBinaryNode_	*left;
	_UniDirBinaryNode_	*right;
};


class _BiDirBinaryNode_ {
// Data
public:
	_BiDirBinaryNode_	*parent;
	_BiDirBinaryNode_	*left;
	_BiDirBinaryNode_	*right;
};


// Function - Prototype
inline uint32_t _getTreeHeightDiff_(
		_UniDirBinaryNode_ *node, uint32_t &height_max, uint32_t &height_min, void *stopper);

inline uint32_t _getTreeHeightDiff_(
		_BiDirBinaryNode_ *node, uint32_t &height_max, uint32_t &height_min, void *stopper);

// traversal - uni-dir
template <class Value>
void _getTraversal_Inorder_(
		_List_<Value> &dst, _UniDirBinaryNode_ *node, void *stopper, const std::function<Value(_UniDirBinaryNode_*)> &get_value);

template <class Value>
void _getTraversal_Preorder_(
		_List_<Value> &dst, _UniDirBinaryNode_ *node, void *stopper, const std::function<Value(_UniDirBinaryNode_*)> &get_value);

template <class Value>
void _getTraversal_Postorder_(
		_List_<Value> &dst, _UniDirBinaryNode_ *node, void *stopper, const std::function<Value(_UniDirBinaryNode_*)> &get_value);

// traversal - bi-dir
template <class Value>
void _getTraversal_Inorder_(
		_List_<Value> &dst, _BiDirBinaryNode_ *node, void *stopper, const std::function<Value(_BiDirBinaryNode_*)> &get_value);

template <class Value>
void _getTraversal_Preorder_(
		_List_<Value> &dst, _BiDirBinaryNode_ *node, void *stopper, const std::function<Value(_BiDirBinaryNode_*)> &get_value);

template <class Value>
void _getTraversal_Postorder_(
		_List_<Value> &dst, _BiDirBinaryNode_ *node, void *stopper, const std::function<Value(_BiDirBinaryNode_*)> &get_value);


// Function - Implementation
// height
inline uint32 getTreeHeight(_UniDirBinaryNode_ *node, void *stopper = nullptr) {
	if (node == nullptr || node == stopper) return 0;
	return max(getTreeHeight(node->left, stopper), getTreeHeight(node->right, stopper)) + 1;
}


inline uint32 getTreeHeight(_BiDirBinaryNode_ *node, void *stopper = nullptr) {
	if (node == nullptr || node == stopper) return 0;
	return max(getTreeHeight(node->left, stopper), getTreeHeight(node->right, stopper)) + 1;
}


// size - number of node in the tree
inline uint32 getTreeSize(_UniDirBinaryNode_ *node, void *stopper = nullptr) {
	if (node == nullptr || node == stopper) return 0;
	return getTreeSize(node->left, stopper) + getTreeSize(node->right, stopper) + 1;
}


inline uint32 getTreeSize(_BiDirBinaryNode_ *node, void *stopper = nullptr) {
	if (node == nullptr || node == stopper) return 0;
	return getTreeSize(node->left, stopper) + getTreeSize(node->right, stopper) + 1;
}


// diff - max difference of height
inline uint32_t getTreeHeightDiff(_UniDirBinaryNode_ *node, void *stopper = nullptr) {
	uint32_t height_min, height_max;
	return _getTreeHeightDiff_(node, height_min, height_max, stopper);
}


inline uint32_t getTreeHeightDiff(_BiDirBinaryNode_ *node, void *stopper = nullptr) {
	uint32_t height_min, height_max;
	return _getTreeHeightDiff_(node, height_min, height_max, stopper);
}


inline uint32_t _getTreeHeightDiff_(
		_UniDirBinaryNode_ *node, uint32_t &height_min, uint32_t &height_max, void *stopper) {

	if (node == nullptr || node == stopper) {
		height_min = 0;
		height_max = 0;
		return 0;
	}

	uint32_t height_l_min, height_l_max, height_r_min, height_r_max;
	const uint32_t l = _getTreeHeightDiff_(node->left, height_l_min, height_l_max, stopper);
	const uint32_t r = _getTreeHeightDiff_(node->right, height_r_min, height_r_max, stopper);

	height_min = min(height_l_min, height_r_min) + 1;
	height_max = max(height_l_max, height_r_max) + 1;

	return max(max(l, r), height_max - height_min);
}


inline uint32_t _getTreeHeightDiff_(
		_BiDirBinaryNode_ *node, uint32_t &height_min, uint32_t &height_max, void *stopper) {

	if (node == nullptr || node == stopper) {
		height_min = 0;
		height_max = 0;
		return 0;
	}

	uint32_t height_l_min, height_l_max, height_r_min, height_r_max;
	const uint32_t l = _getTreeHeightDiff_(node->left, height_l_min, height_l_max, stopper);
	const uint32_t r = _getTreeHeightDiff_(node->right, height_r_min, height_r_max, stopper);

	height_min = min(height_l_min, height_r_min) + 1;
	height_max = max(height_l_max, height_r_max) + 1;

	return max(max(l, r), height_max - height_min);
}


// ordering / traversal
// inorder: LCR
// preorder: CLR
// postorder: LRC
template <class Value>
void getTraversal(
		_List_<Value> &dst, _UniDirBinaryNode_ *node, const std::function<Value(_UniDirBinaryNode_*)> &get_value,
		TraversalOrder order,
		void *stopper = nullptr) {

	switch (order) {
		case TraversalOrder::INORDER:
			_getTraversal_Inorder_(dst, node, stopper, get_value);
			break;

		case TraversalOrder::PREORDER:
			_getTraversal_Preorder_(dst, node, stopper, get_value);
			break;

		case TraversalOrder::POSTORDER:
			_getTraversal_Postorder_(dst, node, stopper, get_value);
			break;

		// do nothing
		default:
			break;
	}
}


template <class Value>
void getTraversal(
		_List_<Value> dst, _BiDirBinaryNode_ *node, const std::function<Value(_BiDirBinaryNode_*)> get_value,
		TraversalOrder order,
		void *stopper = nullptr) {

	switch (order) {
		case TraversalOrder::INORDER:
			_getTraversal_Inorder_(dst, node, stopper, get_value);
			break;

		case TraversalOrder::PREORDER:
			_getTraversal_Preorder_(dst, node, stopper, get_value);
			break;

		case TraversalOrder::POSTORDER:
			_getTraversal_Postorder_(dst, node, stopper, get_value);
			break;

			// do nothing
		default:
			break;
	}
}


// traversal - uni-dir
template <class Value>
void _getTraversal_Inorder_(
		_List_<Value> &dst, _UniDirBinaryNode_ *node, void *stopper, const std::function<Value(_UniDirBinaryNode_*)> &get_value) {

	if (node == nullptr || node == stopper) return;
	_getTraversal_Inorder_(dst, node->left, stopper, get_value);
	dst.push_back(get_value(node));
	_getTraversal_Inorder_(dst, node->right, stopper, get_value);
}


template <class Value>
void _getTraversal_Preorder_(
		_List_<Value> &dst, _UniDirBinaryNode_ *node, void *stopper, const std::function<Value(_UniDirBinaryNode_*)> &get_value) {

	if (node == nullptr || node == stopper) return;
	dst.push_back(get_value(node));
	_getTraversal_Preorder_(dst, node->left, stopper, get_value);
	_getTraversal_Preorder_(dst, node->right, stopper, get_value);
}


template <class Value>
void _getTraversal_Postorder_(
		_List_<Value> &dst, _UniDirBinaryNode_ *node, void *stopper, const std::function<Value(_UniDirBinaryNode_*)> &get_value) {

	if (node == nullptr || node == stopper) return;
	_getTraversal_Postorder_(dst, node->left, stopper, get_value);
	_getTraversal_Postorder_(dst, node->right, stopper, get_value);
	dst.push_back(get_value(node));
}


// traversal - bi-dir
template <class Value>
void _getTraversal_Inorder_(
		_List_<Value> &dst, _BiDirBinaryNode_ *node, void *stopper, const std::function<Value(_BiDirBinaryNode_*)> &get_value) {

	if (node == nullptr || node == stopper) return;
	_getTraversal_Inorder_(dst, node->left, stopper, get_value);
	dst.push_back(get_value(node));
	_getTraversal_Inorder_(dst, node->right, stopper, get_value);
}


template <class Value>
void _getTraversal_Preorder_(
		_List_<Value> &dst, _BiDirBinaryNode_ *node, void *stopper, const std::function<Value(_BiDirBinaryNode_*)> &get_value) {

	if (node == nullptr || node == stopper) return;
	dst.push_back(get_value(node));
	_getTraversal_Preorder_(dst, node->left, stopper, get_value);
	_getTraversal_Preorder_(dst, node->right, stopper, get_value);
}


template <class Value>
void _getTraversal_Postorder_(
		_List_<Value> &dst, _BiDirBinaryNode_ *node, void *stopper, const std::function<Value(_BiDirBinaryNode_*)> &get_value) {

	if (node == nullptr || node == stopper) return;
	_getTraversal_Postorder_(dst, node->left, stopper, get_value);
	_getTraversal_Postorder_(dst, node->right, stopper, get_value);
	dst.push_back(get_value(node));
}


// print node
// TODO: printing order now is fixed
// printing order: LCR
String printTree(
		_UniDirBinaryNode_ *node, const std::function<String(_UniDirBinaryNode_*)> &get_string,
		void *stopper = nullptr, unsigned int indent = 4, unsigned int depth = 0) {

	String string;
	if (node == nullptr || node == stopper) return string;

	// L
	printTree(node->left, get_string, stopper, indent, depth + 1);

	// C
	string.append(' ', indent * depth);
	string += get_string(node);

	// R
	printTree(node->right, get_string, stopper, indent, depth + 1);

	// RET
	return string;
}


String printTree(
		_BiDirBinaryNode_ *node, const std::function<String(_BiDirBinaryNode_*)> &get_string,
		void *stopper = nullptr, unsigned int indent = 4, unsigned int depth = 0) {

	String string;
	if (node == nullptr || node == stopper) return string;

	// L
	printTree(node->left, get_string, stopper, indent, depth + 1);

	// C
	string.append(' ', indent * depth);
	string += get_string(node);

	// R
	printTree(node->right, get_string, stopper, indent, depth + 1);

	// RET
	return string;
}


// Namespace-End - Algo
}


#endif //ALGORITEMIMPLEMENTATION_TREENODE_H
