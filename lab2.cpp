// I will test your BinTree class using either this main or
// a very similar one, and this buildTree.  
// You will want to do thorough testing on your own, 
// which is done by altering the data.

// Windows and unix store files slightly differently. Windows does not
// always store an end-of-line char on the last line, where unix does.
// On windows, always make sure the cursor is on the line after
// the last line of data so it acts like unix/linux.

// presumably bintree.h includes nodedata.h so the include is not needed here
#include "bintree.h"
#include <fstream>
#include <iostream>
using namespace std;

const int ARRAYSIZE = 100;

//global function prototypes
void buildTree(BinTree&, ifstream&);      // 
void initArray(NodeData*[]);             // initialize array to NULL

int main() {
	// create file object infile and open it
	// for testing, call your data file something appropriate, e.g., data2.txt
	ifstream infile("data2.txt");
	if (!infile) {
		cout << "File could not be opened." << endl;
		return 1;
	}

	// the NodeData class must have a constructor that takes a string
	NodeData notND("not");
	NodeData andND("and");
	NodeData sssND("sss");
	NodeData ttttND("tttt");
	NodeData oooND("ooo");
	NodeData yND("y");
	NodeData eND("e");
	NodeData mND("m");
	NodeData tND("t");

	BinTree T, T2, dup;
	NodeData* ndArray[ARRAYSIZE];
	initArray(ndArray);
	cout << "Initial data:" << endl << "  ";
	buildTree(T, infile);              // builds and displays initial data
	cout << endl;
	cout << "right after making T" << endl;
	BinTree first(T);                  // test copy constructor
	dup = dup = T;                     // test operator=, self-assignment
	while (!infile.eof()) {
		cout << "Tree Inorder:" << endl << T;             // operator<< does endl
		T.displaySideways();

		// test retrieve 
		NodeData* p;                    // pointer of retrieved object
		bool found;                     // whether or not object was found in tree
		found = T.retrieve(andND, p);
		cout << "Retrieve --> and:  " << (found ? "found" : "not found") << endl;
		found = T.retrieve(notND, p);
		cout << "Retrieve --> not:  " << (found ? "found" : "not found") << endl;
		found = T.retrieve(sssND, p);
		cout << "Retrieve --> sss:  " << (found ? "found" : "not found") << endl;

		// test getHeight 
		cout << "Height    --> and:  " << T.getHeight(andND) << endl;
		cout << "Height    --> not:  " << T.getHeight(notND) << endl;
		cout << "Height    --> sss:  " << T.getHeight(sssND) << endl;
		cout << "Height    --> tttt:  " << T.getHeight(ttttND) << endl;
		cout << "Height    --> ooo:  " << T.getHeight(oooND) << endl;
		cout << "Height    --> y:  " << T.getHeight(yND) << endl;


		cout << "dup: " << dup << endl;
		cout << "T: " << T << endl;
		cout << "first: " << first << endl;



		// test ==, and != 
		 T2 = T;
		 cout << "@@@T2: " << T2 << endl;
		 cout << "@@@T: " << T << endl;
		cout << "T == T2?     " << (T == T2 ? "equal" : "not equal") << endl;
		cout << "T != first?  " << (T != first ? "not equal" : "equal") << endl;
		cout << "T == dup?    " << (T == dup ? "equal" : "not equal") << endl;
		dup = T;

		// somewhat test bstreeToArray and arrayToBSTree
		T.bstreeToArray(ndArray);
		// cout << "ndArray[0]: " << *ndArray[0] << endl;
		// cout << "ndArray[1]: " << *ndArray[1] << endl;
		// cout << "ndArray[2]: " << *ndArray[2] << endl;
		// cout << "ndArray[3]: " << *ndArray[3] << endl;
		// cout << "ndArray[4]: " << *ndArray[4] << endl;
		// cout << "ndArray[5]: " << *ndArray[5] << endl;
		// cout << "ndArray[6]: " << *ndArray[6] << endl;
		// cout << "ndArray[7]: " << *ndArray[7] << endl;
		// cout << "ndArray[8]: " << *ndArray[8] << endl;
		// cout << "ndArray[9]: " << *ndArray[9] << endl;
		// cout << "ndArray[10]: " << *ndArray[10] << endl;
		// cout << "ndArray[11]: " << *ndArray[11] << endl;
		// cout << "ndArray[12]: " << *ndArray[12] << endl;
		// cout << "ndArray[13]: " << *ndArray[13] << endl;
		// int i=0;
		// do{
		// 	cout << "ndArray[" << i << "]: " << *ndArray[i] << endl;
		// 	i++;
		// } while(ndArray[i] != nullptr);
		//cout << "\n\n\n\n\n\n\n\n\n" << endl;
		T.arrayToBSTree(ndArray);
		//cout << "T after the arrayToBSTree function. \n" << endl;
		cout << "T: " << T << endl;
		T.displaySideways();

		T.makeEmpty();                  // empty out the tree
		initArray(ndArray);             // empty out the array

		cout << "---------------------------------------------------------------"
			<< endl;
		cout << "Initial data:" << endl << "  ";
		buildTree(T, infile);
		cout << endl;
	}

	return 0;
}

//------------------------------- buildTree ----------------------------------
// YOU COMMENT

// To build a tree, read strings from a line, terminating when "$$" is
// encountered. Since there is some work to do before the actual insert that is
// specific to the client problem, it's best that building a tree is not a 
// member function. It's a global function. 

void buildTree(BinTree& T, ifstream& infile) {
	string s;

	for (;;) {
		infile >> s;
		cout << s << ' ';
		if (s == "$$") break;                // at end of one line
		if (infile.eof()) break;             // no more lines of data
		NodeData* ptr = new NodeData(s);     // NodeData constructor takes string
		// would do a setData if there were more than a string

		bool success = T.insert(ptr);
		if (!success)
			delete ptr;                       // duplicate case, not inserted 
	}
}

//------------------------------- initArray ----------------------------------
// initialize the array of NodeData* to NULL pointers

void initArray(NodeData* ndArray[]) {
	for (int i = 0; i < ARRAYSIZE; i++)
		ndArray[i] = NULL;
}
