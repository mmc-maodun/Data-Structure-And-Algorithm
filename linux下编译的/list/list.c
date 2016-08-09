/**************************************************************************************************************
以下为操作链表的算法，该链表为单链表。
链表以头指针为索引，头指针指向头节点，头节点指向首节点，以此类推，直到尾节点。
头节点中不存放数据，只存放指向首节点的指针，
设置头节点的目的是为了方便对链表的操作，如果不设置头节点，而是直接由头指针指向首节点，
这样在对头指针后的节点进行插入删除操作时就会与其他节点进行该操作时有所不同，便要作为一种特殊情况来分析
**************************************************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct Node
{
	int data;
	struct Node *pNext;
}NODE,*PNODE;

PNODE create_list();       
void traverse_list(PNODE);
bool is_empty(PNODE);     
int length_list(PNODE); 
void sort_list(PNODE);    
bool insert_list(PNODE,int,int);
bool delete_list(PNODE,int,int *);
void clear_list(PNODE);

int main(void)
{
	int len;
	int data_del;
	PNODE pHead = NULL;

	//创建链表并遍历输出
 	pHead = create_list();
	traverse_list(pHead);

	//求链表长度，并输出
	len = length_list(pHead);
	if(!is_empty(pHead))
		printf("the length of the list is:%d\n",len);
	
	//向链表中插入数据，并重新遍历输出
	if(insert_list(pHead,3,78))
		printf("insert succeed,");
	else
		printf("insert failed,");
	traverse_list(pHead);

	//从链表中删除数据，并重新遍历输出
	if(delete_list(pHead,3,&data_del))
		{
		  printf("delete succeed,the deleted data is:%d\n",data_del);
		}
	else
		printf("delete failed,");
	traverse_list(pHead);
	
	//对链表排序，重新遍历输出
	sort_list(pHead);
	printf("After sorted,");
	traverse_list(pHead);	
	
	//清空链表，遍历输出（无数据输出）
	clear_list(pHead);
	printf("After cleared,");
	traverse_list(pHead);	
	return 0;
}

/*
  创建一个链表,并返回头指针
*/
PNODE create_list()
{
	int val;
	PNODE pHead =(PNODE)malloc(sizeof(NODE));
	PNODE pCurrent = pHead;
	pCurrent->pNext = NULL;
	if(NULL == pHead)
	{
		printf("pHead malloc failed!");
		exit(-1);
	}
	printf("Input first data(q to quit):");
	while(scanf("%d",&val)==1)
	{
		PNODE pNew = (PNODE)malloc(sizeof(NODE));
		if(NULL == pNew)
		{
			printf("pNew malloc failed!");
			exit(-1);
		}
		pNew->data = val;
		pCurrent->pNext = pNew;
		pNew->pNext = NULL;
		pCurrent = pNew;
		printf("Input next data(q to quit):");
	}

	return pHead;	
}

/*
遍历链表
*/
void traverse_list(PNODE pHead)
{
	PNODE pCurrent = pHead->pNext;
	printf("now dataes in the list are:\n");
	while(pCurrent != NULL)
	{	
		printf("%d ",pCurrent->data);
		pCurrent = pCurrent->pNext;
	}
	printf("\n");
	return ;
}

/*
判断链表是否为空
*/
bool is_empty(PNODE pNode)
{
	if(NULL == pNode->pNext)
		return true;
	else 
		return false;
}

/*
求链表长度，即节点总数（不计入头节点）
*/
int length_list(PNODE pNode)
{
	int count = 0;
	PNODE pCurrent = pNode->pNext;
	while(pCurrent != NULL)
	{
		count++;
		pCurrent = pCurrent->pNext;		
	}

	return count;
}

/*
冒泡法对链表排序
*/
void sort_list(PNODE pHead)
{
	PNODE p,q;
	int temp;
	for(p=pHead->pNext;p!=NULL;p=p->pNext)
	    for(q=p->pNext;q!=NULL;q=q->pNext)
		{
		   if(p->data>q->data)
	              {
			 temp = p->data;
			 p->data = q->data;
			 q->data = temp;
		      }
		}

	return ;
}

/*
在第pos个节点的后面插入一个新的节点，该节点中的数据为val
*/
bool insert_list(PNODE pHead,int pos,int val)
{
	int i = 0;
	PNODE p = pHead;

        //i为0时，p指向第0个节点（这里指没有实际数据的头节点，不计入链表节点总数），
	//i为1时，p指向第1个节点，i为几，p就指向第几个节点
	while(p!=NULL && i<pos)
	{
	   p = p->pNext;
	   i++;
	}

	//当pos的值大于链表长度时，便会出现这种情况
	if(i>pos || p==NULL)
	   return false;

	PNODE pNew = (PNODE)malloc(sizeof(NODE));
	if(NULL == pNew)
	{
	   printf("pNew malloc failed!");
	   exit(-1);
	}
	pNew->data = val;
	pNew->pNext = p->pNext;
	p->pNext = pNew;

	return true;
}

/*
删除第pos个节点，并将删除的数据保存在pData指针所指向的位置
*/
bool delete_list(PNODE pHead,int pos,int *pData)
{
	int i = 0;
	PNODE p = pHead;

	//p最终指向第pos个节点前面的节点
	//如果下面两句分别改为while(p!=NULL && i<pos)和if(i>pos || p==NULL)，则p最终指向第pos个节点，
	//这样因为得不到第pos个节点前面的那个节点，因此无法将pos前后两个节点连结起来
	while(p->pNext!=NULL && i<pos-1)
	{
	   p = p->pNext;
	   i++;
	}

	//当pos的值大于链表长度时，便会出现这种情况
	if(i>pos-1 || p->pNext==NULL)
	   return false;

	PNODE q = p->pNext;
	*pData = q->data;
	p->pNext = p->pNext->pNext;
	free(q);
	q = NULL;
	return true;
}

/*
清空链表，即使链表只剩下头节点（头节点中没有数据）
*/
void clear_list(PNODE pHead)
{
	PNODE p = pHead->pNext;
	PNODE r = NULL;
	while(p != NULL)
	{
	   r = p->pNext;
	   free(p);
	   p = r;
	}
	pHead->pNext = NULL;
	return ;
}
