#include <iostream>

using namespace std;

#define STACK_INIT_SIZE 2//���ͣ��2 ����
#define STACKINCREMENT 10
template <typename T>
class MyStack {
private:
	T* base;
	T* top;
	int stacksize;
public:
	MyStack() {
		this->base = (T*)malloc(STACK_INIT_SIZE * sizeof(T));
		if (!this->base) {
			exit(OVERFLOW);
		}
		this->top = this->base;
		this->stacksize = STACK_INIT_SIZE;
	}
	void DestroyStack(){
		free(this->base);
	}
	bool empty() {
		if (this->top == this->base) {
			return true;
		}
		else {
			return false;
		}
	}
	bool full(){
		if (this->top - this->base >= this->stacksize){
			return true;
		}
		return false;
	}
	void push(T temp) {
		/*if (this->top - this->base >= this->stacksize) {
			//ͣ������С���ɱ䣬���Բ�realloc
			this->base = (T*)realloc(this->base, (this->stacksize + STACKINCREMENT) * sizeof(T));
			if (!this->base) {
				exit(OVERFLOW);
			}
			this->top = this->base + this->stacksize;
			this->stacksize += STACKINCREMENT;
		}*/
		if (this->top - this->base >= this->stacksize){
			exit(OVERFLOW);
		}
		*this->top = temp;
		this->top++;
	}
	bool pop() {
		if (this->top == this->base) {
			return false;
		}
		this->top--;
		return true;
	}
	T getTop() {
		return *(this->top - 1);
	}
};

class Car {
private:
	int num;
	int arriveTime;
public:
	Car() :Car(0, 0) {}
	Car(int num, int arriveTime) :num(num), arriveTime(arriveTime) {}
	int getNum(void) { return this->num; }
	int getArriveTime(void) { return this->arriveTime; }
	void setArriveTime(int time) { this->arriveTime = time; }
};

class ListNode {
public:
	Car data;
	ListNode* next;
	ListNode() {}
	ListNode(Car temp) {
		this->data = temp;
		this->next = NULL;
	}
};

class MyQueue{
public:
	ListNode* front;
	ListNode* rear;
	MyQueue() {
		rear = new ListNode();
		front = rear;
		if (!front) { exit(OVERFLOW); }
	}
	void EnQueue(Car temp){
		ListNode* p = new ListNode(temp);
		if (!p) { exit(OVERFLOW); }
		rear->next = p;
		rear = rear->next;
	}
	Car DeQueue(){
		ListNode* temp = front->next;
		Car res = temp->data;
		front->next = temp->next;
		if (rear == temp) { rear = front; }
		delete temp;
		return res;
	}
	bool empty(){
		if (front == rear) { return true; }
		else { return false; }
	}

};






int main(void){
	char status;
	int num, time;
	MyStack<Car>s;
	MyQueue q;
	do{
		cin >> status >> num >> time;//���복����Ϣ
		while(status != 'A' && status != 'D' && status != 'E'){
			cout << "���벻�Ϸ������������복��״̬��";
			cin >> status;
		}
		if(status == 'A'){//��������
			Car temp = Car(num, time);
			if(!s.full()){ s.push(temp); }//������ûͣ��
			else { q.EnQueue(temp); }//������������������ı���ϵȺ�
		}
		else if(status == 'D'){//�����뿪
			MyStack<Car>temp;//��Ҫ�뿪�ĳ�֮����ĳ������˳�ͣ����Ϊ����·
			while(!s.empty() && s.getTop().getNum() != num){//�ҵ�Ҫ�뿪�ĳ�����Ϣ
				temp.push(s.getTop());
				s.pop();
			}
			if(s.empty()){//δ�ҵ�Ҫ�뿪�ĳ�����Ϣ
				cout << "����������ͣ������" << endl;
				while(!temp.empty()){//�˳��ĳ����½���ͣ����
					s.push(temp.getTop());
					temp.pop();
				}
			}
			else{
				int stayTime = time - s.getTop().getArriveTime();
				int fee = (stayTime) * 5;
				cout << "ͣ��ʱ�䣺" << stayTime << endl;
				cout << "�շ�" << fee << "Ԫ" << endl;
				s.pop();
				while (!temp.empty()) {//�˳��ĳ����½���ͣ����
					s.push(temp.getTop());
					temp.pop();
				}
				if(!q.empty()){//����һ����ͣ�����ڿճ�һ����λ����������г���q��Ϊ�գ���ɽ���һ����
					Car c = q.DeQueue();//����ϵ�һ����
					c.setArriveTime(time);//ǰһ�����ߵ�ʱ����������������ʱ��
					s.push(c);
				}
			}

		}
	} while (status != 'E');
	return 0;
}