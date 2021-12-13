#include <iostream>

using namespace std;

#define STACK_INIT_SIZE 2//最多停放2 辆车
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
			//停车场大小不可变，所以不realloc
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
		cin >> status >> num >> time;//输入车辆信息
		while(status != 'A' && status != 'D' && status != 'E'){
			cout << "输入不合法，请重新输入车辆状态：";
			cin >> status;
		}
		if(status == 'A'){//车辆到达
			Car temp = Car(num, time);
			if(!s.full()){ s.push(temp); }//车场还没停满
			else { q.EnQueue(temp); }//车场已满，需在门外的便道上等候
		}
		else if(status == 'D'){//车辆离开
			MyStack<Car>temp;//在要离开的车之后开入的车辆先退出停车场为它让路
			while(!s.empty() && s.getTop().getNum() != num){//找到要离开的车的信息
				temp.push(s.getTop());
				s.pop();
			}
			if(s.empty()){//未找到要离开的车的信息
				cout << "该辆车不在停车场内" << endl;
				while(!temp.empty()){//退出的车重新进入停车场
					s.push(temp.getTop());
					temp.pop();
				}
			}
			else{
				int stayTime = time - s.getTop().getArriveTime();
				int fee = (stayTime) * 5;
				cout << "停留时间：" << stayTime << endl;
				cout << "收费" << fee << "元" << endl;
				s.pop();
				while (!temp.empty()) {//退出的车重新进入停车场
					s.push(temp.getTop());
					temp.pop();
				}
				if(!q.empty()){//刚走一辆，停车场内空出一个车位，若便道上有车（q不为空）则可进入一辆车
					Car c = q.DeQueue();//便道上第一辆车
					c.setArriveTime(time);//前一辆车走的时间就是这辆车进入的时间
					s.push(c);
				}
			}

		}
	} while (status != 'E');
	return 0;
}