// ------------------------------------------------ Poly.h -------------------------------------------------------
//
// Programmer Name: Aviv Weinstein
// Course Section Number: CSS 502 A
// Creation Date: 1/17/21
// Date of Last Modification: 
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

class BinTree{			// you add class/method comments and assumptions

    friend ostream& operator<<(ostream& out, const BinTree& T);  //Used for output printing of BinTree objects

    public:
        BinTree();								// constructor
        BinTree(const BinTree &);				// copy constructor
        ~BinTree();								// destructor, calls makeEmpty	
        bool isEmpty() const;					// true if tree is empty, otherwise false
        void makeEmpty();						// make the tree empty so isEmpty returns true
        BinTree& operator=(const BinTree &);
        bool operator==(const BinTree &) const;
        bool operator!=(const BinTree &) const;
        bool insert(NodeData*);
        bool retrieve(const NodeData &, NodeData* &) const; //I got these parameters from the PDF.
        void displaySideways() const;			// provided below, displays the tree sideways
        int getHeight(const NodeData &) const;
        void bstreeToArray(NodeData* []);
        void arrayToBSTree(NodeData* []);
        
    private:
        struct Node {
            NodeData* data;						// pointer to data object
            Node* left;							// left subtree pointer
            Node* right;						// right subtree pointer
        };
        Node* root;								// root of the tree

        //Utility functions
        void sideways(Node*, int) const; //provided below, helper for displaySideways()
        bool insertHelp(Node *nodePointer, NodeData* nodeData);
        void postOrderDeleteNode(const Node *node);
        void inorderHelper(Node *startNode) const;
        void inorderHelperArray(NodeData* a[], Node *startNode) const;
        Node* retrieveHelper(Node *root, const NodeData &nodeData) const;
        int getHeightUtil(Node *node)const;
        void preorderTraversal(Node* node);
        void convert(NodeData* a[], int start, int end, Node *root);
};

#endif
