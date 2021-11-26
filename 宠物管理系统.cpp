#include<cstdio>
#include<iostream>
#include<iomanip>
#include<string.h>
#include <algorithm>
#include<string>
#include<math.h>
#include<fstream>
#include<windows.h> 
using namespace std;

struct master
{
	char mnum[10];
	char mname[200];
	int phone;
	int sum;
	master *next;
	float expense;
};

struct pet
{
	int pnum;
	string pname;
	
	string type;
	char owner[10];
	int time;
	float dayprice;
	pet *next;
};

pet *Pet;
master *Master;

pet *CreatePetList();//把文件数据读入链表 
master *CreateHostList();

pet *idGetPet(pet *&Pet, int id);//用id获取链表结点 
pet *nameGetPet(pet *&Pet, string name);//用name获取链表结点 
master *idGetMaster(master *&Master, char id[]);
master *nameGetMaster(master *&Master, char name[]);

void MainMenu();//打印菜单 
void  MasterMenu();
void PetMenu();

void SaveFile(pet *&Pet);//保存数据至文件 
void SaveFile(master *&Master);

void pSearch();//查询单个宠物信息 
void Search();//查询宠物信息 
void mSearch();// 查询单个客户信息 
void Search2();//查询客户信息 

bool idDelData(int id);//依据id、name删除链表结点 
bool nameDelData( string name);
bool idDelData( char num[]); 
void Del() ;//删除处理 

void Change();//更改数据 

void Add();//增加数据 

void ToSort();//客户消费排序 
void Sort();

//把文件数据读入链表 
pet *CreatePetList()
{
	int n;
	pet *head = NULL, *p, *q;
	ifstream f1;
	f1.open("pet.txt", ios::in);	
	f1 >> n;
	if(n == 0)
	{
		cout<<"文件为空！"<<endl; 
		return NULL;
	}
	else{
		p = new pet;
		p -> pnum = n;
		f1 >> p -> pname;
		f1 >> p -> type;
		f1 >> p -> owner;
		f1 >> p -> time;
		f1 >> p -> dayprice;
		if(head == NULL) head = p;
		else {
			q -> next = p;
		}
		q = p;	
	}
	
	while(!f1.eof())
	{
		p = new pet;
		f1 >> p -> pnum;
		f1 >> p -> pname;
		f1 >> p -> type;
		f1 >> p -> owner;
		f1 >> p -> time;
		f1 >> p -> dayprice;
		if(head == NULL) head = p;
		else {
			q -> next = p;
		}
		q = p;
	}
	if(head != NULL) q->next = NULL;
	f1.close();
	return head;
}

//把文件数据读入链表 
master *CreateHostList()
{
	master *head = NULL, *p, *q;
	FILE *fp1; 
	char ch, a[10];
	fp1=fopen("master.txt","r");
	if(fp1 == NULL)
	{
		cout<<"打开文件失败！"<<endl; 
		return NULL ;
	}
	ch = fgetc(fp1);
	if(ch == EOF){
		cout << "文件为空！ ";
		return NULL; 
	}
	else{
		p = new master;
		a[0] = ch;
		strcpy(p->mnum, a);
		fscanf(fp1,"%s %d %d", p->mname, &p->phone, &p->sum);
		p->expense = 0;
		if(head == NULL) 
		{head = p;q=p;} 
		else {
			q->next = p;
			q = p;
		}
	}
	while(!feof(fp1))
	{
		p = new master;
	
		fscanf(fp1,"%s %s %d %d",p->mnum,p->mname,&p->phone,&p->sum);
		p->expense = 0;
		if(head == NULL) 
		{head = p;q=p;} 
		else {
			q->next = p;
			q = p;
		}
	}
	if(head != NULL) q -> next = NULL;
	fclose(fp1);
	return head;
}

//用id获取链表结点
pet *idGetPet(pet *&Pet, int id)
{
	pet *q = Pet;	
	if(NULL == Pet) return NULL;
	if(id == Pet -> pnum){
		return Pet;
	}	
	while(NULL != q && id != q -> pnum){
		q = q -> next;
	}
	return q;
} 

//用name获取链表结点 
pet *nameGetPet(pet *&Pet, string name)
{
	pet *q = Pet;	
	if(NULL == Pet) return NULL;
	if(name == Pet -> pname){
		return Pet;
	}	
	while(NULL != q && name != q -> pname){
		q = q -> next;
	}
	return q;
} 

