#include "Editor.h"

void Editor::AddText(string s){
	if(cursor.column == -1){//光标在某一行末尾
 		Node* temp = new Node(s, CharCount, PunctuationCount, BlankCount);
		Node* p = this->head;
		int tempLine = 0;
		while (p->next != nullptr && tempLine != cursor.line) {
			p = p->next;
			tempLine++;
		}
		if(p->next != nullptr){
			temp->next = p->next;
			p->next = temp;
		}
		else
			p->next = temp;
		line++;
		cursor.line++;
	}
	else{//不在末尾
		Node* p = this->head;
		int tempLine = 0;
		while (p->next != nullptr && tempLine != cursor.line) {
			p = p->next;
			tempLine++;
		}
		//找到了光标所在的行
		p->s->Insert(s, cursor.column, CharCount, PunctuationCount, BlankCount);
		cursor.column += s.size();
	}
}

void Editor::print(){
	cout << endl << "->【文章内容（'{}'为光标位置）】<-" << endl;
	Node* p = head->next;
	int i = 1;
	if (p == NULL) { cout << endl << i << "\t{}"; }
	while(p != nullptr){
		if(cursor.line != i){//光标还在第i行
			cout << endl << i << "\t" << p->s->getContent();
		}
		else{
			if(cursor.column == -1){//光标在该行的末尾
				cout << endl << i << "\t" << p->s->getContent() << "{}";
			}
			else if (cursor.column == 0) {//光标在该行的开头
				cout << endl << i << "\t{}" << p->s->getContent();
			}
			else{//在该行的中间
				string temp = p->s->getContent();
				int k = 0;
				cout << endl << i << "\t";
				for(;k < temp.size() && k != cursor.column; k++){
					cout << temp[k];
				}
				cout << "{}";
				while(k < temp.size()){
					cout << temp[k];
					k++;
				}
			}
		}
		i++;
		p = p->next;
	}
	cout  << endl << endl;
	cout << "\t字符数：" << CharCount << "\t标点数：" << PunctuationCount << "\t空格数：" << BlankCount << endl;
}

void Editor::setCursor(){
	cout << "输入光标所在行数：";
	cin >> cursor.line;
	cout << "输入光标在第几个字符后（0——开头，-1——末尾）：";
	cin >> cursor.column;
}