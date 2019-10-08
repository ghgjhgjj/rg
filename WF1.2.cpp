/*����2��wf.exe -d <directory>  ָ���ļ�Ŀ¼����Ŀ¼��ÿһ���ļ�ִ��  wf.exe -f <file> �Ĳ����� 
wf.exe -d -s  <directory>  ͬ�ϣ� ���ǻ�ݹ����Ŀ¼�µ�������Ŀ¼��*/
#include<iostream> 
#include<cstdio>
#include<map>
#include<cstring>
#include<queue> 
#include <fstream>
#include <io.h>
#include <stdlib.h>
#include <vector>

using namespace std;
map<string, int> countword;// ͳ�Ƶ��ʳ��ֵĴ���
vector<string> word;//ͳ�Ƶ����Ƿ���� 
vector<string> files;//��¼Ŀ¼�µ��ļ��� 

struct cmp{//���ȶ������أ��Ȱ����������ٰ��ֵ�˳�� 
	string words;
	int count;
	friend bool operator <(cmp a,cmp b){
		if(a.count == b.count)
			return a.words.compare(b.words) > 0;//�ֵ�Ƚ� 
		return a.count < b.count;//�����Ƚ� 
	}
}; 

priority_queue<cmp> que;

void getFiles(string path, vector<string>& files){ // �����ļ������ļ���
    long hFile = 0;// �ļ����
    struct _finddata_t fileinfo;// �ļ���Ϣ
    string p;
    if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1) {
        do {
            files.push_back(p.assign(path).append("\\").append(fileinfo.name));// �����ļ���ȫ·��
           } while (_findnext(hFile, &fileinfo) == 0);  //Ѱ����һ�����ɹ�����0������-1
        _findclose(hFile);
    }
}

void getChildFiles(string path, vector<string>& files){ // �ݹ�������ļ��� ��ȡ�ļ���
    long hFile = 0;//�ļ����
    struct _finddata_t fileinfo;//�ļ���Ϣ
    string p;
    if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1) {
        do {
            if ((fileinfo.attrib & _A_SUBDIR)) {  //�Ƚ��ļ������Ƿ����ļ���
                if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0) {
                    files.push_back(p.assign(path).append("\\").append(fileinfo.name));
                    getChildFiles(p.assign(path).append("\\").append(fileinfo.name), files);//�ݹ�����
                }
            }
            else {
                files.push_back(p.assign(path).append("\\").append(fileinfo.name));
            }
        } while (_findnext(hFile, &fileinfo) == 0);  //Ѱ����һ�����ɹ�����0������-1
        _findclose(hFile);
    }
}

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

void solve_d(int op, char *args[]){//����-d����������д��� 
	getFiles(args[op], files);
	int size = files.size();	
	for(int i = 0;i < size;i++){
		string s;
		ifstream inf;
		inf.open(files[i]);
		while(getline(inf, s)) countChar(s);
		inf.close();
	}	
} 

void solve_d_s(int op, char *args[]){//����-d-s����������д��� 
	getChildFiles(args[op], files);
	int size = files.size();
	for(int i = 0;i < size;i++){
		string s;
		ifstream inf;
		inf.open(files[i]);
		while(getline(inf, s)) countChar(s);
		inf.close(); 
	} 
} 

bool judge_f_command(int op, char *args[]){//�ж��Ƿ���-fָ��
	return !strcmp(args[op], "-f"); //�Ƚ��Ƿ���� 
} 

bool judge_d_command(int op, char *args[]){//�ж��Ƿ���-dָ�� 
	return !strcmp(args[op], "-d");//�Ƚ��Ƿ���� 
} 

bool judge_d_s_command(int op, char *args[]){//�ж��Ƿ���-d-sָ�� 
	return !(strcmp(args[op], "-d") ||  strcmp(args[op + 1], "-s"));//�Ƚ��Ƿ���� 
}

int main(int op, char *args[]){//op:����Ĳ���������args:����������ַ������� 
	printf("%d", op); 
	//freopen("NO_Again.txt", "w", stdout);//�����в��ظ��ĵ��ʵĽ����ӡ����
	//int ps = 1;//argsλ�� 
	if(op == 3 && judge_f_command(op - 2, args)) {//����-f���� 
		solve_f(op - 1, args);
		wordF();// �����ʼ������ȶ����У��Զ�����
		printF();//������� 
	}
	else if(op == 3 && judge_d_command(op - 2, args)){//����-d���� 
		solve_d(op - 1, args); 
		wordF();// �����ʼ������ȶ����У��Զ�����
		printF();//�������	
	}
	else if(op == 4 && judge_d_s_command(op - 3, args)){//����-d-s���� 
		solve_d_s(op - 1, args);
		wordF();// �����ʼ������ȶ����У��Զ�����
		printF();//�������	
	}
	else cout << "�����ʽ����"<<endl;

	return 0;
}
