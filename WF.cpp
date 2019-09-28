#include<stdio.h>
#include<string.h>

struct Character{
	char str;//字母 	
	int num;//个数 
	double f;//频率 
}; 

void count(Character chara[], FILE *fp){//统计次数 
    char letter;
    int ret, i;
    
    while(!feof(fp)){
    	ret = fscanf(fp, "%c", &letter);
        if (ret == EOF) break;
    	
    	if(letter >= 'a' && letter <= 'z') chara[int(letter - 'a')].num++;
		if(letter >= 'A' && letter <= 'Z') chara[int(letter - 'A')].num++;

    }
    
    return ;
}


void frequency(Character chara[]){//求频率 
	int sum = 0, i;
	for(int i = 0;i < 26;i++){
		sum += chara[i].num;
	}
	
	for(int i = 0;i < 26;i++){	
		chara[i].f = double(chara[i].num)/sum;
	}
	
	return ;
} 

void print(Character chara[]){//排序并打印 
		
	int i, j;
	Character temp;	
      // 排序 
    for (i = 0; i < 26; i++) { 
        for (j = 0; j < 26 - i; j++) { 
        	if(chara[j].f < chara[j + 1].f){
            	temp = chara[j]; 
            	chara[j] = chara[j+1]; 
            	chara[j+1] = temp;
				} 
        	} 	
      	} 
  
      // 打印排序结果 
    for (i = 0; i < 26; i++) 
        printf("%c:%.2f%%\n", chara[i].str, chara[i].f*100); 
        
    return ;
}

int main()
{
	char filename[260]; 
    FILE *fp;
    int i;
    gets(filename);
    strcat(filename,".txt");
    if((fp=fopen(filename, "r"))==NULL){
        printf("Cannot open the file!\n");
        return -1;
    }

   	Character chara[] = {{'a',0,0.00}, {'b',0,0.00}, {'c',0,0.00}, {'d',0,0.00}, {'e',0,0.00}, {'f',0,0.00},
	   					 {'g',0,0.00}, {'h',0,0.00}, {'i',0,0.00}, {'j',0,0.00}, {'k',0,0.00}, {'l',0,0.00},
						 {'m',0,0.00}, {'n',0,0.00}, {'o',0,0.00}, {'p',0,0.00}, {'q',0,0.00}, {'r',0,0.00},
	   					 {'s',0,0.00}, {'t',0,0.00}, {'u',0,0.00}, {'v',0,0.00}, {'w',0,0.00}, {'x',0,0.00},
						 {'y',0,0.00}, {'z',0,0.00}};
    count(chara, fp);
    frequency(chara);
    print(chara); 
    fclose(fp);

    return 0;
}

