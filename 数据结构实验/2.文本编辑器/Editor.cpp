#include "Editor.h"

void Editor::AddText(string s){
	//先找到光标所在行
	Node* p = this->head;
	if(p->next == NULL){//文档为空
		Node* temp = new Node(s, CharCount, PunctuationCount, BlankCount);
		p->next = temp;
		line++;
		cursor.line++;
		return;
	}
	int tempLine = 0;
	while (p->next != nullptr && tempLine != cursor.line) {
		p = p->next;
		tempLine++;
	}
	if(p->s->getLength() == 0){//该行为空行
		p->s->Insert(s, 0, CharCount, PunctuationCount, BlankCount);
		cursor.column = -1;
		return;
	}
	if(cursor.column == -1){//光标在某一行末尾
 		/*Node* temp = new Node(s, CharCount, PunctuationCount, BlankCount);
		if(p->next != nullptr){
			temp->next = p->next;
			p->next = temp;
		}
		else
			p->next = temp;
		line++;
		cursor.line++;*/
		p->s->Insert(s, p->s->getLength(), CharCount, PunctuationCount, BlankCount);
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
	if (p == NULL) {//说明此时文本为空
		cout << endl << "1\t{}";
		return;
	}
	int i = 1;
	while(p != nullptr){
		if(cursor.line != i){//光标不在第i行
			cout << endl << i << "\t" << p->s->getContent();
		}
		else{
			if(p->s->getLength() == 0){//该行为空行
				cout << endl << i << "\t{}";
			}
			else if(cursor.column == -1){//光标在该行的末尾
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
	if(p->s->getLength() == 0){//目标行为空行
		cursor.column = -1;
		return;
	}
	cout << "\t输入光标在第几个字符后（0——开头，-1——末尾）：";
	cin >> cursor.column;
	while(cursor.column < -1 || cursor.column >= p->s->getLength()){
		cout << "\t输入不合法，请重新输入：";
		cin >> cursor.column;
	}
}

void Editor::search(){
	Node* p = this->head;
	if(p->next == NULL){
		cout << "\t文档为空，查找失败！" << endl;
		return;
	}
	string s;
	cout << "\t快速查找：";
	cin.get();
	getline(cin, s);
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

void Editor::del(){
	Node* p = this->head;
	if (p->next == NULL) {
		cout << "\t文档为空！" << endl;
		return;
	}
	if (cursor.column == -1) {//光标在该行的末尾
		cout << "\t光标位置异常！" << endl;
		return;
	}
	cout << "\t要删除的字符数（0——删除从光标到该行末尾的全部字符）：";
	int cnt;
	cin >> cnt;
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
	//if(p->s->getLength() == 0 && p->next == NULL){//如果是最后一行没有字符了，则光标要移动到上一行的末尾
	//	pre->next = NULL;
	//	delete p;
	//	line--;
	//	cursor.line--;
	//	cursor.column = -1;
	//}
	//else if(p->s->getLength() == 0){//光标还在最后一行且所在行已经没有字符了，可以将该行删除
	//	pre->next = p->next;
	//	delete p;
	//	line--;
	//}
}

void Editor::enter_add(){
	Node* p = this->head;
	if (p->next == NULL) {//插入两空行
		p->next = new Node("");
		line++;
		cursor.line++;
		p = p->next;
		p->next = new Node("");
		line++;
		cursor.line++;
		return;
	}
	//找到光标所在行
	int tempLine = 0;//用于找到光标所在行
	Node* pre = NULL;//光标所在行的前一行
	while (p->next != nullptr && tempLine != cursor.line) {
		if (tempLine + 1 == cursor.line)
			pre = p;
		p = p->next;
		tempLine++;
	}
	if (p->s->getLength() == 0 || cursor.column == -1) {//该行为空行或光标在该行的末尾
		Node* temp = new Node("");
		temp->next = p->next;
		p->next = temp;
		line++;
		cursor.line++;
		return;
	}
	if (cursor.column == 0) {//光标在该行的开头
		Node* temp = new Node("");
		temp->next = pre->next;
		pre->next = temp;
		line++;
		cursor.line++;
		return;
	}
	//光标在目标行的中间
	string s1, s2;
	p->s->split(cursor.column, s1, s2);
	Node* temp1 = new Node(s1);
	Node* temp2 = new Node(s2);
	temp1->next = temp2;
	temp2->next = p->next;
	pre->next = temp1;
	delete p;
	line++;
	cursor.line++;
	cursor.column = 0;
}

void Editor::enter_del() {
	if (head->next == NULL)//文档为空
		return;
	//找到光标所在行
	Node* p = this->head;
	int tempLine = 0;//用于找到光标所在行
	Node* pre = NULL;//光标所在行的前一行
	while (p->next != nullptr && tempLine != cursor.line) {
		if (tempLine + 1 == cursor.line)
			pre = p;
		p = p->next;
		tempLine++;
	}
	if (cursor.line == 1 && p->s->getLength() == 0 && p->next != NULL) {//在第一行且空行且下文不为空
		pre->next = p->next;
		delete p;
		cursor.column = 0;
		line--;
		return;
	}
	else if (cursor.line == 1 && ((p->s->getLength() == 0 && p->next == NULL)//在第一行空行且下文不为空
		|| (p->s->getLength() != 0 && cursor.column == 0)))//在第一行非空且光标在开头
		return;
	else if (cursor.line == line && p->s->getLength() != 0 && cursor.column == -1)//最后一行非空且光标位于末尾
		return;
	else if (p->s->getLength() == 0) {//光标在空行
		pre->next = p->next;
		cursor.column = -1;//移动到上一行末尾
		cursor.line--;
		line--;
		return;
	}
	else if (cursor.column != -1 && cursor.column != 0) {//光标在行中
		cout << "光标位置有误，删除失败！" << endl;
		return;
	}
	else if(cursor.column == 0){//在除了第一行的开头,这一行要合并到上一行的后面
		cursor.column = pre->s->getLength();
		cursor.line--;
		line--;
		string s = pre->s->getContent() + p->s->getContent();
		MyString* temp = pre->s;
		pre->s = new MyString(s);
		delete temp;
		pre->next = p->next;
		delete p;
		return;
	}
	else{//在除了最后一行的结尾
	//不是最后一行，所以p->next != nullptr
		Node* temp = p->next;
		if(p->next->s->getLength() == 0){//如果下一行是空行
			p->next = p->next->next;
			delete temp;
		}
		else{
			cursor.column = p->s->getLength();
			string s = p->s->getContent() + p->next->s->getContent();
			MyString* temp_s = p->s;
			p->s = new MyString(s);
			delete temp_s;
			p->next = p->next->next;
			delete temp;
		}
		line--;
	}
}

void Editor::save(){
	fstream ofs;
	ofs.open("text.txt", std::ios::out);
	Node* p = head->next;
	while(p != NULL){
		ofs << endl << p->s->getContent();
		p = p->next;
	}
	ofs.close();
	cout << "保存成功！" << endl;
}
void Editor::read_file(){
	fstream ifs;
	ifs.open("text.txt", ios::in);
	if (ifs.is_open()) {
		string s;
		getline(ifs, s);//跳过第一行
		while (!ifs.eof()) {
			getline(ifs, s);
			AddText(s);
			enter_add();
		}
		enter_del();
	}
}