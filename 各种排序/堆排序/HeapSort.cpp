/*******************************
		    堆排序
Author:兰亭风雨 Date:2014-02-27
Email:zyb_maodun@163.com
********************************/
#include<stdio.h>
#include<stdlib.h>

/*
arr[start+1...end]满足最大堆的定义，
将arr[start]加入到最大堆arr[start+1...end]中，
调整arr[start]的位置，使arr[start...end]也成为最大堆
注：由于数组从0开始计算序号，也就是二叉堆的根节点序号为0，
因此序号为i的左右子节点的序号分别为2i+1和2i+2
*/
void HeapAdjustDown(int *arr,int start,int end)
{
	int temp = arr[start];	//保存当前节点
	int i = 2*start+1;		//该节点的左孩子在数组中的位置序号
	while(i<=end)
	{
		//找出左右孩子中最大的那个
		if(i+1<=end && arr[i+1]>arr[i])  
			i++;
		//如果符合堆的定义，则不用调整位置
		if(arr[i]<=temp)	
			break;
		//最大的子节点向上移动，替换掉其父节点
		arr[start] = arr[i];
		start = i;
		i = 2*start+1;
	}
	arr[start] = temp;
}

/*
堆排序后的顺序为从小到大
因此需要建立最大堆
*/
void Heap_Sort(int *arr,int len)
{
	int i;
	//把数组建成为最大堆
	//第一个非叶子节点的位置序号为len/2-1
	for(i=len/2-1
		;i>=0;i--)
		HeapAdjustDown(arr,i,len-1);
	//进行堆排序
	for(i=len-1;i>0;i--)
	{
		//堆顶元素和最后一个元素交换位置，
		//这样最后的一个位置保存的是最大的数，
		//每次循环依次将次大的数值在放进其前面一个位置，
		//这样得到的顺序就是从小到大
		int temp = arr[i];
		arr[i] = arr[0];
		arr[0] = temp;
		//将arr[0...i-1]重新调整为最大堆
		HeapAdjustDown(arr,0,i-1);
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

	printf("堆排序后的顺序：");
	Heap_Sort(arr,num);
	for(i=0;i<num;i++)
		printf("%d ",arr[i]);
	printf("\n");

	free(arr);
	arr = 0;
	return 0;
}