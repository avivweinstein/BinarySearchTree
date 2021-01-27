// ------------------------------------------------bintree.h-------------------------------------------------------
//
// Programmer Name: Aviv Weinstein
// Course Section Number: CSS 502 A
// Creation Date: 1/17/21
// Date of Last Modification: 1/27/21
// Instructor Name: Professor Dong Si
// --------------------------------------------------------------------------------------------------------------------
// Purpose - 
// --------------------------------------------------------------------------------------------------------------------
// Notes on specifications, special algorithms, and assumptions: 
// --------------------------------------------------------------------------------------------------------------------

#ifndef Bintree_H                                 
#define Bintree_H
#include "nodedata.h"
//We have inlcuded iostream in nodedata.h

using namespace std;

class BinTree{

    friend ostream& operator<<(ostream& out, const BinTree& T);  //Used for output printing of BinTree objects. To display the tree using inorder traversal. 

    public:
        BinTree();								// constructor
        BinTree(const BinTree &);				// copy constructor
        ~BinTree();								// destructor, calls makeEmpty	
        bool isEmpty() const;					// true if tree is empty, otherwise false
        void makeEmpty();						// make the tree empty so isEmpty returns true
        BinTree& operator=(const BinTree &); //The assignment operator (=) to assign one tree to another
        bool operator==(const BinTree &) const; //Boolean comparison operator for equal
        bool operator!=(const BinTree &) const; //Boolean comparison operator for NOT equal
        bool insert(NodeData*); //inserts a new node, with NodeData, into the BinTree object.
        bool retrieve(const NodeData &, NodeData* &) const; //Looks for a specific node in the BinTree. Returns true if the node exists.
        void displaySideways() const;			// provided below, displays the tree sideways
        int getHeight(const NodeData &) const; //function to find the height of a given value in the tree. 
        void bstreeToArray(NodeData* []); //function to fill an array of Nodedata* by using an inorder traversal of the tree
        void arrayToBSTree(NodeData* []); //function to fill an array of Nodedata* by using an inorder traversal of the tree
        
    private:
        struct Node {
            NodeData* data;						// pointer to data object
            Node* left;							// left subtree pointer
            Node* right;						// right subtree pointer
        };
        Node* root;								// root of the tree

        //Utility functions
        void sideways(Node*, int) const; //provided below, helper for displaySideways()
        bool insertHelp(Node *nodePointer, NodeData* nodeData); //Helper function for the insert function.
        void postOrderDeleteNode(const Node *node); // Helper function. Deletes all nodes in a BinTree object 
        void inorderHelper(Node *startNode) const; //Helper function for printing out all nodes in a BST using in-order traversal
        void inorderHelperArray(NodeData* a[], Node *startNode) const; //Helper function for the operator == and operator!= functions.
                                                                    //Used to compare BSTs to each other using in-order traversal.
        Node* retrieveHelper(Node *root, const NodeData &nodeData) const; //A hlper function for retriving a node in a BinTree
        int getHeightUtil(Node *node)const; //Helper for performing a recursive calculation of the height of a node in a BinTree.
        void preorderTraversal(Node* node); //Performs a pre-order traversal of a BinTree object. Called by the operator= function.
        void convert(NodeData* a[], int start, int end, Node *root); //Performs a utility function in the arraytoBSTree function.
                                                                    //Selects the correct array indexes to be added next into an array.
};

#endif
