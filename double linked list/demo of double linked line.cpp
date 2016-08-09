#include<string.h>
#include<iostream>
#include<iomanip>
using namespace std;
typedef struct
{
	double x0;
	double y0;
	double x1;
	double y1;
	int flag;
}LineDxfData;
typedef struct LineNode
{
	LineDxfData linedata;
	struct LineNode* priorNode;
	struct LineNode* nextNode;
}LineNode;
//加入专用的head使得链表中的头结点和尾结点都指向NULL,这样逻辑才清晰
typedef struct Head
{
	unsigned int ID;
	unsigned int length;
	struct LineNode *first;//注意这里不是用struct Head *first,因为将来first是用来指向LineNode类型的指针的。
}Head;
LineNode*CreatNode(LineDxfData linedata);
Head*CreatHead();
Head*InsertLineNode(Head*head, LineNode*node, LineDxfData lindedata);
LineNode* FlineNode_xystart(Head*head, LineDxfData linedata);
LineDxfData LineDatSwap(LineDxfData linedata);
LineNode* FlineNode_xyend(Head*head, LineDxfData linedata);
LineNode* FlineNode_xySend(Head*head, LineDxfData linedata);
LineNode* FlineNode_xyEstart(Head*head, LineDxfData linedata);
int ShowAllLineNode(Head*head);
int main()
{
	Head* head = NULL;
	LineNode* Newnode = NULL;
	LineDxfData linedata;
	head = CreatHead();
	do
	{
		printf("链表测试。先输入链表中的数据，格式为：x0 y0 x1 y1 flag\n");
		fflush(stdin);
		cin >> linedata.x0 >> linedata.y0 >> linedata.x1 >> linedata.y1 >> linedata.flag;
		Newnode = CreatNode(linedata);//创造一个存放数据的结点
		//要把结点挂到链表上
		head = InsertLineNode(head, Newnode, linedata);//统一用插入，可以有前插，后插\
			//head是传入头结点用来开始搜索，Newnode是用来传入现有的数据，可能要用来调换用的，linedata是用来查找与之前数据关系用的。
		if (0 == linedata.flag)
		{
			break;
		}
		
	} while (1);
	ShowAllLineNode(head);//把所有的结点打印出来
}
LineNode*CreatNode(LineDxfData linedata)
{
	LineNode*newNode = (LineNode*)malloc(sizeof(LineNode));
	newNode->linedata = linedata;
	newNode->priorNode = NULL;//node是双向链表的头结点前向后向指针都为NULL；
	newNode->nextNode = NULL;
	return newNode;
}
Head*CreatHead()
{
	Head*head = (Head*)malloc(sizeof(Head));
	head->length = 0;//初始化的时候长度为零，指向的是一个空表。
	head->first = NULL;//初始化的时候要一并把head里面指向的双向链表的表头设置为NULL
	head->ID = 1;//用以区分不同的双向链表
	return head;
}
Head*InsertLineNode(Head*head, LineNode*node, LineDxfData linedata)
{
	LineDxfData lineNewdata;//用作数据交换
	LineNode*temp= NULL;
	LineNode*pstart= NULL;//判断是不是起起重合
	LineNode*pend = NULL;//判断是不是止止重合
	LineNode*pSend = NULL;//判断是不是起止重合
	LineNode*pEstart = NULL;//判断是不是止起重合
	//主分空表挂入，和有数据时候的挂入
	//空表挂入
	if (!(head->length))
	{
		
		head->first = node;
		head->length++;//注意这个用法，不要写成head->length=length++,因为这里不知道后面的length到底是什么
		return head;
	}
	//如果不是空表
	//判断是不是现有数据的起点和原有数据的终点相同，往后插，不同调换数据位置
	//往后插
	pSend = FlineNode_xySend(head, linedata);
	if (pSend)
	{
		//往后插的都要判断是不是尾结点
		if (!(pSend->nextNode))//尾结点的标志是pend->nextNode=NULL,能进去说明就是尾结点
		{
			/*lineNewdata = LineDatSwap(linedata);
			node->linedata = lineNewdata;//覆盖原来的数据*///注释掉是因为这里不需要调换数据，直接在后面挂就好了。
			pSend->nextNode = node;//pend->priorNode没有变化
			node->priorNode = pSend;//node->nextNode本来也是指向NULL的，所以不需要动
			head->length++;
			return head;
		}
		else//如果不是头结点那么就会涉及到pend前后的结点指向都要变化
		{
			/*lineNewdata = LineDatSwap(linedata);
			node->linedata = lineNewdata;//覆盖原来的数据*///注释掉是因为这里不需要调换数据，直接在后面挂就好了。
			node->priorNode = pSend;//这里只是说node前向指针指向pend，不代表pend的后向指针就是指向node了，因为pend->nextNode 是存放的值，不改变这个值就还是原来的指向。
			node->nextNode = pSend->nextNode;//与最下面不能调换顺序
			pSend->nextNode->priorNode = node;//这里也可以换成node->nextNode->priorNode = node;
			pSend->nextNode = node;
			head->length++;
			return head;

		}
	}
	//判断是不是止止重合，往后插，新数据要前后换位。这里要注意是不是尾结点
	//往后插
	pend = FlineNode_xyend(head, linedata);//查找是否有止止相同的结点
	if (pend)//找到了的情况下，要注意区分是不是尾结点。
	{
		if (!(pend->nextNode))//尾结点的标志是pend->nextNode=NULL,能进去说明就是尾结点
		{
			lineNewdata = LineDatSwap(linedata);
			node->linedata = lineNewdata;//覆盖原来的数据
			pend->nextNode = node;//pend->priorNode没有变化
			node->priorNode = pend;//node->nextNode本来也是指向NULL的，所以不需要动
			head->length++;
			return head;
		}
		else//如果不是头结点那么就会涉及到pend前后的结点指向都要变化
		{
			lineNewdata = LineDatSwap(linedata);
			node->linedata = lineNewdata;//覆盖原来的数据
			node->priorNode = pend;//这里只是说node前向指针指向pend，不代表pend的后向指针就是指向node了，因为pend->nextNode 是存放的值，不改变这个值就还是原来的指向。
			node->nextNode = pend->nextNode;//与最下面不能调换顺序
			pend->nextNode->priorNode = node;//这里也可以换成node->nextNode->priorNode = node;
			pend->nextNode = node;
			head->length++;
			return head;

		}
	}
	//判断是不是现在数据的终点和原来数据的起点是相同的情况
	//往前插，要注意头结点
	pEstart = FlineNode_xyEstart(head, linedata);
	if (pEstart)//要判断pstart是不是头结点，如果是那么pEstart->priorNode=NULL,这个是标志。
	{
		if (!(pEstart->priorNode))//如果pEstart是头结点的情况下,就要把head->first改变
		{
			/*lineNewdata = LineDatSwap(linedata);
			node->linedata = lineNewdata;//覆盖原来的数据*///既然是终点和起点相同，且往前插，那么就不要调换数据了。
			head->first = node;
			node->nextNode = pEstart;//node的前向为NULL
			pEstart->priorNode = node;//pstart的后向没有变化
			head->length++;
			return head;
		}
		else//如果不是在头结点
		{
			/*lineNewdata = LineDatSwap(linedata);
			node->linedata = lineNewdata;//覆盖原来的数据*///既然是终点和起点相同，且往前插，那么就不要调换数据了。
			node->priorNode = pEstart->priorNode;
			pEstart->priorNode->nextNode = node;
			node->nextNode = pEstart;
			pEstart->priorNode = node;
			head->length++;
			return head;
		}
	}
	
	//如果不是空表，那么要根据现在的数据和原来的数据之间的关系进行数据调换和找到插入点。
	//判断是不是起起重合，往前插，如果是那么要将现有的数据前后调换，并插入到原有结点的前面
	//往前插
	pstart = FlineNode_xystart(head, linedata);//pstart就是找到的结点，node该往pstart前面插入
	if (pstart)//要判断pstart是不是头结点，如果是那么pstart->priorNode=NULL,这个是标志。
	{
		if (!(pstart->priorNode))//如果pstart是头结点的情况下,就要把head->first改变
		{
			lineNewdata = LineDatSwap(linedata);
			node->linedata = lineNewdata;//覆盖原来的数据
			head->first = node;
			node->nextNode = pstart;//node的前向为NULL
			pstart->priorNode = node;//pstart的后向没有变化
			head->length++;
			return head;
		}
		else//如果不是在头结点
		{
			lineNewdata = LineDatSwap(linedata);
			node->linedata = lineNewdata;//覆盖原来的数据
			node->priorNode = pstart->priorNode;
			pstart->priorNode->nextNode = node;
			node->nextNode = pstart;
			pstart->priorNode = node;
			head->length++;
			return head;
		}
	}
	
	//如果不是空表,现在数据与以往数据之间也没有关系时候，直接往最后挂
	else
	{
		temp = head->first;//遍历用的，此时temp为头结点
		while (temp->nextNode)//当temp->nextNode为NULL的时候说明已经找到最后一个了，这时候要跳出循环
			//特别注意如果这里用while(temp)那么跳出循环的时候，temp已经是NULL了这不是最后一个结点，要指向NULL才是！！

		{
			temp = temp->nextNode;
		}
		node->priorNode = temp;
		temp->nextNode = node;
		head->length++;//每插入一次就要加一次
		return head;
	}
}
int ShowAllLineNode(Head*head)//if只是判断，没有循环功能
{
	LineNode*temp=NULL;
	int i;//用作循环使用
	if (!(head->length))//空表
		cout << "链表为空" << endl;
	else
	{
		temp= head->first;
		//如果把这里写作是temp->nextNode= head->first那么就会引起访问冲突，
		//因为head->first指的是头结点的地址，这里写成temp->nextNode就会使得temp不知道是哪里位置。
		for (i = 0; i < head->length; i++)//数字控制，也可以是用temp来控制
		{
			cout << temp->linedata.x0 << setw(5) << temp->linedata.y0 << setw(5) << temp->linedata.x1 << setw(5) << temp->linedata.y1 << endl;
			temp = temp->nextNode;
		}
	}
	return 0;
}
//需找是否哪个结点是起起重合
LineNode* FlineNode_xystart(Head*head, LineDxfData linedata)
{
	LineNode*temp = NULL;//用来查找
	double x_start, x_end, y_start, y_end;
	x_start = x_end = y_start = y_end = 0.00;
	x_start = linedata.x0;
	y_start = linedata.y0;
	x_end = linedata.x1;
	y_end = linedata.y1;
	temp = head->first;//此时temp为头结点
	while (temp)//这里不是找最后一个结点，是要全部去比较不能用temp->nextNode，
	{
		if ((x_start ==temp->linedata.x0) && (y_start ==temp->linedata.y0))//这里是不是有问题
			return temp;
		temp = temp->nextNode;
	}
	return NULL;
}
//寻找是否有哪个结点与现来的数据是止止相同
LineNode* FlineNode_xyend(Head*head, LineDxfData linedata)
{
	LineNode*temp = NULL;//用来查找
	double x_start, x_end, y_start, y_end;
	x_start = x_end = y_start = y_end = 0.00;
	x_start = linedata.x0;
	y_start = linedata.y0;
	x_end = linedata.x1;
	y_end = linedata.y1;
	temp = head->first;//此时temp为头结点,从头去遍历
	while (temp)//这里不是找最后一个结点，是要全部去比较不能用temp->nextNode，
	{
		if ((x_end == temp->linedata.x1) && (y_end == temp->linedata.y1))//千万注意不要写成if ((x_end = temp->linedata.x1) && (y_end = temp->linedata.y1))，不然就成了赋值了！！
			return temp;
		temp = temp->nextNode;
	}
	return NULL;
}
//需找是否现有数据的起始点和原有数据的终点是重合
LineNode* FlineNode_xySend(Head*head, LineDxfData linedata)
{
	LineNode*temp = NULL;//用来查找
	double x_start, x_end, y_start, y_end;
	x_start = x_end = y_start = y_end = 0.00;
	x_start = linedata.x0;
	y_start = linedata.y0;
	x_end = linedata.x1;
	y_end = linedata.y1;
	temp = head->first;//此时temp为头结点,从头去遍历
	while (temp)//这里不是找最后一个结点，是要全部去比较不能用temp->nextNode，
	{
		if ((x_start == temp->linedata.x1) && (y_start == temp->linedata.y1))//千万注意不要写成if ((x_end = temp->linedata.x1) && (y_end = temp->linedata.y1))，不然就成了赋值了！！
			return temp;
		temp = temp->nextNode;
	}
	return NULL;
}
//需找是否现有数据的终点和原有数据的起始点是重合
LineNode* FlineNode_xyEstart(Head*head, LineDxfData linedata)
{
	LineNode*temp = NULL;//用来查找
	double x_start, x_end, y_start, y_end;
	x_start = x_end = y_start = y_end = 0.00;
	x_start = linedata.x0;
	y_start = linedata.y0;
	x_end = linedata.x1;
	y_end = linedata.y1;
	temp = head->first;//此时temp为头结点,从头去遍历
	while (temp)//这里不是找最后一个结点，是要全部去比较不能用temp->nextNode，
	{
		if ((x_end == temp->linedata.x0) && (y_end == temp->linedata.y0))//千万注意不要写成if ((x_end = temp->linedata.x1) && (y_end = temp->linedata.y1))，不然就成了赋值了！！
			return temp;
		temp = temp->nextNode;
	}
	return NULL;
}
//数据交换
LineDxfData LineDatSwap(LineDxfData linedata)
{

	LineDxfData LineNewdata;
	LineNewdata.x0 = linedata.x1;
	LineNewdata.y0 = linedata.y1;
	LineNewdata.x1 = linedata.x0;
	LineNewdata.y1 = linedata.y0;
	return LineNewdata;
}