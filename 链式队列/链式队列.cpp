/*******************************************************************
该队列为链式队列，初建队列时，队头和队尾均指向头结点，头结点中不存放
数据，只存放指针，头结点的下一个节点才开始存放数据，这这样做的目的是
为了在入队和出队时方便对队列的操作，而不用考虑特殊情况。
*******************************************************************/

#include<stdio.h>
#include<stdlib.h>

typedef struct Node
{
	int data;
	struct Node *pNext;
}NODE,*PNODE;

typedef struct Queue
{
	PNODE front;  //队头指针
	PNODE rear;   //队尾指针
}QUEUE,*PQUEUE;

PQUEUE create_queue();
bool is_empty(PQUEUE);
void en_queue(PQUEUE, int);
bool de_queue(PQUEUE,int *);
void destroy_queue(PQUEUE);
void traverse_queue(PQUEUE);

int main()
{
	int data_de = 0;         //用来保存出队的元素值

	//创建队列并进行入队测试
	PQUEUE pS = create_queue();
	en_queue(pS,2);
	en_queue(pS,4);
	en_queue(pS,6);
	traverse_queue(pS);
	
	//出队测试
	if(de_queue(pS,&data_de))
		printf("delete succeed,the deleted data is: %d\n",data_de);
	else
		printf("queue is empty! delete falied!\n");
	traverse_queue(pS);
	
	//销毁队列测试
	destroy_queue(pS);
	printf("queue destroyed!\n");
	traverse_queue(pS);

	return 0;
}

/*
创建一个空队列，队头指针和队尾指针都指向头结点，
头结点中不存放数据，只存放指针
*/
PQUEUE create_queue()
{
	PQUEUE pS = (PQUEUE)malloc(sizeof(Queue));
	pS->front = (PNODE)malloc(sizeof(NODE));
	if(!pS || !pS->front)
	{
		printf("pS or front malloc failed!!");
		exit(-1);
	}
	else
	{
		pS->rear = pS->front;
		pS->front->pNext = NULL;
	}
	return pS;
}

/*
判断队列是否为空
*/
bool is_empty(PQUEUE pS)
{
	if(pS->front == pS->rear)
		return true;
	else
		return false;
}

/*
进队函数，从队尾进队，队头指针保持不变
*/
void en_queue(PQUEUE pS, int e)
{
	PNODE pNew = (PNODE)malloc(sizeof(NODE));
	if(!pNew)
	{
		printf("pNew malloc failed");
		exit(-1);
	}
	else
	{
		pNew->data = e;
		pNew->pNext = NULL;
		pS->rear->pNext = pNew;
		pS->rear = pNew;
	}
	return;
}

/*
出队函数，从队头出队，队尾指针保持不变，但当最后一个元素出队时，
需要对队尾指针重新赋值，使其指向头结点
*/
bool de_queue(PQUEUE pS,int *pData)
{
	if(is_empty(pS))
		return false;
	else
	{
		PNODE p = pS->front->pNext;
		*pData = p->data;
		pS->front->pNext = p->pNext;

		//这里是队列头元素出队的特殊情况，一般情况下，删除队头元素时
		//仅需修改头结点中的指针，但当队列中最后一个元素被删除时，
		//队列尾指针也丢失了，因此需对队尾指针重新赋值（指向头结点）。
		if(pS->rear == p)         
			pS->rear = pS->front;
		free(p);
	}
	return true;
}

/*
遍历队列，从对头向队尾依次输出队中的元素
*/
void traverse_queue(PQUEUE pS)
{
	if(is_empty(pS))
		printf("there is no data in the queue!\n");
	else
	{	
		PNODE pCurrent = pS->front->pNext; 
		printf("Now datas int the queue are:\n");
		while(pCurrent)
		{
			printf("%d ",pCurrent->data);
			pCurrent = pCurrent->pNext;
		}
		printf("\n");
	}
	return;
}

/*
销毁队列,头结点也被销毁,最后也将pS节点销毁，并将其指向为空，避免垂直指针的产生
*/
void destroy_queue(PQUEUE pS)
{
	if(is_empty(pS))
		return;
	else
	{
		while(pS->front)
		{
			pS->rear = pS->front->pNext;
			free(pS->front);
			pS->front = pS->rear;
		}
	}
	free(pS);
	pS = 0;
	return;
}

