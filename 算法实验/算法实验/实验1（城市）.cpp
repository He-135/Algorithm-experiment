#include<iostream>
#include<string>
#include<vector>
#include<cmath>
using namespace std;
//坐标类
class Coord{
public:
	int x;
	int y;
	Coord():Coord(0, 0) {}
	Coord(int x, int y){
		this->x = x;
		this->y = y;
	}
	void print(){//输出某个城市的坐标
		cout << "(" << x << "," << y << ")" << endl;
	}
	bool operator==(Coord c){//重载==运算符，用于判断两个点坐标是否相等
		if(this->x == c.x && this->y == c.y){
			return true;
		}
		else{
			return false;
		}
	}
};
//城市链表类
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

	static Coord searchCity(CityList* head, string name){ //根据城市名找坐标
		if(head == NULL || head->next == NULL){//城市链表为空
			return Coord(-1, -1);
		}
		CityList* p = head->next;
		while(p){
			if(p->name == name){//找到城市
				return (p->coord);
			}
			p = p->next;
		}
		return Coord(-1, -1);//要找的城市不存在
	}
	static string searchCity(CityList* head, Coord coord){
		if (head == NULL || head->next == NULL) {//城市链表为空
			return "城市链表为空";
		}
		CityList* p = head->next;
		while (p) {
			if (p->coord == coord) {//找到城市
				return p->name;
			}
		}
		return "该城市不存在";//要找的城市不存在
	}
	static string insertCity(CityList* head, string name, int x, int y) {
		if (head == NULL || head->next == NULL) {//城市链表为空
			return "城市链表为空";
		}
		//CityList* temp = head->next;
		//while(temp){
		//	if(temp == p || temp->name == p->name || temp->coord == p->coord){//该城市已存在
		//		return "该城市已存在";
		//	}
		//	temp = temp->next;
		//}
		//temp->next = p;
		//p->next == NULL;
		CityList* p = new CityList(name, x, y);
		p->next = head->next;
		head->next = p;
		return "插入成功";
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
		if (head == NULL || head->next == NULL) {//城市链表为空
			vector<string> s;
			s.push_back("城市链表为空");
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
	CityList* head = new CityList("", 0, 0);//头节点
	CityList* temp = head;
	//输入城市信息
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
	cout << "建立的链表：";
	p = head->next;
	while(p){
		cout << p->name << " ";
		p->coord.print();
		p = p->next;
	}
	//通过城市名查找坐标
	Coord c = CityList::searchCity(head, "hjy");
	cout << "查找hjy城市坐标：";
	c.print();

	//与p的距离小于d
	vector<string>s = CityList::cityInDistance(head, Coord(100, 100), 200);
	cout << "与点（100，100）距离小于200的城市：";
	for(int i = 0; i < s.size(); i++){
		cout << s[i] << " ";
	}
	cout << endl;

	//删除城市
	if(CityList::deleteCity(head, "wl")){
		cout << "删除成功" << endl;
		CityList* p = head->next;
		cout << "删除wl城市后的城市链表：";
		while(p){//验证是否成功删除
			cout << p->name << " ";
			p = p->next;
		}
	}


	return 0;
}