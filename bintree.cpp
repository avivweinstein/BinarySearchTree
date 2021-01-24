#include "bintree.h"

//constructor
BinTree::BinTree(){
    root = nullptr; //We are making an empty tree, so we set the root to NULL to begin with.
    //root->left = nullptr;
    //root->right = nullptr;
}

// copy constructor
BinTree::BinTree(const BinTree & tree){
    makeEmpty();
    *this = tree;
}

//destructor, calls makeEmpty	
BinTree::~BinTree(){
    //cout << "I am the destructor" << endl;
    makeEmpty();
}					

bool BinTree::isEmpty() const{
    return (this->root == nullptr);
}

bool BinTree::insert(NodeData* nodeData){ //Recursive function implementation
    if(root != nullptr){
        //cout << "root in insert: " << this->root << endl;
        //cout << "*nodeData in insert: " << *nodeData << endl;
        insertHelp(this->root, nodeData);
        return true;
    }
    else{
        //cout << "Root node being created" << endl;
        root = new Node;
        root->left = nullptr;
        root->right = nullptr;
        root->data = nodeData;
        return true;
    }
    return true;
}

bool BinTree::insertHelp(Node *nodePointer, NodeData* nodeData){
    /*cout << "entering insertHelp" << endl;
    cout << "nodePointer:"<< nodePointer << endl;
    cout << "*nodeData:"<< *nodeData << endl;
    cout << "*nodePointer->data: " << *nodePointer->data << endl;*/
    if(*nodeData < *nodePointer->data){
        if(nodePointer->left != nullptr){
            //cout << "\nrecursive call of insertHelp" << endl;
            insertHelp(nodePointer->left, nodeData);
        }
        else{
            //cout << "\nLeft node being created" << endl;
            nodePointer->left = new Node;
            nodePointer->left->left = nullptr;
            nodePointer->left->right = nullptr;
            nodePointer->left->data = nodeData;
            return true;
        }   
    }
    else if(*nodeData > *nodePointer->data){
        if(nodePointer->right != nullptr){
            //cout << "\nrecursive call of insertHelp" << endl;
            insertHelp(nodePointer->right, nodeData);
        }
        else{
            //cout << "\nRight node being created" << endl;
            nodePointer->right = new Node;
            nodePointer->right->left = nullptr;
            nodePointer->right->right = nullptr;
            nodePointer->right->data = nodeData;
            return true;
        }
    }
    else{
        //cout << "\nDuplicate value." << endl;
        //cout << "No new node in tree is made.\n" << endl;
        return false;
    }
    return true;
}

void BinTree::makeEmpty(){
    //You make a tree empty by deleting all notes in a post-order traversal.
    postOrderDeleteNode(this->root); //I will call my postOrderDelete helper function
}

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

BinTree& BinTree::operator=(const BinTree & rhs){
    
    if(this != &rhs){   //Checking for self assignment. If we are self-assigning, we skip this if staetment and return *this.
        //cout << "do we enter the operator=?" << endl;
        if(this->root != nullptr){ //If the binary tree we are trying to assign is not empty, we destroy the binary tree.
            //cout << "is make empty called?" << endl;
            this->makeEmpty();
        }
        else if(rhs.root == nullptr){ //The tree on the RHS is empty/does not exist.
            //cout << "second if statement" << endl;
            this->root = nullptr;
        }
        else{
            //cout << "calling the pre-order traversal function" << endl;
            preorderTraversal(rhs.root);
        }
    }
    // cout << "ending operator="  << endl;
    // cout << "this->root: " << this->root << endl;
    // cout << "rhs->root: " << rhs.root << endl;

    return *this;
}

void BinTree::preorderTraversal(Node* node){
    if(node==nullptr){
        //cout << "do we enter this right away?" << endl;
        return;
    }
    //cout << "*node->data: " << *node->data << endl;
    insert(node->data);
    preorderTraversal(node->left);
    preorderTraversal(node->right);
}

//bool BinTree::operator==(const BinTree &) const;
// bool BinTree::operator!=(const BinTree &) const


bool BinTree::retrieve(const NodeData &nodeData, NodeData* &pointerToNodeData) const{

    Node* result = nullptr; //Creating a Node* to store the result from retrieveHelper function.
    //cout << "Retrieve function" << endl;

    result = retrieveHelper(this->root,nodeData); //See retrieveHelper function for what this is doing.
    
    if(result==nullptr){ //If our retrieveHelper function did not assign a value to result/result got assigned nullptr, that node must not exist in our tree. So we return false.
        return false;
    }
    else{
        pointerToNodeData = result->data; //If we did get a valid pointer, then we assign that value to the pointerToNodeData value and return true;
        return true;
    }
}

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
        //cout << "going left" <<endl;
        return retrieveHelper(root->left, nodeData);
    }
    else if (*root->data < nodeData){
        //cout << "going right" <<endl;
        return retrieveHelper(root->right, nodeData);
    }
    else{
        return nullptr;
    }
}


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
        height = getHeightUtil(nodePointer);
    }
    return height;
}


int BinTree::getHeightUtil(Node *node)const{
    if(node == nullptr){
        return 0;
    }

    int leftHeight = getHeightUtil(node->left);
    int rightHeigh = getHeightUtil(node->right);

    if(leftHeight>=rightHeigh){
        return leftHeight+1;
    }
    else{
        return rightHeigh+1;
    }
}


void BinTree::inorderHelper(Node *startNode) const{
    if (startNode != nullptr){
        inorderHelper(startNode->left);
        cout << *startNode->data;
        inorderHelper(startNode->right);
    }
}

ostream& operator<<(ostream& out, const BinTree& T){
    T.inorderHelper(T.root);
    cout << endl;
    return out;
}

void BinTree::bstreeToArray(NodeData* a[]){
    inorderHelperArray(a, this->root);
}

void BinTree::inorderHelperArray(NodeData* a[], Node *startNode) const{
    int i = 0;
    inorderHelperArray(a, startNode->left);
    a[i] = 


}




/*void BinTree::arrayToBSTree(NodeData* a[]){
//This function builds a balanced Binary Tree! Not necessarily a BST?
//What I want to do in this function, is first find the legnth of my array (a[]).
//Root is located at (low+high)/2 of the array.


}*/

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

