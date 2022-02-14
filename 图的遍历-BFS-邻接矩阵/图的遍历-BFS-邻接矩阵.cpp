#include <iostream>
using namespace std;

/**************************************************************************************
*********************************** ͼ�ṹ���弰���� *********************************** 
***************************************************************************************/
typedef char VertexType;	// �������ͣ��Զ���
typedef int  WeightType;	// ����Ȩֵ���ͣ��Զ���

#define MAXVEX (100)		// ��󶥵���

typedef struct {
	VertexType vexs[MAXVEX];			// ��������
	WeightType arcs[MAXVEX][MAXVEX];	// �ڽӾ���
	int Nv, Ne;							// ������������
} MGraph;

/**
* @brief:	����ͼ���ڽӾ���ṹ
* @param G��ָ��ͼ��ָ��
*/
void createMGraph(MGraph* G) {
	cout << "���붥�����ͱ�����";
	cin >> G->Nv >> G->Ne;

	// ��ʼ���ڽӾ���
	for (int i = 0; i < G->Nv; i++)
	{
		for (int j = 0; j < G->Nv; j++)
		{
			G->arcs[i][j] = 0;	// ��Ȩͼ���ڽӾ���ȫ����ʼ��Ϊ0����ʾû�б�
		}
	}

	cout << "���붥����Ϣ��";
	for (int i = 0; i < G->Nv; i++)
	{
		cin >> G->vexs[i];
	}

	// ����Ne������Ϣ�������ڽӾ���
	int i, j;
	for (int k = 0; k < G->Ne; k++)
	{
		cout << "�����(Vi, Vj)���±�i��j��";
		cin >> i >> j;
		G->arcs[i][j] = 1;
		G->arcs[j][i] = G->arcs[i][j];	// ����ͼ���ڽӾ���Ϊ�Գ���
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
*/
void BFSTraverse(MGraph* G) {
	Queue q;
	initQueue(&q);	// ��ʼ������

	for (int i = 0; i < G->Nv; i++)		// ��ÿ������ѭ������ֹͼ����ͨ���ж���û�ñ�����
	{
		if (0 == visited[i])	// �ö�����δ������
		{
			cout << G->vexs[i] << "\t";
			visited[i] = 1;		// ��ӡ�󽫷��ʱ��λ��1
			enQueue(&q, i);		// ��ͼ�ĵ�һ���������
			while (!queueEmpty(&q))
			{
				QElemType e;	// ���ճ���Ԫ��
				deQueue(&q, &e);

				// ���ö���������ڽӵ����
				for (int j = 0; j < G->Nv; j++)
				{
					if (G->arcs[e][j] == 1 && visited[j] == 0)
					{
						cout << G->vexs[j] << "\t";
						visited[j] = 1;
						enQueue(&q, j);
					}
				}
			}
		}
	}
}

int main() {
	MGraph* G = new MGraph;
	createMGraph(G);

	BFSTraverse(G);

	delete G;
}