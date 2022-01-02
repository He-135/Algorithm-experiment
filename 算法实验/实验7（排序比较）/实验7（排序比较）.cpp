#include <iostream>
using namespace std;
#define SIZE 100
void print(int arr[SIZE + 1]);
class Sort{
public:
	static void insertSort(int arr[SIZE +1]){
		int shift = 0;
		int compare = 0;
		cout << "->插入排序：" << endl;
		for(int i = 2; i < SIZE + 1; i++){
			if(arr[i-1] > arr[i]){//如果前一个（已排序数组的最后一个）元素大于自己则需要移动
				compare++;
				arr[0] = arr[i];//哨兵sentinel
				int j = i - 1;
				for (; /*arr[j] > arr[0]	放在这里不方便统计比较次数*/; j--) {
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
		cout << "  排序后序列为：";
		print(arr);
		cout << endl;
	}

	static void halfInsertSort(int arr[SIZE + 1]) {
		int shift = 0;
		int compare = 0;
		cout << "->折半插入排序：" << endl;
		for (int i = 2; i < SIZE + 1; i++) {
			if (arr[i - 1] > arr[i]) {//如果前一个（已排序数组的最后一个）元素大于自己则需要移动
				compare++;
				int low = 1;
				int high = i - 1;
				int mid;
				arr[0] = arr[i];//暂存
				while (low <= high) //二分思想循环寻找arr[i]的位置
				{
					mid = (low + high) / 2;
					if (arr[0] <= arr[mid]){
						high = mid - 1;  //high指针减小
						compare++;
					}
					else {
						low = mid + 1;   //low指针增加
						compare++;
					}
				}  //循环结束，low就是a[i]应该放置的位置

				for (int j = i; j > low; j--) {  //将元素向后平移
					arr[j] = arr[j - 1];
					shift++;
				}
				arr[low] = arr[0];   //将元素temp = arr[i] 放置到low位置
			}
			else { compare++; }
		}
		cout << "\t比较次数为：" << compare << endl;
		cout << "\t移动次数为：" << shift << endl;
		cout << "  排序后序列为：";
		print(arr);
		cout << endl;
	}

	static void twoPathInsertSort(int arr[SIZE + 1]){
		int shift = 0;
		int compare = 0;
		cout << "->二路插入排序：" << endl;
		//这里从第0号位置开始存入数据
		int d[SIZE];
		int i, j, first, last, mid;
		d[0] = arr[0];
		first = last = 0;       // first和last分别指示 d 中排好序的记录的第一个和最后一个位置

		for (i = 1; i < SIZE; i++) {
			if (first > last) {
				j = SIZE;        // j 是调整系数
			}
			else {
				j = 0;
			}
			mid = ((first + last + j) / 2) % SIZE;  // d 的中间记录的位置
			if (arr[i] < d[mid]) {                    // -- 待插记录应插在 d 的前半部分
				compare++;
				j = first;                           // j 指向 d 的第一个记录
				first = (first - 1 + SIZE) % SIZE;     // first 前移，取余是为了实现循环数组效果
				while (arr[i] > d[j]) {               // 待插记录大于 j 所指记录
					compare++;
					d[(j - 1 + SIZE) % SIZE] = d[j];   // j 所指记录前移，取余是为了实现循环数组效果
					shift++;
					j = (j + 1) % SIZE;               // j 指向下一个记录
				}
				compare++;
				d[(j - 1 + SIZE) % SIZE] = arr[i];    // 移动结束，待插记录插在[j]前
				shift++;
			}
			else {                                   // -- 待插记录应插在 d 的后半部分
				compare++;
				j = last;                            // j 指向当前的最后一个记录
				last++;                              // last后移， 指向插入后的最后一个记录
				while (arr[i] < d[j]) {               // 待插记录小于 j 所指记录
					compare++;
					d[(j + 1) % SIZE] = d[j];        // j 所指记录后移
					shift++;
					j = (j - 1 + SIZE) % SIZE;         // j 指向上一个记录
				}
				compare++;
				d[(j + 1) % SIZE] = arr[i];          // 待插记录不小于 j 所指记录，插在 j 后
				shift++;
			}// end else
		}// end for
		for (i = 0; i < SIZE; i++) {                    // 把在 d 中排好序的记录依次赋给arr
			arr[i + 1] = d[(first + i) % SIZE];
		}

		cout << "\t比较次数为：" << compare << endl;
		cout << "\t移动次数为：" << shift << endl;
		cout << "  排序后序列为：";
		print(arr);
		cout << endl;
	}
	static void shellSort(int arr[SIZE + 1]){
		int shift = 0;
		int compare = 0;
		cout << "->希尔排序：" << endl;
		int d = SIZE / 2;
		for(; d >= 1; d = d / 2){
			for(int j = d + 1; j < SIZE + 1; j++){
				if(arr[j - d] > arr[j]){//如果前面的比后面小则需要排序
					compare++;
					arr[0] = arr[j];
					int k = j - d;
					for (; /*k > 0 && arr[j] > arr[0]	放在这里不方便统计比较次数*/; k -= d) {
						if (k <= 0 || arr[k] <= arr[0]) {//成立则已找到了目标位置
							compare++;//无论是否进入都会产生一次比较，这样不会多也不会少统计
							break;
						}
						compare++;
						arr[k + d] = arr[k];//比哨兵大的值都往后移
						shift++;
					}
					arr[k + d] = arr[0];
				}
				else { compare++; }
			}
		}
		cout << "\t比较次数为：" << compare << endl;
		cout << "\t移动次数为：" << shift << endl;
		cout << "  排序后序列为：";
		print(arr);
		cout << endl;
	}

	static void bubbleSort(int arr[SIZE + 1]){
		int shift = 0;
		int compare = 0;
		cout << "->冒泡排序：" << endl;
		for(int i = SIZE;i > 1; i--){
			bool change = false;
			for(int j = 1; j < i; j++){
				if(arr[j] > arr[j + 1]){
					compare++;
					auto t = arr[j];
					arr[j] = arr[j + 1];
					arr[j + 1] = t;
					shift += 3;
					change = true;
				}
				else { compare++; }
			}
			if (!change) { break; }
		}
		cout << "\t比较次数为：" << compare << endl;
		cout << "\t移动次数为：" << shift << endl;
		cout << "  排序后序列为：";
		print(arr);
		cout << endl;
	}

	static void quickSort(int arr[SIZE + 1]){
		int shift = 0;
		int compare = 0;
		cout << "->快速排序：" << endl;
		quickPartition(arr, 1, SIZE, shift, compare);

		cout << "\t比较次数为：" << compare << endl;
		cout << "\t移动次数为：" << shift << endl;
		cout << "  排序后序列为：";
		print(arr);
		cout << endl;
	}
private:
	static void quickPartition(int arr[SIZE + 1], int low, int high, int& shift, int& compare){
		if (low >= high) { return; }
		int pivotkey = arr[low];
		int tempLow = low;
		int tempHigh = high;

		while (low < high) {
			while(low < high /*&& arr[high] >= pivotkey放在这里不方便统计比较次数 */ ){
				if(arr[high] < pivotkey){
					compare++;
					break;
				}
				compare++;
				high--;
			}
			arr[low] = arr[high];
			if(low < high){//low == high说明没有移动位置
				shift++;
			}

			while (low < high /*&& arr[low] <= pivotkey放在这里不方便统计比较次数 */) {
				if (arr[low] > pivotkey) {
					compare++;
					break;
				}
				compare++;
				low++;
			}
			arr[high] = arr[low];
			if (low < high) {//low == high说明没有移动位置
				shift++;
			}
		}
		arr[low] = pivotkey;
		if(tempLow != low){
			shift++;//说明pivotkey不是放回了原始位置
		}
		quickPartition(arr, tempLow, low - 1, shift, compare);//左半部分
		quickPartition(arr, low + 1, tempHigh, shift, compare);//右半部分
	}
public:
	static void simpleSelectSort(int arr[SIZE + 1]){
		int shift = 0;
		int compare = 0;
		cout << "->简单选择排序：" << endl;
		for(int i = 1; i < SIZE; i++){//最后一个不需要移动
			int min = arr[i];
			int loc = i;//记录最小元素所在位置
			for(int j = i + 1; j < SIZE + 1; j++){
				if(arr[j] < min){
					compare++;
					min = arr[j];
					loc = j;
				}
				else { compare++; }
			}
			if(loc != i){//成立则说明最小元素不在最未排序序列的最左边，需要移动
				arr[loc] = arr[i];
				arr[i] = min;
				shift += 3;
			}
		}

		cout << "\t比较次数为：" << compare << endl;
		cout << "\t移动次数为：" << shift << endl;
		cout << "  排序后序列为：";
		print(arr);
		cout << endl;
	}

	static void heapSort(int arr[SIZE + 1]){
		int shift = 0;
		int compare = 0;
		cout << "->堆排序：" << endl;
		for(int i = SIZE / 2; i > 0; i--){
			heapAdjust(arr, i, SIZE, shift, compare);
		}
		for(int i = SIZE; i > 0; i--){
			int temp = arr[1];
			arr[1] = arr[i];
			arr[i] = temp;
			shift += 3;
			heapAdjust(arr, 1, i - 1, shift, compare);
		}
		cout << "\t比较次数为：" << compare << endl;
		cout << "\t移动次数为：" << shift << endl;
		cout << "  排序后序列为：";
		print(arr);
		cout << endl;
	}
private:
	static void heapAdjust(int arr[SIZE + 1], int start, int max, int& shift, int& compare){
		//堆采用顺序表存储表示
		//调整为大顶堆
		int temp = arr[start];
		for(int j = 2 * start; j <= max; j *= 2){
			if (j < max && arr[j] <= arr[j + 1]) {
				j++;
				compare++;
			}
			else if(j < max) { compare++; }
			if(temp >= arr[j]){
				//比较大的孩子还大就不用移动
				compare++;
				break;
			}
			compare++;
			arr[start] = arr[j];
			start = j;
			shift += 3;
		}
		arr[start] = temp;
	}

public:
	static void mergeSort(int arr[SIZE + 1]){
		int shift = 0;
		int compare = 0;
		cout << "->归并排序：" << endl;
		mergeSeperate(arr, 1, SIZE, shift, compare);

		cout << "\t比较次数为：" << compare << endl;
		cout << "\t移动次数为：" << shift << endl;
		cout << "  排序后序列为：";
		print(arr);
		cout << endl;
	}
private:
	static void mergeSeperate(int arr[SIZE + 1], int low, int high, int& shift, int& compare){
		if (low < high) {
			//划分规则 中点
			int mid = (low + high) / 2;
			mergeSeperate(arr, low, mid, shift, compare);
			mergeSeperate(arr, mid + 1, high, shift, compare);
			//一次划分 一次合并
			merge(arr, low, mid, high, shift, compare);
		}
	}
	static void merge(int arr[SIZE + 1], int low, int mid, int high, int& shift, int& compare) {
		//B里暂存arr的数据
		int B[SIZE + 1];
		for (int k = low; k < high + 1; k++) {
			B[k] = arr[k];
		}
		int i = low, j = mid + 1, k = low;
		while (i < mid + 1 && j < high + 1) {
			//A的元素暂存在B里，因为不能再A上原地操作，会打乱数据
			if (B[i] > B[j]) {
				compare++;
				arr[k++] = B[j++];
				shift++;//前面的比后面的大所以需要移动
			}
			else {
				compare++;
				arr[k++] = B[i++];
			}
		}
		//循环结束后，会有一个没有遍历结束的数组段
		while (i < mid + 1)
			arr[k++] = B[i++];
		while (j < high + 1)
			arr[k++] = B[j++];
	}
};

void print(int arr[SIZE + 1]){
	for(int i = 1; i < SIZE + 1; i++){
		cout << arr[i] << " ";
	}
	cout << endl;
}

//int main(void){
//	int arr[SIZE] = { 21, 25, 8, 25, 16, 49 };
//	Sort::heapSort(arr);
//	return 0;
//}


int main(void){
	for(int j = 0; j < 5; j++){
		int arr1[SIZE + 1];
		int arr2[SIZE + 1];
		int arr3[SIZE + 1];
		int arr4[SIZE + 1];
		int arr5[SIZE + 1];
		int arr6[SIZE + 1];
		int arr7[SIZE + 1];
		int arr8[SIZE + 1];
		int arr9[SIZE + 1];

		for (int i = 1; i < SIZE + 1; i++) {//随机序列
			int temp = rand();
			arr1[i] = temp;
			arr2[i] = temp;
			arr3[i] = temp;
			arr4[i] = temp;
			arr5[i] = temp;
			arr6[i] = temp;
			arr7[i] = temp;
			arr8[i] = temp;
			arr9[i-1] = temp;

		}
		//for(int i = SIZE, j = 1; i >= 1; i--, j++){//逆序
		//	arr1[j] = i;
		//	arr2[j] = i;
		//	arr3[j] = i;
		//	arr4[j] = i;
		//	arr5[j] = i;

		//}

		//for (int j = 1; j < SIZE + 1; j++) {//顺序
		//	arr1[j] = j;
		//	arr2[j] = j;
		//	arr3[j] = j;
		//	arr4[j] = j;
		//	arr5[j] = j;

		//}
		cout << "*第" << j + 1 << "次：" << endl;
		cout << "初始序列为：";
		print(arr1);
		Sort::insertSort(arr1);
		Sort::shellSort(arr2);
		Sort::bubbleSort(arr3);
		Sort::quickSort(arr4);
		Sort::simpleSelectSort(arr5);
		Sort::heapSort(arr6);
		Sort::halfInsertSort(arr7);
		Sort::mergeSort(arr8);
		Sort::twoPathInsertSort(arr9);
		cout << endl;
		cout << endl;
	}
	return 0;
}