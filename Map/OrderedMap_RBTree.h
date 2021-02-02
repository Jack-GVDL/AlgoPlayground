//
// Author: Jack Tse
// Date of creation: 31/1/2021
// Email: jacktsetcy@gmail.com
//

#ifndef ALGORITEMIMPLEMENTATION_ORDEREDMAP_RBTREE_H
#define ALGORITEMIMPLEMENTATION_ORDEREDMAP_RBTREE_H


// Import
#include "OrderedMap_Base.h"
#include <Queue.h>


// Namespace-Begin - Algo
namespace Algo {


// Data Structure
template <class Key, class Value>
class _RBNode_ {
// Data
public:
	_RBNode_	*parent;
    _RBNode_	*left;
    _RBNode_	*right;
    Key			key;
    Value		value;
    Bool		is_black;

// Function
public:
    // init and del
    _RBNode_():
    parent(nullptr),
    left(nullptr),
    right(nullptr),
    value(0),
    is_black(true)
	{
	}

    _RBNode_(const Key &key_, const Value &value_):
    parent(nullptr),
    left(nullptr),
    right(nullptr),
    key(key_),
    value(value_),
    is_black(true)
    {
    }

    _RBNode_(const _RBNode_ *left_, const _RBNode_ *right_, const Key &key_, const Value &value_):
    parent(nullptr),
    left(left_),
    right(right_),
    key(key_),
    value(value),
    is_black(true)
	{
	}

	_RBNode_(
			const _RBNode_ *parent_,  const _RBNode_ *left_, const _RBNode_ *right_,
			const Key &key_, const Value &value_):
	parent(parent_),
	left(left_),
	right(right_),
	key(key_),
	value(value),
	is_black(true)
	{
	}

    ~_RBNode_() {

    }

    // operation
    // ...

// Operator Overload
public:
	// ...
};


template <class Key, class Value>
class OrderedMap_RBTree: public _OrderedMap_<Key, Value> {
// Typedef
typedef _RBNode_<Key, Value> RBNode;

// Class
public:
	class ConstIterator {
	// Data
	public:
		// for the first item in pair is "is_self_visited"
	    Stack<Pair<Bool, const RBNode*>> 	stack;
		Bool 								is_left_first;

	// Function
	public:
	    // init and del
	    ConstIterator(Stack<Pair<Bool, const RBNode*>> &stack_, Bool is_left_first_ = true):
	    is_left_first(is_left_first)
	    {
	    	this->stack = stack;
	    }

	    ~ConstIterator() {

	    }

	    // operation
	    // ...

	// Operator Overload
	public:
		// ...
	};

	class Iterator {
	// Data
	public:
		// for the first item in pair is "is_self_visited"
		// it is: is_left_visited
		Stack<Pair<Bool, RBNode*>> 	stack;
		Bool						is_left_first;

	// Function
	public:
	    // init and del
		Iterator(Stack<Pair<Bool, RBNode*>> &stack_, Bool is_left_first_ = true):
		is_left_first(is_left_first_)
		{
			this->stack = stack_;
		}

		~Iterator() {

	    }

	    // operation
	    // ...

	// Operator Overload
	public:
		// ...
	};

// Data
public:
	// root do not hold any value
	RBNode	_root_;
	RBNode	*root;

    unsigned int			size_allocated;
    Value					default_none;

// Function
public:
    // init and del
    OrderedMap_RBTree():
    root(&_root_),
    size_allocated(0),
    default_none(0)
    {
    }

    OrderedMap_RBTree(const OrderedMap_RBTree &other) {
    	_copyDeep_(other);
    	this->default_none = other.default_none;
    }

    ~OrderedMap_RBTree() {
		_clear_();
    }

    // assignment operator
    OrderedMap_RBTree& operator=(const OrderedMap_RBTree &other) {
    	this->root->left 		= other.root->left;
    	this->size_allocated	= other.size_allocated;
    	this->default_none		= other.default_none;
    	return *this;
    }

    // modifier
	void insert(const Key &key, const Value &value) override {
    	// special case
    	if (size_allocated == 0) {
    		_insertFirst_(key, value);
    		return;
    	}

    	// replace
		RBNode *target = _find_(key);
    	if (key == target->key) {
    		target->value = value;
    		return;
    	}

    	// insert
    	_insert_(target, key, value);
    	size_allocated++;
	}

	void erase(const Key &key) override {

	}

	void clear() override {
    	_clear_();
	}

	void swap(OrderedMap_RBTree &other) override {
    	// temp
    	OrderedMap_RBTree temp;
    	temp = other;

		// this to other
		other = *this;

		// data from other to this
		*this = temp;
	}

