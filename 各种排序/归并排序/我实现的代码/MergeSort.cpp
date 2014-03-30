/*******************************
		    归并排序
Author:兰亭风雨 Date:2014-02-26
Email:zyb_maodun@163.com
********************************/
#include<stdio.h>
#include<stdlib.h>

/*
将有序的arr[start...mid]和有序的arr[mid+1...end]归并为有序的arr[start...end]
*/
void Merge(int *arr,int start,int mid,int end)
{
	int i = start;
	int j = mid+1;
	int k = 0;
	//brr为辅助数组，
	int *brr = (int *)malloc((end-start+1)*sizeof(int));

	//比较两个有序序列中的元素，将较小的元素插入到brr中
	while(i<=mid && j<=end)
	{	
		if(arr[i]<=arr[j])
			brr[k++] = arr[i++];
		else
			brr[k++] = arr[j++];
	}

	//将arr序列中剩余的元素复制到brr中
	//这两个语句只可能执行其中一个
	while(i<=mid)
		brr[k++] = arr[i++];
	while(j<=end)
		brr[k++] = arr[j++];

	//将brr中的元素复制到arr中，使arr[start...end]有序
	for(i=0;i<k;i++)
		arr[i+start] = brr[i];

	//释放brr所占的内存，并将其置为空
	free(brr);    
	brr = 0;
}

/*
对arr[start...end]内的元素进行归并排序
归并排序后的顺序为从小到大
*/
void MSort(int *arr,int start,int end)
{
	if(start < end)
	{
		int mid = (start+end)/2;
		MSort(arr,start,mid);		//左边递归排序
		MSort(arr,mid+1,end);		//右边递归排序
		Merge(arr,start,mid,end);	//左右序列归并
	}
}
/*
将该排序算法封装起来
*/
void Merge_Sort(int *arr,int len)
{
	MSort(arr,0,len-1);
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

	printf("归并排序后的顺序：");
	Merge_Sort(arr,num);
	for(i=0;i<num;i++)
		printf("%d ",arr[i]);
	printf("\n");

	free(arr);
	arr = 0;
	return 0;
}