// ------------------------------------------------bintree.cpp -------------------------------------------------------
// Programmer Name: Aviv Weinstein
// Course Section Number: CSS 502 A
// Instructor: Professor Dong Si
// Creation Date: 1/17/21
// Date of Last Modification: 1/27/21
// --------------------------------------------------------------------------------------------------------------------
// Purpose - The purpose of this file is to implement the functions prototyped in bintree.h as part of completing assignment 2
//            for CSS 502 A with Professor Si.
// --------------------------------------------------------------------------------------------------------------------
// Notes on specifications, special algorithms, and assumptions:
//       - When a BinTree is constructed, its root node poninter is set to nullptr.
// --------------------------------------------------------------------------------------------------------------------
#include "bintree.h"

// ---------------------------------Basic Constructor--------------------------------------------------
// Description: Basic constructor for the BinTree class. Sets the root node pointer to null pointer to prepare to add nodes.
// ---------------------------------------------------------------------------------------------------
BinTree::BinTree(){
    root = nullptr; //We are making an empty tree, so we set the root to NULL to begin with.
}

// ---------------------------------Copy Constructor--------------------------------------------------
// Description: Creates a deep copy of the BinTree object being passed into this constructor.
// ---------------------------------------------------------------------------------------------------
BinTree::BinTree(const BinTree & tree){
    this->root = nullptr;
    *this = tree;
}

// ---------------------------------BinTree Class Destructor--------------------------------------------------
// Description: This is the destructor for the BinTree class.
//              This is to make sure that dynamically allocated Nodes we make add nodes to a BinTree object.
// ---------------------------------------------------------------------------------------------------	
BinTree::~BinTree(){
    makeEmpty();
}					

// ---------------------------------isEmpty--------------------------------------------------
// Description: Traverses a BST using an in-order traversal pattern. Prints out the NodeData at every node it touches using in-order traversal
// ---------------------------------------------------------------------------------------------------
bool BinTree::isEmpty() const{
    return (this->root == nullptr);
}

// ---------------------------------convert--------------------------------------------------
// Description: This is a helper function for the arrayToBSTree function. This functions helps in identifying
//              which of the indexes in the array need to be added to the BST next.
// ---------------------------------------------------------------------------------------------------
void BinTree::convert(NodeData* a[], int start, int end, Node *root){
    static int skip = 0;
    
    if(start > end){ //This is the base case for our recursive function. Once we have the start/end pointers change position, we know we have indexed our entire array 
        return;
    }

    int mid = (start+end)/2; //mid will be the index of the array we add as the next node in the BST.

    if(skip != 0){
        insert(a[mid]);
        convert(a,start,mid-1,this->root); //Recursively calculating the correect indexes to add to the BST.
        convert(a,mid+1,end,this->root);
    }
    else{ //Because of the way I have created my insert function, I need to skip a run of the convert function.
        skip++;
        convert(a,start,end,this->root);
    }

}

// ---------------------------------insert--------------------------------------------------
// Description: This function inserts a new Node into the current BinTree object. You need to pass in the NodeData that you want to add to the BinTree.
//              This function makes use of the insertHelp function, which is a private function that helps to recursively add a node to the BinTree.
// ---------------------------------------------------------------------------------------------------
bool BinTree::insert(NodeData* nodeData){
    if(root != nullptr){ //if the root of the tree is not NULL, meaning that the BST object exists, we call our insertHelp function.
        insertHelp(this->root, nodeData);
        return true;
    }
    else{ //If there is no root node created in our tree, we create a root node.
        root = new Node;
        root->left = nullptr;
        root->right = nullptr;
        root->data = nodeData;
        return true;
    }
    return true;
}

// ---------------------------------insertHelp--------------------------------------------------
// Description: Private function that recursively calls itself in order to find the correct location in a BinTree object to add a new node.
// ---------------------------------------------------------------------------------------------------
bool BinTree::insertHelp(Node *nodePointer, NodeData* nodeData){
      if(*nodeData < *nodePointer->data){ //Here we are deciding if we need to traverse left or not.
        if(nodePointer->left != nullptr){ //If there is a node to the left, we call insertHelper again but on this node to the left.
            insertHelp(nodePointer->left, nodeData);
        }
        else{ //if there is no node the left, and we need to go left, we create a new left node.
            nodePointer->left = new Node;
            nodePointer->left->left = nullptr;
            nodePointer->left->right = nullptr;
            nodePointer->left->data = nodeData;
            return true;
        }   
    } 
    else if(*nodeData > *nodePointer->data){//Here we are deciding if we need to traverse right or not.
        if(nodePointer->right != nullptr){ //if there is no node the right, and we need to go left, we create a new left node.
            insertHelp(nodePointer->right, nodeData);
        }
        else{ //if there is no node the right, and we need to go right, we create a new right node.
            nodePointer->right = new Node;
            nodePointer->right->left = nullptr;
            nodePointer->right->right = nullptr;
            nodePointer->right->data = nodeData;
            return true;
        }
    }
    else{ //catch all case. If something goes wrong, return false.
        return false;
    }
    return true;
}

