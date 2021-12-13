#include <iostream>
#include <string>

using namespace std;

class MyString {
public:
  char* str = nullptr;
  int length = 0;//������¼���鳤��
  MyString(string s) {
    str = new char[s.length() + 1];
    str[0] = 0;//��0�ſճ�
    length = s.length();
    for (int i = 1; i <= length; i++) {
      str[i] = s[i - 1];
    }
  }
  ~MyString() {
    if (!str) { delete[]str; }
  }
  static int Index(MyString s, MyString t, int pos){//�ӵ�pos��Ԫ�ؿ�ʼѰ��
    if (s.length == 0 || t.length == 0 || s.length - pos + 1 < t.length) {
      return -1;
    }
    int i = pos;
    int j = 1;
    while(i <= s.length && j <= t.length){
      if(s.str[i] == t.str[j]){
        i++;
        j++;
      }
      else { i = i - j + 2; j = 1; }
    }
    if(j > t.length){
      return i - j + 1;
    }
    return -1;
  }
};

int main(void){
  while(1){
    string s, t;
    cout << "�����ַ�����";
    cin >> s >> t;
    int pos;
    cout << "���뿪ʼ������λ�ã�����-1��������";
    cin >> pos;
    if (pos == -1) { break; }
    while (pos < 1) {
      cout << "λ�����벻�Ϸ������������룺";
      cin >> pos;
    }
    MyString S(s);
    while (pos > S.length) {
      cout << "λ�����벻�Ϸ������������룺";
      cin >> pos;
    }
    MyString T(t);
    int res = MyString::Index(S, T, pos);
    if (res == -1) { cout << "����ʧ��" << endl; }
    else { cout << "��һ��ƥ����±�Ϊ��" << res << endl; }
  }
  return 0;
}