#include <iostream>
#include <fstream>
#include <string>
#include "BinaryTree.h"
#include "BinaryHeap.h"
using namespace std;

BTree* storeToClass(BinaryHeap<char> heap);
BTree* buildBTree(BinaryHeap<BTree*> ori, BinaryHeap<int> comp, int total);

int main(int argc, char** argv){

	char store; 
	string line;
	int i;
	BTree* root = NULL;
	string code;

	ifstream myfile(argv[1]); //open file

	BinaryHeap<char> heap(1000000); //initialize binary heap

	while (getline(myfile, line)){	//insert char from a line to binary heap
		i = 0;
		while( line[i]){
			heap.insert(line[i++]);
		}
			heap.insert('\n'); //insert end of line
		
	}
	
	root = storeToClass(heap);

	root->printTree(code);
	

}//end of main

BTree* storeToClass(BinaryHeap<char> heap){

	char store;
	BinaryHeap<BTree*> uChar(100000); //binary heap to store all the unique char
	BinaryHeap<int> compare(100000);
	BinaryHeap<BTree*> swap(100000);
	uniqueChar* cStore = NULL;
	BTree* root = NULL;
	int totalCount = 0;

	
	do {
		store = heap.findMin(); //store each char
	
		if (cStore == NULL){
			cStore = new uniqueChar(store);
		}
			
		else {
			if ( store == cStore->getChar() ) { cStore->increment();} //add count to uniqueChar for the same char
			else { uChar.insert(cStore); cStore = new uniqueChar(store);} //add uniqueChar to heap and make new cStore
		}

		heap.deleteMin(); //delete previous min

	}while (!heap.isEmpty());

	
	uChar.insert(cStore);


	while (!uChar.isEmpty()){ //insert count to binary heap to find min

		//cout << ((uniqueChar*)uChar.findMin())->getChar() << " " << ((uniqueChar*)uChar.findMin())->getCount() << endl;
		compare.insert(((uniqueChar*)uChar.findMin())->getCount());
		totalCount += ((uniqueChar*)uChar.findMin())->getCount();
		swap.insert(uChar.findMin());
		uChar.deleteMin();
	}

	
	root = buildBTree(swap, compare, totalCount);

	return root;

}// end of storeToClass

BTree* buildBTree(BinaryHeap<BTree*> ori, BinaryHeap<int> comp, int total){

	BTree* root = NULL;
	BinaryHeap<BTree*> swap(10000);
	int min1 = 0;
	int min2 = 0;
	BTree* store = NULL;
	int newCount = 0;
	char check;
	
	while( comp.findMin() != total){

		root = new BTree('\0', NULL, NULL);

		min1 = comp.findMin();
		comp.deleteMin();
		min2 = comp.findMin();
		comp.deleteMin();

		//cout << "this is min: " << min1 << " " << min2 << endl;

		while (!ori.isEmpty()){

			store = ori.findMin();
			//cout << store->getCount() << flush << endl;
			if (!root->full()){
				//cout << "in" << flush << endl;
				if (store->getCount() == min1){ root->setLeftChild(store);}
				else if ( store->getCount() == min2 && !root->rightFull()){ root->setRightChild(store);}
				else {
					swap.insert(store);}
			}
			else {  //if no storing 
			swap.insert(store); }
			
			ori.deleteMin();

			//cout << "continue: ";
			//cin >> check;
		}
		
		root->updateCount();
		
		ori.insert(root); //insert new root

		comp.insert(root->getCount()); //add new count to comp
		
		while( !swap.isEmpty()){ //return back the original BTree
			store = swap.findMin();
			ori.insert(store);
			swap.deleteMin();
		}

	}

	//cout << "this is final: " << comp.findMin() << endl;

	return root;
}