// ---------------------------------makeEmpty--------------------------------------------------
// Description: Deallocates all the nodes in a BinTree object and properly deals with dynamically allocated memory.
//              This is done by performing a post-order traversal of the array and deleting nodes in that order.
//              This is the public method for deleting/deallocating the nodes of a BinTree. This function calls a private function,
//              called postOrderDeleteNode.
// ---------------------------------------------------------------------------------------------------
void BinTree::makeEmpty(){
    //You make a tree empty by deleting all notes in a post-order traversal.
    postOrderDeleteNode(this->root); //I will call my private postOrderDelete helper function. I broke things up this way to make the code cleaner.
}

// ---------------------------------postOrderDeleteNode--------------------------------------------------
// Description: This is the private function that performs a post-order traversal of the nodes in a BinTree
//              and deletes each node by deallocating the memory assigned when each node is created.
// ---------------------------------------------------------------------------------------------------
void BinTree::postOrderDeleteNode(const Node *rootNode){
    if(rootNode == nullptr){ //Base case, we have an empty tree at this node
        return;
    }
    else{
        postOrderDeleteNode(rootNode->left); //First we delete the left side of the tree
        postOrderDeleteNode(rootNode->right); //Then we delete the right side of the tree.
        delete rootNode; //We finally delete the root of the entire BST.
        this->root = nullptr; 
    }
}

// ---------------------------------operator=--------------------------------------------------
// Description: This is the overloaded assignment operator for the BinTree class. This function assigns
//              the BinTree object on the RHS of the = side with the name of the BinTree on the LHS of the = sign.
// ---------------------------------------------------------------------------------------------------
BinTree& BinTree::operator=(const BinTree & rhs){
    inorderHelperArray(nullptr, nullptr);
    if(this != &rhs){   //Checking for self assignment. If we are self-assigning, we skip this if staetment and return *this.
        if(this->root != nullptr){ //If the binary tree we are trying to assign is not empty, we destroy the binary tree.
            this->makeEmpty();
        }

        if(rhs.root == nullptr){ //The tree on the RHS is empty/does not exist.
            this->root = nullptr;
        }
        else{
            preorderTraversal(rhs.root); //When assigning new nodes to the LHS, we need to perform a pre-order traversal
        }                                //This is so we add nodes lower in the tree without needing to do a lot of pointer arithmetic.
    }
    return *this;
}

// ---------------------------------preorderTraversal--------------------------------------------------
// Description: Visits every node of a BST using pre-order traversal and inserts nodes from the BinTree on the RHS of the = to the LHS.
// ---------------------------------------------------------------------------------------------------
void BinTree::preorderTraversal(Node* node){
    if(node==nullptr){ //base case for the recursive function.
        return;
    }
    insert(node->data); //Here we are recursively insering nodes into the BST on the LHS of the operator=.
    preorderTraversal(node->left);
    preorderTraversal(node->right);
}

