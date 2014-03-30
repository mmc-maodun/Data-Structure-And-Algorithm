#include "sll_node.h"

Node *root = NULL;

int main()
{ 

	/*输入数据，分配内存，并输入原始序列和排序后的序列*/
	input_data(&root);
	if(root== NULL)
		printf("No data entered.");
	else
	{
		printf("Here is the list:\n");
		show(root);
		printf("\nThe sorted list is:\n");
		sort(root);
		show(root);
		printf("\nTotal itms of the list is:\n %d",count(root));
	}


	/*输入需要添加的数据*/
	while(getchar() != '\n')
		continue;                        //这两句必不可少，主要是防止scanf因最后一次读取到的是字母而永远不会越过它
	int new_value;
	printf("\nNow enter the new value:\n");
	scanf("%d",&new_value);
	while(getchar( ) != '\n')
		continue;
	

	/*检查待添加的数据是否在链表中已经存在，若存在，提示重新输入，直到不存在为止*/
	while(!check(root,new_value) )
	{
		printf("Existed in the list ,please input another data:");
		scanf("%d",&new_value);
			while(getchar() != '\n')
				continue;
	}


	/*将待添加的数据加入新建的节点，并分配内存，插入链表，显示插入后的序列*/
	if(sell_insert(&root,new_value))
	{
		printf("\nNow the list is:\n");
		show(root);
		printf("\nNow total itms of the list is:\n %d",count(root));
	}
	else 
		printf("insert error\n");
	printf("\n");


	/*输入待删除的数据*/
	int delete_value;
	printf("\nNow enter the deleted value:\n");
	scanf("%d",&delete_value);
	while(getchar() != '\n')
		continue;


	/*如果待删除的数据不在链表中，提示重新输入，知道存在为止*/
	while(check(root,delete_value) )
	{
		printf("Not exist in the list ,please input a data in the list:");
		scanf("%d",&delete_value);
			while(getchar() != '\n')
				continue;
	}


	/*将待删除的数据所在的节点所占用的内存释放掉，即删除掉，重新链接链表，并显示删除数据后的序列*/
	delete_data(&root,delete_value);
	printf("\nNow the list is:\n");
	show(root);
	printf("\nNow total itms of the list is:\n %d",count(root));
	printf("\n");


	/*释放链表所占用的内存*/
    free_list(&root);

	return 0;
}
