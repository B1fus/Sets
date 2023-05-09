#pragma once
#include <iostream>
#include <iterator>
#include <cstddef>

template <typename T>
void swap(T* a, T* b) {
	T* c = a;
	a = b;
	b = c;
}

enum RBColor { Red, Black };
template <typename T>
struct RBNode
{
	T key;
	RBNode<T>* parent, *left, *right;
	RBColor color;
	RBNode(RBNode<T> const &node);
	RBNode(T key);
	RBNode(T key, RBNode<T>* parent);
	RBNode(T key, RBNode<T>* parent, RBNode<T>* left, RBNode<T>* right);
	RBNode(T key, RBNode<T>* parent, RBNode<T>* left, RBNode<T>* right, RBColor color);
};



template<typename T>
RBNode<T>::RBNode(RBNode<T> const &node)
{
	parent = node.parent;
	left = node.left;
	right = node.right;
	color = node.color;
	key = node.key;
}

template<typename T>
RBNode<T>::RBNode(T key):key(key)
{
	parent = nullptr;
	left = nullptr;
	right = nullptr;
	color = Red;
}

template<typename T>
RBNode<T>::RBNode(T key, RBNode<T>* parent):key(key), parent(parent)
{
	left = nullptr;
	right = nullptr;
	color = Red;
}

template<typename T>
RBNode<T>::RBNode(T key, RBNode<T>* parent, RBNode<T>* left, RBNode<T>* right):key(key), parent(parent), left(left), right(right) {
	color = Red;
}

template<typename T>
RBNode<T>::RBNode(T key, RBNode<T>* parent, RBNode<T>* left, RBNode<T>* right, RBColor color):key(key), parent(parent), left(left), right(right), color(color) {}









template<typename T>
class RBTree
{
public:
	RBTree();
	~RBTree();
	void insert(T key);
	void remove(T key);
	void remove(RBNode<T>* node);
	RBNode<T>* find(T key);
	void clear();
	void copy(RBTree<T> const &tree);
	void print() const;
	int size() const;
	bool contains(T key) const;
	int get_height(T key) const;
	struct iterator {
		using iterator_category = std::forward_iterator_tag;
		using difference_type = std::ptrdiff_t;
		using value_type = RBNode<T>;
		using pointer = RBNode<T>*;
		using reference = RBNode<T>&;

		iterator(RBNode<T>* ptr);
		iterator() { ptr = nullptr; }
		reference operator*() const;
		pointer operator->();
		reference operator=(RBNode<T>* ptr);
		iterator* operator++();
		iterator operator++(int);
		iterator* operator--();
		iterator operator--(int);
		friend bool operator== (const iterator& a, const iterator& b) { return a.ptr == b.ptr; }
		friend bool operator!= (const iterator& a, const iterator& b) { return a.ptr != b.ptr; }
	private:
		RBNode<T>* ptr;
	};
	iterator begin() const;
	iterator end() const;
	iterator rbegin() const;
	iterator rend() const;
protected:
	int sizeTree;
	RBNode<T>* topNode;
	RBNode<T>* _min(RBNode<T>* x) const;
	RBNode<T>* _max(RBNode<T>* x) const;
private:
	void _left_rotate(RBNode<T>* x);
	void _right_rotate(RBNode<T>* y);
	void _transplant(RBNode<T>* u, RBNode<T>* v);

	void _print(RBNode<T> const *x) const;
	void _insert(RBNode<T>* x);
	void _remove(RBNode<T>* x);
	void _destroy(RBNode<T>* x);
	RBNode<T>* _copy(RBNode<T> const *x, RBNode<T> const* parent);

};



template<typename T>
RBTree<T>::RBTree()
{
	topNode = nullptr;
	sizeTree = 0;
}

template<typename T>
RBTree<T>::~RBTree()
{
	sizeTree = 0;
	_destroy(topNode);
}

template<typename T>
void RBTree<T>::clear()
{
	sizeTree = 0;
	_destroy(topNode);
}

template<typename T>
void RBTree<T>::copy(RBTree<T> const &tree)
{
	this->clear();
	topNode = _copy(tree.topNode, nullptr);
	sizeTree = tree.sizeTree;
}

