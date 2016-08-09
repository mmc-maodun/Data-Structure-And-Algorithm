#include<stdio.h>
#include"data_structure.h"

int main()
{
	char str[10];
	TrieTree pTree = create_TrieTree();
	
	printf("Please input all string:\n");
	while(gets(str) && str[0] != '\0')
		insert_TrieTree(pTree,str);

	printf("\nplease intput prefix string:\n");
	while(gets(str) && str[0] != '\0')
		printf("The num of strings started with %s is %d\n",str,count_TrieTree(pTree,str));

	destroy_TrieTree(pTree);
	return 0;
}
