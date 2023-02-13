#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <cmath>

#include "Node.h"
#include "NoSuchItemException.h"

enum TraversalMethod {preorder, inorder, postorder};

template<class T>
class ScapegoatTree {
public: // DO NOT CHANGE THIS PART.
    ScapegoatTree();

    ScapegoatTree(const ScapegoatTree<T> &obj);

    ~ScapegoatTree();

    bool isEmpty() const;

    int getHeight() const;

    int getSize() const;

    bool insert(const T &element);

    bool remove(const T &element);

    void removeAllNodes();

    const T &get(const T &element) const;

    void print(TraversalMethod tp=inorder) const;

    void printPretty() const;

    ScapegoatTree<T> &operator=(const ScapegoatTree<T> &rhs);

    void balance();

    const T &getCeiling(const T &element) const;

    const T &getFloor(const T &element) const;

    const T &getMin() const;

    const T &getMax() const;

    const T &getNext(const T &element) const;

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.
    void print(Node<T> *node, TraversalMethod tp) const;
    void printPretty(Node<T> *node, int indentLevel, bool isLeftChild) const;

    int getHeight_helper(Node<T> *r) const;
    int getSize_helper(Node<T> *r) const;
    void insert_helper(Node<T> *node);


    bool search(Node<T>* r, const T &value) const;
    Node <T> *find_parent_node(Node<T>* r, Node<T>* node);

    Node<T> *operator_helper(Node<T> * &node,Node<T> * rhs) const;

    void sorting_array(Node<T> *r, T *&arr,  int &index);
    Node<T>* build_new_tree(T* arr, int min_index, int max_index);
    Node<T>* balance_helper(Node<T>* r);
    float calculate_log(int n);
    Node<T>* find_the_scapegoat(Node<T>*node);

    T get_min_and_max_helper(Node<T> *r, char tp) const;
    T getCeil_helper(Node<T>* node, Node<T>* &ceil, const T &element) const ;
    T getFloor_helper(Node<T>* node, Node<T>* &floor, const T &element) const ;
    void get_next_helper(Node<T>* node,  Node<T>* &ceil, T element) const;

    void make_empty(Node<T>* &t);
    void remove_helper(Node<T> * &r, const T &element);

private: // DO NOT CHANGE THIS PART.
    Node<T> *root;
    int upperBound;
};

#endif //TREE_H


/*
 * This function searches the given element starting from the given node r, then removes it by making necessary
 * pointer modifications and deallocating the memory.
 */
template<class T>
void ScapegoatTree<T>::remove_helper(Node<T> * &r, const T &element)
{
	if( r == NULL )
		return;
	// Item not found; do nothing
	if( element < r->element )
		remove_helper( r->left , element);

	else if( r->element < element )
		remove_helper(  r->right , element);

	else if( r->left != NULL && r->right != NULL ) // Two children
	{
		r->element = get_min_and_max_helper(r->left, 'g');
		remove_helper( r->left, r->element);
	}

	else
	{
		Node<T> *oldNode = r;
		r = ( r->left != NULL ) ? r->left : r->right;
		delete oldNode;
	}
}


/*
 * This function makes the subtree empty recursively starting from the given node t.
 */
template<class T>
void ScapegoatTree<T>::make_empty(Node<T>* &t)
{
	if( t != NULL)
	{
		make_empty( t->left );
		make_empty( t->right );
		delete t;
	}
	t = NULL;
}

/*
 * This is the default constructor. You should make initializations in this function.
 */
template<class T>
ScapegoatTree<T>::ScapegoatTree() {
	root=NULL;
	upperBound=0;
}

/*
 * This is a helper function for operator= . This function copies rhs node.
 */
template<class T>
Node<T> * ScapegoatTree<T>::operator_helper(Node<T> * &node, Node<T> * rhs) const{

    //if copied node is NULL
    if(rhs==NULL)
	{
		node=NULL;
		return node;
	}

    //if rhs node is not null, it creates a new node by allocating the memory, then it copies
    // rhs left and then right subtree recursively, and return the node.
	Node<T> *copied_node=new Node<T>(rhs->element, NULL, NULL);
	operator_helper(copied_node->left, rhs->left);
	operator_helper(copied_node->right, rhs->right);
	node=copied_node;
	return node;
}

