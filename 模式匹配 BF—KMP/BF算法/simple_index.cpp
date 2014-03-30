#include<iostream>
#include<string>
using namespace std;
int index(const string &,const string &,int);

int main()
{
	char ch;
	do{
		string Tag,Ptn;  
		int pos;
		cout<<"输入主串：";
		cin>>Tag;
		cout<<"输入子串：";
		cin>>Ptn;
		cout<<"输入主串中开始进行匹配的位置（首字符位置为0）：";
		cin>>pos;

		int result = index(Tag,Ptn,pos);
		if(result != -1)
			cout<<"主串与子串在主串的第"<<result<<"个字符（首字符的位置为0）处首次匹配"<<endl;
		else
			cout<<"无匹配子串"<<endl;

		cout<<"是否继续测试（输入y或Y继续，任意其他键结束）：";
		cin>>ch;
	}while(ch == 'y' || ch == 'Y');
	return 0;
}

/*
返回子串Ptn在主串Tag的第pos个字符后(含第pos个位置)第一次出现的位置，若不存在，则返回-1
采用BF算法，这里的位置全部以从0开始计算为准，其中T非空，0<=pos<=Tlen
*/
int index(const string &Tag,const string &Ptn,int pos)
{
	int i = pos;  //主串当前正待比较的位置，初始为pos
	int j = 0;   //子串当前正待比较的位置，初始为0
	int Tlen = Tag.size();  //主串长度
	int Plen = Ptn.size();  //子串长度
	
	while(i<Tlen && j<Plen)
	{
		if(Tag[i] == Ptn[j])   //如果当前字符相同，则继续向下比较
		{   
			i++;
			j++;
		}
		else   //如果当前字符不同，则i和j回退，重新进行匹配
		{   
			//用now_pos表示每次重新进行匹配时开始比较的位置，则
			//i=now_pos+后移量，j=0+后移量
			//则i-j+1=now_pos+1,即为Tag中下一轮开始比较的位置
			i = i-j+1;
			//Ptn退回到子串开始处
			j = 0;
		}
	}

	if(j >= Plen)
		return i - Plen;
	else
		return -1;
}