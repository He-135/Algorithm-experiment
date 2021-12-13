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
		if (t->lchild->data != 0) {
			count += getLeaf(t->lchild);
		}
		if (t->rchild->data != 0) {
			count += getLeaf(t->rchild);
		}
		if (t->lchild->data == 0 && t->rchild->data == 0) { count++; }
		return count;
	}
	static vector<int> exchange(MyTree* t){
		vector<int> res;
		queue<MyTree*>q;
		q.push(t);
		while(!q.empty()){
			if(q.front()->data != 0){
				res.push_back(q.front()->data);
				q.push(q.front()->rchild);
				q.push(q.front()->lchild);
				q.pop();
			}
			else{
				res.push_back(q.front()->data);
				q.pop();
			}
		}
		return res;
	}
};

int main(void) {
	int count = 0;
	cin >> count;
	for (int i = 0; i < count; i++) {
		MyTree* t = NULL;
		MyTree::CreatTree(t);
		vector<int>result = MyTree::exchange(t);
		for(int i = 0; i < result.size(); i++){
			cout << result[i] << " ";
		}
		cout << endl;
	}
	return 0;
}

