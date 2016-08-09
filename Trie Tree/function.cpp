#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"data_structure.h"

/*
创建一棵仅有根节点的字典树
*/
TrieTree create_TrieTree()
{
	TrieTree pTree = (TrieTree)malloc(sizeof(TrieNode));
	pTree->count = 0;
	int i;
	for(i=0;i<MAX;i++)
		pTree->next[i] = NULL;
	return pTree;
}

/*
插入字符串str到字典树pTree中
由于不可能改变根节点，因此这里不需要传入pTree的引用
*/
void insert_TrieTree(TrieTree pTree,char *str)
{
	int i;
	TrieTree pCur = pTree;	//当前访问的节点，初始指向根节点
	int len = strlen(str);
	for(i=0;i<len;i++)
	{
		int id = str[i] - 'a';	//定位到字符应该在的位置
		if(!pCur->next[id])
		{	//如果该字符应该在的位置为空，则将字符插入到该位置
			int j;
			TrieNode *pNew = (TrieNode *)malloc(sizeof(TrieNode));
			if(!pNew)
			{
				printf("pNew malloc fail\n");
				exit(-1);
			}
			pNew->count = 1;
			for(j=0;j<MAX;j++)
				pNew->next[j] = NULL;
			//指针后移，比较下一个字符
			pCur->next[id] = pNew;
			pCur = pCur->next[id]; 
		}
		else
		{	//如果该字符应该在的位置不空，则继续比较下一个字符
			pCur = pCur->next[id];
			pCur->count++;	//每插入一个字符，公共前缀数目就加1
		}
	}
}

/*
统计字典树pTree中以str为前缀的字符串的数目
*/
int count_TrieTree(TrieTree pTree,char *str)
{
	int i;
	TrieTree pCur = pTree;
	int len = strlen(str);
	for(i=0;i<len;i++)
	{
		int id = str[i] - 'a';
		if(!pCur->next[id])
			return 0;
		else
			pCur = pCur->next[id];
	}
	return pCur->count;
}

/*
销毁字典树
*/
void destroy_TrieTree(TrieTree pTree)
{
	int i;
	//递归释放每个节点的内存
	for(i=0;i<MAX;i++)
		if(pTree->next[i])
			destroy_TrieTree(pTree->next[i]);
	free(pTree);
}