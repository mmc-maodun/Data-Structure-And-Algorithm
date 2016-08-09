#include<stdio.h>

/*
第一种形式实现计数排序
计数排序后的顺序为从小到大
arr[0...len-1]为待排数组，每个元素均是0-k中的一个值
brr[0...len-1]为排序后的输出数组
crr[0...k]保存0...k中每个值在数组arr中出现的次数
*/
void Count_Sort(int *arr,int *brr,int *crr,int len,int k)
{
	int i,j=0;
	//数组crr各元素置0
	for(i=0;i<=k;i++)
		crr[i] = 0;
	//统计数组arr中每个元素重复出现的个数
	for(i=0;i<len;i++)
		crr[arr[i]]++;
	//求数组arr中小于等于i的元素个数
	for(i=1;i<=k;i++)
		crr[i] += crr[i-1];
	//把arr中的元素放在brr中对应的位置上
	for(i=len-1;i>=0;i--)
	{
		brr[crr[arr[i]]-1] = arr[i];
		//如果有相同的元素，则放在下一个位置上
		crr[arr[i]]--;
	}
}

/*
第二种形式实现计数排序
计数排序后的顺序为从小到大
arr[0...len-1]为待排数组，每个元素均是0-k中的一个值
crr[0...k]保存0...k中每个值在数组arr中出现的次数
*/
void Count_Sort(int *arr,int *crr,int len,int k)
{
	int i,j=0;
	//数组crr各元素置0
	for(i=0;i<=k;i++)
		crr[i] = 0;
	//统计数组arr中每个元素重复出现的个数
	for(i=0;i<len;i++)
		crr[arr[i]]++;
	//根据crr[i]的大小，将元素i放入arr适当的位置
	for(i=0;i<=k;i++)
		while((crr[i]--)>0)
		{
			arr[j++] = i;
		}
}

int main()
{
	int i; 
	//待排序数组，每个元素均在0-8之间
	int arr[] = {2,1,3,8,6,0};
	int brr[6];
	int crr[9];
	Count_Sort(arr,brr,crr,6,8);
	printf("计数排序后的结果为：");
	for(i=0;i<6;i++)
		printf("%d ",brr[i]);
	printf("\n");
	return 0;
}