#include <iostream>
using namespace std;

class MyTree{
public:
	char data;
	MyTree* lchild,* rchild;
	static int depth;
	MyTree(char data){
		this->data = data;
	}
	//初始化一棵树
	static void CreatTree(MyTree * & t){
		char ch;
		cin >> ch;
		if(ch == '#'){//用#代表空格字符
			t = NULL;
		}
		else{//以前序来建立二叉树
			t = new MyTree(ch);//先双亲结点
			CreatTree(t->lchild);//再左孩子
			CreatTree(t->rchild);//最后右孩子
		}
	}

	//前序遍历
	static void PreOrderTraverse(MyTree * t){
		if(t){//不为空树则访问
			cout << t->data;
			PreOrderTraverse(t->lchild);
			PreOrderTraverse(t->rchild);
		}
	}

	//后序遍历
	static void PostOrderTraverse(MyTree* t) {
		if (t) {
			PostOrderTraverse(t->lchild);
			PostOrderTraverse(t->rchild);
			cout << t->data;
		}
	}

	//中序遍历
	static void InOrderTraverse(MyTree* t) {
		if (t) {
			InOrderTraverse(t->lchild);
			cout << t->data;
			InOrderTraverse(t->rchild);
		}
	}

	//RDL遍历法
	static void RDL(MyTree* t){
		if(t){
			depth++;//进入下一层深度加1
			RDL(t->rchild);
			for(int i = 0; i < depth * 2; i++){//用空格控制同一层的结点打印在同一列
				cout << " ";
			}
			cout << t->data << endl;
			RDL(t->lchild);
			depth--;//该层访问完回到上一层，深度减1
		}
	}
};

int MyTree::depth = -1;
int main(void){
	MyTree* t = NULL;
	MyTree::CreatTree(t);
	cout << "前序：";
	MyTree::PreOrderTraverse(t);
	cout << endl;
	cout << "中序：";
	MyTree::InOrderTraverse(t);
	cout << endl;
	cout << "后序：";
	MyTree::PostOrderTraverse(t);
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	MyTree::RDL(t);
	return 0;
}