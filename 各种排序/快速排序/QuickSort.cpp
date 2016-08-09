/*******************************
		   快速排序
Author:兰亭风雨 Date:2014-02-28
Email:zyb_maodun@163.com
********************************/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void Quick_Sort(int *,int,int);
int findPoss(int *,int,int);
int Patrition(int *,int,int);
int Random_Partition(int *,int,int);
void swap(int *,int *);

int main()
{
	int num; 
	printf("请输入排序的元素的个数：");
	scanf("%d",&num);

	int i;
	int *arr = (int *)malloc(num*sizeof(int));
	printf("请依次输入这%d个元素（必须为整数）：",num);
	for(i=0;i<num;i++)
		scanf("%d",arr+i);

	printf("快速排序后的顺序：");
	Quick_Sort(arr,0,num-1);
	for(i=0;i<num;i++)
		printf("%d ",arr[i]);
	printf("\n");

	free(arr);
	arr = 0;
	return 0;
}

/*
快速排序函数，通过递归实现
*/
void Quick_Sort(int *a,int low,int high)
{
	int pos;

	if(low < high)
	{
	   pos = Random_Partition(a,low,high);
	   Quick_Sort(a,low,pos-1);		//左边子序列排序
	   Quick_Sort(a,pos+1,high);	//右边子序列排序 
	}
}

/*
该函数返回分割点数值所在的位置,a为待排序数组的首地址，
low刚开始表示排序范围内的第一个元素的位置，逐渐向右移动，
high刚开始表示排序范围内的最后一个位置，逐渐向左移动
*/
int findPoss(int *a,int low,int high)
{
	if(a==NULL || low>high)
		return -1;

	int val = a[low];
	while(low < high)
	{
	   while(low<high && a[high]>=val)
	      high--;
	   a[low] = a[high];

	   while(low<high && a[low]<=val)
	      low++;
	   a[high] = a[low];	     
	}

	//最终low=high
	a[low] = val;
	return low;
}

/*
算法导论版快速排序
*/
int Partition(int *a,int low ,int high)
{
	if(a==NULL || low>high)
		return -1;

	int small = low-1;
	int j;
	for(j=low;j<high;j++)
	{
		if(a[j]<a[high])
		{
			small++;
			if(small != j)
				swap(&a[small],&a[j]);
		}
	}
	small++;
	swap(&a[small],&a[high]);
	return small;
}

/*
随机选取枢轴元素
*/
int Random_Partition(int *A,int low,int high)
{
	//设置随机种子
	srand((unsigned)time(0));
	int index = low + rand()%(high-low+1);
	swap(&A[index],&A[high]);
	return Partition(A,low,high);
}


void swap(int *a,int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}