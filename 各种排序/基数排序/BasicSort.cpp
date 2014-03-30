/*******************************
		  基数排序
Author:兰亭风雨 Date:2014-03-03
Email:zyb_maodun@163.com
********************************/
#include<stdio.h>
#include<stdlib.h>

/*
在第一种计数排序的实现形式上做了些修改
计数排序后的顺序为从小到大
arr[0...len-1]为待排数组，我们这里采用三位数
brr[0...len-1]为排序后的有序数组
w[0...len-1]用来保存取出的每一位上的数，其每个元素均是0-k中的一个值
crr[0...k]保存0...k中每个值出现的次数
*/
void Count_Sort(int *arr,int *brr,int *w,int *crr,int len,int k)
{
	int i;
	//数组crr各元素置0
	for(i=0;i<=k;i++)
		crr[i] = 0;
	//统计数组w中每个元素重复出现的个数
	for(i=0;i<len;i++)
		crr[w[i]]++;
	//求数组w中小于等于i的元素个数
	for(i=1;i<=k;i++)
		crr[i] += crr[i-1];
	//把arr中的元素放在brr中对应的位置上
	for(i=len-1;i>=0;i--)
	{
		brr[crr[w[i]]-1] = arr[i];
		//如果有相同的元素，则放在下一个位置上
		crr[w[i]]--;
	}
	//再将brr中的元素复制给arr，这样arr就有序了
	for(i=0;i<len;i++)
	{
		arr[i] = brr[i];
	}
}

/*
基数排序后的顺序为从小到大
其中参数d为元素的位数
*/
void Basic_Sort(int *arr,int *brr,int *w,int *crr,int len,int k,int d)
{
	int i,j,val=1;
	//从低位到高位依次进行计数排序
	for(i=1;i<=d;i++)
	{	//w中保存的是arr中每个元素对应位上的数
		//范围在0-k之间
		for(j=0;j<len;j++)
			w[j] = (arr[j]/val)%10;	
		//对当前位进行计数排序
		Count_Sort(arr,brr,w,crr,len,k);
		val *= 10;
	}
}

int main()
{
	int i; 
	//待排序数组，每个元素的每一位均在0-7之间
	int arr[] = {217,125,362,136,733,522};
	int brr[6];	//用来保存每次计数排序后的结果
	int w[6];	//每次循环时，保存该位上的数
	int crr[8];	//每次循环时，保存该位上的数出现的次数
	Basic_Sort(arr,brr,w,crr,6,7,3);
	printf("基数排序后的结果为：");
	for(i=0;i<6;i++)
		printf("%d ",arr[i]);
	printf("\n");
	return 0;
}


