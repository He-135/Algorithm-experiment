#include <iostream>
using namespace std;
#define SIZE 20
void print(int arr[SIZE + 1]);
class Sort{
public:
	static void InsertSort(int arr[SIZE +1]){
		int shift = 0;
		int compare = 0;
		cout << "��������" << endl;
		for(int i = 2; i < SIZE + 1; i++){
			if(arr[i-1] > arr[i]){//���ǰһ������������������һ����Ԫ�ش����Լ�����Ҫ�ƶ�
				compare++;
				arr[0] = arr[i];//�ڱ�sentinel
				int j = i - 1;
				for (; /*result[j] > arr[i]	�������ﲻ����ͳ�ƱȽϴ���*/; j--) {
					if (arr[j] <= arr[0]) {//���������ҵ���Ŀ��λ��
						compare++;//�����Ƿ���붼�����һ�αȽϣ����������Ҳ������ͳ��
						break;
					}
					compare++;
					arr[j + 1] = arr[j];//���ڱ����ֵ��������
					shift++;
				}
				arr[j + 1] = arr[0];//���ݽ̲���������---��ʼΪ��С�����ƶ�����Ϊ0����Ӧ�ò���ؼ����ƶ�
			}
			else { compare++; }
		}
		cout << "\t�Ƚϴ���Ϊ��" << compare << endl;
		cout << "\t�ƶ�����Ϊ��" << shift << endl;
		cout << "���������Ϊ��";
		print(arr);
		cout << endl;
	}
};

void print(int arr[SIZE + 1]){
	for(int i = 1; i < SIZE + 1; i++){
		cout << arr[i] << " ";
	}
	cout << endl;
}


int main(void){
	for(int j = 0; j < 3; j++){
		int arr[SIZE + 1];
		for (int i = 1; i < SIZE + 1; i++) {
			arr[i] = rand();
		}
		cout << "��" << j + 1 << "�Σ�" << endl;
		cout << "��ʼ����Ϊ��";
		print(arr);
		Sort::InsertSort(arr);
	}
	return 0;
}