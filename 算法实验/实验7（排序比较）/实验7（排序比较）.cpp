#include <iostream>
using namespace std;
#define SIZE 20
void print(int arr[SIZE + 1]);
class Sort{
public:
	static void InsertSort(int arr[SIZE +1]){
		int shift = 0;
		int compare = 0;
		cout << "插入排序：" << endl;
		for(int i = 2; i < SIZE + 1; i++){
			if(arr[i-1] > arr[i]){//如果前一个（已排序数组的最后一个）元素大于自己则需要移动
				compare++;
				arr[0] = arr[i];//哨兵sentinel
				int j = i - 1;
				for (; /*result[j] > arr[i]	放在这里不方便统计比较次数*/; j--) {
					if (arr[j] <= arr[0]) {//成立则已找到了目标位置
						compare++;//无论是否进入都会产生一次比较，这样不会多也不会少统计
						break;
					}
					compare++;
					arr[j + 1] = arr[j];//比哨兵大的值都往后移
					shift++;
				}
				arr[j + 1] = arr[0];//根据教材最好情况下---初始为从小到大，移动次数为0，这应该不算关键字移动
			}
			else { compare++; }
		}
		cout << "\t比较次数为：" << compare << endl;
		cout << "\t移动次数为：" << shift << endl;
		cout << "排序后序列为：";
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
		cout << "第" << j + 1 << "次：" << endl;
		cout << "初始序列为：";
		print(arr);
		Sort::InsertSort(arr);
	}
	return 0;
}