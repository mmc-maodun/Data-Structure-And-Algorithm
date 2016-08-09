#include<stdio.h>
#include<stdlib.h>
#include"data_structure.h"

int main()
{
	BTree pTree = create_tree();

	printf("非递归实现前序遍历结果：");
	pre_traverse(pTree);
	printf("\n");

	printf("非递归实现中序遍历结果：");
	in_traverse(pTree);
	printf("\n");

	printf("非递归实现后序遍历结果：");
	beh_traverse(pTree);
	printf("\n");
	
	return 0;
}






















