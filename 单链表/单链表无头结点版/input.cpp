#include "sll_node.h"

/*ÊäÈëº¯Êý*/
void
input_data(Node **phead)
{
	int value;
	Node *current,*prev;
	root = *phead;
	puts("Enter the first value(q to end):");
	while(scanf("%d",&value)==1)
	{
		while(getchar() != '\n')
			continue;

		current = (Node *)malloc(sizeof(Node));
		if(root == NULL)
			root = current;
		else
			prev->next = current;
		current->next = NULL;
		current->value = value;
		puts("Enter the next value(q to end):");
		prev = current;
	}
}
