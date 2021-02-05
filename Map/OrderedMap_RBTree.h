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
#include <string.h>


// Namespace-Begin - Algo
namespace Algo {


// Enum
enum class RBNodeColor {
	RED = 0,
	BLACK = 1,
	SIZE_ENUM
};


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
	    ConstIterator(Stack<Pair<uint8, const RBNode*>> &stack_, Bool is_left_first_ = true):
	    is_left_first(is_left_first)
	    {
	    	this->stack = stack;
	    }

	    ConstIterator(const ConstIterator &other)
	    {
	    	this->stack 		= Stack<Pair<Bool, const RBNode*>>(other.stack);
	    	this->is_left_first = other.is_left_first;
	    }

	    ~ConstIterator() {

	    }

	    // operation
	    // ...

	// Operator Overload
	public:
		// increment / decrement
		// ++a
		ConstIterator& operator++() {
	    	// if user constantly check "it != map.end()"
	    	// this statement is not needed
	    	if (stack.empty()) return *this;

	    	// check if current is visited or not
	    	// if visited, then go upward
	    	if (stack.top().first == 1) {
	    		while (!stack.empty() && stack.top().first == 1) stack.pop();
	    		return *this;
	    	}

	    	// update node state
	    	stack.top().first = 1;

	    	// current node is visited, need to find the next available node
	    	// check if can go deep into right / left
	    	// if not, then recursively go upward
	    	if (is_left_first && stack.top().second->right == nullptr){
	    		while (!stack.empty() && stack.top().first == 1) stack.pop();
	    		return *this;
	    	}

	    	if (!is_left_first && stack.top().second->left == nullptr) {
				while (!stack.empty() && stack.top().first == 1) stack.pop();
	    		return *this;
	    	}

	    	// go deep
	    	RBNode *cur = stack.top().second;
	    	if (is_left_first) {
	    		cur = cur->right;
	    		while (cur != nullptr) {
	    			stack.push(makePair(0, cur));
	    			cur = cur->left;
	    		}

	    	} else {
	    		cur = cur->left;
	    		while (cur != nullptr) {
	    			stack.push(makePair(0, cur));
	    			cur = cur->right;
	    		}

	    	}

	    	return *this;
		}

		// a++
		ConstIterator operator++(int) {
	    	ConstIterator temp(*this);
	    	++(*this);
	    	return temp;
		}

		// arithmetic
		// ...

		// comparison
		// a == b
		bool operator==(const ConstIterator &other) const {
	    	if (this->stack.empty() && other.stack.empty()) 			return true;
	    	if (this->stack.top().second == other.stack.top().second) 	return true;
	    	return false;
		}

		// a != b
		// bool operator!=(const ConstIterator &other) const {
		// }

		// member access
		// a->
		const Value* operator->() const {
			return &(stack.top().second->value);
		}

		// *a
		const Value& operator*() const {
			return stack.top().second->value;
		}
	};

	class Iterator {
	// Data
	public:
		// for the first item in pair is "is_self_visited"
		// it is: is_left_visited
		Stack<Pair<uint8, RBNode*>> 	stack;
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
	}

	// TODO
	void erase(const Key &key) override {

	}

	void clear() override {
    	_clear_();
	}

	void swap(OrderedMap_RBTree &other) {
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
    		stack.push(makePair(0, left));
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
			stack.push(makePair(0, right));
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
			stack.push(makePair(0, left));
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
			stack.push(makePair(0, right));
			right = right->right;
		}
		return ConstIterator(stack, false);
    }

	ConstIterator crend() const {
		// the item after final one is nullptr
		return ConstIterator(Stack<Pair<Bool, const RBNode*>>(), false);
    }