template<typename T>
typename RBTree<T>::iterator RBTree<T>::begin() const
{
	return _min(topNode);
}

template<typename T>
typename RBTree<T>::iterator RBTree<T>::end() const
{
	return nullptr;
}

template<typename T>
typename RBTree<T>::iterator RBTree<T>::rbegin() const
{
	return _max(topNode);
}

template<typename T>
typename RBTree<T>::iterator RBTree<T>::rend() const
{
	return nullptr;
}

template<typename T>
void RBTree<T>::_left_rotate(RBNode<T>* x)
{
	RBNode<T>* y = x->right;
	x->right = y->left;

	if (y->left != nullptr) y->left->parent = x;
	y->parent = x->parent;

	if (x->parent == nullptr) topNode = y;
	else if (x == x->parent->left) x->parent->left = y;
	else x->parent->right = y;

	y->left = x;
	x->parent = y;
}

template<typename T>
void RBTree<T>::_right_rotate(RBNode<T>* y)
{
	RBNode<T>* x = y->left;
	y->left = x->right;

	if (x->right != nullptr) x->right->parent = y;
	x->parent = y->parent;

	if (y->parent == nullptr) topNode = x;
	else if (y == y->parent->right) y->parent->right = x;
	else y->parent->left = x;

	x->right = y;
	y->parent = x;
}

template<typename T>
void RBTree<T>::_transplant(RBNode<T>* u, RBNode<T>* v)
{
	if (u->parent == nullptr) topNode = v;
	else if (u == u->parent->left) u->parent->left = v;
	else u->parent->right = v;
	v->parent = u->parent;
}

template<typename T>
RBNode<T>* RBTree<T>::_min(RBNode<T>* x) const
{
	if (x == nullptr) return nullptr;
	while (x->left != nullptr) x = x->left;
	return x;
}

template<typename T>
inline RBNode<T>* RBTree<T>::_max(RBNode<T>* x) const
{
	if (x == nullptr) return nullptr;
	while (x->right != nullptr) x = x->right;
	return x;
}

template<typename T>
void RBTree<T>::insert(T key)
{
	RBNode<T>* node = new RBNode<T>(key, nullptr, nullptr, nullptr, Red);
	RBNode<T>* y = nullptr;
	RBNode<T>* temp = topNode;

	while (temp != nullptr)
	{
		y = temp;
		if (node->key < temp->key) temp = temp->left;
		else if (node->key == temp->key) { delete node; return; } //delete duplicates
		else temp = temp->right;
	}
	node->parent = y;
	if (y == nullptr) topNode = node;
	else if (node->key < y->key) y->left = node;
	else y->right = node;

	sizeTree++;
	_insert(node);
}

template<typename T>
void RBTree<T>::remove(T key)
{
	RBNode<T>* node = find(key);
	if (node != nullptr) remove(node);
}

template<typename T>
void RBTree<T>::remove(RBNode<T>* node)
{
	RBNode<T>* child, * parent;
	RBColor color;
	if (node->left != NULL && node->right != NULL)
	{
		RBNode<T>* replace = node;
		replace = node->right;
		while (replace->left != NULL)
		{
			replace = replace->left;
		}
		if (node->parent != NULL)
		{
			if (node->parent->left == node)
				node->parent->left = replace;
			else
				node->parent->right = replace;
		}
		
		else
			topNode = replace;
		child = replace->right;
		parent = replace->parent;
		color = replace->color;

		if (parent == node)
			parent = replace;
		else
		{
			if (child != NULL)
				child->parent = parent;
			parent->left = child;

			replace->right = node->right;
			node->right->parent = replace;
		}
		replace->parent = node->parent;
		replace->color = node->color;
		replace->left = node->left;
		node->left->parent = replace;
		if (color == Black)
			_remove(child);

		sizeTree--;
		delete node;
		return;
	}
	if (node->left != NULL)
		child = node->left;
	else
		child = node->right;

	parent = node->parent;
	color = node->color;
	if (child)
	{
		child->parent = parent;
	}
	if (parent)
	{
		if (node == parent->left)
			parent->left = child;
		else
			parent->right = child;
	}
	else
		topNode = child;

	if (color == Black)
	{
		_remove(child);
	}
	sizeTree--;
	delete node;
}

