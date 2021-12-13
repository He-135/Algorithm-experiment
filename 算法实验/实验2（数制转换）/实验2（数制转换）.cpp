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
	cout << "请输入十进制：";
	cin >> num;
	myStack<int> s;
	s.InitStack();
	if(num >= 0 && num <= 7){//若十进制数为0~7则不用除，直接输出即可
		cout << "八进制：" << num;
	}
	else if(num >= 8){
		while (num >= 8) {//最终除到num<8时就不用除了，直接压入栈
			s.push(num % 8);//取除8得到的余数
			num = num / 8;//每次整数要除8
		}
		s.push(num);
		cout << "八进制：";
		while (!s.empty()) {
			cout << s.getTop();
			s.pop();
		}
	}

	return 0;
}