/*
 * This is the copy constructor. It creates new nodes by copying the nodes of the given obj,
 * and insert those new nodes into this scapegoat tree. The structure among
the nodes of the given obj should also be copied to this scapegoat tree.
 */
template<class T>
ScapegoatTree<T>::ScapegoatTree(const ScapegoatTree<T> &obj) {
	upperBound=obj.upperBound;
	root=NULL;

    //calling operator =
	*this=obj;
}


/*
 * This is the destructor. It deallocate all the memory that you were allocated before.
 */
template<class T>
ScapegoatTree<T>::~ScapegoatTree() {
    // deallocates all the memory including the root
	removeAllNodes();
	delete root;
	upperBound=0;
}


/*
 * This function should return true if this scapegoat tree is empty.
 * If this scapegoat tree is not empty, it should return false.
 */
template<class T>
bool ScapegoatTree<T>::isEmpty() const {

    if(root==NULL)
        return true;

    return false;
}

/*
 * This function is the helper of getHeight function. It starts counting from -1 because if the tree is empty
 * height will be -1, if there is only root, then the height will be 0 and so on. First, this function
 * calculates the right subtree's height, then it calculates left subtree's height. Then it takes the max of these
 */
template<class T>
int ScapegoatTree<T>::getHeight_helper(Node<T> *r) const
{
    int h = -1;
    if(r != NULL)
    {
        int right_h = getHeight_helper(r->right);
        int left_h = getHeight_helper(r->left);

        int max_h = 0;
        if(left_h>=right_h)
        {
            max_h=left_h;
        }
        else
            max_h=right_h;

        h = max_h + 1;
    }
    return h;
}

/*
 * This function should return an integer that is the largest number of edges from the root to the most
distant leaf node in this scapegoat tree. It calls the helper 'getHeight_helper'.
 */
template<class T>
int ScapegoatTree<T>::getHeight() const {
    return getHeight_helper(root);
}

/*
 * This function is the helper of getSize function. This function calculates the left subtrees size
 * and then right subtrees size recursively.
 */
template<class T>
int ScapegoatTree<T>::getSize_helper(Node<T> *r) const {

    if (r == NULL)
        return 0;
    else
        return(getSize_helper(r->left) + 1 + getSize_helper(r->right));
}

/*
 * This function should return an integer that is the number of nodes in this scapegoat tree.
 *  It calls the helper 'getSize_helper'.
 */
template<class T>
int ScapegoatTree<T>::getSize() const {
    return getSize_helper(root);
}

/*
 * This function checks if there exists a node with the given value starting from the root recursively.
 * Since scapegoat tree is a BST tree, if the given value is less than the node r, it searches the left
 * subtree of r. If the given value is found it returns true.
 */
template<class T>
bool ScapegoatTree<T>::search(Node<T>* r, const T &value) const
{
	if (r == NULL)
        return false;

    //if there exist a node with given value, it returns true.
	if (r->element == value)
	{
		return true;
	}

    //if the given value is less than the r's value, it will search the left subtree
    else if(r->element > value)
    {
	    bool left = search(r->left, value);
    	if(left)
    	{
    		return true;
    	}
    }

    //if the given value is larger than the r's value, it will search the right subtree
    if(r->element< value)
    {
	    bool right = search(r->right, value);
        if(right)
    	{
    	    return right;
    	}
    }    

    //if the value is not found it will return false
    return false;
}

/*
 * This function will return the given node's parent starting from the root. It there is not such a node in
 * the tree or the given node is the root itself, it will return NULL.
 */
template<class T>
Node <T> *ScapegoatTree<T>::find_parent_node(Node<T>* r, Node<T> *node)
{
	if (r != NULL && node != NULL)
	{
		if(r->left != NULL && r->left->element == node->element)
			return r;


		else if(r->right != NULL && r->right->element == node->element)
		{
			return r;
		}

		else if(r->element > node->element)
		{
			return find_parent_node(r->left,node);
		}

		else if(r->element < node->element)
		{
			return find_parent_node(r->right,node);
		}
	}
	return NULL;
}

/*
 * It sorts the given array in the ascending order recursively.
 */
