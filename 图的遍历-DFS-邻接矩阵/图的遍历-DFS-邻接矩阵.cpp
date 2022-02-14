#include <iostream>
using namespace std;

typedef char VertexType;	// 顶点类型，自定义
typedef int  WeightType;	// 边上权值类型，自定义

#define MAXVEX (100)		// 最大顶点数

int visited[MAXVEX] = { 0 };	// 辅助数组，记录每个顶点是否被访问过。0：未访问，1：已访问

typedef struct {
	VertexType vexs[MAXVEX];			// 顶点数组
	WeightType arcs[MAXVEX][MAXVEX];	// 邻接矩阵
	int Nv, Ne;							// 顶点数、边数
} MGraph;

/**
* @brief: 建立图的邻接矩阵结构
* @param：指向图的指针
*/
void createMGraph(MGraph* G) {
	cout << "输入顶点数和边数：";
	cin >> G->Nv >> G -> Ne;

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

/**
* @brief: 邻接矩阵的DFS递归算法
* @param G：指向图的指针
* @param i：遍历的顶点编号
*/
void DFS(MGraph* G, int i) {
	cout << G->vexs[i] << "\t";		// 打印顶点值
	visited[i] = 1;					// 更新visited数组
	for (int j = 0; j < G->Nv; j++)
	{
		if (G->arcs[i][j] == 1 && visited[j] == 0)	// 对未访问过的邻接点递归调用DFS
		{
			DFS(G, j);
		}
	}
}

/**
* @brief: DFS的主控函数
* @param：指向图的指针
*/
void DFSTraverse(MGraph* G) {
	for (int i = 0; i < G->Nv; i++)	// 对图的每个顶点DFS，防止图不连通，有顶点没用被遍历
	{
		if (0 == visited[i])
		{
			DFS(G, i);
		}
	}
}

int main() {
	MGraph* G = new MGraph;
	createMGraph(G);

	DFSTraverse(G);
	
	delete G;
}