#include <iostream>
using namespace std;
#define SIZE 100
void print(int arr[SIZE + 1]);
class Sort{
public:
	static void insertSort(int arr[SIZE +1]){
		int shift = 0;
		int compare = 0;
		cout << "->��������" << endl;
		for(int i = 2; i < SIZE + 1; i++){
			if(arr[i-1] > arr[i]){//���ǰһ������������������һ����Ԫ�ش����Լ�����Ҫ�ƶ�
				compare++;
				arr[0] = arr[i];//�ڱ�sentinel
				int j = i - 1;
				for (; /*arr[j] > arr[0]	�������ﲻ����ͳ�ƱȽϴ���*/; j--) {
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
		cout << "  ���������Ϊ��";
		print(arr);
		cout << endl;
	}

	static void halfInsertSort(int arr[SIZE + 1]) {
		int shift = 0;
		int compare = 0;
		cout << "->�۰��������" << endl;
		for (int i = 2; i < SIZE + 1; i++) {
			if (arr[i - 1] > arr[i]) {//���ǰһ������������������һ����Ԫ�ش����Լ�����Ҫ�ƶ�
				compare++;
				int low = 1;
				int high = i - 1;
				int mid;
				arr[0] = arr[i];//�ݴ�
				while (low <= high) //����˼��ѭ��Ѱ��arr[i]��λ��
				{
					mid = (low + high) / 2;
					if (arr[0] <= arr[mid]){
						high = mid - 1;  //highָ���С
						compare++;
					}
					else {
						low = mid + 1;   //lowָ������
						compare++;
					}
				}  //ѭ��������low����a[i]Ӧ�÷��õ�λ��

				for (int j = i; j > low; j--) {  //��Ԫ�����ƽ��
					arr[j] = arr[j - 1];
					shift++;
				}
				arr[low] = arr[0];   //��Ԫ��temp = arr[i] ���õ�lowλ��
			}
			else { compare++; }
		}
		cout << "\t�Ƚϴ���Ϊ��" << compare << endl;
		cout << "\t�ƶ�����Ϊ��" << shift << endl;
		cout << "  ���������Ϊ��";
		print(arr);
		cout << endl;
	}

	static void twoPathInsertSort(int arr[SIZE + 1]){
		int shift = 0;
		int compare = 0;
		cout << "->��·��������" << endl;
		//����ӵ�0��λ�ÿ�ʼ��������
		int d[SIZE];
		int i, j, first, last, mid;
		d[0] = arr[0];
		first = last = 0;       // first��last�ֱ�ָʾ d ���ź���ļ�¼�ĵ�һ�������һ��λ��

		for (i = 1; i < SIZE; i++) {
			if (first > last) {
				j = SIZE;        // j �ǵ���ϵ��
			}
			else {
				j = 0;
			}
			mid = ((first + last + j) / 2) % SIZE;  // d ���м��¼��λ��
			if (arr[i] < d[mid]) {                    // -- �����¼Ӧ���� d ��ǰ�벿��
				compare++;
				j = first;                           // j ָ�� d �ĵ�һ����¼
				first = (first - 1 + SIZE) % SIZE;     // first ǰ�ƣ�ȡ����Ϊ��ʵ��ѭ������Ч��
				while (arr[i] > d[j]) {               // �����¼���� j ��ָ��¼
					compare++;
					d[(j - 1 + SIZE) % SIZE] = d[j];   // j ��ָ��¼ǰ�ƣ�ȡ����Ϊ��ʵ��ѭ������Ч��
					shift++;
					j = (j + 1) % SIZE;               // j ָ����һ����¼
				}
				compare++;
				d[(j - 1 + SIZE) % SIZE] = arr[i];    // �ƶ������������¼����[j]ǰ
				shift++;
			}
			else {                                   // -- �����¼Ӧ���� d �ĺ�벿��
				compare++;
				j = last;                            // j ָ��ǰ�����һ����¼
				last++;                              // last���ƣ� ָ����������һ����¼
				while (arr[i] < d[j]) {               // �����¼С�� j ��ָ��¼
					compare++;
					d[(j + 1) % SIZE] = d[j];        // j ��ָ��¼����
					shift++;
					j = (j - 1 + SIZE) % SIZE;         // j ָ����һ����¼
				}
				compare++;
				d[(j + 1) % SIZE] = arr[i];          // �����¼��С�� j ��ָ��¼������ j ��
				shift++;
			}// end else
		}// end for
		for (i = 0; i < SIZE; i++) {                    // ���� d ���ź���ļ�¼���θ���arr
			arr[i + 1] = d[(first + i) % SIZE];
		}

		cout << "\t�Ƚϴ���Ϊ��" << compare << endl;
		cout << "\t�ƶ�����Ϊ��" << shift << endl;
		cout << "  ���������Ϊ��";
		print(arr);
		cout << endl;
	}
	static void shellSort(int arr[SIZE + 1]){
		int shift = 0;
		int compare = 0;
		cout << "->ϣ������" << endl;
		int d = SIZE / 2;
		for(; d >= 1; d = d / 2){
			for(int j = d + 1; j < SIZE + 1; j++){
				if(arr[j - d] > arr[j]){//���ǰ��ıȺ���С����Ҫ����
					compare++;
					arr[0] = arr[j];
					int k = j - d;
					for (; /*k > 0 && arr[j] > arr[0]	�������ﲻ����ͳ�ƱȽϴ���*/; k -= d) {
						if (k <= 0 || arr[k] <= arr[0]) {//���������ҵ���Ŀ��λ��
							compare++;//�����Ƿ���붼�����һ�αȽϣ����������Ҳ������ͳ��
							break;
						}
						compare++;
						arr[k + d] = arr[k];//���ڱ����ֵ��������
						shift++;
					}
					arr[k + d] = arr[0];
				}
				else { compare++; }
			}
		}
		cout << "\t�Ƚϴ���Ϊ��" << compare << endl;
		cout << "\t�ƶ�����Ϊ��" << shift << endl;
		cout << "  ���������Ϊ��";
		print(arr);
		cout << endl;
	}

	static void bubbleSort(int arr[SIZE + 1]){
		int shift = 0;
		int compare = 0;
		cout << "->ð������" << endl;
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
		cout << "\t�Ƚϴ���Ϊ��" << compare << endl;
		cout << "\t�ƶ�����Ϊ��" << shift << endl;
		cout << "  ���������Ϊ��";
		print(arr);
		cout << endl;
	}

	static void quickSort(int arr[SIZE + 1]){
		int shift = 0;
		int compare = 0;
		cout << "->��������" << endl;
		quickPartition(arr, 1, SIZE, shift, compare);

		cout << "\t�Ƚϴ���Ϊ��" << compare << endl;
		cout << "\t�ƶ�����Ϊ��" << shift << endl;
		cout << "  ���������Ϊ��";
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
			while(low < high /*&& arr[high] >= pivotkey�������ﲻ����ͳ�ƱȽϴ��� */ ){
				if(arr[high] < pivotkey){
					compare++;
					break;
				}
				compare++;
				high--;
			}
			arr[low] = arr[high];
			if(low < high){//low == high˵��û���ƶ�λ��
				shift++;
			}

			while (low < high /*&& arr[low] <= pivotkey�������ﲻ����ͳ�ƱȽϴ��� */) {
				if (arr[low] > pivotkey) {
					compare++;
					break;
				}
				compare++;
				low++;
			}
			arr[high] = arr[low];
			if (low < high) {//low == high˵��û���ƶ�λ��
				shift++;
			}
		}
		arr[low] = pivotkey;
		if(tempLow != low){
			shift++;//˵��pivotkey���ǷŻ���ԭʼλ��
		}
		quickPartition(arr, tempLow, low - 1, shift, compare);//��벿��
		quickPartition(arr, low + 1, tempHigh, shift, compare);//�Ұ벿��
	}
public:
	static void simpleSelectSort(int arr[SIZE + 1]){
		int shift = 0;
		int compare = 0;
		cout << "->��ѡ������" << endl;
		for(int i = 1; i < SIZE; i++){//���һ������Ҫ�ƶ�
			int min = arr[i];
			int loc = i;//��¼��СԪ������λ��
			for(int j = i + 1; j < SIZE + 1; j++){
				if(arr[j] < min){
					compare++;
					min = arr[j];
					loc = j;
				}
				else { compare++; }
			}
			if(loc != i){//������˵����СԪ�ز�����δ�������е�����ߣ���Ҫ�ƶ�
				arr[loc] = arr[i];
				arr[i] = min;
				shift += 3;
			}
		}

		cout << "\t�Ƚϴ���Ϊ��" << compare << endl;
		cout << "\t�ƶ�����Ϊ��" << shift << endl;
		cout << "  ���������Ϊ��";
		print(arr);
		cout << endl;
	}

	static void heapSort(int arr[SIZE + 1]){
		int shift = 0;
		int compare = 0;
		cout << "->������" << endl;
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
		cout << "\t�Ƚϴ���Ϊ��" << compare << endl;
		cout << "\t�ƶ�����Ϊ��" << shift << endl;
		cout << "  ���������Ϊ��";
		print(arr);
		cout << endl;
	}
private:
	static void heapAdjust(int arr[SIZE + 1], int start, int max, int& shift, int& compare){
		//�Ѳ���˳���洢��ʾ
		//����Ϊ�󶥶�
		int temp = arr[start];
		for(int j = 2 * start; j <= max; j *= 2){
			if (j < max && arr[j] <= arr[j + 1]) {
				j++;
				compare++;
			}
			else if(j < max) { compare++; }
			if(temp >= arr[j]){
				//�Ƚϴ�ĺ��ӻ���Ͳ����ƶ�
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
		cout << "->�鲢����" << endl;
		mergeSeperate(arr, 1, SIZE, shift, compare);

		cout << "\t�Ƚϴ���Ϊ��" << compare << endl;
		cout << "\t�ƶ�����Ϊ��" << shift << endl;
		cout << "  ���������Ϊ��";
		print(arr);
		cout << endl;
	}
private:
	static void mergeSeperate(int arr[SIZE + 1], int low, int high, int& shift, int& compare){
		if (low < high) {
			//���ֹ��� �е�
			int mid = (low + high) / 2;
			mergeSeperate(arr, low, mid, shift, compare);
			mergeSeperate(arr, mid + 1, high, shift, compare);
			//һ�λ��� һ�κϲ�
			merge(arr, low, mid, high, shift, compare);
		}
	}
	static void merge(int arr[SIZE + 1], int low, int mid, int high, int& shift, int& compare) {
		//B���ݴ�arr������
		int B[SIZE + 1];
		for (int k = low; k < high + 1; k++) {
			B[k] = arr[k];
		}
		int i = low, j = mid + 1, k = low;
		while (i < mid + 1 && j < high + 1) {
			//A��Ԫ���ݴ���B���Ϊ������A��ԭ�ز��������������
			if (B[i] > B[j]) {
				compare++;
				arr[k++] = B[j++];
				shift++;//ǰ��ıȺ���Ĵ�������Ҫ�ƶ�
			}
			else {
				compare++;
				arr[k++] = B[i++];
			}
		}
		//ѭ�������󣬻���һ��û�б��������������
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

		for (int i = 1; i < SIZE + 1; i++) {//�������
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
		//for(int i = SIZE, j = 1; i >= 1; i--, j++){//����
		//	arr1[j] = i;
		//	arr2[j] = i;
		//	arr3[j] = i;
		//	arr4[j] = i;
		//	arr5[j] = i;

		//}

		//for (int j = 1; j < SIZE + 1; j++) {//˳��
		//	arr1[j] = j;
		//	arr2[j] = j;
		//	arr3[j] = j;
		//	arr4[j] = j;
		//	arr5[j] = j;

		//}
		cout << "*��" << j + 1 << "�Σ�" << endl;
		cout << "��ʼ����Ϊ��";
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