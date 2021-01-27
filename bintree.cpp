#include "bintree.h"

//constructor
BinTree::BinTree(){
    root = nullptr; //We are making an empty tree, so we set the root to NULL to begin with.
}

// copy constructor
BinTree::BinTree(const BinTree & tree){
    //cout << "\n \n \ncopy constructor" << endl;
    this->root = nullptr;
    //cout << "this->root: " << this->root << endl;
    //cout <<"tree.root: " << tree.root << endl;
    *this = tree;
}

//destructor, calls makeEmpty	
BinTree::~BinTree(){
    makeEmpty();
}					

bool BinTree::isEmpty() const{
    return (this->root == nullptr);
}

void BinTree::convert(NodeData* a[], int start, int end, Node *root){
    static int skip = 0;
    //cout << "skip: " << skip << endl;
    
    if(start > end){ //This is the base case for our recursive function. Once we have the start/end pointers change position, we know we have indexed our entire array 
        return;
    }

    int mid = (start+end)/2;

    if(skip != 0){
        // cout << "inserting this value---> a[mid]" << endl;
        // cout << "a[" << mid << "]: " << *a[mid] << endl;
        insert(a[mid]);
        convert(a,start,mid-1,this->root);
        convert(a,mid+1,end,this->root);
    }
    else{ //Because of the way I have created my insert function, I need to skip a run of the convert function.
        skip++;
        convert(a,start,end,this->root);
    }

}

bool BinTree::insert(NodeData* nodeData){ //Recursive function implementation
    if(root != nullptr){ //if the root of the tree is not NULL, meaning that the BST object exists, we call our insertHelp function.
        //cout << "do we go here?" << endl;
        insertHelp(this->root, nodeData);
        return true;
    }
    else{ //If there is no root node created in our tree, we create a root node.
        //cout << "Root node being created" << endl;
        // cout << "OR do we go here?" << endl;
        root = new Node;
        root->left = nullptr;
        root->right = nullptr;
        root->data = nodeData;
        return true;
    }
    return true;
}

