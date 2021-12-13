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
	//��ʼ��һ����
	static void CreatTree(MyTree * & t){
		char ch;
		cin >> ch;
		if(ch == '#'){//��#����ո��ַ�
			t = NULL;
		}
		else{//��ǰ��������������
			t = new MyTree(ch);//��˫�׽��
			CreatTree(t->lchild);//������
			CreatTree(t->rchild);//����Һ���
		}
	}

	//ǰ�����
	static void PreOrderTraverse(MyTree * t){
		if(t){//��Ϊ���������
			cout << t->data;
			PreOrderTraverse(t->lchild);
			PreOrderTraverse(t->rchild);
		}
	}

	//�������
	static void PostOrderTraverse(MyTree* t) {
		if (t) {
			PostOrderTraverse(t->lchild);
			PostOrderTraverse(t->rchild);
			cout << t->data;
		}
	}

	//�������
	static void InOrderTraverse(MyTree* t) {
		if (t) {
			InOrderTraverse(t->lchild);
			cout << t->data;
			InOrderTraverse(t->rchild);
		}
	}

	//RDL������
	static void RDL(MyTree* t){
		if(t){
			depth++;//������һ����ȼ�1
			RDL(t->rchild);
			for(int i = 0; i < depth * 2; i++){//�ÿո����ͬһ��Ľ���ӡ��ͬһ��
				cout << " ";
			}
			cout << t->data << endl;
			RDL(t->lchild);
			depth--;//�ò������ص���һ�㣬��ȼ�1
		}
	}
};

int MyTree::depth = -1;
int main(void){
	MyTree* t = NULL;
	MyTree::CreatTree(t);
	cout << "ǰ��";
	MyTree::PreOrderTraverse(t);
	cout << endl;
	cout << "����";
	MyTree::InOrderTraverse(t);
	cout << endl;
	cout << "����";
	MyTree::PostOrderTraverse(t);
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	MyTree::RDL(t);
	return 0;
}