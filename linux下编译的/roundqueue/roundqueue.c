/**********************************************************************************************************
以下为操作队列的算法，该队列为静态队列，用循环数组实现。
给该队列分配的内存长度为len+1，但实际只用了len个内存空间来保存数据，这样做是为了更方便判断队列的满与空。
队列中front位置中存放的是队首的数据，rear位置的前一个位置中存放队尾的数据，而rear位置中则没有数据存放，
这样做的目的是为了在入队和出队时方便对队列的操作，而不用考虑特殊情况
**********************************************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

int len;//全局变量，静态队列的实际有效长度，即实际存放了len个数
typedef struct Queue
{
	int *pBase;
	int front;
	int rear; 
} QUEUE,*PQUEUE;

PQUEUE creat_queue();
bool enter_queue(PQUEUE,int);
bool full_queue(PQUEUE);
bool empty_queue(PQUEUE);
void traverse_queue(PQUEUE);
bool out_queue(PQUEUE,int *);

int main()
{	//创建静态队列，并定义出队数据的保存在变量data_save中
	int data_save;
	PQUEUE pQueue = creat_queue();
	//将数据入队，并遍历输出队列中的数据
	enter_queue(pQueue,1);
	enter_queue(pQueue,2);
	enter_queue(pQueue,3);
	enter_queue(pQueue,4);
       	traverse_queue(pQueue);
	//将数据出队，并遍历输出队列中的数据
	out_queue(pQueue,&data_save);
       	traverse_queue(pQueue);

	return 0;
}

/*
创建并初始化一个空的静态队列,返回指向该队列的指针，此时首尾在队列同一位置处
*/
PQUEUE creat_queue()
{
	printf("Input the length of the queue:\n");
	scanf("%d",&len);
	PQUEUE pQueue = (PQUEUE)malloc(sizeof(QUEUE));
	pQueue->pBase = (int *)malloc(sizeof(int)*(len+1));
	if(NULL==pQueue || NULL==pQueue->pBase)
	{
	   printf("malloc failed!");
	   exit(-1);
	}
	else
	{
	   pQueue->front = 0;
	   pQueue->rear = 0;
	}
	 return pQueue;
}

/*
判断该静态队列是否满
*/
bool full_queue(PQUEUE pQueue)
{
	if(pQueue->front == (pQueue->rear+1)%(len+1))
	   return true;
	else
	   return false;
}

/*
判断该静态队列是否空
*/
bool empty_queue(PQUEUE pQueue)
{
	if(pQueue->front == pQueue->rear)
	   return true;
	else
	   return false;
}

/*
将变量val从队尾入队
*/
bool enter_queue(PQUEUE pQueue,int val)
{
	if(full_queue(pQueue))
	   return false;
	else
	{
	   pQueue->pBase[pQueue->rear] = val;
	   pQueue->rear = (pQueue->rear+1)%(len+1);
	   return true;
	}
}

/*
将数据出队，并将其保存在out_data指针指向的位置
*/
bool out_queue(PQUEUE pQueue,int *out_data)
{
	if(empty_queue(pQueue))
	   return false;
	else
	{
	   *out_data = pBase[pQueue->front];
   	   pQueue->front = (pQueue->front+1)%(len+1);
	   return true;
	}
}

/*
遍历该静态队列，并自队首向队尾输出队列中的数据
*/
void traverse_queue(PQUEUE pQueue)
{
	if(empty_queue(pQueue))
		printf("there on datas in the queue!\n");
	else
	{
		int i = pQueue->front;
		printf("now datas in the queue are:\n");
		while(i != pQueue->rear)
		{
			printf("%d ",pQueue->pBase[i]);
			i = (i+1)%(len+1);
		}
		printf("\n");		
	}

	return ;
}

