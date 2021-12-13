#include <iostream>

using namespace std;

#define STACK_INIT_SIZE 10
#define STACKINCREMENT 10
template <typename T>
class myStack {
private:
	T* base;
	T* top;
	int stacksize;
public:
	bool InitStack() {
		this->base = (T*)malloc(STACK_INIT_SIZE * sizeof(T));
		if (!this->base) {
			return false;
		}
		this->top = this->base;
		this->stacksize = STACK_INIT_SIZE;
		return true;
	}
	bool empty() {
		if (this->top == this->base) {
			return true;
		}
		else {
			return false;
		}
	}
	void push(T temp) {
		if (this->top - this->base >= this->stacksize) {
			int i = this->top - this->base;
			this->base = (T*)realloc(this->base, (this->stacksize + STACKINCREMENT) * sizeof(T));
			if (!this->base) {
				exit(OVERFLOW);
			}
			this->top = this->base + this->stacksize;
			this->stacksize += STACKINCREMENT;
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

int main(void){
	int num;
	cout << "������ʮ���ƣ�";
	cin >> num;
	myStack<int> s;
	s.InitStack();
	if(num >= 0 && num <= 7){//��ʮ������Ϊ0~7���ó���ֱ���������
		cout << "�˽��ƣ�" << num;
	}
	else if(num >= 8){
		while (num >= 8) {//���ճ���num<8ʱ�Ͳ��ó��ˣ�ֱ��ѹ��ջ
			s.push(num % 8);//ȡ��8�õ�������
			num = num / 8;//ÿ������Ҫ��8
		}
		s.push(num);
		cout << "�˽��ƣ�";
		while (!s.empty()) {
			cout << s.getTop();
			s.pop();
		}
	}

	return 0;
}