//用id获取链表结点 
master *idGetMaster(master *&Master, char id[]){
	master *q = Master;	
	if(NULL == Master) return NULL;
	if(strcmp(id,Master -> mnum)==0){
		return Master;
	}	
	while(NULL != q && strcmp(id, q -> mnum)!=0){
		q = q -> next;
	}
	return q;
}

//用name获取链表结点 
master *nameGetMaster(master *&Master, char name[])
{
	master *q = Master;	
	if(NULL == Master) return NULL;
	if(name == Master->mname){
		return Master;
	}	
	while(NULL != q && name != q->mname){
		q = q -> next;
	}
	return q;
} 

//打印菜单 
void MainMenu(){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE|FOREGROUND_GREEN);
cout<<"                                                                                                          "<<endl;	                                                                                                              
cout<<"                                                      :                                           ..r        "<<endl;
cout<<"        rb1JJr.               rBQ  SB:                DQQi                BB  vBE             .iuX5jvr        "<<endl;
cout<<"      .. .iLsXZJ::.           BB    Q        is.     .BQQP      rJ        b2   EB          iLr.:ZSL7::irU:    "<<endl;
cout<<"     :PLjri::rY  :JSr     :. ..iBPvi:5PDBBDqBBBBBP.EM.LLY:7B.JQQBBBgqQBBbKL:72B2 . .i    .d7r.    i:rrvrv. .  "<<endl;
cout<<"   r.r.rrii11  . i: Z. .dZBdJBBgQg2BBBgBE  M:   .r2BBM M.7BBEv:    R. 7BBgBBPqBgBBKSQMPs  S :. r  IIriii.P77  "<<endl;
cout<<"   LPr  ...::  i  :vv  j7         .   Bq   2BB.   YJQP Q5 B:g    MBg    Bv  .         .2. iq7 .           Qv:."<<endl;
cout<<" ir7g           LIIUiiiB              Br    .i      rBvPrBD      .:     Q5             UMvir2Xj ..       7qi7i"<<endl;
cout<<".rviYSi.....:r7i7ivs.: 7      .       .B     Qi       vQq        Bb    PZ              i.  qL:ii::rrvvv77i.:i."<<endl;
cout<<"      .irrr:.  ..:rv       .           rDJri7d   .     B7        7S:ivKE                    .                 "<<endl;
SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
cout<<"                         ........                                :r                                           "<<endl;
cout<<"                    .YYL7ririrrvL7:                             Q:2:                                         "<<endl;
cout<<"                  v5KI..         .:ru:.                         rZ. u1                                        "<<endl;
cout<<"                i5ur5   . . . . .    SSX:                       qiL  :P:                                      "<<endl;
cout<<"              .q1ri75  ............  I7rSL                      qi5P   vU1Jrirrri7Q.                          "<<endl;
cout<<"              XuiiiJv     ... ...    2riij2:                    PrEr      ...   .qE                           "<<endl;
cout<<"              Luii:5.:Ud7  . ... . : sriii7b5                i7KS   7:        Us5q                            "<<endl;
cout<<"              .SiirI EbQS      .. ZDP5Y:ii7X.                 7g7: ZBBQ       2KY                             "<<endl;
cout<<"               57iU: :.    ..:    :5I:Jiii1i                  :Y :.7BBL  X. BB7J                              "<<endl;
cout<<"              IK5K ::  . KBBBB.    : 71iiK                    d         7. BMPZv                             "<<endl;
cout<<"                  ii1      5PPY  .  i:YI1SS                    :X             5                               "<<endl;
cout<<"                    ivr.....:.   .  d2. :i.                     Z.          .P                                "<<endl;
cout<<"                     1r.71i. .i21:ib                            d            b.                               "<<endl;
cout<<"                    Yr :s ..:....  1:                          .q             Xv                              "<<endl;
cout<<"                   .K   rr.      . iY                          7L              i2s.                           "<<endl;
cout<<"                   iv    :i.. .... .U                          Li                .Uj                          "<<endl;
cout<<"                   :r : .. ....... .j                          J:                  :b:                        "<<endl;
cout<<"                   Ks j: .... .     Y                          7r 5                  Z.         77LY:         "<<endl;
cout<<"                  si1  s. .... .X   J                          :2 .2          :.     .E       :Z:  .PM        "<<endl;
cout<<"                  L..u  u   .  :K  .g                           d   B7       rs       P       g5dJ   XY       "<<endl;
cout<<"                  .j S. 7v .   2   XP                           E   Xru  .:  X        q         :b    q       "<<endl;
cout<<"                   j rr .1  . .v  vq.                           Ji  q b  UJ  v        g7       :P.   K:       "<<endl;
cout<<"                  dX.Ur .Z:::.I:  SJK                           :5 .2 q  DLJLI      .gv.rYvvv1u7   .5r        "<<endl;
cout<<"                  iiiiIY2:    7Sr7P7Y                            E:P: D.Si rg.  ..ruj .7i....   .:uJ.         "<<endl;
cout<<"                               .                                       .     .....         ......             "<<endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE|FOREGROUND_GREEN);
	cout << "                                                                                         " << endl;
	cout << "                             *##*****************";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
	cout << "【宠物寄养管理系统】";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE|FOREGROUND_GREEN);
	cout << "*****************##*" << endl;
	cout << "                             *                                                          *" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED|FOREGROUND_GREEN);	
	cout << "                             *                    请选择要处理的信息：                  *"<< endl;
	cout << "                             *                    [1] 宠物信息                          *" << endl; 
	cout << "                             *                    [2] 主人信息                          *" << endl; 
	cout << "                             *                    [0] 退出系统                          *" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_BLUE|FOREGROUND_GREEN);
	cout << "                             *                                                          *" << endl;
	cout << "                             *##******************************************************##*" << endl;
}


