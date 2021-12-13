#include<iostream>
#include<string>
#include<vector>
#include<cmath>
using namespace std;
//������
class Coord{
public:
	int x;
	int y;
	Coord():Coord(0, 0) {}
	Coord(int x, int y){
		this->x = x;
		this->y = y;
	}
	void print(){//���ĳ�����е�����
		cout << "(" << x << "," << y << ")" << endl;
	}
	bool operator==(Coord c){//����==������������ж������������Ƿ����
		if(this->x == c.x && this->y == c.y){
			return true;
		}
		else{
			return false;
		}
	}
};
//����������
class CityList{
public:
	string name;
	Coord coord;
	CityList* next = NULL;
	CityList():CityList("hjy", 1, 1){}
	CityList(string name, int x, int y){
		this->name = name;
		this->coord.x = x;
		this->coord.y = y;
	}

	static Coord searchCity(CityList* head, string name){ //���ݳ�����������
		if(head == NULL || head->next == NULL){//��������Ϊ��
			return Coord(-1, -1);
		}
		CityList* p = head->next;
		while(p){
			if(p->name == name){//�ҵ�����
				return (p->coord);
			}
			p = p->next;
		}
		return Coord(-1, -1);//Ҫ�ҵĳ��в�����
	}
	static string searchCity(CityList* head, Coord coord){
		if (head == NULL || head->next == NULL) {//��������Ϊ��
			return "��������Ϊ��";
		}
		CityList* p = head->next;
		while (p) {
			if (p->coord == coord) {//�ҵ�����
				return p->name;
			}
		}
		return "�ó��в�����";//Ҫ�ҵĳ��в�����
	}
	static string insertCity(CityList* head, string name, int x, int y) {
		if (head == NULL || head->next == NULL) {//��������Ϊ��
			return "��������Ϊ��";
		}
		//CityList* temp = head->next;
		//while(temp){
		//	if(temp == p || temp->name == p->name || temp->coord == p->coord){//�ó����Ѵ���
		//		return "�ó����Ѵ���";
		//	}
		//	temp = temp->next;
		//}
		//temp->next = p;
		//p->next == NULL;
		CityList* p = new CityList(name, x, y);
		p->next = head->next;
		head->next = p;
		return "����ɹ�";
	}
	static bool deleteCity(CityList*head, string s){
		if(head == NULL || head->next == NULL){
			return false;
		}
		CityList* pre = head;
		while(pre->next){
			if(pre->next->name == s){
				CityList* temp = pre->next;
				pre->next = pre->next->next;
				delete temp;
				return true;
			}
			pre = pre->next;
		}
		return false;
	}
	static vector<string> cityInDistance(CityList* head, Coord P, int D){
		if (head == NULL || head->next == NULL) {//��������Ϊ��
			vector<string> s;
			s.push_back("��������Ϊ��");
			return s;
		}
		CityList* temp = head->next;
		vector<string> res;
		while(temp){
			if((int)(sqrt((temp->coord.x - P.x) * (temp->coord.x - P.x) +
				(temp->coord.y - P.y) * (temp->coord.y - P.y))) <= D){
				res.push_back(temp->name);
			}
			temp = temp->next;
		}
		return res;
	}
};

int main(void){
	CityList* head = new CityList("", 0, 0);//ͷ�ڵ�
	CityList* temp = head;
	//���������Ϣ
	CityList* p;
	p	= new CityList();
	temp->next = p;
	temp = temp->next;
	p = new CityList("wl", 250, 250);
	temp->next = p;
	temp = temp->next;
	p = new CityList("gkw", 100, 100);
	temp->next = p;
	temp = temp->next;
	cout << "����������";
	p = head->next;
	while(p){
		cout << p->name << " ";
		p->coord.print();
		p = p->next;
	}
	//ͨ����������������
	Coord c = CityList::searchCity(head, "hjy");
	cout << "����hjy�������꣺";
	c.print();

	//��p�ľ���С��d
	vector<string>s = CityList::cityInDistance(head, Coord(100, 100), 200);
	cout << "��㣨100��100������С��200�ĳ��У�";
	for(int i = 0; i < s.size(); i++){
		cout << s[i] << " ";
	}
	cout << endl;

	//ɾ������
	if(CityList::deleteCity(head, "wl")){
		cout << "ɾ���ɹ�" << endl;
		CityList* p = head->next;
		cout << "ɾ��wl���к�ĳ�������";
		while(p){//��֤�Ƿ�ɹ�ɾ��
			cout << p->name << " ";
			p = p->next;
		}
	}


	return 0;
}