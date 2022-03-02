#include <iostream>

using namespace std;

#define PARKING_LOT_SIZE 2//最多停放2 辆车
//用于两个栈共享空间
#define STACK_INIT_SIZE 2 * PARKING_LOT_SIZE - 1//用来临时停放为给要离去的汽车让路而从停车场退出来的汽车的栈与停车场栈共享的空间

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
	void pop(int stackNum) {//stackNum用来选择栈
		if (stackNum == 1) { top1--; }
		else if (stackNum == 2) { top2++; }
		else {
			cout << "栈标号错误";
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
		if (stackNum == 1 && top1 == PARKING_LOT_SIZE - 1) { return true; }//停车场大小不能扩大
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
		cin >> status >> num >> time;//输入车辆信息
		while (status != 'A' && status != 'D' && status != 'E') {
			cout << "输入不合法，请重新输入车辆状态：";
			cin >> status;
		}
		if (status == 'A') {//车辆到达
			Car temp = Car(num, time);
			if (!s.full(1)) { 
				s.push(temp, 1); 
				cout << "\t" << num << "号车辆停放在停车场内由北向南" << s.getSize() + 1 << "号车位" << endl;
			}//车场还没停满
			else { 
				q.EnQueue(temp); 
				cout << "\t" << num << "号车辆停放在便道上第" << q.getSize() << "个" << endl;
			}//车场已满，需在门外的便道上等候
		}
		else if (status == 'D') {//车辆离开
			while (!s.empty(1) && s.top(1).getNum() != num) {//找到要离开的车的信息
				s.push(s.top(1), 2);//存入第2个栈
				s.pop(1);
			}
			if (s.empty(1)) {//未找到要离开的车的信息
				cout << "该辆车不在停车场内" << endl;
				while (!s.empty(2)) {//退出的车重新进入停车场(s.top1)
					s.push(s.top(2), 1);
					s.pop(2);
				}
			}
			else {
				int stayTime = time - s.top(1).getArriveTime();
				int fee = (stayTime) * 5;
				cout << "停留时间：" << stayTime << endl;
				cout << "收费" << fee << "元" << endl;
				s.pop(1);
				while (!s.empty(2)) {//退出的车重新进入停车场
					s.push(s.top(2), 1);
					s.pop(2);
				}
				if (!q.empty()) {//刚走一辆，停车场内空出一个车位，若便道上有车（q不为空）则可进入一辆车
					Car c = q.DeQueue();//便道上第一辆车
					c.setArriveTime(time);//前一辆车走的时间就是这辆车进入的时间
					s.push(c, 1);
					cout << endl << "\t" << c.getNum() << "号车辆进入停车场，停放在由北向南" << s.getSize() + 1 << "号车位" << endl;
				}
			}

		}
	} while (status != 'E');
	return 0;
}