	// element access
	Value &at(const Key &key) override {
    	// CONFIG
		RBNode *target;

    	// special case
    	if (size_allocated == 0) {
    		target = _insertFirst_(key, default_none);
    		return target->value;
    	}

    	// find
    	target = _find_(key);
    	if (key == target->key) return target->value;

    	// insert
    	target = _insert_(target, key, default_none);
    	size_allocated++;

    	return target->value;
	}

	// capacity
	unsigned int size() override {
		return size_allocated;
	}

	bool empty() override {
		return size_allocated == 0;
	}

	// TODO
	unsigned int max_size() override {
		return 0;
	}

	// operation
	Iterator begin() {
    	// CONFIG
    	Stack<Pair<Bool, RBNode*>> 	stack;
    	RBNode 						*left = root->left;

    	// continuously stepping left to get the leftmost node
    	while (left != nullptr) {
    		stack.push(makePair(false, left));
    		left = left->left;
    	}
    	return Iterator(stack);
    }

	Iterator end() {
    	// the item after final one is nullptr
    	return Iterator(Stack<Pair<Bool, RBNode*>>());
    }

	Iterator rbegin() {
		// CONFIG
		Stack<Pair<Bool, RBNode*>> 	stack;
		RBNode 						*right = root->right;

		// continuously stepping right to get the rightmost node
		while (right != nullptr) {
			stack.push(makePair(false, right));
			right = right->right;
		}
		return Iterator(stack, false);
    }

	Iterator rend() {
		// the item after final one is nullptr
		return Iterator(Stack<Pair<Bool, RBNode*>>(), false);
    }

	ConstIterator cbegin() const {
		// CONFIG
		Stack<Pair<Bool, const RBNode*>> 	stack;
		const RBNode 						*left = root->left;

		// continuously stepping left to get the leftmost node
		while (left != nullptr) {
			stack.push(makePair(false, left));
			left = left->left;
		}
		return ConstIterator(stack);

    }

	ConstIterator cend() const {
		// the item after final one is nullptr
		return ConstIterator(Stack<Pair<Bool, const RBNode*>>());
    }

	ConstIterator crbegin() const {
		// CONFIG
		Stack<Pair<Bool, const RBNode*>> 	stack;
		const RBNode 						*right = root->right;

		// continuously stepping right to get the rightmost node
		while (right != nullptr) {
			stack.push(makePair(false, right));
			right = right->right;
		}
		return ConstIterator(stack, false);
    }

	ConstIterator crend() const {
		// the item after final one is nullptr
		return ConstIterator(Stack<Pair<Bool, const RBNode*>>(), false);
    }

protected:
	RBNode* _find_(Key &key) {
    	RBNode *cur	= root->left;
    	RBNode *prev	= root;

    	while (cur != nullptr) {

    		// left
    		if (key < cur->key) {
    			prev = cur;
    			cur = cur->left;
    			continue;
    		}

    		// right
    		if (key > cur->key) {
    			prev = cur;
    			cur = cur->right;
    			continue;
    		}

    		// equal
    		return cur;
    	}

    	return prev;
    }

	RBNode* _insertFirst_(Key &key, Value &value) {
    	// create
    	auto node_new = new RBNode(key, value);
    	node_new->is_black	= true;  // top is black
    	node_new->key		= key;
    	node_new->value		= value;

    	// insert
    	root->left		 = node_new;
    	node_new->parent = root;

    	// stat
    	size_allocated++;
	}

    RBNode* _insert_(RBNode *node, Key &key, Value &value) {
    	// find the point of insertion
    	// and the new node is initially painted to be RED
    	auto node_new = new RBNode();
    	node_new->is_black = false;

    	if (key < node->key)	node->left  = node_new;
    	if (key > node->key)	node->right = node_new;

    	// fix-up
    	_fixUp_(node_new);
    }

