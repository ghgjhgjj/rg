#include<iostream> 
#include<cstdio>
#include<map>
#include<cstring>
#include<queue> 
#include <fstream>
#include <io.h>
#include <stdlib.h>
using namespace std;
map<string, int> countword;// 统计单词出现的次数
vector<string> word;//统计单词是否出现 

struct cmp{//优先队列重载，先按次数排序，再按字典顺序 
	string words;
	int count;
	friend bool operator <(cmp a,cmp b){
		if(a.count == b.count) return a.words.compare(b.words) > 0;//字典比较 
		return a.count < b.count;//次数比较 
	}
}; 

long ans = 0;
priority_queue<cmp> que;

void addWords(string s){ // 处理单词
	//cout<<s<<endl;
	for(int i = 0; i < s.size(); i++){// 将单词大写统一变成小写
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


void countChar(string s){//统计单词出现的次数 
	string a; 
	for(int i = 0;i < s.size();i++){
		if(!((s[i] >= '0'&&s[i] <= '9')||(s[i] >= 'a'&&s[i] <= 'z')||(s[i] >= 'A'&&s[i] <= 'Z'))) {
			if(isWord(a)){
				//cout<<a<<endl;
				addWords(a);
			}
			  
			a.clear();//用完之后，清空a,方便下一次统计 
		} 
		else a.push_back(s[i]); //在字符串之后插入一个字符。
	}
	
	if(a.size()) addWords(a);//末尾单词处理 
	
	
}

void wordF(){ // 将单词加入优先队列中，自动排序
	for(int i = 0; i <word.size(); i++){
		que.push({word[i], countword[word[i]]});
	}
}

void printF(){ // 输出单词
	cout << "序号" << "\t" << "出现次数" << '\t' << "单词" << endl;
	int i = 0;
	while(!que.empty() ){
		cmp p = que.top(); 
		que.pop();
		cout << ++i << "\t" << p.count << '\t'<< p.words << endl;
	}
}

void solve_f(int op, char *args[]){ // 对-f命令行参数进行处理
	string s;
	ifstream inf;
	inf.open(args[op]);
	 
	while(getline(inf, s)) {// 单行读入进行操作
		//cout<<s<<endl; 
		countChar(s); 
	}
	inf.close();
} 


bool judge_f_command(int ps, char *args[]){//判断是否是-f指令
	return !strcmp(args[ps], "-f"); //比较是否相等 
} 


int main(int op, char *args[]){//op:输入的参数个数，args:输入参数的字符串数组 
	printf("%d", op); 
	//freopen("NO_Again.txt", "w", stdout);//将所有不重复的单词的结果打印出来
	int ps = 1;//args位置 
	if(ps + 1 < op && judge_f_command(ps, args)) {//处理-f命令 
		solve_f(ps + 1, args);
		wordF();// 将单词加入优先队列中，自动排序
		printF();//输出单词 
	}
	else cout << "输入格式有误！"<<endl;

	return 0;
}
