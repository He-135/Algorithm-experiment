#include"Editor.h"

using namespace std;

int main(void){
  Editor e;
  int choose;
  do{
    e.print();
    cout << endl << "---------------------------------------" << endl;
    cout << "1.�����ı����ڹ�괦��" << endl;
    cout << "2.���ù��λ��" << endl;
    cout << "3.���ң��ӹ�괦��ʼ������ң�" << endl;
    cout << "4.ɾ���ı����ӹ�괦����" << endl;
    cout << "0.�˳�" << endl;
    cout << "---------------------------------------" << endl;
    cout << "��ѡ��:";
    cin >> choose;
    string s;
    switch (choose) {
      case 0:
        return 0;
      case 1:
        cout << "\t" << "���������ݣ�";
        cin.get();
        getline(cin, s);
        e.AddText(s);
        break;
      case 2:
        e.setCursor();
        break;
      case 3:
        cout << "\t���ٲ��ң�";
        cin.get();
        getline(cin, s);
        e.search(s);
        break;
      case 4:
        cout << "\tҪɾ�����ַ�����0����ɾ���ӹ�굽����ĩβ��ȫ���ַ�����";
        int cnt;
        cin >> cnt;
        e.del(cnt);
        break;
      default:
        cout << "�����������������" << endl;
     }
  }while(choose);
}