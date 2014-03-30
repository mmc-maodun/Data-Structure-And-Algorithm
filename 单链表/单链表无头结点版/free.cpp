#include "sll_node.h"

/*ÊÍ·ÅÄÚ´æº¯Êý*/
void 
free_list(Node **phead)
{
	Node *psave;
	while(*phead != NULL)
	{
		psave = (*phead)->next;
		free(*phead);
		*phead = psave;
	}
}

