

#include "BST.hpp"
#include "TNode.hpp"

BST::BST() {
	root = NULL;
}
BST::BST(string s) {
	root = new TNode(s);
}

/*
 * insert: inserts a node
 */
bool BST::insert(string s){
		TNode *newnode = new TNode(s);
		TNode *temp = root;
		TNode * y = NULL;

	    while (temp != NULL) {
	        y = temp;
	        if (s < temp->data->phrase){
	            temp = temp->left;
	        }else if(s > temp->data->phrase){
	            temp = temp->right;
	        }else{
	        	return true; //when its already in
	        }
	    }
	    if (y == NULL){
	    	//setHeight(y);
	        root = newnode;
	        return true;
	    }else if (s < y->data->phrase){
	        y->left = newnode;
	    	newnode->parent = y;
	    	  setHeight(y->left);
	    	return true;
	    }else if(s > y->data->phrase) {
	        y->right = newnode;
	    	newnode->parent =  y;
	    	  setHeight(y->right);
	    	return true;
	    }else{
	    	return false;
	    }

}

/*
 * find: finds a node
 */
TNode * BST::find(string s){
		TNode *temp = root;
		TNode* y = NULL;

	    while (temp != NULL) {
	        y = temp;
	        if(s == temp->data->phrase ){
	        	return temp;
	        }else if (s < temp->data->phrase){
	            temp = temp->left;
	        }else if (s > temp->data->phrase){
	            temp = temp->right;
	        }
	    }
	    if (s == y->data->phrase){
	        return y;
	    }else{
	    	return NULL;
	    }

}


/*
 * printNode: this was a helper function for debugging the code
 */
void BST::printNode(string s){
	TNode * Garbage = find(s);
	cout << Garbage->data->phrase << endl;
	cout << Garbage->left->data->phrase << endl;
	cout << Garbage->right->data->phrase << endl;


}


/*
 * remove: removes a node from the tree
 */
TNode * BST::remove(string s){
	TNode *temp = root;
	 temp = find(s);
	 if (temp == NULL){
		return temp;
	 }else {
		if (temp->left == NULL && temp->right == NULL) {
			//Heights of Tree changes by one
			//Removes node with no children
			return removeNoKids(temp);
		} else if (temp->left == NULL && temp->right != NULL) {
			//Removing node with child
			return removeOneKid(temp, false);
		} else if (temp->right == NULL && temp->left != NULL) {
			//Removing node with child
			return removeOneKid(temp, true);
		} else {

			TNode *farRight = temp->left;
			TNode * Goodbye = temp;
			//iterate through the right most
			while (farRight->right != NULL) {
				farRight = farRight->right;
			}

			if (temp->parent == NULL && farRight == temp->left) {
				//SPEACIAL CASE: Removing Root, FarRight is Temp's left child
					farRight->right = temp->right;
					root = farRight;
					if(temp->height > root->height){
						root->height = temp->height;
					}
					delete temp;
					return Goodbye;

			}else if (farRight->left == NULL && farRight->right == NULL) {
				//Has no children
				//FarRight Replaces Temp and is deleted
				temp->data = farRight->data;
				setHeight(farRight);
				return removeNoKids(farRight);

			} else if (farRight->left == NULL && farRight->right != NULL) {
				//Has no children
				//FarRight Replaces Temp and is deleted
				temp->data = farRight->data;
				setHeight(farRight);
				return removeOneKid(farRight, false);

			} else if (farRight->right == NULL && farRight->left != NULL) {
				//Has no children
				//FarRight Replaces Temp and is deleted
				temp->data = farRight->data;
				setHeight(farRight);
				return removeOneKid(farRight, true);

			}

			//NEVER REACH THIS (GET RID OF WARNING)
			delete temp;
			return Goodbye;

		}

	}


}

/*
 * removeNoKids: helper function to remove(node with no kids)
 */
TNode * BST::removeNoKids(TNode *tmp){
	if(tmp == root){
		//Remove Root
	}else{
		if(tmp->parent->left == tmp){
			//Making it null
			//Re-evaluate Height
			tmp->parent->left = NULL;
			setHeight(tmp->parent);
		}else{
			//Making it null
			//Re-evaluate Height
			tmp->parent->right = NULL;
			setHeight(tmp->parent);

		}
	}
	TNode * Goodbye = tmp;
	delete tmp;
	return Goodbye;
}


/*
 * removeOneKid: helper function to remove(node with one kid)
 */
