#include "sll_node.h"

/*遍历链表——检查输入的数据是否与链表中的数据重复*/
bool
check(Node *root,int value)
{
	Node *current;
	current = root;
	while(current != NULL)
	{
		if(current->value != value)
			current = current->next;
		else
			break;
	}

	if(current == NULL)
		return true;       //输入的数据没有与链表中的数据重复，返回true
	else 
		return false;
}
