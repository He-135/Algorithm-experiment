#include"Editor.h"

using namespace std;

int main(void){
  Editor e;
  int choose;
  do{
    e.print();
    cout << "---------------------------------------" << endl;
    cout << "1.�����ı����ڹ�괦��" << endl;
    cout << "2.���ù��λ��" << endl;
    cout << "3. �ڹ��λ�ô������ı�" << endl;
    cout << "6.���ĵ��в����ı�" << endl;
    cout << "7.���ĵ���ɾ���ı�" << endl;
    cout << "8.ͳ����ĸ�����֡������š��հ׷��ż����ַ�����" << endl;
    cout << "9.�����ı�" << endl;
    cout << "0.�˳�" << endl;
    cout << "---------------------------------------" << endl;
    cout << "��ѡ��:";
    cin >> choose;
    string s;
    switch (choose) {
      case 1:
        cout << "���������ݣ�";
        cin.get();
        getline(cin, s);
        e.AddText(s);
        break;
      case 2:
        e.setCursor();
        break;
     }
  }while(choose);
  return 0;
}