//打印菜单 
void  MasterMenu(){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
	cout << "                                                  [1] 查询信息"<<endl;
	cout << "                                                  [2] 主人消费排序" << endl;
	cout << "                                                  [0] 返回" << endl<<endl;
	cout << "                                                  请选择0~2:" << endl;
}


//打印菜单 
void PetMenu(){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
	cout << "                                                  [1] 查询信息" << endl;
	cout << "                                                  [2] 删除信息" << endl;
	cout << "                                                  [3] 修改信息" << endl;
	cout << "                                                  [4] 增加信息" << endl;
	cout << "                                                  [0] 返回" << endl << endl;
	cout << "                                                  请选择0~4:" << endl;
}

//保存数据至文件 
void SaveFile(pet *&Pet){
	ofstream fout;
	fout.open("pet.txt", ios_base::binary);
	pet *p = Pet;
	while(p != NULL){
		if(p->next != NULL){
			fout << p->pnum << " " << p->pname << " " << p->type << " " << p->owner << " " << p->time << " " << p->dayprice << endl;
			p = p->next;	
		}
		else{
			fout << p->pnum << " " << p->pname << " " << p->type << " " << p->owner << " " << p->time << " " << p->dayprice ;
			p = p->next;
		}
	}
	fout.close();
	return;
}

//保存数据至文件 
void SaveFile(master *&Master){
	ofstream fout;
	fout.open("master.txt", ios_base::binary);
	master *p = Master;
	while(p != NULL){
		if(p->next != NULL){
			fout << p->mnum << " " << p->mname << " " << p->phone << " " << p->sum << endl;
			p = p->next;
		}
		else{
			fout << p->mnum << " " << p->mname << " " << p->phone << " " << p->sum ;
			p = p->next;
		}
	}
	fout.close();
	return;
}

