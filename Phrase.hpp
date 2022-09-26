
#ifndef PHRASE_HPP_
#define PHRASE_HPP_

#include <iostream>
using namespace std;

class Phrase{
	friend class TNode;
	friend class BST;
	string phrase;
public:
	Phrase(string s);
	Phrase();
};




#endif /* PHRASE_HPP_ */
