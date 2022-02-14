#include <iostream>
using namespace std;

/**************************************************************************************
*********************************** ͼ�ṹ���弰���� ***********************************
***************************************************************************************/
typedef char VertexType;	// �������ͣ��Զ���
typedef int  WeightType;	// ����Ȩֵ���ͣ��Զ���

#define MAXVEX (100)		// ��󶥵���

typedef struct EdgeNode {
	int		  adjvex;		// �ڽӵ��򣬴洢�ö����Ӧ���±�
	EdgeNode* next;			// ����ָ����һ���ڽӵ�
	// WeightType	weight;		// Ȩֵ�򣬴洢���ϵ�Ȩֵ		��Ȩͼ����Ҫ
} EdgeNode;

typedef struct VertexNode {
	VertexType data;		// ������Ϣ
	EdgeNode* firstEdge;	// ָ���һ���ڽӵ�
} VertexNode, AdjList[MAXVEX];

typedef struct {
	AdjList adjList;	// �ڽӱ�
	int Nv, Ne;			// ������������
} ALGraph;

/**
* @brief:	����ͼ���ڽӱ�ṹ
* @param G:	ָ��ͼ��ָ��
* @return:	void
*/
void createALGraph(ALGraph* G) {
	cout << "���붥�����ͱ�����";
	cin >> G->Nv >> G->Ne;

	cout << "���붥����Ϣ��";
	for (int i = 0; i < G->Nv; i++)
	{
		cin >> G->adjList[i].data;			// ������Ϣ
		G->adjList[i].firstEdge = nullptr;	// �߱�ָ���ʼ��Ϊ��
	}

	int i, j;
	EdgeNode* e;
	for (int k = 0; k < G->Ne; k++)
	{
		cout << "�����(Vi, Vj)���±�i��j��";
		cin >> i >> j;
		e = new EdgeNode;
		e->adjvex = j;
		e->next = G->adjList[i].firstEdge;	// 1
		G->adjList[i].firstEdge = e;		// 2
		// 1��2������ͷ�巨

		// ����ͼ�ĶԳƲ���
		e = new EdgeNode;
		e->adjvex = i;
		e->next = G->adjList[j].firstEdge;
		G->adjList[j].firstEdge = e;
	}
}

/**
* @brief: ����ͼ���ڽӱ�
* @param G��ָ��ͼ��ָ��
* @return:	void
*/
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
*********************************** ���нṹ���弰���� **********************************
***************************************************************************************/
typedef int QElemType;			// ����Ԫ������
typedef struct
{
	QElemType data[MAXVEX + 1];	// �洢�����±������
	int front;					// ͷָ�룬ָ����еĵ�һ��Ԫ��
	int rear;					// βָ�룬ָ����������һ��Ԫ�ص���һ��λ��
} Queue;

/*
* @brief:	��ʼ��һ���ն���
* @param q: ָ����е�ָ��
* @return:	true
*/
bool initQueue(Queue* q) {
	for (int i = 0; i <= MAXVEX; i++)
	{
		q->data[i] = -1;	// ����Ԫ��ȫ����ʼ��Ϊ-1
	}
	q->front = 0;
	q->rear = 0;
	return true;
}

/**
* @brief:	�ж϶����Ƿ�Ϊ��
* @param q: ָ����е�ָ��
* @return��	true / false
*/
bool queueEmpty(Queue* q) {
	return q->front == q->rear;
}

/**
* @brief:	�ж϶����Ƿ�����
* @param q: ָ����е�ָ��
* @return��	true / false
*/
bool queueFull(Queue* q) {
	return q->rear == MAXVEX;
}

/*
* @brief:		Ԫ�����
* @param q:		ָ����е�ָ��
* @param elem��	��Ҫ��ӵ�Ԫ��
* @return:		true / false
*/
bool enQueue(Queue* q, QElemType elem) {
	if (queueFull(q))	// ��������
	{
		return false;
	}
	else
	{
		q->data[q->rear++] = elem;
		return true;
	}
}

/*
* @brief:		Ԫ�س���
* @param q:		ָ����е�ָ��
* @param elem��	���ճ��ӵ�Ԫ��
* @return:		true / false
*/
bool deQueue(Queue* q, QElemType* elem) {
	if (queueEmpty(q))	// ����Ϊ��
	{
		return false;
	}
	else
	{
		*elem = q->data[q->front++];
		return true;
	}
}

/**************************************************************************************
************************************** BFS�����㷨*** **********************************
***************************************************************************************/
int visited[MAXVEX] = { 0 };	// �������飬��¼ÿ�������Ƿ񱻷��ʹ���0��δ���ʣ�1���ѷ���
/**
* @brief: �ڽӾ����BFS�ݹ��㷨
* @param G��ָ��ͼ��ָ��
* @param i�������Ķ�����
* @return:	void
*/
void BFSTraverse(ALGraph* G) {
	Queue q;
	initQueue(&q);	// ��ʼ������

	for (int i = 0; i < G->Nv; i++)		// ��ÿ������ѭ������ֹͼ����ͨ���ж���û�ñ�����
	{
		if (0 == visited[i])	// �ö�����δ������
		{
			cout << G->adjList[i].data << "\t";
			visited[i] = 1;		// ��ӡ�󽫷��ʱ��λ��1
			enQueue(&q, i);		// ��ͼ�ĵ�һ���������
			while (!queueEmpty(&q))
			{
				QElemType e;	// ���ճ���Ԫ��
				deQueue(&q, &e);
				EdgeNode* edge = G->adjList[e].firstEdge;
				// ���ö���������ڽӵ����
				while (edge)
				{
					if (visited[edge->adjvex] == 0)
					{
						cout << G->adjList[edge->adjvex].data << "\t";
						visited[edge->adjvex] = 1;
						enQueue(&q, edge->adjvex);
					}
					edge = edge->next;
				}
			}
		}
	}
}

int main() {
	ALGraph* G = new ALGraph;
	createALGraph(G);

	BFSTraverse(G);

	destroyAdjList(G);

	delete G;
}