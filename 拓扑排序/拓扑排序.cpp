#include <iostream>
using namespace std;

/**************************************************************************************
******************************** ͼ���ڽӱ�ṹ���弰���� ********************************
***************************************************************************************/
typedef char VertexType;	// �������ͣ��Զ����char
typedef int  WeightType;	// ���ϵ�Ȩֵ���ͣ��Զ����int

#define MAXVEX	 (100)		// ��󶥵���

/* �߱��� */
typedef struct EdgeNode {
	int			adjvex;		// �ڽӵ��򣬴洢�ö����Ӧ���±�
	// WeightType	weight;		// Ȩֵ�򣬴洢����Ȩֵ������ͼ(��Ȩͼ)���ض���
	EdgeNode* next;			// ����ָ����һ���ڽӵ�
} EdgeNode;

/* ������ */
typedef struct VertexNode {
	int in;						// �������
	VertexType	data;			// �����򣬴洢����ֵ
	EdgeNode* firstEdge;		// �߱�ͷָ�룬ָ���һ���ڽӵ�
} VertexNode, AdjList[MAXVEX];	// AdjList��ʾ�ڽӱ�����

typedef struct {
	AdjList adjList;		// �ڽӱ��൱�ڣ�VertexNode adjList[MAXVEX];
	int Nv, Ne;				// ͼ�ж������ͱ���
} ALGraph;

/* ����ͼ���ڽӱ�ṹ */
void createALGraph(ALGraph* G) {
	cout << "���붥�����ͱ�����";
	cin >> G->Nv >> G->Ne;

	// ���붥����Ϣ
	for (int i = 0; i < G->Nv; i++)
	{
		cout << "���붥�����ݼ�����ȣ�";
		cin >> G->adjList[i].data;			// ���붥����ֵ
		cin >> G->adjList[i].in;			// ���붥�����
		G->adjList[i].firstEdge = nullptr;	// ���߱�ָ����Ϊ��
	}

	// ����Ne���ߣ������ڽӱ�
	int i, j;
	// WeightType w;
	EdgeNode* e;
	for (int k = 0; k < G->Ne; k++)
	{
		/*
		cout << "�����(vi, vj)���±꼰i��j��Ȩֵw��" << endl;
		cin >> i >> j >> w;
		*/
		cout << "�����(vi, vj)���±꼰i��j��";
		cin >> i >> j;

		e = new EdgeNode;
		e->adjvex = j;						// �ڽӵ��±�Ϊj
		// e->weight = w;						// ��(vi, vj)�ϵ�Ȩֵ
		e->next = G->adjList[i].firstEdge;	// ��e��nextָ��ָ��ǰ����firstEdgeָ��Ľ��
		G->adjList[i].firstEdge = e;		// ����ǰ�����firstEdgeָ��ָ��e
		/* �������У�ʹ��ͷ�巨�������������� */

		// ����Ϊ����ͼ��Ҫ���֣�����ͼ����Ҫ 
		/*e = new EdgeNode;
		e->adjvex = i;
		e->weight = w;
		e->next = G->adjList[j].firstEdge;
		G->adjList[j].firstEdge = e;*/
	}
}

/* �����ڽӱ� */
void destroyAdjList(ALGraph* G) {
	for (int i = 0; i < G->Nv; i++)
	{
		while (G->adjList[i].firstEdge)
		{
			EdgeNode* e = G->adjList[i].firstEdge;
			G->adjList[i].firstEdge = e->next;
			delete e;
		}
	}
}

/**************************************************************************************
*************************************** �������� ***************************************
***************************************************************************************/
/**
* @brief:		����������G�޻�·������������������в�����0�����л�·����-1
* @param GL:	�ڽӱ��ʾ��ͼָ��
* @return:		0 ���� �ɹ�
*				-1 ���� ʧ��
*/
int TopologicalSort(ALGraph* G)
{
	EdgeNode* e;
	int i, k, gettop;
	int top = -1;	// ����ջָ���±�
	int count = 0;	// ����ͳ���������ĸ���
	int* stack;		// ��ջ�洢���Ϊ0�Ķ���
	stack = new int[G->Nv];

	for (i = 0; i < G->Nv; i++)
	{
		if (G->adjList[i].in == 0)
		{
			stack[++top] = i;	// �����Ϊ0�Ķ�����ջ
		}
	}

	while (top != -1)
	{
		gettop = stack[top--];	// ��ջ
		cout << G->adjList[gettop].data << "\t";
		count++;

		/* �����ö����Ӧ�ı߱� */
		for (e = G->adjList[gettop].firstEdge; e; e = e->next)
		{
			k = e->adjvex;
			G->adjList[k].in--;			// ��k�Ŷ������ȼ�1
			if (G->adjList[k].in == 0)	// �����Ϊ0����ջ
			{
				stack[++top] = k;
			}
		}

	}

	if (count < G->Nv)		// ���countС�ڶ�������˵�����ڻ�
	{
		return -1;
	}
	else
	{
		return 0;
	}
}

int main()
{
	ALGraph* G = new ALGraph;
	// ��ͼ
	createALGraph(G);

	// ��������
	TopologicalSort(G);

	// �����ڽӱ�
	destroyAdjList(G);

	delete G;
}