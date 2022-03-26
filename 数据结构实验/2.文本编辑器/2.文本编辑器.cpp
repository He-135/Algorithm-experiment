#include"Editor.h"

using namespace std;

int main(void){
  Editor e;
  int choose;
  do{
    e.print();
    cout << endl << "---------------------------------------" << endl;
    cout << "1.插入文本（在光标处）" << endl;
    cout << "2.设置光标位置" << endl;
    cout << "3.查找（从光标处开始往后查找）" << endl;
    cout << "4.删除文本（从光标处往后）" << endl;
    cout << "5.添加回车" << endl;
    cout << "6.删除回车" << endl;
    cout << "0.退出" << endl;
    cout << "---------------------------------------" << endl;
    cout << "请选择:";
    cin >> choose;
    string s;
    switch (choose) {
      case 0:
        return 0;
      case 1:
        cout << "\t" << "请输入内容：";
        cin.get();
        getline(cin, s);
        e.AddText(s);
        break;
      case 2:
        e.setCursor();
        break;
      case 3:
        e.search();
        break;
      case 4:
        e.del();
        break;
      case 5:
        e.enter_add();
        break;
      case 6:
        e.enter_del();
        break;
      default:
        cout << "输入错误，请重新输入" << endl;
     }
  }while(choose);
}