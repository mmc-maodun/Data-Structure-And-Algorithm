#include "sll_node.h"

/*节点计数函数*/
unsigned int 
count(Node *root)
{
	unsigned int count = 0;
	while(root != NULL)
	{
		++count;
		root = root->next;
	}
	
	return count;
}