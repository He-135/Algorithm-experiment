#pragma once
#include <string>
#include <iostream>
#include "MyString.h"
using namespace std;

class Node{//������ķ�ʽ���洢ÿ������
public:
	MyString* s = nullptr;
	Node* next = nullptr;
	Node(string s, int& CharCount, int& PunctuationCount, int& BlankCount){
		this->s = new MyString(s, CharCount, PunctuationCount, BlankCount);
	}
};

class Cursor{
public:
	int line = 0;//�����������
	int column = -1;//�����������
	//columnĬ��Ϊ-1��ʾ������µ����
	//column = 1��ʾ�ڸ��еĵ�һ���ַ�֮��
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
	void AddText(string s);
	void print();
	void setCursor();
};