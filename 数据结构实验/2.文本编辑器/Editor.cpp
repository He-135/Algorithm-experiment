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
	cout << "����������������";
	cin >> cursor.line;
	cout << "�������ڵڼ����ַ���0������ͷ��-1����ĩβ����";
	cin >> cursor.column;
}