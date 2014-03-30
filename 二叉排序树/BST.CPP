/*********************************
二叉排序树的相关操作实现
Author:兰亭风雨  Date：2014-02-23
Email:zyb_maodun@163.com
**********************************/
#include<stdio.h>
#include<stdlib.h>

typedef struct Node
{
	int data;
	struct Node *lchild;
	struct Node *rchild;
}NODE,*BSTree;


/*
在指针pTree所指的二叉排序树中递归查找关键字为key的元素，
若查找成功，则返回指向该元素节点的指针，否则返回NULL
*/
BSTree search(BSTree pTree,int key)
{
	if(!pTree || pTree->data == key)	//查找到时返回的pTree为该元素节点，没查找到时为NULL
		return pTree;
	else if(key < pTree->data)			//如果key小于当前节点的值，则在其左子树中递归查找
		return search(pTree->lchild,key);
	else								//如果key大于当前节点的值，则在其右子树中递归查找
		return search(pTree->rchild,key);
}


/*
在指针pTree所指的二叉排序树中递归查找关键字为key的元素，
若查找成功，则返回ture，并查找到的数据对应的节点指针保存在p中，
否则返回false，并将查找路径上访问的最后一个节点指针保存在p中。
这里的参数parent指向每次递归遍历的子树的根节点的父节点，即始终是参数pTree的父节点，
它的初始值为NULL，其目的是跟踪查找路径上访问的当前节点的父节点（即上一个访问节点）
该函数用来被后面的插入函数调用。
*/
bool search_BSTree(BSTree pTree,int key,BSTree parent,BSTree &p)
{
	if(!pTree)         //如果pTree为NULL，则查找不成功												
	{	//这里包含了树空，即pTree为NULL的情况
		p = parent;
		return false;
	}
	else             //否则，继续查找
	{								
		if(key == pTree->data)			//如果相等，则查找成功					
		{
			p = pTree;
			return true;
		}
		else if(key < pTree->data)		//在左子树中递归查找
			return search_BSTree(pTree->lchild,key,pTree,p);    
		else							//在右子树中递归查找
			return search_BSTree(pTree->rchild,key,pTree,p);
    }
}

/*
当在pTree所指向的二叉排序树中查找不到关键字为key的数据元素时，
将其插入该二叉排序树，并返回ture，否则返回false。
树空时插入会改变根节点的值，因此要传入引用。
*/
bool insert(BSTree &pTree,int key)
{
	BSTree p;
	if(!search_BSTree(pTree,key,NULL,p))		//如果查找失败，则执行插入操作
	{
		//为新节点分配空间，并对各域赋值
		BSTree pNew = (BSTree)malloc(sizeof(NODE));
		pNew->data = key;
		pNew->lchild = pNew->rchild = NULL;

		if(!p)						    //如果树空，则直接置pNew为根节点
			pTree = pNew;
		else if(key < p->data)			//作为左孩子插入p的左边
			p->lchild = pNew;	        //作为右孩子插入p的右边	
		else
			p->rchild = pNew;
	}
	else
		return false;
}

/*
采用第一种算法从二叉排序树中删除指针p所指向的节点,
并在保持二叉排序树有序的情况下，将其左右子树重接到该二叉排序树中.
该函数主要用来被后面的删除函数调用
*/
void delete_Node1(BSTree &p)
{ 
	BSTree q,s;
	if(!p->lchild)	
	{	//如果左子树为空，则只需重接其右子树
		//这里包含了左右子树均为空的情况
		q = p;
		p = p->rchild ;
		free(q);
	}
	else if(!p->rchild)
	{	//如果右子树为空，则只需重接其左子树
		q = p;
		p = p->lchild;
		free(q);
	}
	else
	{	//如果左右子树都不为空，我们采取第一种方法来重接左右子树，
		//我们这里采取修改左子树的方法，也可以修改右子树，方法类似
		s = p->lchild;		//取待删节点的左节点

		//一直向右，最终s为待删节点的前驱节点
		//如果将各节点元素按从小到大顺序排列成一个序列，
		//则某节点的前驱节点即为序列中该节点的前面一个节点
		while(s->rchild)
			s = s->rchild;
		s->rchild = p->rchild;	//将p的右子树接为s的右子树
		q = p;
		p = p->lchild;		//将p的左子树直接接到其父节点的左子树上
		free(q);
	}
}

