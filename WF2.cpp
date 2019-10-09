/*支持 stop words
我们从第一步的结果看出，在一本小说里， 频率出现最高的单词一般都是 "a",  "it", "the", "and", "this", 这些词， 我们并不感兴趣. 
 我们可以做一个 stop word 文件 （停词表）， 在统计词汇的时候，跳过这些词。  我们把这个文件叫 "stopwords.txt" file. 
*/
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
map<string, int> countword;// 统计单词出现的次数
vector<string> word;//统计单词是否出现 
vector<string> files;//记录目录下的文件名 
map<string, int> stopword;//停词表 

struct cmp{//优先队列重载，先按次数排序，再按字典顺序 
	string words;
	int count;
	friend bool operator <(cmp a,cmp b){
		if(a.count == b.count)
			return a.words.compare(b.words) > 0;//字典比较 
		return a.count < b.count;//次数比较 
	}
}; 

priority_queue<cmp> que;

void getFiles(string path, vector<string>& files){ // 遍历文件夹中文件名
    long hFile = 0;// 文件句柄
    struct _finddata_t fileinfo;// 文件信息
    string p;
    if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1) {
        do {
            files.push_back(p.assign(path).append("\\").append(fileinfo.name));// 保存文件的全路径
           } while (_findnext(hFile, &fileinfo) == 0);  //寻找下一个，成功返回0，否则-1
        _findclose(hFile);
    }
}

void getChildFiles(string path, vector<string>& files){ // 递归遍历子文件夹 获取文件名
    long hFile = 0;//文件句柄
    struct _finddata_t fileinfo;//文件信息
    string p;
    if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1) {
        do {
            if ((fileinfo.attrib & _A_SUBDIR)) {  //比较文件类型是否是文件夹
                if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0) {
                    files.push_back(p.assign(path).append("\\").append(fileinfo.name));
                    getChildFiles(p.assign(path).append("\\").append(fileinfo.name), files);//递归搜索
                }
            }
            else {
                files.push_back(p.assign(path).append("\\").append(fileinfo.name));
            }
        } while (_findnext(hFile, &fileinfo) == 0);  //寻找下一个，成功返回0，否则-1
        _findclose(hFile);
    }
}

void addWords(string s, int flag){ // 处理单词
	//cout<<s<<endl;
	for(int i = 0; i < s.size(); i++){// 将单词大写统一变成小写
		if(s[i] >= 'A' && s[i] <= 'Z'){
			s[i] += 'a'- 'A';
		}
	}
	
	if(flag == 1)countword[s]++;
	else stopword[s]++; 
}

bool isWord(string s){	
	if(!((s[0] >= 'a' && s[0] <= 'z') || (s[0] >= 'A' && s[0] <= 'Z'))) return false;
	for(int i = 1; i < s.size(); i++){
		if(!((s[i]>='0'&&s[i]<='9')||(s[i]>='a'&&s[i]<='z')||(s[i]>='A'&&s[i]<='Z'))) return false;
	}
	return true;
}


void countChar(string s, int flag){//统计单词出现的次数 
	string a; 
	for(int i = 0;i < s.size();i++){
		if(!((s[i] >= '0'&&s[i] <= '9')||(s[i] >= 'a'&&s[i] <= 'z')||(s[i] >= 'A'&&s[i] <= 'Z'))) {
			if(isWord(a)){
				//cout<<a<<endl;
				addWords(a, flag);
			}
			  
			a.clear();//用完之后，清空a,方便下一次统计 
		} 
		else a.push_back(s[i]); //在字符串之后插入一个字符。
	}
	
	if(a.size()) addWords(a, flag);//末尾单词处理 
	
	
}

void wordF(){ // 将单词加入优先队列中，自动排序
	for(auto i = countword.begin(); i != countword.end(); i++){
		if(stopword.find(i->first) == stopword.end())
			que.push({i->first, i->second});
	}

	//if(countword.find(s) == countword.end()){
	//	countword[s] = 1;
	//	word.push_back(s);
	//}
}

