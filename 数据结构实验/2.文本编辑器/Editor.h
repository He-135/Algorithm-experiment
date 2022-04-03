#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "MyString.h"
using namespace std;

class Node{//以链表的方式来存储每个句子
public:
	MyString* s = nullptr;
	Node* next = nullptr;
	Node(string s, int& CharCount, int& PunctuationCount, int& BlankCount){
		this->s = new MyString(s, CharCount, PunctuationCount, BlankCount);
	}
	Node(string s){
		this->s = new MyString(s);
	}
};

class Cursor{
//colum取值：
//-1——该行的末尾
//0——该行的开头
//1——在该行的第一个字符之后
public:
	int line = 0;//光标所在行数
	int column = -1;//光标所在列数
};

class Editor{
private:
	int CharCount = 0;//字符个数
	int PunctuationCount = 0;//标点符号个数
	int BlankCount = 0;//空白符个数
	Node* head = new Node("", CharCount, PunctuationCount, BlankCount);//头指针
	int line = 0;//记录行数
	Cursor cursor;
public:
	Editor() = default;
	~Editor();
	void AddText(string s);
	void print();
	void setCursor();
	void search();
	void del();
	void enter_add();
	void enter_del();
	void save();
	void read_file();
};