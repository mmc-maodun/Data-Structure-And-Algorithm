#include "sll_node.h"

/*冒泡法排序链表函数——不改变节点位置，只改变节点中数据的存储位置*/
void 
sort(Node *root)
{
	Node *current;
	Node *s;
	
	for(current = root;current->next != NULL;current = current->next)
	{
		for(s = root;s->next != NULL;s = s->next)
		{
			
			if(s->value > s->next->value)
			{
				int temp;
				temp = s->value;
				s->value = s->next->value;
				s->next->value = temp;
			}
		}
	}

}