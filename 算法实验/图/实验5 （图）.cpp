#include <iostream>
#include <stack>
#include <vector>
#include <queue>
using namespace std;
#define MaxVerNum 30

class Edge{//������ű߼�
public:
	int begin, end;
	Edge(int begin, int end){
		this->begin = begin;
		this->end = end;
	}
	void toString(){
		cout << "<" << begin << ", " << end << ">";
	}
};
class ArcNode{//�ڽӱ�߽��
public:
	int adjvex;
	ArcNode* next = NULL;
};

class Vnode{//��ͷ���
public:
	int vertex;
	ArcNode* firstedge = NULL;
};

class Graph{//ͼ
public:
	Vnode* vertices = NULL;//���㼯
	int vexnum, arcnum;//������������

	Graph(){//����һ��ͼ
		cout << "�����붥������";
		cin >> this->vexnum;
		while(this->vexnum > MaxVerNum){
			cout << "���������Ϊ30�����������룺";
			cin >> this->vexnum;
		}
		cout << "�����������";
		cin >> this->arcnum;
		this->vertices = new Vnode[this->vexnum + 1];//��ʼ�����㼯

		//���㼯Ĭ�ϴ�1��ʼ���
		cout << "�����붥����Ϣ��";
		for(int i = 1; i <= this->vexnum; i++){
			cin >> vertices[i].vertex;//��ÿ����������ݴ�����������
		}

		cout << "�������(vi,vj)���±�i,j��";
		for(int k = 0; k < this->arcnum; k++){
			int i, j;
			cin >> i >> j;
			ArcNode* arcNodeTemp1 = new ArcNode;
			arcNodeTemp1->adjvex = j;
			arcNodeTemp1->next = vertices[i].firstedge;//ʹ��ͷ�巨������
			vertices[i].firstedge = arcNodeTemp1;

			//�����������ͼ
			ArcNode* arcNodeTemp2 = new ArcNode;
			arcNodeTemp2->adjvex = i;
			arcNodeTemp2->next = vertices[j].firstedge;//ʹ��ͷ�巨������
			vertices[j].firstedge = arcNodeTemp2;
		}
	}


	void printGraph(){//����ڽӱ�
		for(int i = 1; i <= this->vexnum; i++){
			auto temp = vertices[i].firstedge;
			while(temp != NULL){
				cout << "(" << vertices[i].vertex << ", " << temp->adjvex << ")\t";
				temp = temp->next;
			}
			cout << endl;
		}
	}


	void DFS(){//�������
		int begin;
		cout << "������������ȱ��������(0~vexnum-1)��";
		cin >> begin;
		while(begin <= 0 || begin >= this->vexnum){
			cout << "���벻�Ϸ������������룺";
			cin >> begin;
		}

		bool* check = new bool[this->vexnum + 1];//���ڼ�¼�ý���Ƿ��ѷ���
		for(int i = 1; i <= this->vexnum; i++){
			check[i] = false;//��ʼ״̬Ϊÿ����㶼δ����
		}

		stack<ArcNode*>s;//���ڴ�ű߽�㣬����
		stack<Vnode>s_vnode;//���ڴ��ͷ��㣬����
		vector<Edge>edge;//���ڴ�ű߼�
		vector<int> result;//���ڼ�¼�����Ľ�����

		result.push_back(vertices[begin].vertex);//���û�ָ���Ľ�㿪ʼ����
		check[vertices[begin].vertex] = true;

		Vnode pre = vertices[begin];//��¼ÿ����β
		auto temp = vertices[begin].firstedge;
		result.push_back(temp->adjvex);//������������ͨͼ������temp��Ϊ��
		check[temp->adjvex] = true;
		edge.push_back(Edge(pre.vertex, temp->adjvex));
		s_vnode.push(pre);
		s.push(temp);
		pre = vertices[temp->adjvex];
		temp = vertices[temp->adjvex].firstedge;
		while(!s.empty() || temp != NULL){
			if(temp == NULL){//���л���
				temp = s.top()->next;
				s.pop();
				pre = s_vnode.top();
				s_vnode.pop();
			}
			else if (check[temp->adjvex]) {//ֱ�ӷ�����һ���ھ�,��ʱpre����
				temp = temp->next;
			}
			else{
				result.push_back(temp->adjvex);
				check[temp->adjvex] = true;
				edge.push_back(Edge(pre.vertex, temp->adjvex));
				s_vnode.push(pre);
				s.push(temp);
				pre = vertices[temp->adjvex];
				temp = vertices[temp->adjvex].firstedge;
			}
		}
		cout << "������ȱ��������";
		for(int i = 0; i < result.size(); i++){
			cout << result[i] << " ";
		}
		cout << endl;

		//����������ı�
		cout << "������ȱ����߼���";
		for (int i = 0; i < edge.size(); i++){
			edge[i].toString();
			cout << " ";
		}
		cout << endl;
		delete[]check;
	}


	void BFS(){//������ȱ���
		int begin;
		cout << "�����������ȱ��������(0~vexnum-1)��";
		cin >> begin;
		while (begin <= 0 || begin >= this->vexnum) {
			cout << "���벻�Ϸ������������룺";
			cin >> begin;
		}
		bool* check = new bool[this->vexnum + 1];//���ڼ�¼�ý���Ƿ��ѷ���
		for (int i = 1; i <= this->vexnum; i++) {
			check[i] = false;//��ʼ״̬Ϊÿ����㶼δ����
		}
		queue<ArcNode*>q;//���ڲ�α���;
		vector<Edge>edge;//���ڴ�ű߼�
		vector<int> result;//���ڼ�¼�����Ľ�����
		result.push_back(vertices[begin].vertex);//���û�ָ���Ľ�㿪ʼ����
		check[vertices[begin].vertex] = true;

		Vnode pre = vertices[begin];//��¼ÿ����β
		auto temp = vertices[begin].firstedge;
		result.push_back(temp->adjvex);//������������ͨͼ������temp��Ϊ��
		check[temp->adjvex] = true;
		edge.push_back(Edge(pre.vertex, temp->adjvex));
		q.push(temp);
		temp = temp->next;
		while(!q.empty() || temp != NULL){
			if(temp == NULL){
				pre = vertices[q.front()->adjvex];
				temp = vertices[q.front()->adjvex].firstedge;
				q.pop();
			}
			else if(check[temp->adjvex]){//ֱ�ӷ�����һ������ʱpre����
				temp = temp->next;
			}
			else{
				result.push_back(temp->adjvex);
				check[temp->adjvex] = true;
				edge.push_back(Edge(pre.vertex, temp->adjvex));
				q.push(temp);
				temp = temp->next;//��ʱpreҲ����
			}
		}
		cout << "������ȱ��������";
		for (int i = 0; i < result.size(); i++) {
			cout << result[i] << " ";
		}
		cout << endl;

		//����������ı�
		cout << "������ȱ����߼���";
		for (int i = 0; i < edge.size(); i++) {
			edge[i].toString();
			cout << " ";
		}
		cout << endl;
		delete[]check;
	}
};
int main(void){
	Graph graph;
	graph.printGraph();
	graph.DFS();
	graph.BFS();
	return 0;
}