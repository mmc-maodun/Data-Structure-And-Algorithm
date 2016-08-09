/*******************************
			哈希表
Author:兰亭风雨 Date:2014-03-07
Email:zyb_maodun@163.com
*******************************/
#include<stdio.h>
#include "data_structure.h"

int main()
{
	int len = 15;	//哈希表长，亦即表中槽的数目
	printf("We set the length of hashtable %d\n",len);

	//创建哈希表并插入数据
	HashTable hashtable = create_HashTable(len);
	if(insert_HashTable(hashtable,1))
		printf("insert 1 success\n");
	else 
		printf("insert 1 fail,it is already existed in the hashtable\n");
	if(insert_HashTable(hashtable,8))
		printf("insert 8 success\n");
	else 
		printf("insert 8 fail,it is already existed in the hashtable\n");
	if(insert_HashTable(hashtable,3))
		printf("insert 3 success\n");
	else 
		printf("insert 3 fail,it is already existed in the hashtable\n");
	if(insert_HashTable(hashtable,10))
		printf("insert 10 success\n");
	else 
		printf("insert 10 fail,it is already existed in the hashtable\n");
	if(insert_HashTable(hashtable,8))
		printf("insert 8 success\n");
	else 
		printf("insert 8 fail,it is already existed in the hashtable\n");

	//查找数据
	pNode pFind1 = search_HashTable(hashtable,10);
	if(pFind1)
		printf("find %d in the hashtable\n",pFind1->data);		
	else 
		printf("not find 10 in the hashtable\n");
	pNode pFind2 = search_HashTable(hashtable,4);
	if(pFind2)
		printf("find %d in the hashtable\n",pFind2->data);		
	else 
		printf("not find 4 in the hashtable\n");

	//删除数据
	if(delete_HashTable(hashtable,1))
		printf("delete 1 success\n");
	else 
		printf("delete 1 fail");
	pNode pFind3 = search_HashTable(hashtable,1);
	if(pFind3)
		printf("find %d in the hashtable\n",pFind3->data);		
	else 
		printf("not find 1 in the hashtable,it has been deleted\n");

	//销毁哈希表
	destroy_HashTable(hashtable,len);
	return 0;
}
