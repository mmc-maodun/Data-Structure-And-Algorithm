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
//����ר�õ�headʹ�������е�ͷ����β��㶼ָ��NULL,�����߼�������
typedef struct Head
{
	unsigned int ID;
	unsigned int length;
	struct LineNode *first;//ע�����ﲻ����struct Head *first,��Ϊ����first������ָ��LineNode���͵�ָ��ġ�
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
		printf("������ԡ������������е����ݣ���ʽΪ��x0 y0 x1 y1 flag\n");
		fflush(stdin);
		cin >> linedata.x0 >> linedata.y0 >> linedata.x1 >> linedata.y1 >> linedata.flag;
		Newnode = CreatNode(linedata);//����һ��������ݵĽ��
		//Ҫ�ѽ��ҵ�������
		head = InsertLineNode(head, Newnode, linedata);//ͳһ�ò��룬������ǰ�壬���\
			//head�Ǵ���ͷ���������ʼ������Newnode�������������е����ݣ�����Ҫ���������õģ�linedata������������֮ǰ���ݹ�ϵ�õġ�
		if (0 == linedata.flag)
		{
			break;
		}
		
	} while (1);
	ShowAllLineNode(head);//�����еĽ���ӡ����
}
LineNode*CreatNode(LineDxfData linedata)
{
	LineNode*newNode = (LineNode*)malloc(sizeof(LineNode));
	newNode->linedata = linedata;
	newNode->priorNode = NULL;//node��˫�������ͷ���ǰ�����ָ�붼ΪNULL��
	newNode->nextNode = NULL;
	return newNode;
}
Head*CreatHead()
{
	Head*head = (Head*)malloc(sizeof(Head));
	head->length = 0;//��ʼ����ʱ�򳤶�Ϊ�㣬ָ�����һ���ձ�
	head->first = NULL;//��ʼ����ʱ��Ҫһ����head����ָ���˫������ı�ͷ����ΪNULL
	head->ID = 1;//�������ֲ�ͬ��˫������
	return head;
}
Head*InsertLineNode(Head*head, LineNode*node, LineDxfData linedata)
{
	LineDxfData lineNewdata;//�������ݽ���
	LineNode*temp= NULL;
	LineNode*pstart= NULL;//�ж��ǲ��������غ�
	LineNode*pend = NULL;//�ж��ǲ���ֹֹ�غ�
	LineNode*pSend = NULL;//�ж��ǲ�����ֹ�غ�
	LineNode*pEstart = NULL;//�ж��ǲ���ֹ���غ�
	//���ֿձ���룬��������ʱ��Ĺ���
	//�ձ����
	if (!(head->length))
	{
		
		head->first = node;
		head->length++;//ע������÷�����Ҫд��head->length=length++,��Ϊ���ﲻ֪�������length������ʲô
		return head;
	}
	//������ǿձ�
	//�ж��ǲ����������ݵ�����ԭ�����ݵ��յ���ͬ������壬��ͬ��������λ��
	//�����
	pSend = FlineNode_xySend(head, linedata);
	if (pSend)
	{
		//�����Ķ�Ҫ�ж��ǲ���β���
		if (!(pSend->nextNode))//β���ı�־��pend->nextNode=NULL,�ܽ�ȥ˵������β���
		{
			/*lineNewdata = LineDatSwap(linedata);
			node->linedata = lineNewdata;//����ԭ��������*///ע�͵�����Ϊ���ﲻ��Ҫ�������ݣ�ֱ���ں���Ҿͺ��ˡ�
			pSend->nextNode = node;//pend->priorNodeû�б仯
			node->priorNode = pSend;//node->nextNode����Ҳ��ָ��NULL�ģ����Բ���Ҫ��
			head->length++;
			return head;
		}
		else//�������ͷ�����ô�ͻ��漰��pendǰ��Ľ��ָ��Ҫ�仯
		{
			/*lineNewdata = LineDatSwap(linedata);
			node->linedata = lineNewdata;//����ԭ��������*///ע�͵�����Ϊ���ﲻ��Ҫ�������ݣ�ֱ���ں���Ҿͺ��ˡ�
			node->priorNode = pSend;//����ֻ��˵nodeǰ��ָ��ָ��pend��������pend�ĺ���ָ�����ָ��node�ˣ���Ϊpend->nextNode �Ǵ�ŵ�ֵ�����ı����ֵ�ͻ���ԭ����ָ��
			node->nextNode = pSend->nextNode;//�������治�ܵ���˳��
			pSend->nextNode->priorNode = node;//����Ҳ���Ի���node->nextNode->priorNode = node;
			pSend->nextNode = node;
			head->length++;
			return head;

		}
	}
	//�ж��ǲ���ֹֹ�غϣ�����壬������Ҫǰ��λ������Ҫע���ǲ���β���
	//�����
	pend = FlineNode_xyend(head, linedata);//�����Ƿ���ֹֹ��ͬ�Ľ��
	if (pend)//�ҵ��˵�����£�Ҫע�������ǲ���β��㡣
	{
		if (!(pend->nextNode))//β���ı�־��pend->nextNode=NULL,�ܽ�ȥ˵������β���
		{
			lineNewdata = LineDatSwap(linedata);
			node->linedata = lineNewdata;//����ԭ��������
			pend->nextNode = node;//pend->priorNodeû�б仯
			node->priorNode = pend;//node->nextNode����Ҳ��ָ��NULL�ģ����Բ���Ҫ��
			head->length++;
			return head;
		}
		else//�������ͷ�����ô�ͻ��漰��pendǰ��Ľ��ָ��Ҫ�仯
		{
			lineNewdata = LineDatSwap(linedata);
			node->linedata = lineNewdata;//����ԭ��������
			node->priorNode = pend;//����ֻ��˵nodeǰ��ָ��ָ��pend��������pend�ĺ���ָ�����ָ��node�ˣ���Ϊpend->nextNode �Ǵ�ŵ�ֵ�����ı����ֵ�ͻ���ԭ����ָ��
			node->nextNode = pend->nextNode;//�������治�ܵ���˳��
			pend->nextNode->priorNode = node;//����Ҳ���Ի���node->nextNode->priorNode = node;
			pend->nextNode = node;
			head->length++;
			return head;

		}
	}
	//�ж��ǲ����������ݵ��յ��ԭ�����ݵ��������ͬ�����
	//��ǰ�壬Ҫע��ͷ���
	pEstart = FlineNode_xyEstart(head, linedata);
	if (pEstart)//Ҫ�ж�pstart�ǲ���ͷ��㣬�������ôpEstart->priorNode=NULL,����Ǳ�־��
	{
		if (!(pEstart->priorNode))//���pEstart��ͷ���������,��Ҫ��head->first�ı�
		{
			/*lineNewdata = LineDatSwap(linedata);
			node->linedata = lineNewdata;//����ԭ��������*///��Ȼ���յ�������ͬ������ǰ�壬��ô�Ͳ�Ҫ���������ˡ�
			head->first = node;
			node->nextNode = pEstart;//node��ǰ��ΪNULL
			pEstart->priorNode = node;//pstart�ĺ���û�б仯
			head->length++;
			return head;
		}
		else//���������ͷ���
		{
			/*lineNewdata = LineDatSwap(linedata);
			node->linedata = lineNewdata;//����ԭ��������*///��Ȼ���յ�������ͬ������ǰ�壬��ô�Ͳ�Ҫ���������ˡ�
			node->priorNode = pEstart->priorNode;
			pEstart->priorNode->nextNode = node;
			node->nextNode = pEstart;
			pEstart->priorNode = node;
			head->length++;
			return head;
		}
	}
	
	//������ǿձ���ôҪ�������ڵ����ݺ�ԭ��������֮��Ĺ�ϵ�������ݵ������ҵ�����㡣
	//�ж��ǲ��������غϣ���ǰ�壬�������ôҪ�����е�����ǰ������������뵽ԭ�н���ǰ��
	//��ǰ��
	pstart = FlineNode_xystart(head, linedata);//pstart�����ҵ��Ľ�㣬node����pstartǰ�����
	if (pstart)//Ҫ�ж�pstart�ǲ���ͷ��㣬�������ôpstart->priorNode=NULL,����Ǳ�־��
	{
		if (!(pstart->priorNode))//���pstart��ͷ���������,��Ҫ��head->first�ı�
		{
			lineNewdata = LineDatSwap(linedata);
			node->linedata = lineNewdata;//����ԭ��������
			head->first = node;
			node->nextNode = pstart;//node��ǰ��ΪNULL
			pstart->priorNode = node;//pstart�ĺ���û�б仯
			head->length++;
			return head;
		}
		else//���������ͷ���
		{
			lineNewdata = LineDatSwap(linedata);
			node->linedata = lineNewdata;//����ԭ��������
			node->priorNode = pstart->priorNode;
			pstart->priorNode->nextNode = node;
			node->nextNode = pstart;
			pstart->priorNode = node;
			head->length++;
			return head;
		}
	}
	
	//������ǿձ�,������������������֮��Ҳû�й�ϵʱ��ֱ��������
	else
	{
		temp = head->first;//�����õģ���ʱtempΪͷ���
		while (temp->nextNode)//��temp->nextNodeΪNULL��ʱ��˵���Ѿ��ҵ����һ���ˣ���ʱ��Ҫ����ѭ��
			//�ر�ע�����������while(temp)��ô����ѭ����ʱ��temp�Ѿ���NULL���ⲻ�����һ����㣬Ҫָ��NULL���ǣ���

		{
			temp = temp->nextNode;
		}
		node->priorNode = temp;
		temp->nextNode = node;
		head->length++;//ÿ����һ�ξ�Ҫ��һ��
		return head;
	}
}
int ShowAllLineNode(Head*head)//ifֻ���жϣ�û��ѭ������
{
	LineNode*temp=NULL;
	int i;//����ѭ��ʹ��
	if (!(head->length))//�ձ�
		cout << "����Ϊ��" << endl;
	else
	{
		temp= head->first;
		//���������д����temp->nextNode= head->first��ô�ͻ�������ʳ�ͻ��
		//��Ϊhead->firstָ����ͷ���ĵ�ַ������д��temp->nextNode�ͻ�ʹ��temp��֪��������λ�á�
		for (i = 0; i < head->length; i++)//���ֿ��ƣ�Ҳ��������temp������
		{
			cout << temp->linedata.x0 << setw(5) << temp->linedata.y0 << setw(5) << temp->linedata.x1 << setw(5) << temp->linedata.y1 << endl;
			temp = temp->nextNode;
		}
	}
	return 0;
}
//�����Ƿ��ĸ�����������غ�
LineNode* FlineNode_xystart(Head*head, LineDxfData linedata)
{
	LineNode*temp = NULL;//��������
	double x_start, x_end, y_start, y_end;
	x_start = x_end = y_start = y_end = 0.00;
	x_start = linedata.x0;
	y_start = linedata.y0;
	x_end = linedata.x1;
	y_end = linedata.y1;
	temp = head->first;//��ʱtempΪͷ���
	while (temp)//���ﲻ�������һ����㣬��Ҫȫ��ȥ�Ƚϲ�����temp->nextNode��
	{
		if ((x_start ==temp->linedata.x0) && (y_start ==temp->linedata.y0))//�����ǲ���������
			return temp;
		temp = temp->nextNode;
	}
	return NULL;
}
//Ѱ���Ƿ����ĸ������������������ֹֹ��ͬ
LineNode* FlineNode_xyend(Head*head, LineDxfData linedata)
{
	LineNode*temp = NULL;//��������
	double x_start, x_end, y_start, y_end;
	x_start = x_end = y_start = y_end = 0.00;
	x_start = linedata.x0;
	y_start = linedata.y0;
	x_end = linedata.x1;
	y_end = linedata.y1;
	temp = head->first;//��ʱtempΪͷ���,��ͷȥ����
	while (temp)//���ﲻ�������һ����㣬��Ҫȫ��ȥ�Ƚϲ�����temp->nextNode��
	{
		if ((x_end == temp->linedata.x1) && (y_end == temp->linedata.y1))//ǧ��ע�ⲻҪд��if ((x_end = temp->linedata.x1) && (y_end = temp->linedata.y1))����Ȼ�ͳ��˸�ֵ�ˣ���
			return temp;
		temp = temp->nextNode;
	}
	return NULL;
}
//�����Ƿ��������ݵ���ʼ���ԭ�����ݵ��յ����غ�
LineNode* FlineNode_xySend(Head*head, LineDxfData linedata)
{
	LineNode*temp = NULL;//��������
	double x_start, x_end, y_start, y_end;
	x_start = x_end = y_start = y_end = 0.00;
	x_start = linedata.x0;
	y_start = linedata.y0;
	x_end = linedata.x1;
	y_end = linedata.y1;
	temp = head->first;//��ʱtempΪͷ���,��ͷȥ����
	while (temp)//���ﲻ�������һ����㣬��Ҫȫ��ȥ�Ƚϲ�����temp->nextNode��
	{
		if ((x_start == temp->linedata.x1) && (y_start == temp->linedata.y1))//ǧ��ע�ⲻҪд��if ((x_end = temp->linedata.x1) && (y_end = temp->linedata.y1))����Ȼ�ͳ��˸�ֵ�ˣ���
			return temp;
		temp = temp->nextNode;
	}
	return NULL;
}
//�����Ƿ��������ݵ��յ��ԭ�����ݵ���ʼ�����غ�
LineNode* FlineNode_xyEstart(Head*head, LineDxfData linedata)
{
	LineNode*temp = NULL;//��������
	double x_start, x_end, y_start, y_end;
	x_start = x_end = y_start = y_end = 0.00;
	x_start = linedata.x0;
	y_start = linedata.y0;
	x_end = linedata.x1;
	y_end = linedata.y1;
	temp = head->first;//��ʱtempΪͷ���,��ͷȥ����
	while (temp)//���ﲻ�������һ����㣬��Ҫȫ��ȥ�Ƚϲ�����temp->nextNode��
	{
		if ((x_end == temp->linedata.x0) && (y_end == temp->linedata.y0))//ǧ��ע�ⲻҪд��if ((x_end = temp->linedata.x1) && (y_end = temp->linedata.y1))����Ȼ�ͳ��˸�ֵ�ˣ���
			return temp;
		temp = temp->nextNode;
	}
	return NULL;
}
//���ݽ���
LineDxfData LineDatSwap(LineDxfData linedata)
{

	LineDxfData LineNewdata;
	LineNewdata.x0 = linedata.x1;
	LineNewdata.y0 = linedata.y1;
	LineNewdata.x1 = linedata.x0;
	LineNewdata.y1 = linedata.y0;
	return LineNewdata;
}