//查询单个宠物信息 
void pSearch(){
	system("cls");
	cout << "[1] 编号" << endl;
	cout << "[2] 名字" << endl;
	cout << "[0] 返回" << endl;
	cout << "******请选择0~2：" << endl;
	int choice;
	cin >> choice;
	if(choice == 1){
		cout << "请输入编号：" << endl; 
		int num;
		cin >> num;
		pet *k= idGetPet(Pet, num);
		if(k == NULL) cout << "请检查" << num <<"是否存在！";
		else{
			cout << "编号：" << k->pnum << endl;
			cout << "名字：" << k->pname << endl;
			cout << "品种：" << k->type << endl;
			cout << "主人编号：" << k->owner << endl;
			cout << "寄养天数" << k->time << endl;
			cout << "每日价格" << k->dayprice << endl << endl; 
			master *k2 = idGetMaster(Master, k->owner);
			if(k2 !=NULL){
				cout << "主人信息:" <<endl;
				cout << "    主人编号：" << k2->mnum <<endl;
				cout << "    主人名字：" << k2->mname << endl;
				cout << "    联系方式：" << k2->phone << endl;
				cout << "    寄养宠物数量：" << k2->sum << endl << endl;
			} 
			else{
				cout << "缺少主人信息！" << endl;
			}
		} 
		
		system("pause");
	}
	else if(choice == 2){
		cout << "请输入名字：" << endl; 
		string name;
		cin >> name;
		pet *k = NULL;
		k = nameGetPet(Pet, name);
		if(k == NULL) cout << "请检查" << name <<"是否存在！";
		else{
			cout << "编号：" << k->pnum << endl;
			cout << "名字：" << k->pname << endl;
			cout << "品种：" << k->type << endl;
			cout << "主人编号：" << k->owner << endl;
			cout << "寄养天数:" << k->time << endl;
			cout << "每日价格:" << k->dayprice << endl << endl;  
			master *k2 = idGetMaster(Master, k->owner);
			cout << "主人信息:" <<endl;
			cout << "    主人编号：" << k2->mnum <<endl;
			cout << "    主人名字：" << k2->mname << endl;
			cout << "    联系方式：" << k2->phone << endl;
			cout << "    寄养宠物数量：" << k2->sum << endl << endl;
		} 
		system("pause");
	} 
	else{
		return;
	} 
}

//查询宠物信息 
void Search(){
	system("cls");
	if(Pet == NULL){
		cout << "没有宠物信息！" << endl;
		system("pause");
		return;
	}
	cout << "[1] 查询单个宠物信息" << endl;
	cout << "[2] 查询所有宠物信息" << endl;
	cout << "[0] 返回" << endl;
	cout << "******请选择0~2：" << endl;
	int choice;
	cin >> choice;
	if(choice == 1){
		pSearch();
	} 
	else if(choice == 2){
		pet *p = Pet;
		while(p != NULL){
			cout << "编号：" << p->pnum << endl;
			cout << "名字：" << p->pname << endl;
			cout << "品种：" << p->type << endl;
			cout << "主人编号：" << p->owner << endl;
			cout << "寄养天数:" << p->time << endl;
			cout << "每日价格:" << p->dayprice << endl << endl;
			master *k2 = idGetMaster(Master, p->owner);
			if(k2 != NULL){
				cout << "主人信息:" <<endl;
				cout << "    主人编号：" << k2->mnum <<endl;
				cout << "    主人名字：" << k2->mname << endl;
				cout << "    联系方式：" << k2->phone << endl;
				cout << "    寄养宠物数量：" << k2->sum << endl << endl;	
			}
			else{
				cout << "缺少主人信息！" << endl << endl;
			}
			p = p->next; 
		}
		system("pause");
	}
	else{
		return;
	}
}

// 查询单个客户信息 
void mSearch(){
	system("cls");
	cout << "[1] 编号" << endl;
	cout << "[2] 名字" << endl;
	cout << "[0] 返回" << endl;
	cout << "******请选择0~2：" << endl;
	int choice;
	cin >> choice;
	if(choice == 1){
		cout << "请输入编号：" << endl; 
		char num[10];
		cin >> num;
		master *k = NULL;
		k = idGetMaster(Master, num);
		if(k == NULL) cout << "请检查" << num <<"是否存在！";
		else{
			cout << "编号：" << k->mnum << endl;
			cout << "名字：" << k->mname << endl;
			cout << "联系方式:" << k->phone << endl;
			cout << "寄养宠物数量:" << k->sum << endl; 
		} 
		system("pause");
	}
	else if(choice == 2){
		cout << "请输入名字：" << endl; 
		char name[100];
		cin >> name;
		master *k = NULL;
		k = nameGetMaster(Master, name);
		if(k == NULL) cout << "请检查" << name <<"是否存在！";
		else{
			cout << "编号：" << k->mnum << endl;
			cout << "名字：" << k->mname << endl;
			cout << "联系方式:" << k->phone << endl;
			cout << "寄养宠物数量:" << k->sum << endl;
		} 
		system("pause");
	} 
	else{
		return;
	} 
}

