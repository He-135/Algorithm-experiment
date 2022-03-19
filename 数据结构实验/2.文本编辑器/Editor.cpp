#include "Editor.h"

void Editor::AddText(string s){
	if(cursor.column == -1){//�����ĳһ��ĩβ
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
	else{//����ĩβ
		Node* p = this->head;
		int tempLine = 0;
		while (p->next != nullptr && tempLine != cursor.line) {
			p = p->next;
			tempLine++;
		}
		//�ҵ��˹�����ڵ���
		p->s->Insert(s, cursor.column, CharCount, PunctuationCount, BlankCount);
		cursor.column += s.size();
	}
}

void Editor::print(){
	cout << endl << "->���������ݣ�'{}'Ϊ���λ�ã���<-" << endl;
	Node* p = head->next;
	int i = 1;
	if (p == NULL) { cout << endl << i << "\t{}"; }
	while(p != nullptr){
		if(cursor.line != i){//��껹�ڵ�i��
			cout << endl << i << "\t" << p->s->getContent();
		}
		else{
			if(cursor.column == -1){//����ڸ��е�ĩβ
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
	cout << "\t" << "����������������";
	cin >> cursor.line;
	while(cursor.line < 1 || cursor.line > line){
		cout << "\t" << "���벻�Ϸ������������룺";
		cin >> cursor.line;
	}
	Node* p = this->head;
	int tempLine = 0;
	while (p->next != nullptr && tempLine != cursor.line) {
		p = p->next;
		tempLine++;
	}
	cout << "\t" << "�������ڵڼ����ַ���0������ͷ��-1����ĩβ����";
	cin >> cursor.column;
	while(cursor.column < -1 || cursor.column >= p->s->length){
		cout << "\t" << "���벻�Ϸ������������룺";
		cin >> cursor.column;
	}
}

void Editor::search(string s){
	Node* p = this->head;
	if(p->next == NULL){
		cout << "\t" << "�ĵ�Ϊ�գ�����ʧ�ܣ�" << endl;
		return;
	}
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