template<class T>
void ScapegoatTree<T>::sorting_array(Node<T> *r, T *&arr,  int &index)
{
	if (r != NULL)
	{
		sorting_array(r->left, arr, index);
		arr[index]=r->element;

		index++;
		sorting_array(r->right, arr, index);
	}
}


/*
 * This is a helper for function for balance_helper. It builds the new balanced tree by using the sorted array.
• Start from the entire array (for example, [1, 3, 5, 7, 9] ),
• Pick the middle element to make it a tree node (5 ),
• Recurse on the left subarray ([1, 3] ),
• Recurse on the right subarray ([7, 9] ).
 Then it returns the root of the balanced tree.
 */
template<class T>
Node<T>* ScapegoatTree<T>::build_new_tree(T* arr, int min_index, int max_index)
{
	int mid_index = min_index + (max_index - min_index)/2;
	Node<T> *new_node = new Node<T>(arr[mid_index],NULL,NULL);
	new_node->left = NULL;
	new_node->right = NULL;
	if (min_index < mid_index)
	{
		new_node->left = build_new_tree(arr, min_index, mid_index-1);
	}
	if (mid_index < max_index)
	{
		new_node->right = build_new_tree(arr, mid_index+1, max_index);
	}
	return new_node;
}



/*
 * This function is a helper for balance(). It takes root as an argument, balances the tree applying the following steps:
 * 1) Output the elements of the tree into an array in sorted (ascending) order by calling sorting_array function
 * 2) Build a new balanced binary search tree from the sorted array using the technique similar to a
binary search:
• Start from the entire array (for example, [1, 3, 5, 7, 9] ),
• Pick the middle element to make it a tree node (5 ),
• Recurse on the left subarray ([1, 3] ),
• Recurse on the right subarray ([7, 9] ).
 */
template<class T>
Node<T>* ScapegoatTree<T>::balance_helper(Node<T>* r) {
    
		int number = getSize_helper(r);

        //if the tree is not empty
		if(number > 0)
		{
            //allocate memory for the array
			T *sorted_array=new T[number];

            //calling sorting_array to sort the elements of the tree.
			int a=0;
			sorting_array(r, sorted_array, a);
            
            //deallocate the memory in order to build the new balanced tree.
			make_empty(r);

            
            //create the new tree by calling build_new_tree function
			Node<T>* balanced_root = build_new_tree(sorted_array, 0, number-1);

            //deallocate the memory of array
			delete [] sorted_array;

            //return the root of the balanced tree.
			return balanced_root;
		}
		return NULL;
}


/*
 * This function manually balances this scapegoat tree. It rebuilds the entire tree into a balanced binary
search tree by calling balance_helper.
 */
template<class T>
void ScapegoatTree<T>::balance() {
	root = balance_helper(root);
}

template<class T>
void ScapegoatTree<T>::insert_helper(Node<T> *node){
	Node<T> *temp=root;
	if(temp==NULL)
	{
		root=node;
		return ;
	}

	bool inserted=false;

    //iterate until the given node is inserted to appropriate location.
	while(!inserted)
	{
		if(node->element < temp->element)
		{
			if(temp->left==NULL)
			{
				temp->left=node;
				inserted=true;
			}
			else{
				temp=temp->left;
			}
		}
		else if(node->element > temp->element)
		{
			if(temp->right == NULL)
			{
				temp->right=node;
				inserted=true;
			}
			else{
				temp=temp->right;
			}
		}
		else
            return;


	}

}

/*
 * This is a helper function of insert. It checks the height condition of scapegoat tree after a new node is inserted.
 */
template<class T>
float ScapegoatTree<T>::calculate_log(int n){
	float first = log10(n);
	float second = log10(((float)3)/2);
	return first/second;
}



/*
 * This is a helper function. It finds which node is the scapegoat starting from the newly inserted
 * node and follow its parents back towards the root to find a scapegoat. The scapegoat is the first node
 * (on the path from the newly inserted node towards the root) that satisfies
 * sizeOf Subtree(scapegoat.child)/sizeOf Subtree(scapegoat) > (2/3)
 */
template<class T>
Node<T>* ScapegoatTree<T>::find_the_scapegoat(Node<T>*node)
{
	Node<T>* parent_of_node=find_parent_node(root, node);
	int p_size=getSize_helper(parent_of_node);
	int node_size=getSize_helper(node);
	
	if(node_size*3 > p_size*2)
	{
		return parent_of_node;
	}

	return find_the_scapegoat(parent_of_node);
}

