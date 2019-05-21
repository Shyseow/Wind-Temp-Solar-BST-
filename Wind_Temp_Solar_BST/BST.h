/* The BST class Header (BST.h) */
//---------------------------------------------------------------------------------
	/**
	 * @class BST
     * @file  BST.h
     * @brief  A templated Binary Search Tree
	 *         Declaration for function and variables; and macro definition is made
     *         in this class.
     *
	 * @author Seow Hui Yin
	 * @version 1.0
	 * @date submission : 23/07/2018
     */
//---------------------------------------------------------------------------------
#ifndef BST_H_INCLUDED
#define BST_H_INCLUDED
//---------------------------------------------------------------------------------

#include <iostream>
using namespace std;
    /**
    * @Struct nodeType
    * @brief  Declaration and struct nodeType
    *		  Represents each node of a BST. Two link pointer variables to store the address
    *         of the trail nodes and one variable to store the info of the node.
    *
    */

template <class elemType>
struct nodeType
{
	elemType info;
	nodeType<elemType> *llink;
	nodeType<elemType> *rlink;
};

/**
* @class  NodeBST
* @brief  Declaration and implementation of Binary Search Tree Template class.
*         This is a template class. nodeType defines the BST Node.
*		  This class implements most of the BST related operations
*
*/
template<class elemType>
class NodeBST

{
public:
	/**
	* @brief  Constructor
	*/
	NodeBST();

	/**
	* @brief  Destructor
	*/
	~NodeBST();

	/**
	* @brief  Search function used to search for an item in the BST
	* @return boolean
	*/
	bool search(const elemType & searchItem) const;

	/**
	* @brief  Insert function used to insert an item in the BST
	* @return void
	*/
	void insert(const elemType & i);

	/**
	* @brief  deleteFromTree function used to delete an  item in the BST
	* @return void
	*/
	void deleteFromTree(nodeType<elemType>* &p);

	/**
	* @brief  deleteNode function used to delete a node from BST.
	*         This function search for the node to be deleted first and then uses deleteFromTree function to delete
	* @return void
	*/
	void deleteNode(const elemType & deleteItem);

	/**
	* @brief  Function to check if the BST is empty.
	*         Return true if the binary tree is empty;else return false .
	* @return boolean
	*/
	bool isEmpty() const;

	/**
	* @brief  Function to do an inorder traversal of the binary tree
	*         Print the nodes in inorder sequence.
	* @return void
	*/
	void inOrderTraverse() const;

	/**
	* @brief  Function to do an preorder traversal of the binary tree
	* Print the nodes in preorder sequence.
	* @return void .
	*/
	void preOrderTraverse() const;

	/**
	* @brief  Function to do an postorder traversal of the binary tree
	*         Print the nodes in postorder sequence.
	* @return void
	*/
	void postOrderTraverse() const;

	/**
	* @brief  Function to destroy the binary tree
	*         Memory allocated to each node will be be allocated
	* @return void
	*/
	void destroy(nodeType<elemType>* &p);

    /**
	* @brief  Function to starts up the recursive clearing function
	* @return void
	*/
	void clearTree();


private:
    int counter;
    // private helper functions
	/**
	* @brief  Function to do an in order traversal of the BST
	*         Nodes of the BST to which the pointer p points are printed in in order sequence
	* @return void
	*/
	void inOrder(nodeType<elemType> *p) const;

	/**
	* @brief  Function to do an pre order traversal of the BST
	* Nodes of the BST to which the pointer p points are printed in pre order sequence
	* @return void
	*/
	void preOrder(nodeType<elemType> *p) const;

	/**
	* @brief  Function to do an postorder traversal of the BST
	*         Nodes of the BST to which the pointer p points are printed in postorder sequence
	* @return void
	*/
	void postOrder(nodeType<elemType> *p) const;

	/**
	* @brief  Pointer variable root of type nodeType
	*/
	nodeType<elemType> * root;

	/**
	* @brief  Implementation of this function starts up the recursive clearing function
	*         private function declare for clear tree
	* @return void
	*/
	void clearTreeTool(nodeType<elemType> *ptr);


};


//Implementation of constructor.
template <class elemType>
NodeBST<elemType>::NodeBST()
{
	root = NULL;
}


//Implementation of insert function that insert and entry to the BST.
template <class elemType>
void NodeBST<elemType>::insert(const elemType & i)
{
    //bool found = true;

    nodeType<elemType>* newNode=new nodeType<elemType>;
    nodeType<elemType>* trailCurrent=NULL;
    nodeType<elemType>* current;
    newNode->info=i;
    newNode->llink=NULL;
    newNode->rlink=NULL;

    if(isEmpty()==true)
    {
        root=newNode;
    }
    else
    {
        current=root;

        //Find the node's trailCurrent.Find where there is appropriate space
        while(current !=NULL)
        {
            trailCurrent=current;
            if(i==current->info)
            {
                //cout<<i<<" Item already inserted! No duplicates allowed"<<endl;
				return;
            }
            else if(i> current->info)
            {
                current=current->rlink;
            }
            else
            {
                current=current->llink;
            }
        }//end while

        if(i>trailCurrent->info)
        {
            trailCurrent->rlink=newNode;
            //cout<<newNode->info<<" Inserted!"<<endl;//not needed(for testing only)
        }
        else
        {
            trailCurrent->llink=newNode;
            //cout<<newNode->info<<" Inserted!"<<endl;
        }
    }
  }


