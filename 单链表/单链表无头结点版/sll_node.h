#include <stdio.h>
#include <stdlib.h>

struct NODE
{
	int value;
	struct NODE *next;
};
typedef struct NODE Node;

extern Node *root;               //这里的root是在link_main文件中的定义的,同时应用于input.cpp文件，该文件中没有定义指针root，
					            //其结果是在调用过input函数之后，root值改变，不再为NULL；

bool sell_insert(Node **,int );  //插入节点函数

void show(Node *);				//显示链表数据函数

void input_data(Node **);		//输入链表数据函数

void free_list(Node **);		//释放链表内存函数

unsigned int count(Node *);     //链表节点计数函数

bool check(Node *,int);			//检查输入的数据是否在聊表中已经存在的函数

void sort(Node *);			//链表排序函数——冒泡法

void delete_data(Node **,int); //删除节点函数
