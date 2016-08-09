/*******************************
		  折半插入排序
Author:兰亭风雨 Date:2014-02-25
Email:zyb_maodun@163.com
********************************/
#include<stdio.h>
#include<stdlib.h>
/*
插入排序后的顺序为从小到大
*/
void BInsert_Sort(int *arr,int len)
{
	int i;
	//从第1个元素开始循环执行插入排序
	for(i=1;i<len;i++)	
	{	
		int low =0;
		int high = i-1;
		int key = arr[i];
		//循环至要插入的两个点之间
		while(low<=high)
		{
			int mid = (low+high)/2;	
			if(key<arr[mid])
				high = mid-1;
			else
				low = mid+1;
		}
		//循环结束后low=high+1，并且low位置即为key要插入的位置

		//从low到i的元素依次后移一位
		int j;
		for(j=i;j>low;j--)
			arr[j] = arr[j-1];
		//将key插入到low位置处
		arr[low] = key;
	}
}

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

	printf("插入排序后的顺序：");
	BInsert_Sort(arr,num);
	for(i=0;i<num;i++)
		printf("%d ",arr[i]);
	printf("\n");
	return 0;
}