//Implementation of search function that search for entry in the BST
template <class elemType>
bool NodeBST<elemType>::search(const elemType & searchItem) const
{
	nodeType<elemType> * current;
	bool found = false;
	if (root == NULL)
		cout << "The Tree is empty and no search can be performed" << endl;
	else
	{
		current = root;
		while (current != NULL && !found)
		{
			if (current->info == searchItem)
				found = true;
			else if (current->info > searchItem)
				current = current->llink;
			else
				current = current->rlink;

		}
	}
	return found;
}


//Implementation of isEmpty function that check if the BST is empty and return true if empty
template <class elemType>
bool NodeBST<elemType>::isEmpty() const
{
	return (root == NULL);
}

//Implementation of preOrderTraverse function that traverse the BST in preorder sequence.
template <class elemType>
void NodeBST<elemType>::preOrderTraverse() const
{
	preOrder(root);
}

//Implementation of inOrderTraverse function that traverse the BST in in order sequence.
template <class elemType>
void NodeBST<elemType>::inOrderTraverse() const
{

	inOrder(root);
}

//Implementation of postOrderTraverse function that traverse the BST in postorder sequence
template <class elemType>
void NodeBST<elemType>::postOrderTraverse() const
{
	postOrder(root);
}

//Implementation of preOrder function that traverse the BST in preorder sequence.
template <class elemType>
void NodeBST<elemType>::preOrder(nodeType<elemType> *p) const
{
	if (p != NULL)
	{
		cout << p->info << " ";
		preOrder(p->llink);
		preOrder(p->rlink);

	}
}

//Implementation of postOrder function that traverse the BST in postorder sequence.
template <class elemType>
void NodeBST<elemType>::postOrder(nodeType<elemType> * p) const
{
	if (p != NULL)
	{
		postOrder(p->llink);
		postOrder(p->rlink);
		cout << p->info << " ";
	}
}

//Implementation of inOrder function that traverse the BST in inorder sequence.
template <class elemType>
void NodeBST<elemType>::inOrder(nodeType<elemType> * p) const
{
	if (p != NULL)
	{
		inOrder(p->llink);
		cout << p->info << " ";
		inOrder( p->rlink);
	}
}

//Implementation of destroy function that destroy the BST.
template <class elemType>
void NodeBST<elemType>::destroy(nodeType<elemType>* &p)
{
	if (p != NULL)
	{
		destroy(p->llink);
		destroy(p->rlink);
		delete p;
		p = NULL;
	}
}


//Implementation of this function starts up the recursive clearing function..
template <class elemType>
void NodeBST<elemType>::clearTree()
{
	nodeType<elemType> * i= root;
	if (i == NULL) {
		cout << "The binary tree is already empty." << endl;
	}
	else {
		clearTreeTool(i->llink);
		clearTreeTool(i->rlink);
		delete i; // delete the root node last.
		root = NULL;  // the root must be set to NULL to properly indicate an empty tree.
		counter = 0;
	}
}


//Implementation of this function starts up the recursive clearing function.is a private function declare for clear tree
template <class elemType>
void NodeBST<elemType>::clearTreeTool(nodeType<elemType> * ptr)
{
	nodeType<elemType> * i = ptr;

	if (i != NULL) {  //if the pointer passed into this function exists
		clearTreeTool(i->llink); //send and inspector down its two link fields
		clearTreeTool(i->rlink);
		delete i; //and when control returns to this instance of the function, delete the parent node.
	}
}


//Implementation of destructor function that destroy the BST by using the destroy function
template <class elemType>
NodeBST<elemType>::~NodeBST()
{
	destroy(root);
}

//Implementation of deleteFromTree that delete a node from the BST.
template <class elemType>
void NodeBST<elemType>::deleteFromTree(nodeType<elemType>* &p)
{
	nodeType<elemType> *current; //pointer to traverse the tree
	nodeType<elemType> *trailCurrent;//pointer behind current
	nodeType<elemType> *temp;//pointer to delete the node

	if (p == NULL)
		cout << "The node to be deleted does not exist." << endl;
	else if (p->lLink == NULL && p->rLink == NULL)
	{
		temp = p;
		p = NULL;
		delete temp;
	}
	else if (p->lLink == NULL)
	{
		temp = p;
		p = temp->rlink;
		delete temp;
	}
	else if (p->rLink == NULL)
	{
		temp = p;
		p = temp->lLink;
		delete temp;
	}
	else
	{
		current = p->lLink;
		trailCurrent = NULL;
		while (current->rLink != NULL)
		{
			trailCurrent = current;
			current = current->rLink;
		}
		p->info = current->info;
		if (trailCurrent == NULL)
			p->lLink = current->lLink;
		else
			trailCurrent->rLink = current->lLink;
		delete current;
	}

}

//Implementation of deleteFromTree that delete a node from the BST.It uses the deleteFromTree function to perform the deletion.
template <class elemType>
void NodeBST<elemType>::deleteNode(const elemType & deleteItem)
{
	nodeType<elemType> *current; //pointer to traverse the tree
	nodeType<elemType> *trailCurrent; //pointer behind current
	bool found = false;
	if (root == NULL)
		cout << "Cannot delete from an empty tree." << endl;
	else
	{
		current = root;
		trailCurrent = root;
		while (current != NULL && !found)
		{
			if (current->info == deleteItem)
				found = true;
			else
			{
				trailCurrent = current;
				if (current->info > deleteItem)
					current = current->lLink;
				else
					current = current->rLink;
			}
		}
		if (current == NULL)
			cout << "The item to be deleted is not in the tree." << endl;
		else if (found)
		{
			if (current == root)
				deleteFromTree(root);
			else if (trailCurrent->info > deleteItem)
				deleteFromTree(trailCurrent->lLink);
			else
				deleteFromTree(trailCurrent->rLink);
		}
		else
			cout << "The item to be deleted is not in the tree." << endl;
	}
}


#endif // BST_H_INCLUDED
