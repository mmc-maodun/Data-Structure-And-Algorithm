/**********************************
封装实现图的BFS和DFS相关操作
Author:兰亭风雨 Date:2014-02-20
Email:zyb_maodun@163.com
***********************************/

#include<stdio.h>
#include<stdlib.h>
#include"data_structure.h"

/*
根据图例创建对应的图
*/
Graph create_graph()
{
	//为保存顶点相关信息的数组分配空间，并对数据域赋值
	Graph graph = (Graph)malloc(NUM*sizeof(Head));
	int i;
	//顶点的序号按照输入顺序从0依次向后
	for(i=0;i<NUM;i++)
		graph[i].data = 'A' + i;
	
	//为每个节点对应的的单链表中的节点分配空间
	Node *p00 = (Node *)malloc(sizeof(Node));
	Node *p01 = (Node *)malloc(sizeof(Node));
	Node *p10 = (Node *)malloc(sizeof(Node));
	Node *p11 = (Node *)malloc(sizeof(Node));
	Node *p12 = (Node *)malloc(sizeof(Node));
	Node *p20 = (Node *)malloc(sizeof(Node));
	Node *p21 = (Node *)malloc(sizeof(Node));
	Node *p22 = (Node *)malloc(sizeof(Node));
	Node *p30 = (Node *)malloc(sizeof(Node));
	Node *p31 = (Node *)malloc(sizeof(Node));
	Node *p40 = (Node *)malloc(sizeof(Node));
	Node *p41 = (Node *)malloc(sizeof(Node));
	Node *p50 = (Node *)malloc(sizeof(Node));
	Node *p51 = (Node *)malloc(sizeof(Node));
	Node *p60 = (Node *)malloc(sizeof(Node));
	Node *p61 = (Node *)malloc(sizeof(Node));
	Node *p70 = (Node *)malloc(sizeof(Node));
	Node *p71 = (Node *)malloc(sizeof(Node));

	//为各单链表中的节点的相关属性赋值
	p00->vertex = 1;
	p00->pNext = p01;
	p01->vertex = 2;
	p01->pNext = NULL;
	p10->vertex = 0;
	p10->pNext = p11;
	p11->vertex = 3;
	p11->pNext = p12;
	p12->vertex = 4;
	p12->pNext = NULL;
	p20->vertex = 0;
	p20->pNext = p21;
	p21->vertex = 5;
	p21->pNext = p22;
	p22->vertex = 6;
	p22->pNext = NULL;
	p30->vertex = 1;
	p30->pNext = p31;
	p31->vertex = 7;
	p31->pNext = NULL;
	p40->vertex = 1;
	p40->pNext = p41;
	p41->vertex = 7;
	p41->pNext = NULL;
	p50->vertex = 2;
	p50->pNext = p51;
	p51->vertex = 6;
	p51->pNext = NULL;
	p60->vertex = 2;
	p60->pNext = p61;
	p61->vertex = 5;
	p61->pNext = NULL;
	p70->vertex = 3;
	p70->pNext = p71;
	p71->vertex = 4;
	p71->pNext = NULL;

	//将顶点与每个单链表连接起来
	graph[0].first = p00;	
	graph[1].first = p10;
	graph[2].first = p20;	
	graph[3].first = p30;
	graph[4].first = p40;	
	graph[5].first = p50;
	graph[6].first = p60;	
	graph[7].first = p70;

	return graph;
}

/*
返回图Gp中pos顶点（序号为pos的顶点）的第一个邻接顶点的序号，如果不存在，则返回-1
*/
int first_vertex(Graph Gp,int pos)
{
	if(Gp[pos].first)  //如果存在邻接顶点，返回第一个邻接顶点的序号
		return 	Gp[pos].first->vertex;
	else              //如果不存在，则返回-1
		return -1;
}

/*
cur顶点是pos顶点（cur和pos均为顶点的序号）的其中一个邻接顶点，
返回图Gp中，pos顶点的（相对于cur顶点）下一个邻接顶点的序号,如果不存在，则返回-1
*/
int next_vertex(Graph Gp,int pos,int cur)
{
	Node *p = Gp[pos].first; //p初始指向顶点的第一个邻接点
	//循环pos节点对应的链表，直到p指向序号为cur的邻接点
	while(p->vertex != cur)
		p = p->pNext;

	//返回下一个节点的序号
	if(p->pNext)
		return p->pNext->vertex; 
	else 
		return -1;
}

bool visited[NUM];   //定义全局变量辅助数组，用来保存每个节点的访问信息

/*
从序号为begin的顶点出发，递归深度优先遍历连通图Gp
*/
void DFS(Graph Gp, int begin)
{
	//遍历输出序号为begin的顶点的数据域，并保存遍历信息
	printf("%c ",Gp[begin].data);
	visited[begin] = true; 

	//循环访问当前节点的所有邻接点（即该节点对应的链表）
	int i;
	for(i=first_vertex(Gp,begin); i>=0; i=next_vertex(Gp,begin,i))
	{
		if(!visited[i])  //对于尚未遍历的邻接节点，递归调用DFS
			DFS(Gp,i);
	}
} 

/*
从序号为begin的节点开始深度优先遍历图Gp，Gp可以是连通图也可以是非连通图
*/
void DFS_traverse(Graph Gp,int begin)
{
	int i;
	for(i=0;i<NUM;i++)    //初始化遍历标志数组
		visited[i] = false; 

	//先从序号为begin的顶点开始遍历对应的连通图
	DFS(Gp,begin);
	//如果是非连通图，该循环保证每个极大连通子图中的顶点都能被遍历到   
	for(i=0;i<NUM;i++)
	{	    
		if(!visited[i])
			DFS(Gp,i);
	}
}

/*
从序号为begin的顶点开始，广度优先遍历图Gp，Gp可以是连通图也可以是非连通图
*/
void BFS_traverse(Graph Gp,int begin)
{
	int i;
	for(i=0;i<NUM;i++)    //初始化遍历标志数组
		visited[i] = false;

	//先从序号为begin的顶点开始遍历对应的连通图
	BFS(Gp,begin);
	//如果是非连通图，该循环保证每个极大连通子图中的顶点都能被遍历到   
	for(i=0;i<NUM;i++)
	{	if(!visited[i])
			BFS(Gp,i);		
	}
}

/*
从序号为begin的顶点开始，广度优先遍历连通图Gp
*/
void BFS(Graph Gp,int begin)
{
	//遍历输出序号为begin的顶点的数据域，并保存遍历信息
	printf("%c ",Gp[begin].data);
	visited[begin] = true; 

	int i;
	int pVertex;  //用来保存从队列中出队的顶点的序号
	PQUEUE queue = create_queue();  //创建一个空的辅助队列
	en_queue(queue, begin);          //首先将序号为begin的顶点入队
	while(!is_empty(queue))
	{
		de_queue(queue,&pVertex);
		//循环遍历，访问完pVertex顶点的所有邻接顶点,并将访问后的邻接顶点入队
		for(i=first_vertex(Gp,pVertex); i>=0; i=next_vertex(Gp,pVertex,i))
		{
			if(!visited[i])
			{
				printf("%c ",Gp[i].data);
				visited[i] = true;
				en_queue(queue,i);
			}
		}
	}
	//销毁队列，释放其对应的内存
	destroy_queue(queue);
}
