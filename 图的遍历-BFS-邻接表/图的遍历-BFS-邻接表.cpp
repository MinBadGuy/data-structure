#include <iostream>
using namespace std;

/**************************************************************************************
*********************************** 图结构定义及操作 ***********************************
***************************************************************************************/
typedef char VertexType;	// 顶点类型，自定义
typedef int  WeightType;	// 边上权值类型，自定义

#define MAXVEX (100)		// 最大顶点数

typedef struct EdgeNode {
	int		  adjvex;		// 邻接点域，存储该顶点对应的下标
	EdgeNode* next;			// 链域，指向下一个邻接点
	// WeightType	weight;		// 权值域，存储边上的权值		无权图不需要
} EdgeNode;

typedef struct VertexNode {
	VertexType data;		// 顶点信息
	EdgeNode* firstEdge;	// 指向第一个邻接点
} VertexNode, AdjList[MAXVEX];

typedef struct {
	AdjList adjList;	// 邻接表
	int Nv, Ne;			// 顶点数、边数
} ALGraph;

/**
* @brief:	创建图的邻接表结构
* @param G:	指向图的指针
* @return:	void
*/
void createALGraph(ALGraph* G) {
	cout << "输入顶点数和边数：";
	cin >> G->Nv >> G->Ne;

	cout << "输入顶点信息：";
	for (int i = 0; i < G->Nv; i++)
	{
		cin >> G->adjList[i].data;			// 顶点信息
		G->adjList[i].firstEdge = nullptr;	// 边表指针初始化为空
	}

	int i, j;
	EdgeNode* e;
	for (int k = 0; k < G->Ne; k++)
	{
		cout << "输入边(Vi, Vj)的下标i、j：";
		cin >> i >> j;
		e = new EdgeNode;
		e->adjvex = j;
		e->next = G->adjList[i].firstEdge;	// 1
		G->adjList[i].firstEdge = e;		// 2
		// 1、2两步：头插法

		// 无向图的对称操作
		e = new EdgeNode;
		e->adjvex = i;
		e->next = G->adjList[j].firstEdge;
		G->adjList[j].firstEdge = e;
	}
}

/**
* @brief: 销毁图的邻接表
* @param G：指向图的指针
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
*********************************** 队列结构定义及操作 **********************************
***************************************************************************************/
typedef int QElemType;			// 队列元素类型
typedef struct
{
	QElemType data[MAXVEX + 1];	// 存储顶点下标的数组
	int front;					// 头指针，指向队列的第一个元素
	int rear;					// 尾指针，指向队列中最后一个元素的下一个位置
} Queue;

/*
* @brief:	初始化一个空队列
* @param q: 指向队列的指针
* @return:	true
*/
bool initQueue(Queue* q) {
	for (int i = 0; i <= MAXVEX; i++)
	{
		q->data[i] = -1;	// 数组元素全部初始化为-1
	}
	q->front = 0;
	q->rear = 0;
	return true;
}

/**
* @brief:	判断队列是否为空
* @param q: 指向队列的指针
* @return：	true / false
*/
bool queueEmpty(Queue* q) {
	return q->front == q->rear;
}

/**
* @brief:	判断队列是否已满
* @param q: 指向队列的指针
* @return：	true / false
*/
bool queueFull(Queue* q) {
	return q->rear == MAXVEX;
}

/*
* @brief:		元素入队
* @param q:		指向队列的指针
* @param elem：	需要入队的元素
* @return:		true / false
*/
bool enQueue(Queue* q, QElemType elem) {
	if (queueFull(q))	// 队列已满
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
* @brief:		元素出队
* @param q:		指向队列的指针
* @param elem：	接收出队的元素
* @return:		true / false
*/
bool deQueue(Queue* q, QElemType* elem) {
	if (queueEmpty(q))	// 队列为空
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
************************************** BFS遍历算法*** **********************************
***************************************************************************************/
int visited[MAXVEX] = { 0 };	// 辅助数组，记录每个顶点是否被访问过。0：未访问，1：已访问
/**
* @brief: 邻接矩阵的BFS递归算法
* @param G：指向图的指针
* @param i：遍历的顶点编号
* @return:	void
*/
void BFSTraverse(ALGraph* G) {
	Queue q;
	initQueue(&q);	// 初始化队列

	for (int i = 0; i < G->Nv; i++)		// 对每个点做循环，防止图不连通，有顶点没用被遍历
	{
		if (0 == visited[i])	// 该顶点尚未被访问
		{
			cout << G->adjList[i].data << "\t";
			visited[i] = 1;		// 打印后将访问标记位置1
			enQueue(&q, i);		// 将图的第一个顶点入队
			while (!queueEmpty(&q))
			{
				QElemType e;	// 接收出队元素
				deQueue(&q, &e);
				EdgeNode* edge = G->adjList[e].firstEdge;
				// 将该顶点的所有邻接点入队
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