#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "MyString.h"
using namespace std;

class Node{//������ķ�ʽ���洢ÿ������
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
//columȡֵ��
//-1�������е�ĩβ
//0�������еĿ�ͷ
//1�����ڸ��еĵ�һ���ַ�֮��
public:
	int line = 0;//�����������
	int column = -1;//�����������
};

class Editor{
private:
	int CharCount = 0;//�ַ�����
	int PunctuationCount = 0;//�����Ÿ���
	int BlankCount = 0;//�հ׷�����
	Node* head = new Node("", CharCount, PunctuationCount, BlankCount);//ͷָ��
	int line = 0;//��¼����
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