// ---------------------------------operator==--------------------------------------------------
// Description: Boolean comparison operator. Checks if two BSTs are equal to one another or not.
//              Calls the inorderHelperArray helper function to convert the BSTs being compared to arrays.
// ---------------------------------------------------------------------------------------------------
bool BinTree::operator==(const BinTree &rightSide) const{
    //The way I wrote this function is to convert both BST to arrays.
    //For every node in each BST, I add them to an array using in-order traversal.
    //I then compare each of these two arrays. If they are equal, then I know that the BSTs are equal.
    
    //Here I am creating the arrays that I will end up string the in-order traversal of my BSTs
    NodeData* lhs[100];
    NodeData* rhs[100];

    for(int i=0;i<100;i++){ //initialize both arrays to nullptr
        lhs[i] = nullptr;
        rhs[i] = nullptr;
    }

    //This call of inorderHelperArray converts the LHS of the == to an array
    inorderHelperArray(lhs, this->root);

    //I need this call of inorderHelperArray to reset the static int that I am using in that function.
    //If I dont reset the static int in the inorderHelperArray function, then it wont work properly.
    //I need to reset inorderHelperArray after every time it is called.
    inorderHelperArray(nullptr, nullptr); 
    
    //This call of inorderHelperArray converts the RHS of the == to an array
    inorderHelperArray(rhs, rightSide.root);

    //Initializing the ints I will use to store the length of each array.
    //If the lengths of the arrays of the LHS and RHS differ, we know the BSTs are not equal.
    int lengthLHS = 0;
    int lengthRHS = 0;

    //Calculating length for LHS BST
    while(lhs[lengthLHS] != nullptr){
       lengthLHS++;
    }
    
    //Calculating length for RHS BST
    while(rhs[lengthRHS] != nullptr){
       lengthRHS++;
    }

    //Checking that lengths of the arrays are the same.
    if(lengthLHS != lengthRHS){
        return false;
    }
    
    //Here I am checking that all the values of both arrays are the same.
    for(int j=0;j<lengthLHS;j++){
        if(lhs[j] != rhs[j]){ //if the values ever differ, the BSTs are not equal.
            return false;
        }
    }

    //Like I mentioned above. After everytime I call inorderHelperArray, I need to call it with the parameters nullptr to reset a static int I use in that function.
    inorderHelperArray(nullptr, nullptr);
    
    //If we checked that the lengths of the arrays are equal
    //And we checked that the contents of each array are equal
    //Then we can return true.
    return true;
}

// ---------------------------------operator!=--------------------------------------------------
// Description: Checks if two BSTs are NOT equal to one another. Make use of the negation of the operator== function.              
// ---------------------------------------------------------------------------------------------------
bool BinTree::operator!=(const BinTree &rhs) const{
    if(*this==rhs){
        return false;
    }
    else{
        return true;
    }
}

// ---------------------------------retrieve--------------------------------------------------
// Description: This function looks for a node with the same data that you pass into it.
//              If the node exists, then it sets a pointer equal to that node.
//              If the node doesnt exist, then it returns false and sets teh pointer to nullptr.
// ---------------------------------------------------------------------------------------------------
bool BinTree::retrieve(const NodeData &nodeData, NodeData* &pointerToNodeData) const{

    Node* result = nullptr; //Creating a Node* to store the result from retrieveHelper function.

    result = retrieveHelper(this->root,nodeData); //See retrieveHelper function for what this is doing.
    
    if(result==nullptr){ //If our retrieveHelper function did not assign a value to result/result got assigned nullptr, that node must not exist in our tree. So we return false.
        return false;
    }
    else{
        pointerToNodeData = result->data; //If we did get a valid pointer, then we assign that value to the pointerToNodeData value and return true;
        return true;
    }
}

// ---------------------------------retrieveHelper--------------------------------------------------
// Description: A helper function for the retrieve function.
// ---------------------------------------------------------------------------------------------------
BinTree::Node* BinTree::retrieveHelper(Node *root, const NodeData &nodeData)const{
    //This is a helper function for the retrieve function.
    //I am going to return a Node* to the initial retrieve function.
    //I can then set the final pointerToNodeData equal to the NodeData of the node I am passing back
    //cout << "retrieveHelper Function" << endl;

    Node* foundNode = nullptr; //Creating a variable to store the pointer to the node if we find it.
    //We initialize this to nullptr in the event that the node we are trying to retrieve doesnt exist.
    
    //If the root is null or if the nodeData value that we are looking for is at the root.
    if (root == nullptr || *root->data == nodeData){
        //cout << "Base case reached" << endl; //When we reach this block, we have either found the node, or determined it doesnt exist.
        foundNode = root; //We assign the node we haev found, or not found, to the pointer we end up returning for this function.
        return foundNode;
    }
    //In the below if/else if/else statements, we are traversing our tree based on the node we are looking for.
    //We use this  by the property of BSTs that each node to the left is smaller and each node to the right is larger.
    //We are also recursively calling the retrieveHelper, to narrow down on the node of interest.
    if(*root->data > nodeData){
        return retrieveHelper(root->left, nodeData);
    }
    else if (*root->data < nodeData){
        return retrieveHelper(root->right, nodeData);
    }
    else{
        return nullptr;
    }
}

// ---------------------------------getHeight--------------------------------------------------
// Description: returns the height of the nodedata that yo pass in.
//              if the node you are trying to get the height for does not exist, then 0 is returned.
// ---------------------------------------------------------------------------------------------------
int BinTree::getHeight(const NodeData &nodeData) const{
    int height = 0; //To store the heigh of the node in our BST.
    
    //Creating a pointer to a Node.
    //I will use this pointer to point to the node in our BST that we want to calculate the height of.
    Node *nodePointer = retrieveHelper(this->root, nodeData);

    //If the nodePointer is nullprt, that means that the nodeData we are looking for doesnt exist in our tree.
    if (nodePointer==nullptr){
        height = 0;
    }
    else{
        height = getHeightUtil(nodePointer); //Once we have located the node in our BST, we need to caluclate the height of the tree.
    }
    return height;
}

