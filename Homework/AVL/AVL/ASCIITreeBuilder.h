#pragma once

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>

#define MAX_HEIGHT 1000
#define LABEL_SIZE 11

struct AsciiNode
{
	AsciiNode* _left, * _right;

	//length of the edge from this node to its children
	int edge_length;
	int height;
	int lablen;

	//-1=I am _left, 0=I am root, 1=_right   
	int parent_dir;

	//max supported unit32 in dec, 10 digits max
	char label[LABEL_SIZE];
};

template <typename T>
struct tree_node;

template <typename T>
class ASCIITreeBuilder
{
public:
	ASCIITreeBuilder(int spacing = 3);

	void print_ascii_tree(std::ostream& out, tree_node<T>* t);

private:
	AsciiNode* build_ascii_tree_recursive(tree_node<T>* t);
	AsciiNode* build_ascii_tree(tree_node<T>* t);
	void clear(AsciiNode* node);
	void compute_lprofile(AsciiNode* node, int x, int y);
	void compute_rprofile(AsciiNode* node, int x, int y);
	void compute_edge_lengths(AsciiNode* node);
	void print_level(std::ostream& out, AsciiNode* node, int x, int level);

	int lprofile[MAX_HEIGHT];
	int rprofile[MAX_HEIGHT];

	//adjust gap between _left and _right nodes
	int nodeSpacing;

	//used for printing next node in the same level, 
	//this is the x coordinate of the next char printed
	int print_next;
};

template<typename T>
inline ASCIITreeBuilder<T>::ASCIITreeBuilder(int spacing) :
	nodeSpacing(spacing)
{

}

template <typename T>
AsciiNode* ASCIITreeBuilder<T>::build_ascii_tree_recursive(tree_node<T>* t)
{
	if (!t) 
		return nullptr;

	AsciiNode* node = new AsciiNode();
	node->_left = build_ascii_tree_recursive(t->_left);
	node->_right = build_ascii_tree_recursive(t->_right);

	if (node->_left)
		node->_left->parent_dir = -1;

	if (node->_right)
		node->_right->parent_dir = 1;

	sprintf_s(node->label, LABEL_SIZE, "%d", t->_item);
	node->lablen = strlen(node->label);

	return node;
}


//Copy the tree into the ascii node structre
template <typename T>
AsciiNode* ASCIITreeBuilder<T>::build_ascii_tree(tree_node<T>* t)
{
	if (!t)
		return nullptr;

	AsciiNode* node = build_ascii_tree_recursive(t);
	node->parent_dir = 0;

	return node;
}

//Free all the nodes of the given tree
template <typename T>
void ASCIITreeBuilder<T>::clear(AsciiNode* node)
{
	if (!node) 
		return;

	clear(node->_left);
	clear(node->_right);
	
	delete node;
}

//The following function fills in the lprofile array for the given tree.
//It assumes that the center of the label of the root of this tree
//is located at a position (x,y).  It assumes that the edge_length
//fields have been computed for this tree.
template <typename T>
void ASCIITreeBuilder<T>::compute_lprofile(AsciiNode* node, int x, int y)
{
	if (!node) 
		return;

	int isleft = (node->parent_dir == -1);
	lprofile[y] = std::min(lprofile[y], x - ((node->lablen - isleft) / 2));

	if (node->_left)
		for (int i = 1; i <= node->edge_length && y + i < MAX_HEIGHT; ++i)
			lprofile[y + i] = std::min(lprofile[y + i], x - i);

	compute_lprofile(node->_left, x - node->edge_length - 1, y + node->edge_length + 1);
	compute_lprofile(node->_right, x + node->edge_length + 1, y + node->edge_length + 1);
}

template <typename T>
void ASCIITreeBuilder<T>::compute_rprofile(AsciiNode* node, int x, int y)
{
	if (!node) 
		return;

	int notleft = (node->parent_dir != -1);

	rprofile[y] = std::max(rprofile[y], x + ((node->lablen - notleft) / 2));
	
	if (node->_right)
		for (int i = 1; i <= node->edge_length && y + i < MAX_HEIGHT; ++i)
			rprofile[y + i] = std::max(rprofile[y + i], x + i);

	compute_rprofile(node->_left, x - node->edge_length - 1, y + node->edge_length + 1);
	compute_rprofile(node->_right, x + node->edge_length + 1, y + node->edge_length + 1);
}

