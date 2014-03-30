/**********************
快速排序算法，以升序为例
**********************/

#include<stdio.h>

void quickSort(int *,int,int);
int findPoss(int *,int,int);

int main()
{
	int i;
	int arry[] = {8,9,0,-3,6,7,-11};

	quickSort(arry,0,6);

	printf("After sorted:\n");
	for(i=0;i<7;i++)
	   printf("%d ",arry[i]);
	printf("\n");
	return 0;
}

/*
快速排序函数，通过递归实现
*/
void quickSort(int *a,int low,int high)
{
	int pos;

	if(low < high)
	{
	   pos = findPoss(a,low,high);
	   quickSort(a,low,pos-1);
	   quickSort(a,pos+1,high); 
	}
	return ;
}

/*
该函数返回分割点数值所在的位置,a为待排序数组的首地址，
low刚开始表示排序范围内的第一个元素的位置，逐渐向右移动，
high刚开始表示排序范围内的最后一个位置，逐渐向左移动
*/
int findPoss(int *a,int low,int high)
{
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

	//此时low=high
	a[low] = val;
	return low;
}