/*
 * This function creates a new node with the given element and insert it at the appropriate location in
 * this scapegoat tree and return true. If there already exists a node with the given element in this
 * scapegoat tree, this function should do nothing but return false.
 */
template<class T>
bool ScapegoatTree<T>::insert(const T &element) {

    //check if the element exists in the tree by calling search function
	bool is_exists = this->search(root, element);

    //if there is no such node with the given element in the tree, insert the element.
	if (!is_exists)
	{
		Node<T> *new_node=new Node<T>(element, NULL,NULL);
		insert_helper(new_node); //insert the new_node to the appropriate location
		int height = this->getHeight();
		upperBound++;

        /*
         * After inserting the new node at the appropriate location, check the height condition (2) of the
         * scapegoat tree. If the height condition is not violated, you should do nothing. If it is
         * violated, you should find a scapegoat and the scapegoat node's parent node and rebuild
         * the subtree rooted at the scapegoat. Finding scapegoat's parent node is needed to make necessary
         * pointer modifications
         */
		if (height > calculate_log(upperBound)) //check the height condition
		{
            //calling helper function to find the scapegoat
			Node<T>* scapegoat = find_the_scapegoat(new_node);

            //calling helper function to find the parent node of scapegoat
			Node<T>* scapegoat_parent = find_parent_node(root, scapegoat);
			if (scapegoat_parent->left == scapegoat)
			{
                //balance the subtree that starts with scapegoat
				scapegoat_parent->left = balance_helper(scapegoat);
			}
			if (scapegoat_parent->right == scapegoat)
			{
                //balance the subtree that starts with scapegoat
				scapegoat_parent->right = balance_helper(scapegoat);
			}
		}
		return true;

	}
	return false;

}

/*
 * This function removes the node with the given element from this scapegoat tree and return true.
 * If there exists no such node in this scapegoat tree, this function should return false. There will be
 * no duplicated elements in the scapegoat tree. After removing the node from the scapegoat tree,
 * it checks the upper bound condition (1) of the scapegoat tree. At removal, you should not change
 * the upper bound. If the upper bound condition is not violated, you should do nothing. If it is violated,
 * you should rebuild the entire tree into a balanced binary search tree and reset upper bound to the
 * number of nodes.
 */
template<class T>
bool ScapegoatTree<T>::remove(const T &element) {

	if(search(root, element)) //searching the tree if the given element exists
	{
        //remove the node
		remove_helper(root,element);

        //after removal, if the tree is not empty, check the upper bound condition
		if(root)
		{
            //if the upper-bound condition is not violated, do nothing
			if(((float)upperBound/2 <= getSize() && getSize()<=upperBound)|| getSize()==1)
			{
				;
			}
			else{
				balance(); //balance the entire tree
				upperBound=getSize(); //reset the upper-bound
			}
		}

		return true;
	}
	return false;
}

/*
 * This function removes all nodes of this scapegoat tree so that the scapegoat tree becomes empty.
 */
template<class T>
void ScapegoatTree<T>::removeAllNodes() {

    make_empty(root);
}



/*
 * This function searches this scapegoat tree for the node that has the same element with the given element
and return the element of that node. If there exists no such node in this scapegoat tree, this function
should throw NoSuchItemException.
 */
template<class T>
const T &ScapegoatTree<T>::get(const T &element) const {

    //if the tree is empty, throw an exception
    if(root==NULL)
        throw NoSuchItemException();


    //search the tree by calling get_helper. If the element is not in the tree, throw an exception
    if(!search(root, element))
        throw NoSuchItemException();


    //if the given element exists in the tree, return the element
    return element;
}

/*
 * Given a traversal method (inorder, preorder or postorder) as parameter (namely tp), this function
prints this scapegoat tree by traversing its nodes accordingly.
 */
