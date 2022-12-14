
#ifndef TNODE_HPP_
#define TNODE_HPP_
#include <iostream>
#include "Phrase.hpp"
using namespace std;

class TNode{
	friend class BST;
	TNode *left;
	TNode *right;
	TNode *parent;
	Phrase *data;
	int height;
public:
	TNode(string s);
	TNode();
	~TNode();
	void printNode();
};



#endif /* TNODE_HPP_ */
