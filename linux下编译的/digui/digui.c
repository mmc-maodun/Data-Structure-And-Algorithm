/**********************************
数据结构与算法分析第八页1.3题源代码
用递归方法打印出输入的任意整数
**********************************/

#include<stdio.h>
#include<math.h>
void printDigit(int);
void printOut(long);
void printPositive(unsigned long);
int main(void)
{
	int a;
	printf("Input a num(q to exit):");
	while(scanf("%d",&a)==1)
	{
	   printf("Output:");
	   printOut(a);
	   printf("\nInpout another num(q to exit):");
	}
	printf("Byebye!\n");
	return 0;
}


//该函数用于输出任意整数的值
void printOut(long N)
{
	if(N>0)
	   printPositive(N);
	else if(N<0)
	{
	   printf("-");
	   printPositive(abs(N)); 
	}	
	else
	   printDigit(N);
}


//该函数用于输出正整数的值
void printPositive(unsigned long N)
{
	if(N>10||N==10)
	   printPositive(N/10);
	printDigit(N%10);
}


//该函数负责输出小于10的非负整数值
void printDigit(int N)
{
	printf("%d",N);
}
