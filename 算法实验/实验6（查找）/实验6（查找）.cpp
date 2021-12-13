#include <iostream>
#include <queue>
using namespace std;

class BST{
public:
	int data;
	BST* lchild = nullptr;
	BST* rchild = nullptr;
	BST(int data){
		this->data = data;
	}
	static void createTree(BST*& tree) {//以-1为结尾
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

	static bool serch(BST* tree, int temp){
		int count = 0;
		while(tree != nullptr){
			count++;
			if (temp == tree->data) {
				cout << temp << "查找成功！查找长度：" << count << endl;
				return true;
			}
			else if(temp > tree->data){
				tree = tree->rchild;
			}
			else{
				tree = tree->lchild;
			}
		}
		cout << temp << "查找失败！查找长度：" << count << endl;
		return false;
	}

	static void inOrder(BST* tree){
		if (tree == nullptr) { return; }
		inOrder(tree->lchild);
		cout << tree->data << " ";
		inOrder(tree->rchild);
	}

	~BST(){
		queue<BST*>q;
		q.push(this);
		while(!q.empty()){
			if (q.front()->lchild != nullptr) { q.push(q.front()->lchild); }
			if (q.front()->rchild != nullptr) { q.push(q.front()->rchild); }
			delete q.front();
			q.pop();
		}
	}
};


int main(void){
	BST* tree = nullptr;
	BST::createTree(tree);
	BST::serch(tree, 7);
	BST::serch(tree, 4);
	BST::serch(tree, 16);
	BST::serch(tree, 21);
	BST::serch(tree, 8);
	BST::serch(tree, 14);
	BST::inOrder(tree);
	cout << endl;
	return 0;
}