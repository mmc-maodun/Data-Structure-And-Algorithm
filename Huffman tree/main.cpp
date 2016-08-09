#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"data_structure.h"

int main()
{
	int n;   //需要编码的字符的个数
	printf("请输入需要编码的字符的个数（>1）：");
	scanf("%d",&n);
    while(n<=1)
	{
		printf("字符个数必须大于1，请重新输入：");
		scanf("%d",&n);
	}

	int i;
	int *wet = (int *)malloc(n*sizeof(int));  //存放每个字符的权值
	printf("请依次输入这%d个字符的权值（整型）：",n);
	for(i=0;i<n;i++)
	{
		scanf("%d",wet+i);
	}

	HuffmanCode HC;  //保存赫夫曼编码
	HuffmanTree HT = create_HuffmanTree(wet,n);  //生成赫夫曼树
	HuffmanCoding(HT,HC,n);        //第一种方法求每个字符的赫夫曼编码	
//	HuffmanCoding2(HT,HC,n);        //第二种方法求每个字符的赫夫曼编码

	for(i=0;i<n;i++)
	{
		puts(HC[i]);
	}
	free(wet);

	return 0;
}