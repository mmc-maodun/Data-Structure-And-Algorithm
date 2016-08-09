/**************************************************************************************************************
以下为操作栈的算法，该栈为动态栈。
在该栈中，pTop指向的节点中存放该栈的栈顶数据
pBottom指向的节点的上一个节点存放该栈的栈底数据，pBottom指向的节点中不存放有效数据，
这样做的目的是为了在进行入栈和出栈时方便对栈的操作，而用考虑特殊情况
**************************************************************************************************************/

#include<stdio.h>
#include<stdlib.h>

typedef struct Node
{
	int data;
	struct Node *pNext;
}NODE,*PNODE;

typedef struct Stack
{
	PNODE pTop;
	PNODE pBottom;
}STACK,*PSTACK;

PSTACK create_stack();
void push_stack(PSTACK,int);
void traverse_stack(PSTACK);
bool pop_stack(PSTACK,int *);
bool is_empty(PSTACK);
void clear_stack(PSTACK);

int main()
{	
	int data_pop;
	//创建一个空的栈，pS指针指向该栈
	PSTACK pS = create_stack();

	//向该栈中压入数据，遍历该栈并输出栈中的数据
	push_stack(pS,2);
	push_stack(pS,6);
	push_stack(pS,28);
	traverse_stack(pS);	

	//从该栈中推出数据，遍历该栈并输出栈中的数据
	if(pop_stack(pS,&data_pop))
	   printf("pop succeed,the data poped out is:%d\n",data_pop);
	else 
   	   printf("pop failed\n");
	traverse_stack(pS);
	
	//清空栈，遍历该栈并输出栈中的数据
	clear_stack(pS);
	printf("data cleared!\n");
	traverse_stack(pS);

	return 0;
}

/*
创建一个空栈,并返回指向该栈的指针
*/
PSTACK create_stack()
{
	PSTACK pS = (PSTACK)malloc(sizeof(STACK));
	pS->pTop = (PNODE)malloc(sizeof(NODE));
	if(NULL==pS || NULL==pS->pTop)
	{
	   printf("malloc failed");
	   exit(-1);
	}	
	else
	{
	   pS->pBottom = pS->pTop;
	   pS->pBottom->pNext = NULL;
	}
	
	return pS;
}

/*
判断该栈是否为空
*/
bool is_empty(PSTACK pS)
{
	if(pS->pTop == pS->pBottom)
	   return true;
    else
	   return false;
}

/*
向pS指针指向的栈中压入数据val
*/
void push_stack(PSTACK pS,int val)
{
	PNODE pNew = (PNODE)malloc(sizeof(NODE));
	if(NULL==pNew)
	{
	   printf("malloc failed");
	   exit(-1);
	}	
	else
	{
	   pNew->data = val;
	   pNew->pNext = pS->pTop;
	   pS->pTop = pNew;
	}	
	return ;
}

/*
从栈中推出数据，并将推出的数据保存在pData指针所指向的位置
*/
bool pop_stack(PSTACK pS,int *pData)
{
	if(is_empty(pS))
	   return false;
	else
	{
	   PNODE p = pS->pTop;
	   *pData = p->data;
	   pS->pTop = p->pNext;
	   free(p);
	   p = NULL;
	   return true;
	}
}

/*
遍历栈，并自栈顶向栈底输出栈中的数据
*/
void traverse_stack(PSTACK pS)
{
	PNODE pCurrent = pS->pTop; 
	printf("Now datas int the stack are:\n");
	while(pCurrent != pS->pBottom)
       {
	   printf("%d ",pCurrent->data);
	   pCurrent = pCurrent->pNext;
	}
	printf("\n");
	return ;
}

/*
清空栈，即将其还原为空栈
*/
void clear_stack(PSTACK pS)
{
	if(is_empty(pS))
	   return ;
	else
	{
	   PNODE p = pS->pTop;
	   PNODE r = NULL;
	   while(p != pS->pBottom)
	   {
			r = p->pNext;
			free(p);
			p = r;
	   }
	   pS->pTop = pS->pBottom;
   	}
}
