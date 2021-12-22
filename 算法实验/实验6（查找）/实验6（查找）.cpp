#include <iostream>
#include <queue>
using namespace std;

class BST{
public:
	int data;
	BST* lchild = nullptr;
	BST* rchild = nullptr;
	static int depth;
	BST(int data){
		this->data = data;
	}
	//�������봴��������
	static void createTree(BST*& tree) {//��-1Ϊ��β
		int val;
		cin >> val;
		if (val == -1) { return; }//��������
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
				createTree(tree);//ʹ�õݹ�
			}
		}
	}
	//�ڶ������в���
	static bool serch(BST* tree, int temp){
		int count = 0;
		while(tree != nullptr){
			count++;
			if (temp == tree->data) {
				cout << temp << "���ҳɹ������ҳ��ȣ�" << count << endl;
				return true;
			}
			else if(temp > tree->data){
				tree = tree->rchild;
			}
			else{
				tree = tree->lchild;
			}
		}
		cout << temp << "����ʧ�ܣ����ҳ��ȣ�" << count << endl;
		return false;
	}
	//�������----����
	static void inOrder(BST* tree){
		if (tree == nullptr) { return; }
		inOrder(tree->lchild);
		cout << tree->data << " ";
		inOrder(tree->rchild);
	}

	//RDL����������ӡ������
	static void RDL(BST* t) {
		if (t) {
			depth++;//������һ����ȼ�1
			RDL(t->rchild);
			for (int i = 0; i < depth * 2; i++) {//�ÿո����ͬһ��Ľ���ӡ��ͬһ��
				cout << " ";
			}
			cout << t->data << endl;
			RDL(t->lchild);
			depth--;//�ò������ص���һ�㣬��ȼ�1
		}
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

int BST::depth = -1;
int main(void){
	BST* tree = nullptr;
	BST::createTree(tree);
	BST::RDL(tree);
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