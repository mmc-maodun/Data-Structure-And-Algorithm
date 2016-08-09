#include<stdio.h>
#include<stdlib.h>
#include"data_structure.h"

//创建一个空栈,并返回指向该栈的指针   
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
   
//判断该栈是否为空     
bool is_empty(PSTACK pS)  
{  
	if(pS->pTop == pS->pBottom)  
	   return true;  
	else  
	   return false;  
}  
  
//向pS指针指向的栈中压入数据val  
void push_stack(PSTACK pS,BTree val)  
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
   
//从栈中推出数据，并将推出的数据保存在pData指针所指向的位置  
bool pop_stack(PSTACK pS,BTree *pData)  
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
  
//遍历栈，并自栈顶向栈底输出栈中的数据  
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
   
//清空栈，即将其还原为空栈  
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

//如果栈不空，返回栈顶元素,如果栈空，返回空指针
BTree getTop(PSTACK pS)
{
	if(!is_empty(pS))
		return pS->pTop->data;
	else
		return NULL;
}   