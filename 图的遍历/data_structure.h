#define NUM 8          //图中顶点的个数

/*
用邻接表作为图的存储结构
在邻接表中，用一个一维数组存储图中的每个顶点的信息，
同时为每个顶点建立一个单链表，链表中的节点保存依附在该顶点上的边或弧的信息
*/
typedef struct node
{	//链表中的每个节点，保存依附在该节点上的边或弧的信息
	int vertex;          //在有向图中表示该弧所指向的顶点（即弧头）的位置，
				         //在无向图中表示依附在该边上的另一个顶点的位置
	struct node *pNext;  //指向下一条依附在该顶点上的弧或边
}Node;
typedef struct head
{	//数组中的每个元素，保存图中每个顶点的相关信息
	char data;          //顶点的数据域
	Node *first;        //在有向图中，指向以该顶点为弧尾的第一条弧
						//在无向图中，指向依附在该顶点上的第一条边
}Head,*Graph;           //动态分配数组保存每个顶点的相关信息


//根据图例创建对应的图
Graph create_graph();

//返回图中指定序号顶点的第一个邻接点
int first_vertex(Graph,int);

//返回图中指定序号节点的下一个邻接点
int next_vertex(Graph,int,int);

//从指定顶点出发，深度优先遍历连通图
void DFS(Graph, int);

//从指定顶点出发深度优先遍历图,可以是连通图也可以是非连通图
void DFS_traverse(Graph,int);

//从指定顶点出发，广度优先遍历连通图
void BFS(Graph,int);

//从指定顶点出发广度优先遍历图,可以是连通图也可以是非连通图
void BFS_traverse(Graph,int);



/*
链式队列的存储结构
*/
typedef struct NODE
{	//队列中的每个节点
	int data;
	struct NODE *pNext;
}NODE,*PNODE;
typedef struct Queue
{	//始终指向队的头部和尾部
	PNODE front;  //队头指针
	PNODE rear;   //队尾指针
}QUEUE,*PQUEUE;


//创建和一个空队列
PQUEUE create_queue();

//判断队列是否为空
bool is_empty(PQUEUE);

//进队函数
void en_queue(PQUEUE, int);

//出队函数
bool de_queue(PQUEUE,int *);

//销毁队列
void destroy_queue(PQUEUE);

//遍历队列
void traverse_queue(PQUEUE);






