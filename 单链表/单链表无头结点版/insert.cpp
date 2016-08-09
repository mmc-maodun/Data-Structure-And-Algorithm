#include "sll_node.h"

/*²åÈëº¯Êý*/
bool 
sell_insert(Node **phead,int new_value)
{
	Node *current;
	Node *previous;
	Node *newn;
	
	current = *phead;
	previous = NULL;

	while(current != NULL && current->value < new_value)
	{
		previous = current;
		current = current->next;
	}

	newn = (Node *)malloc(sizeof(Node));
	if(newn == NULL)
		return false;

	newn->value = new_value;
	newn->next = current;
	if(previous==NULL)
		*phead = newn;
	else
		previous->next = newn;

	return true;
}

