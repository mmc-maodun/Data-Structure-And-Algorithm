#define MAX 26	//字符集的大小

/*
字典树的存储结构
*/
typedef struct Node
{
	struct Node *next[MAX];	//每个节点下面可能有MAX个字符
	int count;				//以从根节点到当前节点的字符串为公共前缀的字符串数目
}TrieNode,*TrieTree;

//创建一课只有根节点的字典树
TrieTree create_TrieTree();

//向字典树中插入字符串
void insert_TrieTree(TrieTree,char *);

//统计字典树中有给定公共前缀的字符串的数目
int count_TrieTree(TrieTree ,char *);

//销毁字典树
void destroy_TrieTree(TrieTree);
