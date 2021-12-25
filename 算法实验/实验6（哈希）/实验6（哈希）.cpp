#include <iostream>
using namespace std;
#define HASH_SIZE 51//��ϣ��ĳ���
#define NAME_SIZE 30//���ֱ���
#define R 51//С�ڵ��ڹ�ϣ���ȵ�R��������

class Name{
public:
	const char* name;
	int asc;
};

class Hash{
public:
	const char* name = "\0";
	int asc = 0;
	int times = 0;//�Ƚϴ���
};

Name nameList[NAME_SIZE];
Hash hashTable[HASH_SIZE];

void initNameList();
void collision(int i, int key);
void averageTimes();
void search();

void initNameList(){
  nameList[0].name = "hejunyuan";
  nameList[1].name = "yangjinyu";
  nameList[2].name = "wanglin";
  nameList[3].name = "gaokangwen";
  nameList[4].name = "guoxuhong";
  nameList[5].name = "tujiarui";
  nameList[6].name = "mawentao";
  nameList[7].name = "heqi";
  nameList[8].name = "wangxiaolong";
  nameList[9].name = "zhuxiao";
  nameList[10].name = "yangyuhang";
  nameList[11].name = "zhangyuehan";
  nameList[12].name = "wangjiaqi";
  nameList[13].name = "shidequan";
  nameList[14].name = "sunyulou";
  nameList[15].name = "liuershao";
  nameList[16].name = "lihao";
  nameList[17].name = "huangzhifeng";
  nameList[18].name = "liangsifen";
  nameList[19].name = "yanzhiwo";
  nameList[20].name = "liyanlin";
  nameList[21].name = "liuxiaohan";
  nameList[22].name = "tanghuan";
  nameList[23].name = "gongxiaoyu";
  nameList[24].name = "haoren";
  nameList[25].name = "huairen";
  nameList[26].name = "shuchang";
  nameList[27].name = "lixinru";
  nameList[28].name = "zhouhang";
  nameList[29].name = "wangcunwen";
  for (int i = 0; i < NAME_SIZE; i++)
  {
    for (int j = 0; (*(nameList[i].name + j)) != '\0'; j++)
      nameList[i].asc += toascii(*(nameList[i].name + j));//ascii�����
  }
}

void initHashTable(){
  initNameList();
  int key = 0;
  for(int i = 0; i < NAME_SIZE; i++){
    key = (nameList[i].asc) % R;//��������
    if(hashTable[key].times == 0){//��δ����Ԫ��
      hashTable[key].name = nameList[i].name;
      hashTable[key].asc = nameList[i].asc;
      hashTable[key].times = 1;
    }
    else{//������ͻ
      collision(i, key);
    }
  }
}

void collision(int i, int key){
  int flag = 0;//���ڱ���Ƿ񵽴��β
  while(hashTable[key].times != 0){//˵����λ���Ѵ���Ԫ��
    if(key == HASH_SIZE-1){//�����β
      key = 0;
      flag = 1;
    }
    else { key++; }
  }
  hashTable[key].name = nameList[i].name;
  hashTable[key].asc = nameList[i].asc;
  if (flag == 0){
    hashTable[key].times = (key - (nameList[i].asc % R)) + 1;
  }
  else{
    hashTable[key].times = (HASH_SIZE - (nameList[i].asc % R)) + key + 1;
  }
}

void averageTimes(){
  double times = 0;
  for(int i = 0; i < HASH_SIZE; i++){
    times += hashTable[i].times;
  }
  double average = times / NAME_SIZE;
  cout << "ƽ�����ҳ��ȣ�" << average << endl;
}

void search() {
  string name;
  cout << "������������ƴ����ȫСд����";
  cin >> name;
  int asc = 0;
  for (int i = 0; i < name.size(); i++) {
    asc += toascii(name[i]);
  }
  int key = asc % R;
  while (hashTable[key].times != 0){
    if(hashTable[key].name == name){
      cout << "���ҳɹ����ڱ���λ�ã�" << key << endl;
      return;
    }
    else { key++; }
  }
  cout << name << "������" << endl;
  return;
}
int main(void){
  initHashTable();
  averageTimes();
  search();
  return 0;
}