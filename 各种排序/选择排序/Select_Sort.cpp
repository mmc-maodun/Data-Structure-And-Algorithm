/*******************************
		   选择排序
Author:兰亭风雨 Date:2014-02-26
Email:zyb_maodun@163.com
********************************/
#include<stdio.h>
#include<stdlib.h>
/*
第一种形式的选择排序
选择排序后的顺序为从小到大
*/
void Select_Sort1(int *arr,int len)
{
	int i,j;
	for(i=0;i<len;i++)
		for(j=i+1;j<len;j++)
			if(arr[i] > arr[j])
			{
				int exchange = arr[i];
				arr[i] = arr[j];
				arr[j] = exchange;
			}
}

/*
第二种形式的选择排序，减少了元素互换的操作
选择排序后的顺序为从小到大
*/
void Select_Sort2(int *arr,int len)
{
	int i,j,min;
	for(i=0;i<len;i++)
	{
		min = i;	//用来记录每一趟比较的最小值的位置
		for(j=i+1;j<len;j++)
			if(arr[min] > arr[j])
				min = j;	 //仅记录最小值的位置
		//如果最小值的位置发生了变化，
		//则最后执行一次元素互换的操作
		if(min != i)
		{
			int exchange = arr[i];
			arr[i] = arr[min];
			arr[min] = exchange;
		}
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
	Select_Sort2(arr,num);
	for(i=0;i<num;i++)
		printf("%d ",arr[i]);
	printf("\n");

	free(arr);
	arr = 0;
	return 0;
}