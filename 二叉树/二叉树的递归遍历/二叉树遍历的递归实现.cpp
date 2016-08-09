#include<stdio.h>
#include<stdlib.h>
typedef struct BTNode
{
	char data;
	struct BTNode *pLchild;
	struct BTNode *pRchild;
}BTNode, *BTree;

BTree create_tree();
void pre_traverse(BTree);
void in_traverse(BTree);
void beh_traverse(BTree);

int main()
{
	BTree pTree = create_tree();

	printf("递归实现前序遍历结果：");
	pre_traverse(pTree);
	printf("\n");

	printf("递归实现中序遍历结果：");
	in_traverse(pTree);
	printf("\n");

	printf("递归实现后序遍历结果：");
	beh_traverse(pTree);
	printf("\n");
	
	return 0;
}

BTree create_tree()
{
	BTree pA = (BTree)malloc(sizeof(BTNode));
	BTree pB = (BTree)malloc(sizeof(BTNode));
	BTree pD = (BTree)malloc(sizeof(BTNode));
	BTree pE = (BTree)malloc(sizeof(BTNode));
	BTree pC = (BTree)malloc(sizeof(BTNode));
	BTree pF = (BTree)malloc(sizeof(BTNode));
	
	pA->data = 'A';
	pB->data = 'B';
	pD->data = 'D';
	pE->data = 'E';
	pC->data = 'C';
	pF->data = 'F';
	
	pA->pLchild = pB;
	pA->pRchild = pC;
	pB->pLchild = pD;
	pB->pRchild = pE;
	pD->pLchild = pD->pRchild = NULL;
	pE->pLchild = pE->pRchild = NULL;
	pC->pLchild = pF;
	pC->pRchild = NULL;
	pF->pLchild = pF->pRchild = NULL;	
	
	return pA;
}

/*
前序遍历的递归实现
*/
void pre_traverse(BTree pTree)
{
	if(pTree)
	{
		printf("%c ",pTree->data);
		if(pTree->pLchild)
			pre_traverse(pTree->pLchild);
		if(pTree->pRchild)
			pre_traverse(pTree->pRchild);	
	}
}

/*
中序遍历的递归实现
*/
void in_traverse(BTree pTree)
{
	if(pTree)
	{
		if(pTree->pLchild)
			in_traverse(pTree->pLchild);
		printf("%c ",pTree->data);
		if(pTree->pRchild)
			in_traverse(pTree->pRchild);	
	}
}

/*
后序遍历的递归实现
*/
void beh_traverse(BTree pTree)
{
	if(pTree)
	{
		if(pTree->pLchild)
			beh_traverse(pTree->pLchild);
		if(pTree->pRchild)
			beh_traverse(pTree->pRchild);	
		printf("%c ",pTree->data);
	}
}
