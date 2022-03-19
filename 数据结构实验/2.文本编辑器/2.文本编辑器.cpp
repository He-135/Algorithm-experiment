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
    cout << "3.在文档中查找文本（从光标处开始往后查找）" << endl;
    cout << "6." << endl;
    cout << "7.在文档中删除文本" << endl;
    cout << "8.统计字母、数字、标点符号、空白符号及总字符个数" << endl;
    cout << "9.输入文本" << endl;
    cout << "0.退出" << endl;
    cout << "---------------------------------------" << endl;
    cout << "请选择:";
    cin >> choose;
    string s;
    switch (choose) {
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
        cout << "\t" << "快速查找：";
        cin.get();
        getline(cin, s);
        e.search(s);
        break;
     }
  }while(choose);
  return 0;
}