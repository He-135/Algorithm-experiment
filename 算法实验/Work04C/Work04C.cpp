#include <iostream>
#include <vector>
#include <queue>

using namespace std;
class MyTree {
public:
	int data;
	MyTree* lchild, * rchild;
	int Ltag, Rtag;
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
				que.front()->data = temp;
				if (!(que.front()->lchild = new MyTree(0))) { exit(OVERFLOW); }
				if (!(que.front()->rchild = new MyTree(0))) { exit(OVERFLOW); }

				que.push(que.front()->lchild);
				que.push(que.front()->rchild);
				que.pop();
			}
		}

	}
	static void inThread(MyTree*& cur, MyTree*& pre) {
		if (cur != NULL && cur->data != 0) {
			inThread(cur->lchild, pre);
			if (cur->lchild->data == 0) {//Ã»ÓÐ×óº¢×Ó
				cur->lchild = pre;
				cur->Ltag = 1;
			}
			if (pre != NULL && pre->rchild != NULL && pre->rchild->data == 0) {
				pre->rchild = cur;
				pre->Rtag = 1;
			}
			pre = cur;
			inThread(cur->rchild, pre);
		}

	}
	static void InOrderTraverse(MyTree* t, vector<int>& v) {
		queue<MyTree*>q;
		q.push(t);
		while (!q.empty()) {
			if (q.front()->data == 0) {
				q.pop();
			}
			else {
				if (q.front()->Ltag == 0 && q.front()->Rtag == 0) {
					//cout << q.front()->lchild->data << " " << q.front()->rchild->data << " ";
					v.push_back(q.front()->lchild->data);
					v.push_back(q.front()->rchild->data);
				}
				else {
					if (q.front()->Ltag == 1) {
						//cout << q.front()->lchild->data << " "; 
						v.push_back(q.front()->lchild->data);
					}
					else {
						auto temp = q.front()->lchild;
						while (temp->rchild != q.front()) { temp = temp->rchild; }
						//cout << temp->data << " ";
						v.push_back(temp->data);
					}

					if (q.front()->Rtag == 1) {
						//cout << q.front()->rchild->data << " ";
						v.push_back(q.front()->rchild->data);
					}
					else {
						auto temp = q.front()->rchild;
						while (temp->lchild != q.front()) { temp = temp->lchild; }
						//cout << temp->data << " ";
						v.push_back(temp->data);
					}
				}
				if (q.front()->Ltag == 0) { q.push(q.front()->lchild); }
				if (q.front()->Rtag == 0) { q.push(q.front()->rchild); }
				q.pop();
			}
		}
		//cout << endl;
	}
};

int main(void) {
	int count = 0;
	cin >> count;
	vector<vector<int>>result;
	for (int i = 0; i < count; i++) {
		MyTree* t = NULL;
		MyTree::CreatTree(t);

		auto pre = new MyTree(0);
		auto pre_copy = pre;
		MyTree::inThread(t, pre);
		MyTree* temp = t;
		while (temp->rchild->data != 0) { temp = temp->rchild; }
		temp->rchild = pre_copy;
		temp->Rtag = 1;
		vector<int>res;
		MyTree::InOrderTraverse(t, res);
		result.push_back(res);
	}
	for(int i = 0; i < result.size(); i++){
		for(int j = 0; j < result[i].size(); j++){
			cout << result[i][j] << " ";
		}
		cout << endl;
	}
	return 0;
}