TNode *BST::removeOneKid(TNode *tmp, bool leftFlag){
	TNode * Goodbye = tmp;
	if(tmp == root){
		if(leftFlag == false){
			//Height won't change for other nodes
			root = tmp->right;
		}else{
			//Height won't change  for other nodes
			root = tmp->left;

		}
	}else{
		if(tmp->parent->left == tmp){
			if(leftFlag == false){
				//Skipping Node
				tmp->parent->left = tmp->right;
				tmp->right->parent = tmp->parent;
				//Re-evaluate Height
				setHeight(tmp->right);
				delete tmp;
				return Goodbye;
			}else{
				//Skipping Node
				tmp->parent->left = tmp->left;
				tmp->left->parent = tmp->parent;
				//Re-evaluate Height
				setHeight(tmp->left);
				delete tmp;
				return Goodbye;
			}
		}else{
			if (leftFlag == false) {
				//Skipping Node
				tmp->parent->right = tmp->right;
				tmp->right->parent = tmp->parent;
				//Re-evaluate Height
				setHeight(tmp->right);
				delete tmp;
				return Goodbye;
			} else {
				//Skipping Node
				tmp->parent->right = tmp->left;
				tmp->left->parent = tmp->parent;
				//Re-evaluate Height
				setHeight(tmp->left);
				delete tmp;
				return Goodbye;
			}

		}
	}
	delete tmp;
	return Goodbye;

}


/*
 * setHeight: sets the height of the node and goes up the tree
 */
void BST::setHeight(TNode *n) {
	int count = n->height;
	//Checking if the input node is being inserted
	if (n->left == NULL && n->right == NULL) {
		n->height = 1;
		count = 1;
	}

	while (n->parent != NULL) {
		//If the parent has two nodes, Take the highest height among the nodes and add 1
		if ((n->parent->right == n && n->parent->left != NULL)|| (n->parent->left == n && n->parent->right != NULL)) {

			//Right Child > Left Child
			if (n->parent->right->height > n->parent->left->height) {
				n->parent->height = n->parent->right->height + 1;
				count = n->parent->height;


			//Left Child > Right Child
			} else if (n->parent->right->height < n->parent->left->height) {
				n->parent->height = n->parent->left->height + 1;
				count = n->parent->height;

			//Left Child == Right Child
			} else {
				n->parent->height = n->parent->left->height + 1;
				count = n->parent->height;

			}
			//break;

		}else{
			count++;
		}

		//Keep Going (Parents with a single child)
		n->parent->height = count;
		n = n->parent;

	}
}



//PRINTING FUNCTIONS
void BST::printTreeIO() {
	if (root == NULL ) {
		cout << "Empty Tree" << endl;
	}
	else {
		cout << endl<<"Printing In Order:" <<endl;
		printTreeIO(root->left);
		cout << root->data->phrase <<  ", " << root->height << endl;
		printTreeIO(root->right);

	}
}

void BST::printTreeIO(TNode *n) {
	if (n == NULL ) {
		//cout << "Empty Tree" << endl;
	}
	else {
		printTreeIO(n->left);
		cout << n->data->phrase<<  ", " << n->height << endl;
		printTreeIO(n->right);
	}
}



void BST::printTreePre() {
	if (root == NULL ) {
		cout << "Empty Tree" << endl;
	}
	else {
		cout << endl<<"Printing PreOrder:" <<endl;
		cout << root->data->phrase << ", " << root->height << endl;
		printTreePre(root->left);
		printTreePre(root->right);

	}
}

void BST::printTreePre(TNode *n) {
	if (n == NULL ) {
		//cout << "Empty Tree" << endl;
	}
	else {
		cout << n->data->phrase << " :" << n->height << endl;
		printTreePre(n->left);
		printTreePre(n->right);

	}
}

void BST::printTreePost() {
	if (root == NULL ) {
		cout << "Empty Tree" << endl;
	}
	else {
		cout << endl<<"Printing PostOrder:" <<endl;
		printTreePost(root->left);
		printTreePost(root->right);
		cout << root->data->phrase <<  ", " << root->height << endl;
	}
}

void BST::printTreePost(TNode *n) {
	if (n == NULL ) {
		//cout << "Empty Tree" << endl;
	}
	else {
		printTreePost(n->left);
		printTreePost(n->right);
		cout << n->data->phrase <<  ", " << n->height <<endl;
	}
}


void BST::clearTree() {
	if (root == NULL) {
		cout << "Tree already empty" << endl;
	}
	else {
		cout << endl << "Clearing Tree:" << endl;
		clearTree(root);
		root = NULL;
	}
}
void BST::clearTree(TNode *tmp) {
	if (tmp == NULL) {
		return;
	}
	else {
		clearTree(tmp->left);
		clearTree(tmp->right);
		tmp->printNode();
		delete(tmp);
	}
}