//This function fills in the edge_length and 
//height fields of the specified tree
template <typename T>
void ASCIITreeBuilder<T>::compute_edge_lengths(AsciiNode* node)
{
	if (!node)
		return;

	int h, hmin, delta;

	compute_edge_lengths(node->_left);
	compute_edge_lengths(node->_right);

	/* first fill in the edge_length of node */
	if (!node->_right && !node->_left)
		node->edge_length = 0;
	else
	{
		if (node->_left)
		{
			for (int i = 0; i < node->_left->height && i < MAX_HEIGHT; ++i)
				rprofile[i] = -INFINITY;

			compute_rprofile(node->_left, 0, 0);
			hmin = node->_left->height;
		}
		else
			hmin = 0;

		if (node->_right)
		{
			for (int i = 0; i < node->_right->height && i < MAX_HEIGHT; ++i)
				lprofile[i] = INFINITY;

			compute_lprofile(node->_right, 0, 0);
			hmin = std::min(node->_right->height, hmin);
		}
		else
			hmin = 0;

		delta = 4;

		for (int i = 0; i < hmin; ++i)
			delta = std::max(delta, nodeSpacing + 1 + rprofile[i] - lprofile[i]);

		//If the node has two children of height 1, then we allow the
		//two leaves to be within 1, instead of 2 
		if (((node->_left && node->_left->height == 1) ||
			 (node->_right && node->_right->height == 1)) && delta > 4)
			--delta;

		node->edge_length = ((delta + 1) / 2) - 1;
	}

	//now fill in the height of node
	h = 1;

	if (node->_left)
		h = std::max(node->_left->height + node->edge_length + 1, h);
	if (node->_right)
		h = std::max(node->_right->height + node->edge_length + 1, h);
	
	node->height = h;
}

//This function prints the given level of the given tree, assuming
//that the node has the given x cordinate.
template <typename T>
void ASCIITreeBuilder<T>::print_level(std::ostream& out, AsciiNode* node, int x, int level)
{
	if (!node) 
		return;

	int isleft = (node->parent_dir == -1);
	int i;

	if (!level)
	{
		for (i = 0; i < (x - print_next - ((node->lablen - isleft) / 2)); ++i)
			out << " ";

		print_next += i;
		out << node->label;
		print_next += node->lablen;
	}
	else if (node->edge_length >= level)
	{
		if (node->_left)
		{
			for (i = 0; i < (x - print_next - (level)); ++i)
				out << " ";

			print_next += i;
			out << "/";
			++print_next;
		}

		if (node->_right)
		{
			for (i = 0; i < (x - print_next + (level)); ++i)
				out << " ";

			print_next += i;
			out << "\\";
			++print_next;
		}
	}
	else
	{
		print_level(out, node->_left,
					x - node->edge_length - 1,
					level - node->edge_length - 1);
		print_level(out, node->_right,
					x + node->edge_length + 1,
					level - node->edge_length - 1);
	}
}

//prints ascii tree for given Tree structure
template <typename T>
void ASCIITreeBuilder<T>::print_ascii_tree(std::ostream& out, tree_node<T>* t)
{
	if (!t)
		return;

	AsciiNode* proot = build_ascii_tree(t);
	compute_edge_lengths(proot);

	for (int i = 0; i < proot->height && i < MAX_HEIGHT; ++i)
		lprofile[i] = INFINITY;

	compute_lprofile(proot, 0, 0);
	int xmin = 0;

	for (int i = 0; i < proot->height && i < MAX_HEIGHT; ++i)
		xmin = std::min(xmin, lprofile[i]);

	for (int i = 0; i < proot->height; ++i)
	{
		print_next = 0;
		print_level(out, proot, -xmin, i);
		out << std::endl;
	}

	if (proot->height >= MAX_HEIGHT)
		out << "This tree is taller than " << MAX_HEIGHT << ", and may be drawn incorrectly." << std::endl;

	clear(proot);
}
