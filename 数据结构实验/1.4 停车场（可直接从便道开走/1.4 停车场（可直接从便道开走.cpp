//基于1.3
//汽车可以直接从便道上开走，此时排在它前面的汽车要先开走让路，然后再依次排到队尾。

#include <iostream>

using namespace std;

//本文件完成对于多种车型的适配，采用将一个车位划分为两个小车位的方式解决占地面积不同的问题
//小汽车S_Car占2个车位，客车P_Car占3个车位（1.5辆小汽车），卡车Truck占6个车位（3辆小汽车）
//所以小汽车占用停车场栈的2个空间，push两次；其余以此类推
//输入时需要输入车型，S---S_Car, P---P_Car, T---Truck

#define STACK_INIT_SIZE 13
//各种车型所占车位数
#define S_CAR 2
#define P_CAR 3
#define TRUCK 6

//每个车位单位时间收费金额
#define FEE 5

template <typename T>
class MyStack {
private:
	T* base;
	T* top;
	int stacksize;
	int count = 0;
public:
	MyStack() {
		this->base = (T*)malloc(STACK_INIT_SIZE * sizeof(T));
		if (!this->base) {
			exit(OVERFLOW);
		}
		this->top = this->base;
		this->stacksize = STACK_INIT_SIZE;
	}
	void DestroyStack() {
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
	bool full(int type) {//根据要停入的车型判断是否还有足够停放该车型的车位
		if (this->stacksize - this->count < type) {
			return true;
		}
		return false;
	}
	void push(T temp) {
		if (this->top - this->base >= this->stacksize) {
			exit(OVERFLOW);
		}
		*this->top = temp;
		this->top++;
		count++;
	}
	bool pop() {
		if (this->top == this->base) {
			return false;
		}
		this->top--;
		count--;
		return true;
	}
	T getTop() {
		return *(this->top - 1);
	}
	int getSize() {
		return this->top - this->base;
	}
};

class Car {
private:
	int num;
	int arriveTime;
	int type;
public:
	Car() :Car(0, 0, 2) {}
	Car(int num, int arriveTime, int type) :num(num), arriveTime(arriveTime), type(type) {}
	int getNum(void) { return this->num; }
	int getArriveTime(void) { return this->arriveTime; }
	int getType(void) { return this->type; }
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
	ListNode* top;
	ListNode* rear;
	int count = 0;
	MyQueue() {
		rear = new ListNode();
		top = rear;
		if (!top) { exit(OVERFLOW); }
	}
	void EnQueue(Car temp) {
		ListNode* p = new ListNode(temp);
		if (!p) { exit(OVERFLOW); }
		rear->next = p;
		rear = rear->next;
		count++;
	}
	Car DeQueue() {
		ListNode* temp = top->next;
		Car res = temp->data;
		top->next = temp->next;
		if (rear == temp) { rear = top; }
		delete temp;
		count--;
		return res;
	}
	bool empty() {
		if (top == rear) { return true; }
		else { return false; }
	}
	int getSize() {
		return this->count;
	}
	Car front() {
		return top->next->data;
	}
};



int main(void) {
	char status;
	int num, time;
	int cnt = 0;//记录停车场内有几辆车
	MyStack<Car>s;
	MyQueue q;
	do {
		cin >> status >> num >> time;//输入车辆信息
		while (status != 'A' && status != 'D' && status != 'E') {
			cout << "输入不合法，请重新输入车辆状态：";
			cin >> status;
		}
		if (status == 'A') {//车辆到达
			int type;
			char tempType;
			cout << "请输入车辆类型（S--小汽车，P--客车，T--卡车）：";
			cin >> tempType;
			//判断车辆类型
			switch (tempType) {
			case 'S':
				type = S_CAR;
				break;
			case 'P':
				type = P_CAR;
				break;
			case 'T':
				type = TRUCK;
				break;
			}
			Car temp = Car(num, time, type);
			if (!s.full(temp.getType())) {//车场还没停满
				cnt++;
				cout << "\t" << num << "号车进入停车场，停放在第" << cnt << "个" << endl;
				for (int i = 0; i < temp.getType(); i++) {
					s.push(temp);
				}
			}
			else {//车场已满，需在门外的便道上等候
				q.EnQueue(temp);
				cout << "\t" << num << "号车停放在便道上第" << q.getSize() << "个" << endl;
			}
		}
		else if (status == 'D') {//车辆离开
			//先判断是否是便道上的车要离开
			int cnt = q.getSize();
			bool find = false;//用于判断是否在便道上找到
			for(int i = 0; i < cnt; i++){
				if(q.front().getNum() == num){
					find = true;
					cout << "\t" << num << "号车从便道上离开" << endl;
					q.DeQueue();
					break;
				}
				else{
					q.EnQueue(q.DeQueue());//排在前面的汽车要先开走让路，然后再依次排到队尾
				}
			}
			if(!find){//如果便道上没找到，则可能在停车场内
				MyStack<Car>temp;//在要离开的车之后开入的车辆先退出停车场为它让路
				while (!s.empty() && s.getTop().getNum() != num) {//找到要离开的车的信息
					temp.push(s.getTop());
					s.pop();
				}
				if (s.empty()) {//未找到要离开的车的信息
					cout << "该辆车不在停车场内" << endl;
					while (!temp.empty()) {//退出的车重新进入停车场
						s.push(temp.getTop());
						temp.pop();
					}
				}
				else {//此时已找到目标车辆，在栈顶
					cnt--;
					int stayTime = time - s.getTop().getArriveTime();
					int fee = (stayTime)*s.getTop().getType() * FEE;//不同车型收费不同
					cout << "\t" << s.getTop().getNum() << "号车离开停车场" << endl;
					cout << "\t停留时间：" << stayTime << endl;
					cout << "\t收费" << fee << "元" << endl;
					while (s.getTop().getNum() == num) {//车辆驶出停车场
						s.pop();
					}
					while (!temp.empty()) {//退出的车重新进入停车场
						s.push(temp.getTop());
						temp.pop();
					}
					if (!q.empty() && !s.full(q.front().getType())) {//若便道上有车（q不为空）且停车场内能停放下便道上的第一辆车则可进入一辆车
						Car c = q.DeQueue();//便道上第一辆车
						c.setArriveTime(time);//前一辆车走的时间就是这辆车进入的时间
						cnt++;
						cout << endl << "\t" << c.getNum() << "号车进入停车场，停放在第" << cnt << "个" << endl;
						for (int i = 0; i < c.getType(); i++) {
							s.push(c);
						}
					}
				}
			}
		}
	} while (status != 'E');
	return 0;
}