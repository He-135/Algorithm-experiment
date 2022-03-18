#pragma once
#include <iostream>
#include <string>
using namespace std;

class MyString {
public:
  char* str = nullptr;
  int length = 0;//用来记录数组长度
  MyString(string s, int& CharCount, int& PunctuationCount, int& BlankCount);
  ~MyString();
  static int Index(MyString s, MyString t, int pos);//在s中查找t第一次出现的下标
  string getContent();
  void Insert(string s, int pos, int& CharCount, int& PunctuationCount, int& BlankCount);//在第pos个字符后插入字符串
};