template<class T>
void ScapegoatTree<T>::print(TraversalMethod tp) const {

    if (tp == preorder) {
    	 if (isEmpty())
    	 {
    	    // the tree is empty.
			std::cout << "BST_preorder{}" << std::endl;
			return;
    	 }
    	 std::cout << "BST_preorder{" << std::endl;
		 print(root, tp);
		 std::cout << std::endl << "}" << std::endl;
    }
    else if (tp == inorder) {
        // check if the tree is empty?
        if (isEmpty()) {
            // the tree is empty.
            std::cout << "BST_inorder{}" << std::endl;
            return;
        }

        // the tree is not empty.

        // recursively output the tree.
        std::cout << "BST_inorder{" << std::endl;
        print(root, tp);
        std::cout << std::endl << "}" << std::endl;
    }
    else if (tp == postorder) {
    	if (isEmpty())
		 {
			// the tree is empty.
			std::cout << "BST_postorder{}" << std::endl;
			return;
		 }
    	std::cout << "BST_postorder{" << std::endl;
		print(root, tp);
		std::cout << std::endl << "}" << std::endl;

    }
}


/*
 * This is a helper function for print.
 */
template<class T>
void ScapegoatTree<T>::print(Node<T> *node, TraversalMethod tp) const {

    if (tp == preorder)
    {
    	if (node == NULL)
    	        return;


	    std::cout << "\t" << node->element;


        if (node->left) {
            std::cout << "," << std::endl;
        }
        print(node->left, preorder);

        if (node->right)
        {
                std::cout << "," << std::endl;
        }
        print(node->right, preorder);
    }

    else if (tp == inorder) {
        // check if the node is NULL?
        if (node == NULL)
          return;

        // first, output left subtree and comma (if needed).
        print(node->left, inorder);

        if (node->left) {
            std::cout << "," << std::endl;
        }

        // then, output the node.
        std::cout << "\t" << node->element;

        // finally, output comma (if needed) and the right subtree.
        if (node->right) {
            std::cout << "," << std::endl;
        }
        print(node->right, inorder);
    }
    else if (tp == postorder) {
    	if (node == NULL)
    	        return;

    	    // first recur on left subtree
        print(node->left, postorder);

        if (node->left) {
            std::cout << "," << std::endl;
        }

        print(node->right, postorder);
        if (node->right) {
            std::cout << "," << std::endl;
        }


    	std::cout << "\t" << node->element;
    }
}

template<class T>
void ScapegoatTree<T>::printPretty() const {

    // check if the tree is empty?
    if (isEmpty()) {
        std::cout << "BST_pretty{}" << std::endl;
        return;
    }

    // the tree is not empty.

    // recursively output the tree.
    std::cout << "BST_pretty{" << std::endl;
    printPretty(root, 0, false);
    std::cout << "}" << std::endl;

}

template<class T>
void ScapegoatTree<T>::printPretty(Node<T> *node, int indentLevel, bool isLeftChild) const {

    // check if the node is NULL?
    if (node == NULL)
        return;

    // output the indentation and the node.
    std::cout << "\t";
    for (int i = 0; i < indentLevel; ++i) {
        std::cout << "---";
    }
    std::cout << (indentLevel == 0 ? "root:" : (isLeftChild ? "l:" : "r:")) << node->element << std::endl;

    // first, output left subtree with one more indentation level.
    printPretty(node->left, indentLevel + 1, true);

    // then, output right subtree with one more indentation level.
    printPretty(node->right, indentLevel + 1, false);
}


/*
 * This is the overloaded assignment operator. Firstly, it removes all nodes of this scapegoat tree and
then, you should create new nodes by copying the nodes of the given rhs and insert those new nodes
into this scapegoat tree.
 */
template<class T>
ScapegoatTree<T> &ScapegoatTree<T>::operator=(const ScapegoatTree<T> &rhs) {
	if(this != &rhs)
	{
		if(rhs.root == NULL)
		{
			this->removeAllNodes();
			this->root = NULL;
			this->upperBound=rhs.upperBound;
		}
		else
		{
			this->upperBound=rhs.upperBound;
			this->removeAllNodes();
			operator_helper(root, rhs.root);
		}
	}
	return *this;
}



/*
 * This is a helper function of getCeiling. It searches the ceil element of the given element iteratively
 * and updates the ceil by using call by reference method.
 */
template<class T>
T ScapegoatTree<T>::getCeil_helper(Node<T>* node, Node<T>* &ceil, const T &element) const {
	 while (node)
	{
		if (element < node->element)
		{
			ceil = node;
			node = node->left;
		}

		else if (node->element == element)
		{
			 ceil = node;
			 break;
		}

		else {
			node = node->right;
		}
	}
}


