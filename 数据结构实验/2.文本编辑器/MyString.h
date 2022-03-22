#pragma once
#include <iostream>
#include <string>
using namespace std;

class MyString {
private:
  char* str = nullptr;
  int length = 0;//用来记录数组长度
public:
  MyString() = default;
  MyString(string s, int& CharCount, int& PunctuationCount, int& BlankCount);
  ~MyString();
  int getLength();
  int Index(string t, int pos);//查找t第一次出现的下标
  string getContent();
  void Insert(string s, int pos, int& CharCount, int& PunctuationCount, int& BlankCount);//在第pos个字符后插入字符串
  void del(int pos, int cnt, int& CharCount, int& PunctuationCount, int& BlankCount);
};