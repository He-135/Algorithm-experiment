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
	cout << "\t" << "输入光标所在行数：";
	cin >> cursor.line;
	while(cursor.line < 1 || cursor.line > line){
		cout << "\t" << "输入不合法，请重新输入：";
		cin >> cursor.line;
	}
	Node* p = this->head;
	int tempLine = 0;
	while (p->next != nullptr && tempLine != cursor.line) {
		p = p->next;
		tempLine++;
	}
	cout << "\t" << "输入光标在第几个字符后（0——开头，-1——末尾）：";
	cin >> cursor.column;
	while(cursor.column < -1 || cursor.column >= p->s->length){
		cout << "\t" << "输入不合法，请重新输入：";
		cin >> cursor.column;
	}
}

void Editor::search(string s){
	Node* p = this->head;
	if(p->next == NULL){
		cout << "\t" << "文档为空，查找失败！" << endl;
		return;
	}
	int tempLine = 0;//用于找到光标所在行
	int tempColumn = cursor.column;//标识光标所在列
	if(cursor.line == line && cursor.column == -1){//光标在全文档的末尾，直接从文档开头开始查找
		p = p->next;
		tempLine = 1;
		tempColumn = 0;
	}
	else{//光标不在文档末尾，先找到光标所在的行
		while (p->next != nullptr && tempLine != cursor.line) {
			p = p->next;
			tempLine++;
		}
	}
	int pos = -1;
	//如果光标不在该行的开头或末尾，先在该行查找
	if(tempColumn != 0 && tempColumn != -1){
		pos = p->s->Index(s, tempColumn);
	}
	else if(tempColumn == -1){//光标在该行的末尾，则直接从下一行开头开始查找
		p = p->next;
		tempLine++;
		tempColumn = 0;
	}
	if(pos == -1){//说明前面没找到或者直接从该行的开头开始找
		do{
			pos = p->s->Index(s, tempColumn);
			if (pos != -1)
				break;//已经找到了
			p = p->next;
			tempLine++;
		} while (p != NULL);//只要后面还有文本且还没找到就要继续找
	}
	if (pos == -1)//说明直到文本末尾都没找到
		cout << "\t" <<  s << "：未找到" << endl;
	else if (pos == 0)
		cout << "\t" << s << "：第" << tempLine << "行开头" << endl;
	else
		cout << "\t" << s << "：第" << tempLine << "行第" << pos << "个字符后" << endl;
}