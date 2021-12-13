#include <iostream>

#include <queue>

using namespace std;
class MyTree {
public:
	int data;
	MyTree* lchild, * rchild;
	MyTree(int data) {
		this->data = data;
	}
	static void CreatTree(MyTree*& t) {
		queue<MyTree*>que;
		t = new MyTree(0);
		que.push(t);
		int temp;
		for (cin >> temp; temp != -1; cin >> temp) {
			if (temp == 0) { que.pop(); }
			else {
				que.front()->lchild = new MyTree(0);
				que.front()->rchild = new MyTree(0);
				que.front()->data = temp;
				que.push(que.front()->lchild);
				que.push(que.front()->rchild);
				que.pop();
			}
		}

	}
	static int getLeaf(MyTree* t) {
		int count = 0;
		if (t->lchild->data != 0 ) {
			count += getLeaf(t->lchild);
		}
		if(t->rchild->data != 0){
			count += getLeaf(t->rchild);
		}
		if (t->lchild->data == 0 && t->rchild->data == 0) { count++; }
		return count;
	}

};

int main(void) {
	int count = 0;
	cin >> count;
	for(int i = 0; i < count; i++){
		MyTree* t = NULL;
		MyTree::CreatTree(t);
		
		cout << MyTree::getLeaf(t) << endl;
	}
	return 0;
}

