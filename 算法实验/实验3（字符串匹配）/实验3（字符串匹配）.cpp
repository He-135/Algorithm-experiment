#include <iostream>
#include <string>

using namespace std;

class MyString {
public:
  char* str = nullptr;
  int length = 0;//用来记录数组长度
  MyString(string s) {
    str = new char[s.length() + 1];
    str[0] = 0;//第0号空出
    length = s.length();
    for (int i = 1; i <= length; i++) {
      str[i] = s[i - 1];
    }
  }
  ~MyString() {
    if (!str) { delete[]str; }
  }
  static int Index(MyString s, MyString t, int pos){//从第pos个元素开始寻找
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
    cout << "输入字符串：";
    cin >> s >> t;
    int pos;
    cout << "输入开始搜索的位置（输入-1结束）：";
    cin >> pos;
    if (pos == -1) { break; }
    while (pos < 1) {
      cout << "位置输入不合法，请重新输入：";
      cin >> pos;
    }
    MyString S(s);
    while (pos > S.length) {
      cout << "位置输入不合法，请重新输入：";
      cin >> pos;
    }
    MyString T(t);
    int res = MyString::Index(S, T, pos);
    if (res == -1) { cout << "搜索失败" << endl; }
    else { cout << "第一个匹配的下标为：" << res << endl; }
  }
  return 0;
}