//����1.3
//��������ֱ�Ӵӱ���Ͽ��ߣ���ʱ������ǰ�������Ҫ�ȿ�����·��Ȼ���������ŵ���β��

#include <iostream>

using namespace std;

//���ļ���ɶ��ڶ��ֳ��͵����䣬���ý�һ����λ����Ϊ����С��λ�ķ�ʽ���ռ�������ͬ������
//С����S_Carռ2����λ���ͳ�P_Carռ3����λ��1.5��С������������Truckռ6����λ��3��С������
//����С����ռ��ͣ����ջ��2���ռ䣬push���Σ������Դ�����
//����ʱ��Ҫ���복�ͣ�S---S_Car, P---P_Car, T---Truck

#define STACK_INIT_SIZE 13
//���ֳ�����ռ��λ��
#define S_CAR 2
#define P_CAR 3
#define TRUCK 6

//ÿ����λ��λʱ���շѽ��
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
	bool full(int type) {//����Ҫͣ��ĳ����ж��Ƿ����㹻ͣ�Ÿó��͵ĳ�λ
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
	int cnt = 0;//��¼ͣ�������м�����
	MyStack<Car>s;
	MyQueue q;
	do {
		cin >> status >> num >> time;//���복����Ϣ
		while (status != 'A' && status != 'D' && status != 'E') {
			cout << "���벻�Ϸ������������복��״̬��";
			cin >> status;
		}
		if (status == 'A') {//��������
			int type;
			char tempType;
			cout << "�����복�����ͣ�S--С������P--�ͳ���T--��������";
			cin >> tempType;
			//�жϳ�������
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
			if (!s.full(temp.getType())) {//������ûͣ��
				cnt++;
				cout << "\t" << num << "�ų�����ͣ������ͣ���ڵ�" << cnt << "��" << endl;
				for (int i = 0; i < temp.getType(); i++) {
					s.push(temp);
				}
			}
			else {//������������������ı���ϵȺ�
				q.EnQueue(temp);
				cout << "\t" << num << "�ų�ͣ���ڱ���ϵ�" << q.getSize() << "��" << endl;
			}
		}
		else if (status == 'D') {//�����뿪
			//���ж��Ƿ��Ǳ���ϵĳ�Ҫ�뿪
			int cnt = q.getSize();
			bool find = false;//�����ж��Ƿ��ڱ�����ҵ�
			for(int i = 0; i < cnt; i++){
				if(q.front().getNum() == num){
					find = true;
					cout << "\t" << num << "�ų��ӱ�����뿪" << endl;
					q.DeQueue();
					break;
				}
				else{
					q.EnQueue(q.DeQueue());//����ǰ�������Ҫ�ȿ�����·��Ȼ���������ŵ���β
				}
			}
			if(!find){//��������û�ҵ����������ͣ������
				MyStack<Car>temp;//��Ҫ�뿪�ĳ�֮����ĳ������˳�ͣ����Ϊ����·
				while (!s.empty() && s.getTop().getNum() != num) {//�ҵ�Ҫ�뿪�ĳ�����Ϣ
					temp.push(s.getTop());
					s.pop();
				}
				if (s.empty()) {//δ�ҵ�Ҫ�뿪�ĳ�����Ϣ
					cout << "����������ͣ������" << endl;
					while (!temp.empty()) {//�˳��ĳ����½���ͣ����
						s.push(temp.getTop());
						temp.pop();
					}
				}
				else {//��ʱ���ҵ�Ŀ�공������ջ��
					cnt--;
					int stayTime = time - s.getTop().getArriveTime();
					int fee = (stayTime)*s.getTop().getType() * FEE;//��ͬ�����շѲ�ͬ
					cout << "\t" << s.getTop().getNum() << "�ų��뿪ͣ����" << endl;
					cout << "\tͣ��ʱ�䣺" << stayTime << endl;
					cout << "\t�շ�" << fee << "Ԫ" << endl;
					while (s.getTop().getNum() == num) {//����ʻ��ͣ����
						s.pop();
					}
					while (!temp.empty()) {//�˳��ĳ����½���ͣ����
						s.push(temp.getTop());
						temp.pop();
					}
					if (!q.empty() && !s.full(q.front().getType())) {//��������г���q��Ϊ�գ���ͣ��������ͣ���±���ϵĵ�һ������ɽ���һ����
						Car c = q.DeQueue();//����ϵ�һ����
						c.setArriveTime(time);//ǰһ�����ߵ�ʱ����������������ʱ��
						cnt++;
						cout << endl << "\t" << c.getNum() << "�ų�����ͣ������ͣ���ڵ�" << cnt << "��" << endl;
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