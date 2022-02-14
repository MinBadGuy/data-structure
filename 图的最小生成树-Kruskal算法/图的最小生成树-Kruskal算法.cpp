#include <iostream>
using namespace std;

/**************************************************************************************
*********************************** 图的边集数组表示 ***********************************
***************************************************************************************/
typedef int	 WeightType;	// 边上权值类型，自定义
typedef char VertexType;	// 顶点类型，自定义

#define MAXVEX	(100)	// 最大顶点数
#define MAXEDGE	(100)	// 最大边数

/* 边集数组的Edge结构定义 */
typedef struct {
	int begin;		// 存储边的起点下标
	int end;		// 存储边的终点下标
	WeightType w;	// 权值
} Edge;

typedef struct {
	VertexType vexs[MAXVEX];	// 顶点数组
	Edge edges[MAXEDGE];		// 边集数组
	int Nv, Ne;					// 顶点数，边数
} EGraph;

/**
* @brief:	创建图的边集数组表示
* @param G：指向图的指针
* @return：	void
*/
void createEGraph(EGraph* G) {
	cout << "输入顶点数和边数：";
	cin >> G->Nv >> G->Ne;

	cout << "输入顶点信息：";
	for (int i = 0; i < G->Nv; i++)
	{
		cin >> G->vexs[i];
	}

	// 读入Ne条边信息，建立边集数组
	int i, j;
	WeightType w;
	Edge e;
	for (int k = 0; k < G->Ne; k++)
	{
		cout << "输入边(Vi, Vj)的下标i、j及其权值w：";
		cin >> i >> j >> w;
		e.begin = i;
		e.end = j;
		e.w = w;
		G->edges[k] = e;
	}
}

/**
* @brief:	对边集合数组进行排序(采用冒泡排序)
* @param G：指向图的指针
* @return：	void
*/
void edgesSort(EGraph* G) {
	for (int i = 1; i < G->Ne; i++)
	{
		for (int j = 0; j < G->Ne - i; j++)
		{
			if (G->edges[j].w > G->edges[j+1].w)
			{
				Edge e = G->edges[j];
				G->edges[j] = G->edges[j + 1];
				G->edges[j + 1] = e;
			}
		}
	}

	/*
	// 打印排序后的结果
	for (int i = 0; i < G->Ne; i++)
	{
		cout << G->edges[i].w << "\t";
	}
	cout << endl;
	*/
}

/**************************************************************************************
******************************** 最小生成树之Kruskal算法 ********************************
***************************************************************************************/
int parent[MAXVEX] = { 0 };		// 辅助数组，用来判断边与边是否形成环路

/**
* @brief:		 查找连线顶点的尾部下标
* @param parent: 用来判断是否形成回路的数组
* @param f:		 顶点下标
* @return:		 int
*/
int Find(int* parent, int f) {
	while (parent[f] > 0)
	{
		f = parent[f];
	}
	return f;
}

/**
* @brief:	最小生成树Kruskal算法
* @param G: 指向图的指针
* @return:  void
*/
void minSpanTreeKruskal(EGraph* G) {
	int n, m;
	for (int i = 0; i < G->Ne; i++)	// 循环每一条边
	{
		n = Find(parent, G->edges[i].begin);
		m = Find(parent, G->edges[i].end);
		if (n != m)	// 假如n与m不等，说明此边没有与现有生成树形成环路
		{
			parent[n] = m;	/* 将此边的结尾顶点放入下标为起点的parent中，
							   表示此顶点已经在生成树集合中
							*/
			cout << "(" << G->edges[i].begin << ", " << G->edges[i].end << ")\t" 
				 << G->edges[i].w << endl;
		}
	}
}

int main() {
	EGraph* G = new EGraph;
	createEGraph(G);
	edgesSort(G);

	minSpanTreeKruskal(G);

	delete G;
}