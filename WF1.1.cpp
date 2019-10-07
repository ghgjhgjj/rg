#include<iostream> 
#include<cstdio>
#include<map>
#include<cstring>
#include<queue> 
#include <fstream>
#include <io.h>
#include <stdlib.h>
using namespace std;
map<string, int> countword;// ͳ�Ƶ��ʳ��ֵĴ���
vector<string> word;//ͳ�Ƶ����Ƿ���� 

struct cmp{//���ȶ������أ��Ȱ����������ٰ��ֵ�˳�� 
	string words;
	int count;
	friend bool operator <(cmp a,cmp b){
		if(a.count == b.count) return a.words.compare(b.words) > 0;//�ֵ�Ƚ� 
		return a.count < b.count;//�����Ƚ� 
	}
}; 

long ans = 0;
priority_queue<cmp> que;

void addWords(string s){ // ������
	//cout<<s<<endl;
	for(int i = 0; i < s.size(); i++){// �����ʴ�дͳһ���Сд
		if(s[i] >= 'A' && s[i] <= 'Z'){
			s[i] += 'a'- 'A';
		}
	}
	
//	auto t = ;
	if(countword.find(s) == countword.end()){
		countword[s] = 1;
		word.push_back(s);
	}
	else countword[s]++;
}

bool isWord(string s){	
	if(!((s[0] >= 'a' && s[0] <= 'z') || (s[0] >= 'A' && s[0] <= 'Z'))) return false;
	for(int i = 1; i < s.size(); i++){
		if(!((s[i]>='0'&&s[i]<='9')||(s[i]>='a'&&s[i]<='z')||(s[i]>='A'&&s[i]<='Z'))) return false;
	}
	return true;
}


void countChar(string s){//ͳ�Ƶ��ʳ��ֵĴ��� 
	string a; 
	for(int i = 0;i < s.size();i++){
		if(!((s[i] >= '0'&&s[i] <= '9')||(s[i] >= 'a'&&s[i] <= 'z')||(s[i] >= 'A'&&s[i] <= 'Z'))) {
			if(isWord(a)){
				//cout<<a<<endl;
				addWords(a);
			}
			  
			a.clear();//����֮�����a,������һ��ͳ�� 
		} 
		else a.push_back(s[i]); //���ַ���֮�����һ���ַ���
	}
	
	if(a.size()) addWords(a);//ĩβ���ʴ��� 
	
	
}

void wordF(){ // �����ʼ������ȶ����У��Զ�����
	for(int i = 0; i <word.size(); i++){
		que.push({word[i], countword[word[i]]});
	}
}

void printF(){ // �������
	cout << "���" << "\t" << "���ִ���" << '\t' << "����" << endl;
	int i = 0;
	while(!que.empty() ){
		cmp p = que.top(); 
		que.pop();
		cout << ++i << "\t" << p.count << '\t'<< p.words << endl;
	}
}

void solve_f(int op, char *args[]){ // ��-f�����в������д���
	string s;
	ifstream inf;
	inf.open(args[op]);
	 
	while(getline(inf, s)) {// ���ж�����в���
		//cout<<s<<endl; 
		countChar(s); 
	}
	inf.close();
} 


bool judge_f_command(int ps, char *args[]){//�ж��Ƿ���-fָ��
	return !strcmp(args[ps], "-f"); //�Ƚ��Ƿ���� 
} 


int main(int op, char *args[]){//op:����Ĳ���������args:����������ַ������� 
	printf("%d", op); 
	//freopen("NO_Again.txt", "w", stdout);//�����в��ظ��ĵ��ʵĽ����ӡ����
	int ps = 1;//argsλ�� 
	if(ps + 1 < op && judge_f_command(ps, args)) {//����-f���� 
		solve_f(ps + 1, args);
		wordF();// �����ʼ������ȶ����У��Զ�����
		printF();//������� 
	}
	else cout << "�����ʽ����"<<endl;

	return 0;
}
