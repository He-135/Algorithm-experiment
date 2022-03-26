#include"MyString.h"

MyString::MyString(string s, int& CharCount, int& PunctuationCount, int& BlankCount) {
  str = new char[s.length() + 1];
  str[0] = 0;//第0号空出
  length = s.length();
  for (int i = 1; i <= length; i++) {
    str[i] = s[i - 1];
    if (str[i] >= '0' && str[i] <= '9' ||
      str[i] > 'a' && str[i] < 'z' ||
      str[i]>'A' && str[i] < 'Z')
      CharCount++;
    else if (ispunct(str[i]))
      PunctuationCount++;
    else if (str[i] == ' ')
      BlankCount++;
  }
}

MyString::MyString(string s){
  str = new char[s.length() + 1];
  str[0] = 0;//第0号空出
  length = s.length();
  for (int i = 1; i <= length; i++) {
    str[i] = s[i - 1];
  }
}

MyString::~MyString() {
  if (!str) { delete[]str; }
}

int MyString::getLength(){
  return this->length;
}

int MyString::Index(string t, int pos) {//从第pos个元素开始寻找
  if (this->length - pos + 1 < t.length()) {
    return -1;
  }
  int i = pos+1;
  int j = 0;
  while (i <= this->length && j < t.length()) {
    if (this->str[i] == t[j]) {
      i++;
      j++;
    }
    else { i = i - j + 1; j = 0; }
  }
  if (j >= t.length()) {
    return i - 1 - j;
  }
  return -1;
}

string MyString::getContent(){
  string s;
  for(int i = 0; i < length; i++){
    s += str[i + 1];
  }
  return s;
}

void MyString::Insert(string s, int pos, int& CharCount, int& PunctuationCount, int& BlankCount){
  for (int i = 0; i < s.length(); i++) {
    if (s[i] >= '0' && s[i] <= '9' ||
      s[i] > 'a' && s[i] < 'z' ||
      s[i]>'A' && s[i] < 'Z')
      CharCount++;
    else if (ispunct(s[i]))
      PunctuationCount++;
    else if (s[i] == ' ')
      BlankCount++;
  }
  string temp_s;//取出原先的字符串并插入新的字符串
  int i = 0;
  for (; i < length && i != pos; i++) {
    temp_s += str[i + 1];
  }
  temp_s += s;
  for (; i < length; i++) {
    temp_s += str[i + 1];
  }
  char* temp = str;//将原先new得到的数组delete
  delete[]temp;
  length += s.length();
  //根据新的串new数组
  str = new char[length + 1];
  for (int k = 1; k <= length; k++) {
    str[k] = temp_s[k - 1];
  }
}

void MyString::del(int pos, int cnt, int& CharCount, int& PunctuationCount, int& BlankCount){
  char* temp = str;
  str = new char[this->length - cnt + 1];
  this->length = length - cnt;
  int i = 0;
  for(; i < pos; i++){//循环结束时就到了光标所在的位置
    str[i + 1] = temp[i + 1];
  }
  for (; i < this->length; i++) {
    str[i + 1] = temp[i + 1 + cnt];
  }
  for(int j = pos; j < pos + cnt; j++){
    if (temp[j + 1] >= '0' && temp[j + 1] <= '9' ||
      temp[j + 1] > 'a' && temp[j + 1] < 'z' ||
      temp[j + 1]>'A' && temp[j + 1] < 'Z')
      CharCount--;
    else if (ispunct(temp[j + 1]))
      PunctuationCount--;
    else if (temp[j + 1] == ' ')
      BlankCount--;
  }
  delete[] temp;
}

void MyString::split(int pos, string& s1, string& s2){
  for(int i = 1; i <= pos; i++){
    s1 += str[i];
  }
  for (int i = pos + 1; i <= length; i++) {
    s2 += str[i];
  }

}