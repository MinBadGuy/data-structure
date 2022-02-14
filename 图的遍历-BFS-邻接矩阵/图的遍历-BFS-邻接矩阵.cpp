#include <iostream>
using namespace std;

/**************************************************************************************
*********************************** 图结构定义及操作 *********************************** 
***************************************************************************************/
typedef char VertexType;	// 顶点类型，自定义
typedef int  WeightType;	// 边上权值类型，自定义

#define MAXVEX (100)		// 最大顶点数

typedef struct {
	VertexType vexs[MAXVEX];			// 顶点数组
	WeightType arcs[MAXVEX][MAXVEX];	// 邻接矩阵
	int Nv, Ne;							// 顶点数、边数
} MGraph;

/**
* @brief:	建立图的邻接矩阵结构
* @param G：指向图的指针
*/
void createMGraph(MGraph* G) {
	cout << "输入顶点数和边数：";
	cin >> G->Nv >> G->Ne;

	// 初始化邻接矩阵
	for (int i = 0; i < G->Nv; i++)
	{
		for (int j = 0; j < G->Nv; j++)
		{
			G->arcs[i][j] = 0;	// 无权图的邻接矩阵全部初始化为0，表示没有边
		}
	}

	cout << "输入顶点信息：";
	for (int i = 0; i < G->Nv; i++)
	{
		cin >> G->vexs[i];
	}

	// 读入Ne条边信息，建立邻接矩阵
	int i, j;
	for (int k = 0; k < G->Ne; k++)
	{
		cout << "输入边(Vi, Vj)的下标i、j：";
		cin >> i >> j;
		G->arcs[i][j] = 1;
		G->arcs[j][i] = G->arcs[i][j];	// 无向图的邻接矩阵为对称阵
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
*/
void BFSTraverse(MGraph* G) {
	Queue q;
	initQueue(&q);	// 初始化队列

	for (int i = 0; i < G->Nv; i++)		// 对每个点做循环，防止图不连通，有顶点没用被遍历
	{
		if (0 == visited[i])	// 该顶点尚未被访问
		{
			cout << G->vexs[i] << "\t";
			visited[i] = 1;		// 打印后将访问标记位置1
			enQueue(&q, i);		// 将图的第一个顶点入队
			while (!queueEmpty(&q))
			{
				QElemType e;	// 接收出队元素
				deQueue(&q, &e);

				// 将该顶点的所有邻接点入队
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