// ---------------------------------getHeightUtil--------------------------------------------------
// Description: A utility/helper function for the getHeight function.
//              Calculates the height of a node on both the left and right sides of a node in the BST.
// ---------------------------------------------------------------------------------------------------
int BinTree::getHeightUtil(Node *node)const{
    if(node == nullptr){
        return 0;
    }
    
    //These recursive calls calculate the height on both sides of the node.
    int leftHeight = getHeightUtil(node->left);
    int rightHeigh = getHeightUtil(node->right);

    if(leftHeight>=rightHeigh){
        return leftHeight+1;
    }
    else{
        return rightHeigh+1;
    }
}

// ---------------------------------inorderHelper--------------------------------------------------
// Description: Traverses a BST using an in-order traversal pattern. Prints out the NodeData at every node it touches using in-order traversal
// ---------------------------------------------------------------------------------------------------
void BinTree::inorderHelper(Node *startNode) const{
    if (startNode != nullptr){ //Here we recursively traverse the BST.
        inorderHelper(startNode->left); 
        cout << *startNode->data << " ";
        inorderHelper(startNode->right);
    }
}

// ---------------------------------operator<<--------------------------------------------------
// Description: Prints out a BST's nodes in in-order traversal. Uses a helper function called inorderHelper
// ---------------------------------------------------------------------------------------------------
ostream& operator<<(ostream& out, const BinTree& T){
    T.inorderHelper(T.root);
    cout << endl;
    return out;
}

// ---------------------------------bstreeToArray--------------------------------------------------
// Description: Converts a BST to an array
//              The array is filled in from the nodes of the BST as if they were presented using in-order traversal.
// ---------------------------------------------------------------------------------------------------
void BinTree::bstreeToArray(NodeData* a[]){
    inorderHelperArray(a, this->root);
}

// ---------------------------------retrieveHelper--------------------------------------------------
// Description: A helper function for the retrieve function. Converts a BST into an array by traversing it in order.
// ---------------------------------------------------------------------------------------------------
void BinTree::inorderHelperArray(NodeData* a[], Node *startNode) const{
    static int i = 0; //This variable is used to index the array we are creating.
    
    if(startNode != nullptr){
        inorderHelperArray(a, startNode->left);
        a[i++] = startNode->data;
        inorderHelperArray(a, startNode->right);
    }
    else{
        if(a==nullptr){ //Sometimes, I need to call inorderHelperArray with both paramaters set to nullptr to reset my static int i back to 0;
            i = 0;
        }
    }
}

// ---------------------------------arrayToBSTree--------------------------------------------------
// Description: Builds a balanced BinTree from a sorted array of NodeData* leaving the array filled with NULLs.
//              The root (recursively) is at (low+high)/2 where low is the lowest subscript of the array range and high is the highest.
// ---------------------------------------------------------------------------------------------------
void BinTree::arrayToBSTree(NodeData* a[]){
    this->makeEmpty(); //First thing I want to do is clear the BinTree object we are working with
    
    if(a[0]==nullptr){ //Checking if we have an empty array or not.
        return;
    }
    //Initializing variables that are used to measure the length of the array he have to convert to a BST.
    int i=0;
    int end = 0;
    int start = 0;
    
    //Calculaing length of the array in this while loop.
    while(a[i]!=nullptr){
        end++;
        i++;
    }
    end = end-1;

    int mid = (start + end)/2;
    insert(a[mid]); //Here we are creating a new BST with the root node being the middle point of the array.
    convert(a,start,end,this->root);

    for(int j=0;j<end+1;j++){
        a[j] = nullptr; //Setting the initial array we used to have all values of nullptr, as assignment 2 instructions ask for.
    }
    return;
}

//------------------------- displaySideways ---------------------------------
// Displays a binary tree as though you are viewing it from the side;
// hard coded displaying to standard output.
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
void BinTree::displaySideways() const {
	sideways(root, 0);
}

//---------------------------- Sideways -------------------------------------
// Helper method for displaySideways
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
void BinTree::sideways(Node* current, int level) const {
	if (current != NULL) {
		level++;
		sideways(current->right, level);

		// indent for readability, 4 spaces per depth level 
		for (int i = level; i >= 0; i--) {
			cout << "    ";
		}

		cout << *current->data << endl;        // display information of object
		sideways(current->left, level);
	}
}