int outWords(int op, char *args[]){ // 处理是否输出限定单词数
	//cout<<op<<endl;
	if(!strcmp(args[op], "-n")) return atoi(args[op + 1]);//字符串转换成整型数 
	return que.size(); // 不存在，返回默认所有的单词数
}

void printF(int n){ // 输出单词
	//cout<<n<<endl;
	cout << "序号" << "\t" << "出现次数" << '\t' << "单词" << endl;
	int i = 0;
	while(!que.empty() && i < n){
		cmp p = que.top(); 
		que.pop();
		cout << ++i << "\t" << p.count << '\t'<< p.words << endl;
	}
}

void solve_x(int op,char *args[]){//对-x命令行参数进行处理 
	string s;
	ifstream inf;
//	cout<<op<<endl;
	inf.open(args[op]);
	while(getline(inf, s)){
		//cout<<s<<endl;
		countChar(s, 0);
	} 
	inf.close(); 
} 

void solve_f(int op, char *args[]){ // 对-f命令行参数进行处理
	string s;
	ifstream inf;
	inf.open(args[op]);
	//cout<<op<<endl; 
	while(getline(inf, s)) {// 单行读入进行操作
		//cout<<s<<endl; 
		countChar(s, 1); 
	}
	inf.close();
} 

void solve_d(int op, char *args[]){//对于-d命令参数进行处理 
	getFiles(args[op], files);
	int size = files.size();	
	for(int i = 0;i < size;i++){
		string s;
		ifstream inf;
		inf.open(files[i]);
		while(getline(inf, s)) countChar(s, 1);
		inf.close();
	}	
} 

void solve_d_s(int op, char *args[]){//对于-d-s命令参数进行处理 
	getChildFiles(args[op], files);
	int size = files.size();
	for(int i = 0;i < size;i++){
		string s;
		ifstream inf;
		inf.open(files[i]);
		while(getline(inf, s)) countChar(s, 1);
		inf.close(); 
	} 
} 

bool judge_x_command(int op, char *args[]){//判断是否是-x指令
	return !strcmp(args[op], "-x");//比较是否相等 
} 

bool judge_f_command(int op, char *args[]){//判断是否是-f指令
	return !strcmp(args[op], "-f"); //比较是否相等 
} 

bool judge_d_command(int op, char *args[]){//判断是否是-d指令 
	return !strcmp(args[op], "-d");//比较是否相等 
} 

bool judge_d_s_command(int op, char *args[]){//判断是否是-d-s指令 
	return !(strcmp(args[op], "-d") ||  strcmp(args[op + 1], "-s"));//比较是否相等 
}

int main(int op, char *args[]){//op:输入的参数个数，args:输入参数的字符串数组 
	//cout<<op<<endl;
	int ps = 1;
	
	if(ps + 1 < op && judge_x_command(ps, args)){//处理-x命令 
		cout<<"123"<<endl;
		solve_x(ps + 1,args); 
		ps += 2;
	}
	if(ps + 1 < op && judge_f_command(ps, args)) {//处理-f命令 
		solve_f(ps + 1, args);
		wordF();// 将单词加入优先队列中，自动排序
		int outWord = que.size();
		if(ps + 3 < op) outWord = outWords(op - 2, args);
		printF(outWord);//输出单词 
	} 
	else if(ps + 1 <= op && judge_d_s_command(ps, args)){//处理-d-s命令 
		solve_d_s(ps + 2, args);
	//	cout<<ps<<endl;
		wordF();// 将单词加入优先队列中，自动排序
		int outWord = que.size();
		if(ps + 4 < op) outWord = outWords(op - 2, args);
		printF(outWord);//输出单词 
	}
	else if(ps + 2 <= op && judge_d_command(ps, args)){//处理-d命令 
		solve_d(ps + 1, args); 
		wordF();// 将单词加入优先队列中，自动排序
		int outWord = que.size();
		if(ps + 3 < op) outWord = outWords(op - 2, args);
		printF(outWord);//输出单词 
	}

	else cout << "输入格式有误！"<<endl;

	
	return 0;
}