template<typename T>
void RBTree<T>::print() const
{
	_print(topNode);
}

template<typename T>
inline int RBTree<T>::size() const
{
	return sizeTree;
}

template<typename T>
bool RBTree<T>::contains(T key) const
{
	RBNode<T>* curr = topNode;
	while (1)
	{
		if (curr == nullptr) return 0;
		if (curr->key > key) curr = curr->left;
		else if (curr->key == key) return 1;
		else curr = curr->right;
	}
}

template<typename T>
RBNode<T>* RBTree<T>::find(T key)
{
	RBNode<T>* curr = topNode;
	while (1)
	{
		if (curr == nullptr) return nullptr;
		if (curr->key > key) curr = curr->left;
		else if (curr->key == key) return curr;
		else curr = curr->right;
	}
}

template<typename T>
int RBTree<T>::get_height(T key) const
{
	RBNode<T>* curr = topNode;
	int height = 0;
	while (1)
	{
		if (curr == nullptr) return 0;
		if (curr->key > key) curr = curr->left;
		else if (curr->key == key) return height;
		else curr = curr->right;
		height++;
	}
}

template<typename T>
void RBTree<T>::_print(RBNode<T> const *x) const
{
	if (x == nullptr) return;
	_print(x->left);
	std::cout << x->key << " ";
	_print(x->right);
}

template<typename T>
void RBTree<T>::_insert(RBNode<T>* x)
{
	while (x != topNode && x->parent->color == Red)
	{
		if (x->parent == x->parent->parent->left) {
			RBNode<T>* y = x->parent->parent->right;
			if (y != nullptr && y->color == Red) {
				x->parent->color = Black;
				y->color = Black;
				x->parent->parent->color = Red;
				x = x->parent->parent;
			}
			else
			{
				if (x == x->parent->right) {
					x = x->parent;
					_left_rotate(x);
				}
				x->parent->color = Black;
				x->parent->parent->color = Red;
				_right_rotate(x->parent->parent);
			}
		}
		else
		{
			RBNode<T>* y = x->parent->parent->left;
			if (y!=nullptr && y->color == Red) {
				x->parent->color = Black;
				y->color = Black;
				x->parent->parent->color = Red;
				x = x->parent->parent;
			}
			else
			{
				if (x == x->parent->left) {
					x = x->parent;
					_right_rotate(x);
				}
				x->parent->color = Black;
				x->parent->parent->color = Red;
				_left_rotate(x->parent->parent);
			}
		}
	}
	topNode->color = Black;
}

template<typename T>
void RBTree<T>::_remove(RBNode<T>* x)
{
	RBNode<T>* w = nullptr;
	bool q = 0;
	//while (x!=nullptr || x!=topNode && (x != nullptr && x->color == Black))
	while (x!=nullptr && x!=topNode && x->color == Black)
	{
		if (x == x->parent->left) {
			w = x->parent->right;
			if (!w) break;
			//if (w == nullptr) w = x->parent->left;
			if (w->color == Red) {
				w->color = Black;
				x->parent->color = Red;
				_left_rotate(x->parent);
				w = x->parent->right;
				//if (w == nullptr) w = x->parent->left;
			}
			if (!w) break;
			if ((!w->left || w->left->color == Black) && (!w->right|| w->right->color == Black)) {
				w->color = Red;
				x = x->parent;
			}
			else {
				if (!w->right || w->right->color == Black) {
					if(w->left)
					w->left->color = Black;
					w->color = Red;
					_right_rotate(w);
					w = x->parent->right;
				}
				w->color = x->parent->color;
				x->parent->color = Black;
				if (w->left != nullptr)
				w->right->color = Black;
				_left_rotate(x->parent);
				x = topNode;
			}

			/*if (w->left == nullptr || w->right == nullptr) {
				//q = 1;
				if (w->left == nullptr && w->right == nullptr) q = 1;
				else if (w->left == nullptr && w->right->color == Black) q = 1;
				else if (w->right == nullptr && w->left->color == Black) q = 1;
				else w->color = Red;
				if (q) {
					w->color = Red;
					x = x->parent;
					q = 0;
				}
			}
			else */ /**/

		}
		else {
			w = x->parent->left;
			if (!w) break;
			//if (w == nullptr) w = x->parent->right;
			if (w->color == Red) {
				w->color = Black;
				x->parent->color = Red;
				_right_rotate(x->parent);
				w = x->parent->left;
				//if (w == nullptr) w = x->parent->right;
			}
			if (!w) break;

			/*if (w->left == nullptr || w->right == nullptr) {
				//q = 1;
				if (w->left == nullptr && w->right == nullptr) q = 1;
				else if (w->left == nullptr && w->right->color == Black) q = 1;
				else if (w->right == nullptr && w->left->color == Black) q = 1;
				else w->color = Red;
				if (q) {
					w->color = Red;
					x = x->parent;
					q = 0;
				}
			}
			else */if ((!w->left || w->left->color == Black) && (!w->right || w->right->color == Black)) {
				w->color = Red;
				x = x->parent;
			}

			else {
				if (!w->left || w->left->color == Black) {
					w->right->color = Black;
					w->color = Red;
					_left_rotate(w);
					w = x->parent->left;
				}
				w->color = x->parent->color;
				x->parent->color = Black;
				if(w->left!=nullptr)
				w->left->color = Black;
				_right_rotate(x->parent);
				x = topNode;
			}
		}
	}
	if(x) x->color = Black;
}

