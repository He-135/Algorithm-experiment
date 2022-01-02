#include <iostream>
#include <string>
using namespace std;

class Student{
public:
	int studentNum;
	string name;
	int Ascore;
	int Bscore;
	int Cscore;
	int totalScore;
	Student() = default;
	Student(int studentNum, string name, int Ascore, int Bscore, int Cscore){
		this->studentNum = studentNum;
		this->name = name;
		this->Ascore = Ascore;
		this->Bscore = Bscore;
		this->Cscore = Cscore;
		this->totalScore = Ascore + Bscore + Cscore;
	}

};

void print(Student students[6]){
	int j = 1;
	cout << "名次\t学号\t姓名\t总分\t科目A\t科目B\t科目C" << endl;
	for (int i = 0; i < 5; i++) {
		if(students[i].totalScore > students[i + 1].totalScore){
			cout << j++ << "\t" << students[i].studentNum << "\t" << students[i].name << "\t" << students[i].totalScore << "\t"
				<< students[i].Ascore << "\t" << students[i].Bscore << "\t" << students[i].Cscore << endl;
		}
		else{
			cout << j << "\t" << students[i].studentNum << "\t" << students[i].name << "\t" << students[i].totalScore << "\t"
				<< students[i].Ascore << "\t" << students[i].Bscore << "\t" << students[i].Cscore << endl;
		}
	}
	cout << j << "\t" << students[5].studentNum << "\t" << students[5].name << "\t" << students[5].totalScore << "\t"
		<< students[5].Ascore << "\t" << students[5].Bscore << "\t" << students[5].Cscore << endl;
}

//使用希尔排序
void shellSort(Student students[6]) {
	int d = 3;
	Student temp;
	for (; d >= 1; d = d / 2) {
		for (int j = d; j < 6; j++) {
			if (students[j - d].totalScore < students[j].totalScore) {//如果前面的比后面小则需要排序
				temp = students[j];
				int k = j - d;
				for (; k > 0 && students[k].totalScore < temp.totalScore; k -= d) {
					students[k + d] = students[k];//比哨兵小的值都往后移
				}
				students[k + d] = temp;
			}
		}
	}
	print(students);
}

int main(void){
	Student students[6];
	students[0] = Student(1, "hjy", 100, 97, 92);
	students[1] = Student(2, "wl", 50, 60, 70);
	students[2] = Student(3, "gkw", 54, 88, 79);
	students[3] = Student(4, "gxh", 95, 49, 84);
	students[4] = Student(5, "zyh", 92, 76, 94);
	students[5] = Student(6, "zx", 79, 94, 89);
	shellSort(students);
	return 0;
}
