#include<iostream>
#include<vector>
using namespace std;
class List{
public:
	int num;
	int code;
	List* next = nullptr;
	List() :List(0, 0) {}
	List(int num, int code){
		this->num = num;
		this->code = code;
	}
};

int main(void){
	//构建链表
	List* head = new List();
	vector<int> code = { 5, 2, 4, 7, 9, 6, 3, 6 };
	List* p = head;
	for(int i = 0; i < code.size(); i++){
		List* temp = new List(i + 1, code[i]);
		p->next = temp;
		p = p->next;
	}
	p->next = head->next;//尾结点指向首结点形成单向循环链表

	vector<int> num;
	int m = 10;
	p = head;//p的下一个结点为所需的结点
	for(int j = 0; j < 8; j++){
		for (int i = 1; i < m; i++) {
			p = p->next;
		}
		num.push_back(p->next->num);
		m = p->next->code;
		p->next = p->next->next;
	}
	for(int i = 0; i < num.size(); i++){
		cout << num[i] << " ";
	}

}