template<typename T>
void RBTree<T>::_destroy(RBNode<T>* x) {
	if (x == nullptr) return;
	_destroy(x->left);
	_destroy(x->right);
	delete x;
	x = nullptr;
}

template<typename T>
RBNode<T>* RBTree<T>::_copy(RBNode<T> const *x, RBNode<T> const *parent)
{
	if (x == nullptr) return nullptr;
	RBNode<T>* newNode = new RBNode<T>(*x);
	newNode->parent = const_cast<RBNode<T>*>(parent);
	newNode->left = _copy(x->left, newNode);
	newNode->right = _copy(x->right, newNode);
	return newNode;
}

template<typename T>
RBTree<T>::iterator::iterator(RBNode<T>* ptr):ptr(ptr) {}

template<typename T>
RBNode<T>& RBTree<T>::iterator::operator*() const
{
	return *ptr;
}

template<typename T>
RBNode<T>* RBTree<T>::iterator::operator->()
{
	return ptr;
}

template<typename T>
RBNode<T>& RBTree<T>::iterator::operator=(RBNode<T>* ptr)
{
	this->ptr = ptr;
	return *this;
}

template<typename T>
typename RBTree<T>::iterator* RBTree<T>::iterator::operator++()
{
	if (ptr->right) {
		ptr = ptr->right;
		while (ptr->left)
		{
			ptr = ptr->left;
		}
	}
	else if (ptr->parent) {
		if (ptr == ptr->parent->left) {
			ptr = ptr->parent;
		}
		else {
			while (ptr->parent->right == ptr)
			{
				ptr = ptr->parent;
				if (!ptr->parent) {
					ptr = nullptr;
					return this;
				}
			}
			if (ptr->parent) ptr = ptr->parent;
		}
	}
	return this;
}

template<typename T>
typename RBTree<T>::iterator RBTree<T>::iterator::operator++(int)
{
	iterator tmp = *this; 
	++(*this); 
	return tmp;
}

template<typename T>
typename RBTree<T>::iterator* RBTree<T>::iterator::operator--()
{
	if (ptr->left) {
		ptr = ptr->left;
		while (ptr->right)
		{
			ptr = ptr->right;
		}
	}
	else if (ptr->parent) {
		if (ptr == ptr->parent->right) {
			ptr = ptr->parent;
		}
		else {
			while (ptr->parent->left == ptr)
			{
				ptr = ptr->parent;
				if (!ptr->parent) {
					ptr = nullptr;
					return this;
				}
			}
			if (ptr->parent) ptr = ptr->parent;
		}
	}
	return this;
}

template<typename T>
typename RBTree<T>::iterator RBTree<T>::iterator::operator--(int)
{
	iterator tmp = *this;
	--(*this);
	return tmp;
}
