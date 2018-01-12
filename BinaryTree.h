#ifndef BTREE_H
	#define BTREE_H


	class BTree {

		protected:
			char element;
			int count = 0;
			BTree* leftChild;
			BTree* rightChild;

		public:
			BTree(char element, BTree* left, BTree* right) : element(element), leftChild(left), rightChild(right) {}
			void setLeftChild(BTree* node) { 
				if(leftChild != NULL) {rightChild = node; return;} 
				leftChild = node; }
			void setRightChild(BTree* node) { rightChild = node; }
			void setCount(int num) { count = num;}
			int getCount(void) { return count;}
			void updateCount(void) { if(leftChild == NULL || rightChild == NULL) { std::cout << "yep" << std::endl;}
				this->count = leftChild->getCount() + rightChild->getCount();}
			bool full(void) { if( leftChild != NULL && rightChild != NULL) { return true;}
				else {return false;}}
			bool rightFull(void) { if (rightChild != NULL) {return true;} return false;}
			void printTree(std::string huff) {

				if( element != '\0') {
					std::cout << element;
					std::cout.width(5);
					std::cout << count;
					std::cout << " " << huff << std::endl;
				}

				else {
					huff = huff + '0';
					leftChild->printTree(huff);
					huff.pop_back();
					huff = huff + '1';
					rightChild->printTree(huff);
				}
								
			}

	};// end of BTree class

	class uniqueChar : public BTree
	{
		
		public:
			uniqueChar(char element): BTree(element, NULL, NULL) {count++;}
			void increment(void) {count++;}
			char getChar(void) { return element;}
			//getCount


	};// end of uniqueChar class

#endif 