//查询客户信息 
void Search2(){
	system("cls");
	cout << "[1] 查询单个客户信息" << endl;
	cout << "[2] 查询所有客户信息" << endl;
	cout << "[0] 返回" << endl;
	cout << "******请选择0~2：" << endl;
	int choice;
	cin >> choice;
	if(choice == 1){
		mSearch();
	} 
	else if(choice == 2){
		master *p = Master;
		if(p == NULL){
			cout << "没有客户信息！" << endl;
			system("pause");  
		} 
		while(p != NULL){
			cout << "编号：" << p->mnum << endl;
			cout << "名字：" << p->mname << endl;
			cout << "联系方式:" << p->phone << endl;
			cout << "寄养宠物数量:" << p->sum << endl;
			p = p->next; 
		}
		system("pause");
	}
	else{
		return;
	}
} 

//依据id删除链表结点 
bool idDelData(int id){
	pet *p = Pet, *q = NULL;	
	if(id == Pet -> pnum){
		Pet = Pet->next;
		delete p;
		return true;
	}	
	q = p->next;
	while(NULL != q && id != q -> pnum){
		p = q; 
		q = q -> next;
	}
	if(NULL != q){
		p->next = q->next;
		delete q;
		return true;
	}
	return false;
}

//依据name删除链表结点 
bool nameDelData( string name){
	pet *p = Pet, *q = NULL;	
	if(name == Pet -> pname){
		Pet = Pet->next;
		delete p;
		return true;
	}	
	q = p->next;
	while(NULL != q && name != q -> pname){
		p = q; 
		q = q -> next;
	}
	if(NULL != q){
		p->next = q->next;
		delete q;
		return true;
	}
	return false;
}

//依据id删除链表结点 
bool idDelData( char num[]){
	master *p = Master, *q = NULL;	
	if(strcmp(num, Master->mnum)==0){
		Master = Master->next;
		delete p;
		return true;
	}	
	q = p->next;
	while(NULL != q && strcmp(num, q -> mnum) != 0){
		p = q; 
		q = q -> next;
	}
	if(NULL != q){
		p->next = q->next;
		delete q;
		return true;
	}
	return false;
}

//删除处理 
void Del() 
{
	system("cls");
	cout << "[1] 按编号删除" << endl;
	cout << "[2] 按名字删除" << endl;
	cout << "[0] 返回" << endl;
	cout << "******请选择0~2：" << endl;
	int choice;
	cin >> choice;
	while(true){
		if(choice == 1){
		cout << "请输入编号：" << endl; 
		int num;
		cin >> num;
		pet *k = idGetPet(Pet, num);
		if(k == NULL){
			cout << "请检查" << num <<"是否存在！" << endl;
			system("pause");
			continue;
		}
		else{
			cout << "编号：" << k->pnum << endl;
			cout << "名字：" << k->pname << endl;
			cout << "品种：" << k->type << endl;
			cout << "主人编号：" << k->owner << endl;
			cout << "寄养天数:" << k->time << endl;
			cout << "每日价格:" << k->dayprice << endl;
			char mnum[10];
			strcpy(mnum,k->owner);
			master *t = idGetMaster(Master, mnum);
			if(t->sum == 1){
				cout << "已近找到编号为" << num << "的数据，是否删除全部数据和其主人信息？" << endl;
				if(MessageBox(NULL,"【确定要进行删除操作吗？】","提示",MB_OKCANCEL) == 1){
					if(idDelData(num)&&idDelData(mnum)){
						SaveFile(Pet);
						SaveFile(Master);
						cout << "操作成功！"<<endl; 
						system("pause");
						break;
					} 
					else{
						 cout<<"操作失败！"<<endl;
						 system("pause");
						continue;
					}
				} 
				else{
					return;
				}
			}
			else 
			{
				cout << "已近找到编号为" << num << "的数据，是否全部删除？" << endl;
				if(MessageBox(NULL,"【确定要进行删除操作吗？】","提示",MB_OKCANCEL) == 1){
					if(idDelData(num)){
						t->sum--;
						SaveFile(Master);
						SaveFile(Pet);
						cout << "操作成功！"<<endl; 
						system("pause");
						break;
					} 
					else{
						 cout<<"操作失败！"<<endl;
						 system("pause");
						 continue;
					}
				} 
				else{
					return;
				}
			} 
		system("pause");
		}
		} 
	else if(choice == 2){
		cout << "请输入名字：" << endl; 
		string name;
		cin >> name;
		pet *k = NULL;
		k = nameGetPet(Pet, name);
		if(k == NULL) cout << "请检查" << name <<"是否存在！" << endl;
		else{
			cout << "编号：" << k->pnum << endl;
			cout << "名字：" << k->pname << endl;
			cout << "品种：" << k->type << endl;
			cout << "主人编号：" << k->owner << endl;
			cout << "寄养天数:" << k->time << endl;
			cout << "每日价格:" << k->dayprice << endl;  
			char mnum[10];
			strcpy(mnum,k->owner);
			master *t = idGetMaster(Master, mnum);
			if(t->sum == 1){
				cout << "已近找到名字为" << name << "的数据，是否删除全部数据和其主人信息？" << endl;
				if(MessageBox(NULL,"【确定要进行删除操作吗？】","提示",MB_OKCANCEL) == 1){
					if(nameDelData(name)&&idDelData(mnum)){
						SaveFile(Pet);
						SaveFile(Master);
						cout << "操作成功！"<<endl; 
						system("pause");
						break;
					} 
					else{
						 cout<<"操作失败！"<<endl;
						 system("pause");
						continue;
					}
				} 
				else{
						return;
				}
			} 
			else{
				cout << "已近找到名字为" << name << "的数据，是否全部删除？" << endl;
				if(MessageBox(NULL,"【确定要进行删除操作吗？】","提示",MB_OKCANCEL) == 1){
					if(nameDelData(name)){
						t->sum--;
						
						SaveFile(Master);
						SaveFile(Pet);
						cout << "操作成功！"<<endl; 
						system("pause");
						break;
					} 
					else{
						 cout<<"操作失败！"<<endl;
						 system("pause");
						continue;
					}
				} 
				else{
					return;
				}
			}
		system("pause");
		} 
	}
	else{
		return;
	} 
	}
	
}

