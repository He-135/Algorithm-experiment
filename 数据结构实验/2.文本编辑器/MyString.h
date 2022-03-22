#pragma once
#include <iostream>
#include <string>
using namespace std;

class MyString {
private:
  char* str = nullptr;
  int length = 0;//������¼���鳤��
public:
  MyString() = default;
  MyString(string s, int& CharCount, int& PunctuationCount, int& BlankCount);
  ~MyString();
  int getLength();
  int Index(string t, int pos);//����t��һ�γ��ֵ��±�
  string getContent();
  void Insert(string s, int pos, int& CharCount, int& PunctuationCount, int& BlankCount);//�ڵ�pos���ַ�������ַ���
  void del(int pos, int cnt, int& CharCount, int& PunctuationCount, int& BlankCount);
};