/*
 * This function returns the element of a node which is associated with the least element greater than or equal
 * to the given element and return the element of that node. If there exists no such node in this
 * scapegoat tree, it throws NoSuchItemException.
 */
template<class T>
const T &ScapegoatTree<T>::getCeiling(const T &element) const {

	if(root==NULL) //if the tree is empty
        throw NoSuchItemException();

    //if the element is the greatest element in the tree
	if(element > get_min_and_max_helper(root, 'g'))
		throw NoSuchItemException();


	Node<T> *ceil = NULL;
	getCeil_helper(root, ceil, element);
	return ceil->element;
}



/*
 * This is a helper function of getFloor. It searches the floor element of the given element iteratively
 * and updates the floor by using call by reference method.
 */
template<class T>
T ScapegoatTree<T>::getFloor_helper(Node<T>* node, Node<T>* &floor,const T &element) const {
	 while (node)
	{
		if (node->element == element)
		{
			 floor = node;
			 break;

		}
		else if (element < node->element)
        {
            node = node->left;
        }
		else //if(element > node->element)
		{
			floor=node;
			node = node->right;
		}
	}
}



/*
 * This function returns the element of a node which is associated with the greatest element less than or equal
 * to the given element and return the element of that node. If there exists no such node in this
 * scapegoat tree, it throws NoSuchItemException.
 */
template<class T>
const T &ScapegoatTree<T>::getFloor(const T &element) const {

	if(root==NULL)
		throw NoSuchItemException();

    //if the given element is the least element in the tree
	if(element < get_min_and_max_helper(root, 'g'))
		throw NoSuchItemException();

	Node<T> *floor = NULL;
	getFloor_helper(root, floor, element);
	return floor->element;
}


/*
 * This is a helper function that finds the greatest or least element in the tree. Char tp is to
 * decide whether it finds the greatest or the least value.
 */
template<class T>
T ScapegoatTree<T>::get_min_and_max_helper(Node<T> *r, char tp) const {
	Node<T>* current = r;

	while(r)
	{
		if(tp== 'l')
		{
			while (current->left != NULL)
			{
				current = current->left;
			}
			return (current->element);

		}
		else if (tp=='g')
		{
			while (current->right != NULL) {
					current = current->right;
				}
			return (current->element);
		}

	}
}



/*
 * THis function return the least element in the tree If there exists no such node in this scapegoat tree
 * (i.e., the scapegoat tree is empty), this function should throw NoSuchItemException.
 */
template<class T>
const T &ScapegoatTree<T>::getMin() const {

	if(!root) //if the tree is empty
        throw NoSuchItemException();

	T min= get_min_and_max_helper(root,'l');
    return min;
}


/*
 *This function returns the greatest element in the tree. If there exists no such node in this scapegoat tree
 * (i.e., the scapegoat tree is empty), this function should throw NoSuchItemException.
 */
template<class T>
const T &ScapegoatTree<T>::getMax() const {

	if(!root) //if the tree is empty, throw an exception
		throw NoSuchItemException();


	T max=get_min_and_max_helper(root, 'g');
	return max;
}


/*
 * This is a helper function for getNext.
 */
template<class T>
void ScapegoatTree<T>::get_next_helper(Node<T>* node, Node<T>* &next, T element) const
{
	 while (node)
	    {
	        if (element < node->element)
	        {
	        	next = node;
	        	node = node->left;
	        }
	        else {
	            node = node->right;
	        }
	    }
}

/*
 * You should search this scapegoat tree for the node associated with the least element greater than the
 * given element and return the element of that node. If there exists no such node in this scapegoat tree
 * (i.e., all nodes have elements less than or equal to the given element), this function should throw NoSuchItemException.
 * This function is similar to the getFloor function, only difference is that this function only searches the element
 * which is greater than the given element, not the equal to the given element.
 */
template<class T>
const T &ScapegoatTree<T>::getNext(const T &element) const {

	if(element==get_min_and_max_helper(root, 'g') || element>get_min_and_max_helper(root, 'g'))
	{
		throw NoSuchItemException();

	}
	Node<T> *next = NULL;
	get_next_helper(root, next, element);
	return next->element;
}