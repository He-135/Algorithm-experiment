#include "Editor.h"

void Editor::AddText(string s){
	//先找到光标所在行
	Node* p = this->head;
	//if(p->next == NULL){//文档为空，编辑器为刚启用状态
	//	Node* temp = new Node(s, CharCount, PunctuationCount, BlankCount);
	//	p->next = temp;
	//	line++;
	//	cursor.line++;
	//	cursor.column = -1;//初始时为0，插入文本后要设置到末尾
	//	return;
	//}
	int tempLine = 0;
	while (p->next != nullptr && tempLine != cursor.line) {
		p = p->next;
		tempLine++;
	}
	if(cursor.column == -1){//光标在某一行末尾
 		Node* temp = new Node(s, CharCount, PunctuationCount, BlankCount);
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
		p->s->Insert(s, cursor.column, CharCount, PunctuationCount, BlankCount);
		cursor.column += s.size();
	}
}

Editor::~Editor(){
	while(head != NULL){
		Node* temp = head->next;
		delete head;
		head = temp;
	}
}

void Editor::print(){
	cout << endl << "->【文章内容（'{}'为光标位置）】<-" << endl;
	Node* p = head->next;
	int i = 1;
	if (p == NULL) { cout << endl << i << "\t{}"; }//说明此时文本为空
	while(p != nullptr){
		if(cursor.line != i){//光标不在第i行
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
	if(line == 0){//文档为空，无法设置光标位置
		cout << "\t当前文档为空，无法设置" << endl;
		return;
	}
	cout << "\t输入光标所在行数：";
	cin >> cursor.line;
	while(cursor.line < 1 || cursor.line > line){
		cout << "\t输入不合法，请重新输入：";
		cin >> cursor.line;
	}
	Node* p = this->head;
	int tempLine = 0;
	while (p->next != nullptr && tempLine != cursor.line) {
		p = p->next;
		tempLine++;
	}
	cout << "\t输入光标在第几个字符后（0——开头，-1——末尾）：";
	cin >> cursor.column;
	while(cursor.column < -1 || cursor.column >= p->s->getLength()){
		cout << "\t输入不合法，请重新输入：";
		cin >> cursor.column;
	}
}

void Editor::search(string s){
	Node* p = this->head;
	if(p->next == NULL){
		cout << "\t文档为空，查找失败！" << endl;
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

void Editor::del(int cnt){
	if(cursor.column == -1){//光标在该行的末尾
		cout << "\t光标位置异常，删除失败！" << endl;
		return;
	}
	Node* p = this->head;
	if (p->next == NULL) {
		cout << "\t文档为空，删除失败！" << endl;
		return;
	}
	int tempLine = 0;//用于找到光标所在行
	Node* pre = NULL;//光标所在行的前一行
	while (p->next != nullptr && tempLine != cursor.line) {
		if (tempLine + 1 == cursor.line)
			pre = p;
		p = p->next;
		tempLine++;
	}
	if (cnt == 0)//要删除该行光标后的所有字符
		cnt = p->s->getLength() - cursor.column;
	else if(p->s->getLength() - cursor.column < cnt){//要删除的过多
		cout << "\t输入数量有误，删除失败！" << endl;
		return;
	}
	p->s->del(cursor.column, cnt, CharCount, PunctuationCount, BlankCount);
	if(p->s->getLength() == 0 && p->next == NULL){//如果是最后一行没有字符了，则光标要移动到上一行的末尾
		pre->next = NULL;
		delete p;
		line--;
		cursor.line--;
		cursor.column = -1;
	}
	else if(p->s->getLength() == 0){//光标还在最后一行且所在行已经没有字符了，可以将该行删除
		pre->next = p->next;
		delete p;
		line--;
	}
}