//更改数据 
void Change(){
	system("cls");
	cout << "******请输入宠物编号：" << endl;
	int num;
	int day;
	float price;
	cin >> num;
	pet *k = NULL;
	k = idGetPet(Pet, num);
	if(k == NULL) cout << "请检查" << num <<"是否存在！";
	else{
		cout << "编号：" << k->pnum << endl;
		cout << "名字：" << k->pname << endl;
		cout << "品种：" << k->type << endl;
		cout << "主人编号：" << k->owner << endl;
		cout << "寄养天数:" << k->time << endl;
		cout << "每日价格:" << k->dayprice << endl; 
		cout << "[1] 修改寄养天数" << endl;
		cout << "[2] 修改寄养价格" << endl;
		cout << "******请选择1~2：" << endl;
		int choice ;
		cin >> choice;
		if(choice == 1){
			cout << "请输入寄养天数：" << endl;
			cin >> day; 
			k->time = day;
			SaveFile(Pet);
			cout << "操作成功！"<<endl; 
		}
		else if(choice == 2){
			cout << "请输入寄养价格：" << endl;
			cin >> price; 
			k->dayprice = price;
			SaveFile(Pet);
			cout << "操作成功！"<<endl; 
		}
		else{
			cout << "无此选项！" << endl;
		}
	} 
	system("pause");	
}