protected:
	RBNode* _find_(const Key &key) {
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

	RBNode* _insertFirst_(const Key &key, const Value &value) {
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

    	return node_new;
	}

    RBNode* _insert_(RBNode *node, const Key &key, const Value &value) {
    	// find the point of insertion
    	// and the new node is initially painted to be RED
    	auto node_new = new RBNode();

    	node_new->is_black	= (uint8)RBNodeColor::RED;
    	node_new->key		= key;
    	node_new->value		= value;

    	if (key < node->key) node->left  = node_new;
    	if (key > node->key) node->right = node_new;
    	node_new->parent = node;

    	// fix-up
		_fixInsertion_(node_new);

		// stat
		size_allocated++;

		return node_new;
    }

    void _erase_(RBNode *node) {
    	// assumed: node must exist

    	// check if node has 2 children
    	// if so, then need to convert this to the situation of node only has 1 child
    	//
    	// convert find the leftmost / rightmost node (node_bottom) on the right / left child, and
    	// do swapping (value only) on node and node_bottom
    	// finally change the node to be node_bottom
    	if (node->left != nullptr && node->right != nullptr) {
    		auto node_bottom = _getLeftmost_(node->right);

    		Key 	temp_key 	= node_bottom->key;
    		Value	temp_value	= node_bottom->value;

    		node_bottom->key 	= node->key;
    		node_bottom->value	= node->value;

    		node->key	= temp_key;
    		node->value = temp_value;

    		node = node_bottom;
    	}

    	// fix-deletion
    	_fixDeletion_(node);

    	// destroy
    	delete node;
    }

    // for insertion, only 2 rotation at max is needed
    void _fixInsertion_(RBNode *node) {
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
    		node->parent->is_black 	= (uint8)RBNodeColor::BLACK;
    		uncle->is_black 		= (uint8)RBNodeColor::BLACK;
    		grandparent->is_black	= (uint8)RBNodeColor::RED;

			_fixInsertion_(grandparent);
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
    	if (node->parent->left == node && grandparent->left == node->parent) {
    		_rotateRight_(node->parent, grandparent);
    	} else {
    		_rotateLeft_(node->parent, grandparent);
    	}
    }

    void _fixDeletion_(RBNode *node) {
    	RBNode *node_child = node->left == nullptr ? node->right : node->left;

    	// ----- preprocessing -----
    	// replace node
		if (node->parent->left == node) node->parent->right	= node_child;
		else							node->parent->left	= node_child;

		// if there is no child for node
		// else set node_child->parent
    	if (node_child == nullptr) return;
    	node_child->parent = node->parent;

    	// if self is RED
    	if (!node->is_black) return;

    	// if self is BLACK and child is RED
    	if (!node_child->is_black) {
    		node_child->is_black = true;
    		return;
    	}

    	// reset node
    	node = node_child;

    	// ----- situation 1 -----
    	// check if node now is at the top
    	if (node->parent == root) return;

    	// ----- situation 2 -----
    	// rotation on sibling and parent
    	// after rotation, node->parent is changed to be sibling
    	RBNode *node_sibling = _getSibling_(node);
    	if (!node_sibling->is_black) {
    		if (node->parent->left == node) _rotateLeft_(node_sibling, node->parent);
    		else							_rotateRight_(node_sibling, node->parent);
    	}

    	// as sibling for node is changed, then need to refresh the variable again
    	node_sibling = _getSibling_(node);

    	// ----- situation 3 -----
    	// situation 2 and situation 3 cannot be co-exist
    	if (node->parent->is_black &&
    		node_sibling->is_black &&
    		node_sibling->left->is_black &&
    		node_sibling->right->is_black) {

    		node_sibling->is_black = false;
    		_fixDeletion_(node->parent);
    		return;
    	}

    	// ----- situation 4 -----
    	if (!node->parent->is_black &&
    		node_sibling->is_black &&
    		node_sibling->left->is_black &&
    		node_sibling->right->is_black) {

    		node_sibling->is_black = false;
    		node->parent->is_black = true;
    		return;
    	}

    	// ----- situation 5 -----
    	if (node->parent->left == node &&
    		node_sibling->right->is_black == (uint8)RBNodeColor::BLACK &&
    		node_sibling->left->is_black  == (uint8)RBNodeColor::RED) {

    		_rotateRight_(node_sibling->left, node_sibling);
    	}
    	else if (node->parent->right == node &&
    			 node_sibling->left->is_black  == (uint8)RBNodeColor::BLACK &&
    			 node_sibling->right->is_black == (uint8)RBNodeColor::RED) {

    		_rotateLeft_(node_sibling->right, node_sibling);
    	}

    	// update sibling node
    	// node_sibling = _getSibling_(node);

    	// ----- situation 6 -----
    	if (node->parent->left == node) _rotateLeft_(node->parent, node->parent->parent);
    	else							_rotateRight_(node->parent, node->parent->parent);
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
	RBNode* _getGrandparent_(RBNode *node) const {
    	return node->parent->parent;
    }

    RBNode* _getUncle_(RBNode *node) const {
    	if (node->parent == _getGrandparent_(node)->left) 	return _getGrandparent_(node)->right;
    	else											 	return _getGrandparent_(node)->left;
    }

    RBNode* _getSibling_(RBNode *node ) const {
    	if (node->parent->left == node) return node->parent->right;
    	else							return node->parent->left;
    }

    RBNode* _getLeftmost_(const RBNode *node) const {
    	if (node == nullptr) return node;
    	while (node->left != nullptr) node = node->left;
    	return node;
    }

    RBNode* _getRightmost_(const RBNode *node) const {
    	if (node == nullptr) return node;
    	while (node->right != nullptr) node = node->right;
    	return node;
    }

// Operator Overload
public:
	// ...
};


// Function
// traversal: LCR
template <class Key, class Value>
std::string getString_RBTree(
		_RBNode_<Key, Value> *node,
		const std::function<std::string(Key)>	*func_key_to_string,
		const std::function<std::string(Value)>	*func_value_to_string,
		unsigned int depth = 0,
		unsigned int indent = 4) {

	std::string content;
	if (node == nullptr) {
		content.append(indent * depth, ' ');
		content.append("NULL\n");
		return content;
	}

	// left
	content += getString_RBTree(node->left, func_key_to_string, func_value_to_string, depth + 1, indent);

	// center
	content.append(indent * depth, ' ');
	content += '(';
	content += (*func_key_to_string)(node->key);
	content += ',';
	content += (*func_value_to_string)(node->value);;
	content += ',';
	content += node->is_black ? "B" : "R";
	content += ')';
	content += '\n';

	// right
	content += getString_RBTree(node->right, func_key_to_string, func_value_to_string, depth + 1, indent);

	// ret
	return content;
}


// Namespace-End - Algo
}


#endif //ALGORITEMIMPLEMENTATION_ORDEREDMAP_RBTREE_H
