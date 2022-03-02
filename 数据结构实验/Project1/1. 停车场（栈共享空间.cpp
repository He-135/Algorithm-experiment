#include <iostream>

using namespace std;

#define PARKING_LOT_SIZE 2//���ͣ��2 ����
//��������ջ����ռ�
#define STACK_INIT_SIZE 2 * PARKING_LOT_SIZE - 1//������ʱͣ��Ϊ��Ҫ��ȥ��������·����ͣ�����˳�����������ջ��ͣ����ջ����Ŀռ�

template<typename T>
class MyStack {
private:
	T data[STACK_INIT_SIZE];
	int top1;
	int top2;
public:
	MyStack() {
		if (!data) { exit(OVERFLOW); }
		top1 = -1;
		top2 = STACK_INIT_SIZE;
	}
	void pop(int stackNum) {//stackNum����ѡ��ջ
		if (stackNum == 1) { top1--; }
		else if (stackNum == 2) { top2++; }
		else {
			cout << "ջ��Ŵ���";
			exit;
		}
	}
	void push(T e, int stackNum) {
		if (stackNum == 1 && top1 + 1 < top2) {
			top1++;
			data[top1] = e;
		}
		else if (stackNum == 2 && top2 - 1 > top1) {
			top2--;
			data[top2] = e;
		}
		else { exit(OVERFLOW); }
	}
	T top(int stackNum) {
		if (stackNum == 1 && top1 != -1) {
			return data[top1];
		}
		else if (stackNum == 2 && top2 != STACK_INIT_SIZE) {
			return data[top2];
		}
	}
	bool full(int stackNum) {
		if (stackNum == 1 && top1 == PARKING_LOT_SIZE - 1) { return true; }//ͣ������С��������
		else if (stackNum == 2 && top2 == PARKING_LOT_SIZE) { return true; }
		else if (stackNum != 1 && stackNum != 2) { exit; }
		else { return false; }
	}
	bool empty(int stackNum) {
		if (stackNum == 1 && top1 == -1) { return true; }
		else if (stackNum == 2 && top2 == STACK_INIT_SIZE) { return true; }
		else if (stackNum != 1 && stackNum != 2) { exit; }
		else { return false; }
	}
	int getSize() {
		return top1;
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

class MyQueue {
public:
	ListNode* front;
	ListNode* rear;
	int count = 0;
	MyQueue() {
		rear = new ListNode();
		front = rear;
		if (!front) { exit(OVERFLOW); }
	}
	void EnQueue(Car temp) {
		ListNode* p = new ListNode(temp);
		if (!p) { exit(OVERFLOW); }
		rear->next = p;
		rear = rear->next;
		count++;
	}
	Car DeQueue() {
		ListNode* temp = front->next;
		Car res = temp->data;
		front->next = temp->next;
		if (rear == temp) { rear = front; }
		delete temp;
		count--;
		return res;
	}
	bool empty() {
		if (front == rear) { return true; }
		else { return false; }
	}
	int getSize() {
		return this->count;
	}
};


int main(void) {
	char status;
	int num, time;
	MyStack<Car>s;
	MyQueue q;
	do {
		cin >> status >> num >> time;//���복����Ϣ
		while (status != 'A' && status != 'D' && status != 'E') {
			cout << "���벻�Ϸ������������복��״̬��";
			cin >> status;
		}
		if (status == 'A') {//��������
			Car temp = Car(num, time);
			if (!s.full(1)) { 
				s.push(temp, 1); 
				cout << "\t" << num << "�ų���ͣ����ͣ�������ɱ�����" << s.getSize() + 1 << "�ų�λ" << endl;
			}//������ûͣ��
			else { 
				q.EnQueue(temp); 
				cout << "\t" << num << "�ų���ͣ���ڱ���ϵ�" << q.getSize() << "��" << endl;
			}//������������������ı���ϵȺ�
		}
		else if (status == 'D') {//�����뿪
			while (!s.empty(1) && s.top(1).getNum() != num) {//�ҵ�Ҫ�뿪�ĳ�����Ϣ
				s.push(s.top(1), 2);//�����2��ջ
				s.pop(1);
			}
			if (s.empty(1)) {//δ�ҵ�Ҫ�뿪�ĳ�����Ϣ
				cout << "����������ͣ������" << endl;
				while (!s.empty(2)) {//�˳��ĳ����½���ͣ����(s.top1)
					s.push(s.top(2), 1);
					s.pop(2);
				}
			}
			else {
				int stayTime = time - s.top(1).getArriveTime();
				int fee = (stayTime) * 5;
				cout << "ͣ��ʱ�䣺" << stayTime << endl;
				cout << "�շ�" << fee << "Ԫ" << endl;
				s.pop(1);
				while (!s.empty(2)) {//�˳��ĳ����½���ͣ����
					s.push(s.top(2), 1);
					s.pop(2);
				}
				if (!q.empty()) {//����һ����ͣ�����ڿճ�һ����λ����������г���q��Ϊ�գ���ɽ���һ����
					Car c = q.DeQueue();//����ϵ�һ����
					c.setArriveTime(time);//ǰһ�����ߵ�ʱ����������������ʱ��
					s.push(c, 1);
					cout << endl << "\t" << c.getNum() << "�ų�������ͣ������ͣ�����ɱ�����" << s.getSize() + 1 << "�ų�λ" << endl;
				}
			}

		}
	} while (status != 'E');
	return 0;
}