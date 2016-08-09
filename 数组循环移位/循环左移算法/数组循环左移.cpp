#include<stdio.h>
#include<malloc.h>

int main()
{
	int len;
	int *start;
	int *end;

	printf("请输入数组个数：");
	scanf("%d",&len);

	start = (int *)malloc(len*sizeof(int));
	end   = (int *)malloc(len*sizeof(int));

	printf("请输入数组元素，以空格键隔开：");
	for(int i=0;i<len;i++)
		scanf("%d",&start[i]);

	for(int current=0;current<len;current++)
	{
		for(int k=0;k<len-current;k++)
			end[k] = start[current+k];
		for(int t=len-current,j=0;t<len;t++,j++)
			end[t] = start[j];
		printf("循环左移%d位后的结果：", current);
		for(int m=0;m<len;m++)
			printf("%d ",end[m]);
		printf("\n");
	}

	return 0;
}
