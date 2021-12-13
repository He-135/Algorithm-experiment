#include <iostream>

#define STACK_INIT_SIZE 10
#define STACKINCREMENT 10
class myStack {
private:
	char* base;
	char* top;
	int stacksize;
public:
	bool InitStack() {
		this->base = (char*)malloc(STACK_INIT_SIZE * sizeof(char));
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
	void push(char temp) {
		if (this->top - this->base >= this->stacksize) {
			this->base = (char*)realloc(this->base, (this->stacksize + STACKINCREMENT) * sizeof(char));
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
	char getTop() {
		return *(this->top - 1);
	}
};

using namespace std;
int main(void){
	myStack s;
	s.InitStack();
	cout << "��������Ÿ�����";
	int count;
	cin >> count;
	cout << "���������Ŵ���";
	for(int i = 0; i < count; i++){
		char temp;
		cin >> temp;
		if(temp == '(' || temp == '['){
			s.push(temp);
		}
		else{
			if(s.empty()){//����������ƥ��
				cout << "�˴�����ƥ�䲻�Ϸ���" << endl;
				return 0;
			}
			if(temp == ')' && s.getTop() != '('){//û����')'ƥ��ķ���
				cout << "�˴�����ƥ�䲻�Ϸ���" << endl;
				return 0;
			}
			else if (temp == ']' && s.getTop() != '[') {//û����']'ƥ��ķ���
				cout << "�˴�����ƥ�䲻�Ϸ���" << endl;
				return 0;
			}
			else{
				s.pop();
			}
		}
	}
	if(!s.empty()){//��ʣ��˵�����Ų���һһ��Ӧ��
		cout << "�˴�����ƥ�䲻�Ϸ���" << endl;
		return 0;
	}
	else{
		cout << "ƥ��" << endl;
		return 0;
	}
}