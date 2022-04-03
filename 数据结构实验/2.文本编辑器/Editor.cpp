#include "Editor.h"

void Editor::AddText(string s){
	//���ҵ����������
	Node* p = this->head;
	if(p->next == NULL){//�ĵ�Ϊ��
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
	if(p->s->getLength() == 0){//����Ϊ����
		p->s->Insert(s, 0, CharCount, PunctuationCount, BlankCount);
		cursor.column = -1;
		return;
	}
	if(cursor.column == -1){//�����ĳһ��ĩβ
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
	else{//����ĩβ
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
	cout << endl << "->���������ݣ�'{}'Ϊ���λ�ã���<-" << endl;
	Node* p = head->next;
	if (p == NULL) {//˵����ʱ�ı�Ϊ��
		cout << endl << "1\t{}";
		return;
	}
	int i = 1;
	while(p != nullptr){
		if(cursor.line != i){//��겻�ڵ�i��
			cout << endl << i << "\t" << p->s->getContent();
		}
		else{
			if(p->s->getLength() == 0){//����Ϊ����
				cout << endl << i << "\t{}";
			}
			else if(cursor.column == -1){//����ڸ��е�ĩβ
				cout << endl << i << "\t" << p->s->getContent() << "{}";
			}
			else if (cursor.column == 0) {//����ڸ��еĿ�ͷ
				cout << endl << i << "\t{}" << p->s->getContent();
			}
			else{//�ڸ��е��м�
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
	cout << "\t�ַ�����" << CharCount << "\t�������" << PunctuationCount << "\t�ո�����" << BlankCount << endl;
}

void Editor::setCursor(){
	if(line == 0){//�ĵ�Ϊ�գ��޷����ù��λ��
		cout << "\t��ǰ�ĵ�Ϊ�գ��޷�����" << endl;
		return;
	}
	cout << "\t����������������";
	cin >> cursor.line;
	while(cursor.line < 1 || cursor.line > line){
		cout << "\t���벻�Ϸ������������룺";
		cin >> cursor.line;
	}
	Node* p = this->head;
	int tempLine = 0;
	while (p->next != nullptr && tempLine != cursor.line) {
		p = p->next;
		tempLine++;
	}
	if(p->s->getLength() == 0){//Ŀ����Ϊ����
		cursor.column = -1;
		return;
	}
	cout << "\t�������ڵڼ����ַ���0������ͷ��-1����ĩβ����";
	cin >> cursor.column;
	while(cursor.column < -1 || cursor.column >= p->s->getLength()){
		cout << "\t���벻�Ϸ������������룺";
		cin >> cursor.column;
	}
}

void Editor::search(){
	Node* p = this->head;
	if(p->next == NULL){
		cout << "\t�ĵ�Ϊ�գ�����ʧ�ܣ�" << endl;
		return;
	}
	string s;
	cout << "\t���ٲ��ң�";
	cin.get();
	getline(cin, s);
	int tempLine = 0;//�����ҵ����������
	int tempColumn = cursor.column;//��ʶ���������
	if(cursor.line == line && cursor.column == -1){//�����ȫ�ĵ���ĩβ��ֱ�Ӵ��ĵ���ͷ��ʼ����
		p = p->next;
		tempLine = 1;
		tempColumn = 0;
	}
	else{//��겻���ĵ�ĩβ�����ҵ�������ڵ���
		while (p->next != nullptr && tempLine != cursor.line) {
			p = p->next;
			tempLine++;
		}
	}
	int pos = -1;
	//�����겻�ڸ��еĿ�ͷ��ĩβ�����ڸ��в���
	if(tempColumn != 0 && tempColumn != -1){
		pos = p->s->Index(s, tempColumn);
	}
	else if(tempColumn == -1){//����ڸ��е�ĩβ����ֱ�Ӵ���һ�п�ͷ��ʼ����
		p = p->next;
		tempLine++;
		tempColumn = 0;
	}
	if(pos == -1){//˵��ǰ��û�ҵ�����ֱ�ӴӸ��еĿ�ͷ��ʼ��
		do{
			pos = p->s->Index(s, tempColumn);
			if (pos != -1)
				break;//�Ѿ��ҵ���
			p = p->next;
			tempLine++;
		} while (p != NULL);//ֻҪ���滹���ı��һ�û�ҵ���Ҫ������
	}
	if (pos == -1)//˵��ֱ���ı�ĩβ��û�ҵ�
		cout << "\t" <<  s << "��δ�ҵ�" << endl;
	else if (pos == 0)
		cout << "\t" << s << "����" << tempLine << "�п�ͷ" << endl;
	else
		cout << "\t" << s << "����" << tempLine << "�е�" << pos << "���ַ���" << endl;
}

void Editor::del(){
	Node* p = this->head;
	if (p->next == NULL) {
		cout << "\t�ĵ�Ϊ�գ�" << endl;
		return;
	}
	if (cursor.column == -1) {//����ڸ��е�ĩβ
		cout << "\t���λ���쳣��" << endl;
		return;
	}
	cout << "\tҪɾ�����ַ�����0����ɾ���ӹ�굽����ĩβ��ȫ���ַ�����";
	int cnt;
	cin >> cnt;
	int tempLine = 0;//�����ҵ����������
	Node* pre = NULL;//��������е�ǰһ��
	while (p->next != nullptr && tempLine != cursor.line) {
		if (tempLine + 1 == cursor.line)
			pre = p;
		p = p->next;
		tempLine++;
	}
	if (cnt == 0)//Ҫɾ�����й���������ַ�
		cnt = p->s->getLength() - cursor.column;
	else if(p->s->getLength() - cursor.column < cnt){//Ҫɾ���Ĺ���
		cout << "\t������������ɾ��ʧ�ܣ�" << endl;
		return;
	}
	p->s->del(cursor.column, cnt, CharCount, PunctuationCount, BlankCount);
	//if(p->s->getLength() == 0 && p->next == NULL){//��������һ��û���ַ��ˣ�����Ҫ�ƶ�����һ�е�ĩβ
	//	pre->next = NULL;
	//	delete p;
	//	line--;
	//	cursor.line--;
	//	cursor.column = -1;
	//}
	//else if(p->s->getLength() == 0){//��껹�����һ�����������Ѿ�û���ַ��ˣ����Խ�����ɾ��
	//	pre->next = p->next;
	//	delete p;
	//	line--;
	//}
}

void Editor::enter_add(){
	Node* p = this->head;
	if (p->next == NULL) {//����������
		p->next = new Node("");
		line++;
		cursor.line++;
		p = p->next;
		p->next = new Node("");
		line++;
		cursor.line++;
		return;
	}
	//�ҵ����������
	int tempLine = 0;//�����ҵ����������
	Node* pre = NULL;//��������е�ǰһ��
	while (p->next != nullptr && tempLine != cursor.line) {
		if (tempLine + 1 == cursor.line)
			pre = p;
		p = p->next;
		tempLine++;
	}
	if (p->s->getLength() == 0 || cursor.column == -1) {//����Ϊ���л����ڸ��е�ĩβ
		Node* temp = new Node("");
		temp->next = p->next;
		p->next = temp;
		line++;
		cursor.line++;
		return;
	}
	if (cursor.column == 0) {//����ڸ��еĿ�ͷ
		Node* temp = new Node("");
		temp->next = pre->next;
		pre->next = temp;
		line++;
		cursor.line++;
		return;
	}
	//�����Ŀ���е��м�
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
	if (head->next == NULL)//�ĵ�Ϊ��
		return;
	//�ҵ����������
	Node* p = this->head;
	int tempLine = 0;//�����ҵ����������
	Node* pre = NULL;//��������е�ǰһ��
	while (p->next != nullptr && tempLine != cursor.line) {
		if (tempLine + 1 == cursor.line)
			pre = p;
		p = p->next;
		tempLine++;
	}
	if (cursor.line == 1 && p->s->getLength() == 0 && p->next != NULL) {//�ڵ�һ���ҿ��������Ĳ�Ϊ��
		pre->next = p->next;
		delete p;
		cursor.column = 0;
		line--;
		return;
	}
	else if (cursor.line == 1 && ((p->s->getLength() == 0 && p->next == NULL)//�ڵ�һ�п��������Ĳ�Ϊ��
		|| (p->s->getLength() != 0 && cursor.column == 0)))//�ڵ�һ�зǿ��ҹ���ڿ�ͷ
		return;
	else if (cursor.line == line && p->s->getLength() != 0 && cursor.column == -1)//���һ�зǿ��ҹ��λ��ĩβ
		return;
	else if (p->s->getLength() == 0) {//����ڿ���
		pre->next = p->next;
		cursor.column = -1;//�ƶ�����һ��ĩβ
		cursor.line--;
		line--;
		return;
	}
	else if (cursor.column != -1 && cursor.column != 0) {//���������
		cout << "���λ������ɾ��ʧ�ܣ�" << endl;
		return;
	}
	else if(cursor.column == 0){//�ڳ��˵�һ�еĿ�ͷ,��һ��Ҫ�ϲ�����һ�еĺ���
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
	else{//�ڳ������һ�еĽ�β
	//�������һ�У�����p->next != nullptr
		Node* temp = p->next;
		if(p->next->s->getLength() == 0){//�����һ���ǿ���
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
	cout << "����ɹ���" << endl;
}
void Editor::read_file(){
	fstream ifs;
	ifs.open("text.txt", ios::in);
	if (ifs.is_open()) {
		string s;
		getline(ifs, s);//������һ��
		while (!ifs.eof()) {
			getline(ifs, s);
			AddText(s);
			enter_add();
		}
		enter_del();
	}
}