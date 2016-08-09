/*******************************
		   shell排序
Author:兰亭风雨 Date:2014-02-25
Email:zyb_maodun@163.com
********************************/
#include<stdio.h>
#include<stdlib.h>

/*
第一种形式的代码
对长为len的数组进行一趟增量为ader的插入排序
本算法在插入排序算法的第一种实现形式上进行修改得到
*/
void Shell_Insert1(int *arr,int len,int ader)
{
	int i,k;
	//循环对ader个子序列进行插入排序操作
	for(k=0;k<ader;k++)
		for(i=ader+k;i<len;i+=ader)		//对一个子序列进行插入排序操作
		{	//将第i个元素分别与前面的每隔ader个位置的元素比较，插入适当的位置
			if(arr[i]<arr[i-ader])
			{	//一直向左进行比较，直到插入到适当的位置
				int key = arr[i];
				int count = 0;	//用来记录key在与前面元素比较时向左移动了几个ader长度
				while(i>k && key<arr[i-ader])
				{
					arr[i] = arr[i-ader];
					arr[i-ader] = key;
					i -= ader;
					count++;
				}
				//将待插入的数定位到下一个元素，执行下一次插入排序
				//因为后面还要执行i+=ader，所以这里回到原位置即可
				i += count*ader;  
			} 
		}
}

/*
第二种形式的代码
对长为len的数组进行一趟增量为ader的插入排序
本算法在插入排序算法的第二种实现形式上进行修改得到
*/
void Shell_Insert2(int *arr,int len,int ader)
{
	int i,j,k;
	//循环对ader个子序列各自进行插入排序
	for(k=0;k<ader;k++)
		for(i=ader+k;i<len;i+=ader)
			if(arr[i] < arr[i-ader])
			{
				int key = arr[i];
				for(j=i-ader;j>=k && arr[j]>key;j-=ader)
					arr[j+ader] = arr[j];
				arr[j+ader] = key;
			}
}

/*
在第二种代码的形式上继续精简代码
交叉进行各个子序列的插入排序
*/
void Shell_Insert2_1(int *arr,int len,int ader)
{
	int i,j;
	//对ader子序列交叉进行插入排序
	for(i=ader;i<len;i++)
		if(arr[i] < arr[i-ader])
		{
			int key = arr[i];
			for(j=i-ader;j>=0 && arr[j]>key;j-=ader)
				arr[j+ader] = arr[j];
			arr[j+ader] = key;
		}
}

/*
第三种形式的代码
对长为len的数组进行一趟增量为ader的插入排序
本算法在插入排序算法的第三种实现形式上进行修改得到
*/
void Shell_Insert3(int *arr,int len,int ader)
{
	int i,j,k;
	//循环对ader个子序列各自进行插入排序
	for(k=0;k<ader;k++)
		for(i=ader+k;i<len;i+=ader)
			for(j=i-ader;j>=k && arr[j]>arr[j+ader];j-=ader)
			{
				//交换元素数值
				arr[j]^=arr[j+ader];
				arr[j+ader]^=arr[j];
				arr[j]^=arr[j+ader];
			}
}

/*
在第三种代码的形式上继续精简代码
交叉进行各个子序列的插入排序
*/
void Shell_Insert3_1(int *arr,int len,int ader)
{
	int i,j;
	//交叉对ader个子序列进行插入排序
		for(i=ader;i<len;i++)
			for(j=i-ader;j>=0 && arr[j]>arr[j+ader];j-=ader)
			{
				//交换元素数值
				//由于arr[j]不等于arr[j+1]，
				//因此可以安全地用该交换方法
				arr[j]^=arr[j+ader];
				arr[j+ader]^=arr[j];
				arr[j]^=arr[j+ader];
			}
}

/*
shell排序后的顺序为从小到大,
arr为要排序的数组，长为len，
add为增量数组，长为num
*/
void Shell_Sort(int *arr,int len,int *add,int num)
{
	int i;
	//共进行nun趟不同增量的插入排序
	for(i=0;i<num;i++)
		Shell_Insert2_1(arr, len,add[i]);	//一趟增量为add[i]的插入排序
}
 
int main()
{
	int len;
	printf("请输入排序的元素的个数：");
	scanf("%d",&len);

	int i;
	int add[] = {3,2,1};  //增量数组
	int *arr = (int *)malloc(len*sizeof(int));
	printf("请依次输入这%d个元素（必须为整数）：",len);
	for(i=0;i<len;i++)
		scanf("%d",arr+i);

	printf("shell排序后的顺序：");
	Shell_Sort(arr,len,add,3);
	for(i=0;i<len;i++)
		printf("%d ",arr[i]);
	printf("\n");

	free(arr);
	arr = 0;
	return 0;
}