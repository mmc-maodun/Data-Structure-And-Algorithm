/**********************************
图的BFS和DFS
Author:兰亭风雨 Date:2014-02-20
Email:zyb_maodun@163.com
**********************************/
#include<stdio.h>
#include<stdlib.h>
#include "data_structure.h"

int main()
{
	Graph Gp = create_graph();

	//深度优先遍历
	printf("对图进行深度优先遍历：\n");
	printf("从顶点A出发DFS的结果：");
	DFS_traverse(Gp,0);
	printf("\n");
	printf("从顶点H出发DFS的结果：");
	DFS_traverse(Gp,7);
	printf("\n");
	printf("从顶点E出发DFS的结果：");
	DFS_traverse(Gp,4);
	printf("\n");
	printf("\n");

	//广度优先遍历
	printf("对图进行广度优先遍历：\n");
	printf("从顶点A出发BFS的结果：");
	BFS_traverse(Gp,0);
	printf("\n");
	printf("从顶点H出发BFS的结果：");
	BFS_traverse(Gp,7);
	printf("\n");
	printf("从顶点E出发BFS的结果：");
	BFS_traverse(Gp,4);
	printf("\n");

	int i;
	//释放掉为每个单链表所分配的内存
	for(i=0;i<NUM;i++)
	{
		free(Gp[i].first);
		Gp[i].first = 0;  //防止悬垂指针的产生
	}

	//释放掉为顶点数组所分配的内存
	free(Gp);
	Gp = 0;
	return 0;
}
