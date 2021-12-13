#include <iostream>
#include <stack>
#include <vector>
#include <queue>
using namespace std;
#define MaxVerNum 30

class Edge{//用来存放边集
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
class ArcNode{//邻接表边结点
public:
	int adjvex;
	ArcNode* next = NULL;
};

class Vnode{//表头结点
public:
	int vertex;
	ArcNode* firstedge = NULL;
};

class Graph{//图
public:
	Vnode* vertices = NULL;//顶点集
	int vexnum, arcnum;//顶点数，边数

	Graph(){//创建一个图
		cout << "请输入顶点数：";
		cin >> this->vexnum;
		while(this->vexnum > MaxVerNum){
			cout << "顶点数最大为30，请重新输入：";
			cin >> this->vexnum;
		}
		cout << "请输入边数：";
		cin >> this->arcnum;
		this->vertices = new Vnode[this->vexnum + 1];//初始化顶点集

		//顶点集默认从1开始编号
		cout << "请输入顶点信息：";
		for(int i = 1; i <= this->vexnum; i++){
			cin >> vertices[i].vertex;//将每个顶点的数据存入其数据域
		}

		cout << "请输入边(vi,vj)的下标i,j：";
		for(int k = 0; k < this->arcnum; k++){
			int i, j;
			cin >> i >> j;
			ArcNode* arcNodeTemp1 = new ArcNode;
			arcNodeTemp1->adjvex = j;
			arcNodeTemp1->next = vertices[i].firstedge;//使用头插法插入结点
			vertices[i].firstedge = arcNodeTemp1;

			//输入的是无向图
			ArcNode* arcNodeTemp2 = new ArcNode;
			arcNodeTemp2->adjvex = i;
			arcNodeTemp2->next = vertices[j].firstedge;//使用头插法插入结点
			vertices[j].firstedge = arcNodeTemp2;
		}
	}


	void printGraph(){//输出邻接表
		for(int i = 1; i <= this->vexnum; i++){
			auto temp = vertices[i].firstedge;
			while(temp != NULL){
				cout << "(" << vertices[i].vertex << ", " << temp->adjvex << ")\t";
				temp = temp->next;
			}
			cout << endl;
		}
	}


	void DFS(){//深度优先
		int begin;
		cout << "请输入深度优先遍历的起点(0~vexnum-1)：";
		cin >> begin;
		while(begin <= 0 || begin >= this->vexnum){
			cout << "输入不合法，请重新输入：";
			cin >> begin;
		}

		bool* check = new bool[this->vexnum + 1];//用于记录该结点是否已访问
		for(int i = 1; i <= this->vexnum; i++){
			check[i] = false;//初始状态为每个结点都未访问
		}

		stack<ArcNode*>s;//用于存放边结点，回溯
		stack<Vnode>s_vnode;//用于存放头结点，回溯
		vector<Edge>edge;//用于存放边集
		vector<int> result;//用于记录遍历的结点次序

		result.push_back(vertices[begin].vertex);//从用户指定的结点开始访问
		check[vertices[begin].vertex] = true;

		Vnode pre = vertices[begin];//记录每个弧尾
		auto temp = vertices[begin].firstedge;
		result.push_back(temp->adjvex);//由于是无向连通图，所以temp不为空
		check[temp->adjvex] = true;
		edge.push_back(Edge(pre.vertex, temp->adjvex));
		s_vnode.push(pre);
		s.push(temp);
		pre = vertices[temp->adjvex];
		temp = vertices[temp->adjvex].firstedge;
		while(!s.empty() || temp != NULL){
			if(temp == NULL){//进行回溯
				temp = s.top()->next;
				s.pop();
				pre = s_vnode.top();
				s_vnode.pop();
			}
			else if (check[temp->adjvex]) {//直接访问下一个邻居,此时pre不变
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
		cout << "深度优先遍历结果：";
		for(int i = 0; i < result.size(); i++){
			cout << result[i] << " ";
		}
		cout << endl;

		//输出生成树的边
		cout << "深度优先遍历边集：";
		for (int i = 0; i < edge.size(); i++){
			edge[i].toString();
			cout << " ";
		}
		cout << endl;
		delete[]check;
	}


	void BFS(){//广度优先遍历
		int begin;
		cout << "请输入广度优先遍历的起点(0~vexnum-1)：";
		cin >> begin;
		while (begin <= 0 || begin >= this->vexnum) {
			cout << "输入不合法，请重新输入：";
			cin >> begin;
		}
		bool* check = new bool[this->vexnum + 1];//用于记录该结点是否已访问
		for (int i = 1; i <= this->vexnum; i++) {
			check[i] = false;//初始状态为每个结点都未访问
		}
		queue<ArcNode*>q;//用于层次遍历;
		vector<Edge>edge;//用于存放边集
		vector<int> result;//用于记录遍历的结点次序
		result.push_back(vertices[begin].vertex);//从用户指定的结点开始访问
		check[vertices[begin].vertex] = true;

		Vnode pre = vertices[begin];//记录每个弧尾
		auto temp = vertices[begin].firstedge;
		result.push_back(temp->adjvex);//由于是无向连通图，所以temp不为空
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
			else if(check[temp->adjvex]){//直接访问下一个，此时pre不变
				temp = temp->next;
			}
			else{
				result.push_back(temp->adjvex);
				check[temp->adjvex] = true;
				edge.push_back(Edge(pre.vertex, temp->adjvex));
				q.push(temp);
				temp = temp->next;//此时pre也不变
			}
		}
		cout << "广度优先遍历结果：";
		for (int i = 0; i < result.size(); i++) {
			cout << result[i] << " ";
		}
		cout << endl;

		//输出生成树的边
		cout << "广度优先遍历边集：";
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