/*
采用第二种算法从二叉排序树中删除指针p所指向的节点,
并在保持二叉排序树有序的情况下，将其左右子树重接到该二叉排序树中.
该函数主要用来被后面的删除函数调用
*/
void delete_Node2(BSTree &p)
{
	BSTree q,s;		
	if(!p->lchild)	
	{	//如果左子树为空，则只需重接其右子树
		//这里包含了左右子树均为空的情况
		q = p;
		p = p->rchild ;
		free(q);
	}
	else if(!p->rchild)
	{	//如果右子树为空，则只需重接其左子树
		q = p;
		p = p->lchild;
		free(q);
	}
	else
	{	//如果左右子树都不为空，我们采取第二种方法来重接左右子树，
		//我们这里采取修改左子树的方法，也可以修改右子树，方法类似
		q = p;
		s = p->lchild;		//取待删节点的左节点
		while(s->rchild)		
		{	//一直向右，最终s为待删节点的前驱节点。
			//如果将各节点元素按从小到大顺序排列成一个序列，
			//则某节点的前驱节点即为序列中该节点的前面一个节点
			q = s;
			s = s->rchild;
		}
		//用s来替换待删节点p
		p->data = s->data;  
		//根据情况，将s的左子树重接到q上
		if(p != q)
			q->rchild = s->lchild;
		else
			q->lchild =s->lchild;
		free(s);
	}
}

/*
若pTree所指向的二叉排序树中查找到关键字为key的数据元素，
则删除该元素对应的节点，并返回true，否则返回false
如果要删除的恰好是根节点，则会改变根节点的值，因此要传入引用
*/
bool delete_BSTree(BSTree &pTree,int key)
{
	//不存在关键字为key的节点
	if(!pTree)
		return false;
	else
	{	
		if(key == pTree->data)       //查找到关键字为key的节点
		{
			delete_Node1(pTree);
//			delete_Node2(pTree);
			return true;			
		}
		else if(key < pTree->data)  //继续查找左子树
			return delete_BSTree(pTree->lchild,key);
		else                        //继续查找右子树
			return delete_BSTree(pTree->rchild,key);
	}
}

/*
根据所给的长为len的arr数组，按数组中元素的顺序构建一棵二叉排序树
*/
BSTree create_BSTree(int *arr,int len)
{
	BSTree pTree = NULL;
	int i;
	//按顺序逐个节点插入到二叉排序树中
	for(i=0;i<len;i++)
		insert(pTree,arr[i]);
	return pTree;	
}

/*
递归中序遍历二叉排序树，得到元素从小到大有序排列的序列
*/
void in_traverse(BSTree pTree)
{
	if(pTree)
	{
		if(pTree->lchild)
			in_traverse(pTree->lchild);
		printf("%d ",pTree->data);
		if(pTree->rchild)
			in_traverse(pTree->rchild);	
	}
}


int main()
{
	int i;
	int num;
	printf("请输入节点个数：");
	scanf("%d",&num);

	//输入num个整数
	int *arr = (int *)malloc(num*sizeof(int));
	printf("请依次输入这%d个整数（必须互不相等）：",num);
	for(i=0;i<num;i++)
		scanf("%d",arr+i);

	//中序遍历该二叉排序树，使数据按照从小到大的顺序输出
	BSTree pTree = create_BSTree(arr,num);
	printf("中序遍历该二叉排序树的结果：");
	in_traverse(pTree);
	printf("\n");

	//查找给定的整数
	int key;
	printf("请输入要查找的整数：");
	scanf("%d",&key);
	if(search(pTree,key))
		printf("查找成功\n");
	else 
		printf("查找不到该整数\n");

	//插入给定的整数
	printf("请输入要插入的整数：");
	scanf("%d",&key);
	if(insert(pTree,key))
	{
		printf("插入成功，插入后的中序遍历结果：");
		in_traverse(pTree);
		printf("\n");
	}
	else
		printf("插入失败，该二叉排序树中已经存在整数%d\n",key);

	//删除给定的整数
	printf("请输入要删除的整数：");
	scanf("%d",&key);
	if(delete_BSTree(pTree,key))
	{
		printf("删除成功，插入后的中序遍历结果：");
		in_traverse(pTree);
		printf("\n");
	}
	else
		printf("删除失败，该二叉排序树中不存在整数%d\n",key);

	return 0;
}