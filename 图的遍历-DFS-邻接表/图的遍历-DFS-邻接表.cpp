#include <iostream>
using namespace std;

#define MAXVEX (100)		// 最大顶点数

int visited[MAXVEX] = { 0 };	// 辅助数组，标记顶点是否被访问

typedef char VertexType;	// 顶点类型，自定义
typedef int  WeightType;	// 边上权值类型，自定义

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
* @brief: 创建图的邻接表结构
* @param G：指向图的指针
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

		// 无向图的对阵操作
		e = new EdgeNode;
		e->adjvex = i;
		e->next = G->adjList[j].firstEdge;
		G->adjList[j].firstEdge = e;
	}
}

/**
* @brief: 销毁图的邻接表
* @param G：指向图的指针
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

/**
* @brief: 邻接表的DFS递归算法
* @param G: 指向图的指针
* @param i: 顶点下标
*/
void DFS(ALGraph* G, int i) {
	cout << G->adjList[i].data << "\t";
	visited[i] = 1;
	EdgeNode* p = G->adjList[i].firstEdge;
	while (p)
	{
		if (0 == visited[p->adjvex])
		{
			DFS(G, p->adjvex);
		}
		p = p->next;
	}
}

/**
* @brief: 邻接表的DFS递归算法
* @param G: 指向图的指针
*/
void DFSTraverse(ALGraph* G) {
	for (int i = 0; i < G->Nv; i++)
	{
		if (0 == visited[i])
		{
			DFS(G, i);
		}
	}
}

int main() {
	ALGraph* G = new ALGraph;
	createALGraph(G);
	
	DFSTraverse(G);

	destroyAdjList(G);

	delete G;
}