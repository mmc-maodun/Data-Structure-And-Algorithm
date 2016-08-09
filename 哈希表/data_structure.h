#define M 7		//哈希函数中的除数,必须小于等于表长
typedef int ElemType;

/*
该哈希表采用链接法解决冲突问题
*/
typedef struct Node	
{	//Node为链表节点的数据结构
	ElemType data;
	struct Node *next;
}Node,*pNode;

typedef struct HashNode
{	//HashNode为哈希表的每个槽的数据结构
	pNode first;	//first指向链表的第一个节点
}HashNode,*HashTable;

//创建哈希表
HashTable create_HashTable(int);

//在哈希表中查找数据
pNode search_HashTable(HashTable, ElemType);

//插入数据到哈希表
bool insert_HashTable(HashTable,ElemType);

//从哈希表中删除数据
bool delete_HashTable(HashTable,ElemType);

//销毁哈希表
void destroy_HashTable(HashTable,int);