//增加数据 
void Add(){
	int id;
	string name;
	string ty;
	int day, price;
	char mnum1[10];
	struct pet *p, *q = NULL, *r = NULL;
	while(true){
		system("cls");
		cout << "******请输入要增加的宠物编号：" << endl;
		cin >> id;	
		if(idGetPet(Pet,id) != NULL){
			cout << "编号 "<<id<<" 已经存在!请重新输入！"<<endl; 
			system("pause");
			continue;
		}
		else{
			p = new pet;
			p->pnum = id;
			p->next = NULL;
			cout << "请输入 宠物名字 " ;
			cout << " 宠物品种 " ;
			cout << " 主人编号 " ;
			cout << " 寄养天数 " ;
			cout << " 寄养每日价格 :" <<endl;
			cout << "输入格式：一行数据&各数据之间有一空格。例如 ：momo 萨摩耶 b 1 600 " << endl <<"请输入：";
			cin >> name; 
			cin >> ty; 
			cin >> mnum1; 
			cin >> day; 
			cin >> price;
			p->pname = name;
			p->type = ty;
			strcpy(p->owner, mnum1);
			p->time = day;
			p->dayprice = price;
			if(NULL == Pet || p->pnum <= Pet->pnum){
				p->next = Pet;
				Pet = p;
				SaveFile(Pet);
				cout << "操作成功！"<<endl; 
				system("pause");
			} 
			else{
				r = Pet;
				q = Pet->next;
				while(q != NULL){
					if(p->pnum > q->pnum){
						r = q;
						q = q->next;
					}
					else {
						break;
					}
				}
				r->next = p;
				p->next = q;		 
				master *t = idGetMaster(Master, p->owner);
				if(t != NULL){
					t->sum++;
					SaveFile(Pet);
					SaveFile(Master);
					cout<< "操作成功！"<<endl;
					system("pause");
					break;
				}
				else{
					cout << "未查到此顾客，需新增主人信息！" << endl;
					master *p2, *q2, *r2;
					char name2[10];
					int phone2, sum2; 
					p2 = new master;
					p2->next = NULL;
					strcpy(p2->mnum, mnum1);
					cout << "请输入 主人名字 ";
					cout << " 联系方式 " ;
					cout << " 寄养宠物数量：" << endl;
					cout << "输入格式：一行数据&各数据之间有一空格。"<< endl << " 请输入："; 
					cin >> name2; 
					cin >> phone2; 
					cin >> sum2; 
					strcpy(p2->mname, name2);
					p2->phone = phone2;
					p2->sum = sum2;
		
					r2 = Master;
					q2 = Master->next;
					r2->next = p2;
					p2->next = q2;
					SaveFile(Pet);
					SaveFile(Master);
					cout<< "操作成功！"<<endl;
					system("pause");
					break;
					}
				}
			
		}
	} 
}

//客户消费排序 
void ToSort(){
	if(Master == NULL || Pet == NULL){
		return;
	}
	float m,n;
	master *p, *q, *bigger, *a, *b;
	for(p = Master; p != NULL; p = p->next){
		bigger = p;
		q=p->next;
		while( q != NULL){
			m=bigger->expense;
			n=q->expense;
			if(m < n){
				bigger = q;
			}
			q=q->next;
		}
		if(bigger != p){
			swap(bigger->mnum, p->mnum);
			swap(bigger->mname, p->mname);
			swap(bigger->phone , p->phone);
			swap(bigger->sum , p->sum);
			swap(bigger->expense , p->expense);
		}
	}
}

//排序模块 
void Sort(){
	pet *p = Pet;
	master *p1;
	while(p != NULL){
		p1 = idGetMaster(Master, p->owner);
		p1->expense += (p->time) * (p->dayprice);
		p = p->next;
	}
	ToSort();
	master *o = Master;
	while(o != NULL){
		p = Pet;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		cout << "主人编号：" << o->mnum << endl;
		cout << "主人名字：" << o->mname << endl;
		cout << "联系方式：" << o->phone << endl;
		cout << "寄养宠物个数：" << o->sum << endl;
		cout << "总花费:" << o->expense << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
		cout << "拥有宠物："<<endl;
		while(p!=NULL){
			if(strcmp(p->owner, o->mnum)==0){
				cout << "     宠物名字：" << p->pname << endl;
				cout << "     品种：" << p->type << endl << endl;
			}
			p=p->next;
		}
		cout << endl;
		o = o->next; 
	}
	system("pause");
}

int main()
{
	Master = CreateHostList();
	Pet = CreatePetList();
	
	int choice = -1;
	while(1)
	{
		system("cls");	
		MainMenu();
		cin >> choice;
		if( choice == 1 )
		{
			PetMenu();
			cin >> choice;
			switch(choice)
			{
				case 1:
					Search();
					break;
				case 2:
					Del();
					break;
				case 3:
					Change();
					break;
				case 4:
					Add();
					break;
				case 0:
					continue;
				
			}
		}
		else if( choice == 2 )
		{
			MasterMenu();
			cin >> choice;
			switch(choice)
			{
				case 1:
					Search2();
					break;
				case 2:
					Sort();
					break;
				case 0:
					continue;
			}
		}
		else{
			break;
		}
	}
	return 0;
}


