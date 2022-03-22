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
        cout << "\t快速查找：";
        cin.get();
        getline(cin, s);
        e.search(s);
        break;
      case 4:
        cout << "\t要删除的字符数（0——删除从光标到该行末尾的全部字符）：";
        int cnt;
        cin >> cnt;
        e.del(cnt);
        break;
      default:
        cout << "输入错误，请重新输入" << endl;
     }
  }while(choose);
}