bool BinTree::insertHelp(Node *nodePointer, NodeData* nodeData){
    // cout << "entering insertHelp" << endl;
    // cout << "nodePointer:"<< nodePointer << endl;
    // cout << "*nodeData:"<< *nodeData << endl;
    //cout << "*nodePointer->data: " << *nodePointer->data << endl; - DO NOT UNCOMMENT
    //For some reason, trying to access *nodePointer->data kills us.
    //cout << "Where are we dying?"<<  endl;
    
    if(*nodeData < *nodePointer->data){ //Here we are deciding if we need to traverse left or not.
        //cout << "if statement 1 kill us?"<<  endl;
        if(nodePointer->left != nullptr){ //If there is a node to the left, we call insertHelper again but on this node to the left.
            //cout << "\nrecursive call of insertHelp" << endl;
            insertHelp(nodePointer->left, nodeData);
        }
        else{ //if there is no node the left, and we need to go left, we create a new left node.
            //cout << "\nLeft node being created" << endl;
            nodePointer->left = new Node;
            nodePointer->left->left = nullptr;
            nodePointer->left->right = nullptr;
            nodePointer->left->data = nodeData;
            return true;
        }   
    }
    else if(*nodeData > *nodePointer->data){
        //cout << "if statement 2 kill us?"<<  endl;
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
    //cout << "do we just skip it all?" << endl;
    return true;
}

void BinTree::makeEmpty(){
    //cout << " makeEmpty" << endl;
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
    inorderHelperArray(nullptr, nullptr);
    if(this != &rhs){   //Checking for self assignment. If we are self-assigning, we skip this if staetment and return *this.
        //cout << "do we enter the operator=?" << endl;
        if(this->root != nullptr){ //If the binary tree we are trying to assign is not empty, we destroy the binary tree.
            //cout << "is make empty called?" << endl;
            this->makeEmpty();
        }

        if(rhs.root == nullptr){ //The tree on the RHS is empty/does not exist.
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
    //cout << "made it past insert?" << endl;
    preorderTraversal(node->left);
    preorderTraversal(node->right);
}

bool BinTree::operator==(const BinTree &rightSide) const{
    //cout << "Entered operator==" << endl;
    NodeData* lhs[100];
    NodeData* rhs[100];

    for(int i=0;i<100;i++){
        lhs[i] = nullptr;
        rhs[i] = nullptr;
    }

    //cout << "have we initialized our arrays?" << endl;

    inorderHelperArray(lhs, this->root);
		// int q=0;
		// do{
		// 	cout << "lhs[" << q << "]: " << *lhs[q] << endl;
		// 	q++;
		// } while(lhs[q] != nullptr);
    inorderHelperArray(nullptr, nullptr);
        //cout << "\n\n\n\n\n\n" << endl;
    inorderHelperArray(rhs, rightSide.root);

    //cout << "rhs[0]: " << *rhs[0] << endl;

    // cout << "And have we gotten past our arrayhellper?" << endl;
    // cout << "If so, lets show the contents of each array" << endl;
		/*int i=0;
		do{
			cout << "lhs[" << i << "]: " << *lhs[i] << endl;
            //cout << "is it the first value in rhs?" << endl;
            cout << "rhs[" << i << "]: " << *rhs[i] << endl;
            cout << "" << endl;
			//cout << "it would appear so" << endl;
            i++;
		} while(lhs[i] != nullptr || rhs[i] != nullptr);*/


    int lengthLHS = 0;
    int lengthRHS = 0;

    // cout << "lengthLHS: " << lengthLHS << endl;
    // cout << "lengthRHS: " << lengthRHS << endl;

    while(lhs[lengthLHS] != nullptr){
       lengthLHS++;
    }
    
    while(rhs[lengthRHS] != nullptr){
       lengthRHS++;
    }

    // cout << "lengthLHS: " << lengthLHS << endl;
    // cout << "lengthRHS: " << lengthRHS << endl;

    if(lengthLHS != lengthRHS){
        return false;
    }

    for(int j=0;j<lengthLHS;j++){
        if(lhs[j] != rhs[j]){
            return false;
        }
    }

    inorderHelperArray(nullptr, nullptr);
    
    return true;
    
}


bool BinTree::operator!=(const BinTree &rhs) const{
    if(*this==rhs){
        return false;
    }
    else{
        return true;
    }
}


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
        cout << *startNode->data << " ";
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
    //cout << "inorderHelperArray" << endl;
    static int i = 0;
    
    if(startNode != nullptr){
        //cout << "do we enter this is statemenet in inorderHelperArray?" << endl;
        inorderHelperArray(a, startNode->left);
        //cout << "i: " << i << endl;
        a[i++] = startNode->data;
        inorderHelperArray(a, startNode->right);
    }
    else{
        if(a==nullptr){
            i = 0;
        }
    }
    //cout << "do we hit the end of inorderhelperarray?" << endl;
}




// This function builds a balanced Binary Tree! Not necessarily a BST?
// What I want to do in this function, is first find the legnth of my array (a[]).
// The node(s) to be added are always at (low+high)/2 of the array.
void BinTree::arrayToBSTree(NodeData* a[]){
    //cout << "-------------------------------arrayToBSTree Function--------------------------" << endl;
    this->makeEmpty(); //First thing I want to do is clear the BinTree object we are working with
    
    if(a[0]==nullptr){ //Checking if we have an empty array or not.
        return;
    }

    int i=0;
    int end = 0;
    int start = 0;
    

    while(a[i]!=nullptr){
        end++;
        i++;
    }
    //cout << "end: " << end << endl;
    end = end-1;
    //cout << "corrected end: " << end << endl;

    int mid = (start + end)/2;
    insert(a[mid]); //Here we are creating a new BST with the root node being the middle point of the array.
    //cout << "here we call convert" << endl;
    convert(a,start,end,this->root);

    for(int j=0;j<end+1;j++){
        //cout << "a[" << j << "]: " << *a[j] << endl;
        a[j] = nullptr; //Setting the initial array we used to have all values of nullptr, as assignment 2 instructions ask for.
    }

    /*for(int j=0;j<end+1;j++){
        cout << "a[" << j << "]: " << *a[j] << endl;
    }*/


    //cout << "-------------------------------end of arrayToBSTree Function--------------------------" << endl;

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

