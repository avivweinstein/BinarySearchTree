#include "nodedata.h"

int main(){
	cout << "This is a test driver for the Node Data Class" << endl;

	NodeData A("abc");
	cout << "A: " << A << endl;

	NodeData B("def");
	cout << "B: " << B << endl;	
	
	NodeData C = A;
	cout << "C: " << C << endl;

	if(A>B){
		cout << "A > B" << endl;
	}
	else if(A<B){
		cout << "A < B" << endl;
	}
	else if(A==B){
		cout << "A==B" << endl;
	}

	if(A==C){
		cout << "A==C" << endl;
	}

	NodeData iii("iii");
	NodeData jj("jj");
	NodeData qnot("not");
	NodeData m("m");

	if (iii>jj){
		cout << "iii is > jj" << endl;
	}
	else if(iii<jj){
		cout << "iii is < jj" << endl;
	}

	if (qnot>jj){
		cout << "qnot is > jj" << endl;
	}
	else if(qnot<jj){
		cout << "qnot is < jj" << endl;
	}

	if(qnot<m){
		cout << "qnot < m" << endl;
	}
	else if(qnot>m){
		cout << "qnot > m" << endl;
	}




	return 0;
}