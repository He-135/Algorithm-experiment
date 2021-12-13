#include <iostream>
using namespace std;

class BST{
public:
	int data;
	BST* lchild = nullptr;
	BST* rchild = nullptr;
	BST(int data){
		this->data = data;
	}
	static void createTree(BST*& tree) {
		int val;
		cin >> val;
		if (val == -1) { return; }
		else{
			if (tree == nullptr) {
				tree = new BST(val);
				createTree(tree);
			}
			else {
				BST* temp = tree;
				BST* newt = new BST(val);
				while (1) {
					if (temp->rchild == nullptr && val > temp->data) {
						temp->rchild = newt;
						break;
					}
					else if (temp->rchild != nullptr && val > temp->data) { temp = temp->rchild; }
					else if (temp->lchild == nullptr) {
						temp->lchild = newt;
						break;
					}
					else if (temp->lchild != nullptr) { temp = temp->lchild; }
				}
				createTree(tree);
			}
		}
	}
};


int main(void){
	BST* tree = nullptr;
	BST::createTree(tree);
	return 0;
}