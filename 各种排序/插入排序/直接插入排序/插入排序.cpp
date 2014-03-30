/*******************************
		  直接插入排序
Author:兰亭风雨 Date:2014-02-25
Email:zyb_maodun@163.com
********************************/
#include<stdio.h>
#include<stdlib.h>
/*
第一种代码形式
插入排序后的顺序为从小到大
*/
void Insert_Sort1(int *arr,int len)
{
	int i;
	//从第1个元素开始循环执行插入排序
	for(i=1;i<len;i++)	
	{	//将第i个元素分别与前面的元素比较，插入适当的位置
		int key = arr[i];
		if(key<arr[i-1])
		{	//一直向左进行比较，直到插入到适当的位置
			int count = 0;	//用来记录key在与前面元素时向左移动的位置
			while(i>0 && key<arr[i-1])
			{
				arr[i] = arr[i-1];
				arr[i-1] = key;
				i--;
				count++;
			}
			//将待插入的数定位到下一个元素，
			//因为后面还要执行i++，所以这里不再加1
			i += count;  
		} 
	}
}

/*
第二种代码形式
插入排序后的顺序为从小到大
*/
void Insert_Sort2(int *arr,int len)
{
	int i,j;
	for(i=1;i<len;i++)
		if(arr[i] < arr[i-1])
		{	//向前逐个比较，直到需要插入的地方
			int key = arr[i];
			for(j=i-1;j>=0 && arr[j]>key;j--)
				arr[j+1] = arr[j];
			arr[j+1] = key;	   //插入key
		}
}

/*
第三种代码形式
插入排序后的顺序为从小到大
*/
void Insert_Sort3(int *arr,int len)
{
	int i,j;
	for(i=1;i<len;i++)
		for(j=i-1;j>=0 && arr[j]>arr[j+1];j--)
		{
			//交换元素数值
			//由于arr[j]不等于arr[j+1]，
			//因此可以安全地用该交换方法
			arr[j]^=arr[j+1];
			arr[j+1]^=arr[j];
			arr[j]^=arr[j+1];
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
//	Insert_Sort1(arr,num);
//	Insert_Sort2(arr,num);
	Insert_Sort3(arr,num);
	for(i=0;i<num;i++)
		printf("%d ",arr[i]);
	printf("\n");

	free(arr);
	arr = 0;
	return 0;
}