    void _fixUp_(RBNode *node) {
    	// condition 1 / base condition
    	// current node is top
    	if (node->parent == root) {
    		node->is_black = true;
    		return;
    	}

    	// condition 2 / base condition
    	// parent (father) is BLACK (at this point, input node must be RED)
    	// then the tree is valid and can quit
    	if (node->parent->is_black) return;

    	// condition 3
    	// uncle is present AND uncle is RED
    	// -> repaint father and uncle to BLACK, repaint grandfather as RED
    	// -> fix grandfather
    	RBNode *uncle 		= _getUncle_(node);
    	RBNode *grandparent	= _getGrandparent_(node);

    	if (uncle != nullptr && !uncle->is_black) {
    		node->parent->is_black 	= true;
    		uncle->is_black 		= true;
    		grandparent->is_black	= false;  // grandparent now is red

    		_fixUp_(grandparent);
    		return;
    	}

    	// condition 4
    	// uncle is absent OR uncle is BLACK

    	// sub-condition
    	// parent right is node, grandparent left is parent -> left rotation
    	// parent left is node, grandparent right is parent -> right rotation
    	if (node->parent->right == node && grandparent->left == node->parent) {
    		_rotateLeft_(node, node->parent);
    		node = node->left;
    	}
    	else if (node->parent->left == node && grandparent->right == node->parent) {
    		_rotateRight_(node, node->parent);
    		node = node->right;
    	}

    	// sub-condition
    	//
    	// it is noticed that grandparent is changed after rotation
    	// and at this point, grandparent is either to be root or to be RED
    	if (node->parent->left == node && grandparent->left == node->parent) {
    		_rotateRight_(node->parent, grandparent);
    		grandparent = _getGrandparent_(node);
    	} else {
    		_rotateLeft_(node->parent, grandparent);
    		grandparent = _getGrandparent_(node);
    	}

    	_fixUp_(grandparent);
    }

    void _clear_() {
		// iteration instead of recursion
		Stack<RBNode*> stack;
		if (root->left != nullptr)	stack.push(root->left);
		// if (root->right != nullptr)	stack.push(root->right);

		while (!stack.empty()) {
			RBNode *top = stack.top();
			stack.pop();

			if (top->left != nullptr)	stack.push(top->left);
			if (top->right != nullptr)	stack.push(top->right);

			delete top;
		}

		// structure
		root->left = nullptr;

		// stat
		size_allocated = 0;
    }

    void _copyDeep_(const OrderedMap_RBTree &other) {
    	// first remove the current tree
    	_clear_();

    	// iteration instead of recursion
    	// format: Pair<this, other>
    	Stack<Pair<RBNode*, RBNode*>> stack;
    	stack.push(makePair(this->root, other.root));

    	while (!stack.empty()) {
    		Pair<RBNode*, RBNode*> top = stack.top();
    		stack.pop();

    		// CONFIG
    		RBNode *node_new;
    		RBNode *node_old;

    		// push left
    		node_old = top.second->left;
    		if (node_old != nullptr) {
    			node_new 			= new RBNode(node_old->key, node_old->value);
    			top.first->left 	= node_new;
    			node_new->parent	= top.first;
    			stack.push(makePair(node_new, node_old));
    		}

    		// push right
			node_old = top.second->right;
    		if (node_old != nullptr) {
				node_new 			= new RBNode(node_old->key, node_old->value);
				top.first->right 	= node_new;
				node_new->parent	= top.first;
				stack.push(makePair(node_new, node_old));
    		}
    	}

    	// stat
    	this->size_allocated = other.size_allocated;
    }

    // rotation
    // position described below is the initial position (before rotation)
    void _rotateRight_(RBNode *node, RBNode *top) {
    	// topmost connection
    	// top must have parent (could be root)
    	RBNode *topmost = top->parent;
    	if (topmost->left == top) 	topmost->left  = node;
    	else						topmost->right = node;
		node->parent = topmost;

    	// node-top connection
    	top->parent = node;

    	// node-right connection
    	top->left	= node->right;
		node->right	= top;

    	// re-painting
    	node->is_black	= !(node->is_black);
    	top->is_black	= !(top->is_black);
    }

	// position described below is the initial position (before rotation)
    void _rotateLeft_(RBNode *node, RBNode *top) {
    	// topmost connection
    	RBNode *topmost = top->parent;
    	if (topmost->left == top)	topmost->left	= node;
    	else						topmost->right	= node;
		node->parent = topmost;

    	// node-top connection
    	top->parent = node;

    	// node-left connection
    	top->right	= node->left;
		node->left	= top;

    	// re-painting
		node->is_black	= !(node->is_black);
		top->is_black	= !(top->is_black);
	}

	// get node
	RBNode* _getGrandparent_(RBNode *node) {
    	return node->parent->parent;
    }

    RBNode* _getUncle_(RBNode *node) {
    	if (node->parent == _getGrandparent_(node)->left) 	return _getGrandparent_(node)->right;
    	else											 	return _getGrandparent_(node)->left;
    }

// Operator Overload
public:
	// ...
};


// Function
// ...


// Namespace-End - Algo
}


#endif //ALGORITEMIMPLEMENTATION_ORDEREDMAP_RBTREE_H
