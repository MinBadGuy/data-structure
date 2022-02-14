#include <iostream>
using namespace std;

/**************************************************************************************
*********************************** 图结构定义及操作 ***********************************
***************************************************************************************/
typedef char VertexType;	// 顶点类型，自定义
typedef int  WeightType;	// 边上权值类型，自定义

#define MAXVEX		(100)	// 最大顶点数
#define INFINITY	(65535)	// 用65535表示∞，表示顶点之间没有边

typedef struct {
	VertexType vexs[MAXVEX];			// 顶点数组
	WeightType arcs[MAXVEX][MAXVEX];	// 邻接矩阵
	int Nv, Ne;							// 顶点数、边数
} MGraph;

/**
* @brief:	建立图的邻接矩阵结构
* @param G：指向图的指针
* @return:	void
*/
void createMGraph(MGraph* G) {
	cout << "输入顶点数和边数：";
	cin >> G->Nv >> G->Ne;

	// 初始化邻接矩阵
	for (int i = 0; i < G->Nv; i++)
	{
		for (int j = 0; j < G->Nv; j++)
		{
			G->arcs[i][j] = (i == j) ? 0 : INFINITY;	// 邻接矩阵主对角线初始化为0，其余初始化为INFINITY
		}
	}

	cout << "输入顶点信息：";
	for (int i = 0; i < G->Nv; i++)
	{
		cin >> G->vexs[i];
	}

	// 读入Ne条边信息，建立邻接矩阵
	int i, j;
	WeightType w;
	for (int k = 0; k < G->Ne; k++)
	{
		cout << "输入边(Vi, Vj)的下标i、j及其权值w：";
		cin >> i >> j >> w;
		G->arcs[i][j] = w;
		G->arcs[j][i] = G->arcs[i][j];	// 无向图的邻接矩阵为对称阵
	}
}

/**************************************************************************************
********************************* 最小生成树之Prim算法 *********************************
***************************************************************************************/
void minSpanTreePrim(MGraph* G) {
	int adjvex[MAXVEX];
	WeightType lowcost[MAXVEX];	/* 保存相关顶点间边的权值
								   若lowcost[i]的值为0，表示下标为i的顶点已被纳入生成树中
								*/ 
	/* 初始化操作，从V0顶点开始构建最小生成树 */

	adjvex[0] = 0;		// 初始化第一个顶点的下标为0
	lowcost[0] = 0;		// 将lowcost[0]初始化为0，即将顶点V0纳入生成树
	for (int i = 1; i < G->Nv; i++)
	{
		lowcost[i] = G->arcs[0][i];	// 将V0与其邻接点之间的边上权值存入lowcost数组
		adjvex[i] = 0;				// 均初始化为V0的下标
	}

	for (int i = 1; i < G->Nv; i++)	// 这里循环从1开始，因为生成树有n-1条边
	{
		WeightType minVal = INFINITY;	// 记录最小权值，初始化为INFINITY
		int minIdx;						// 记录最小权值顶点下标
		for (int j = 0; j < G->Nv; j++)
		{
			if (lowcost[j] != 0 && lowcost[j] < minVal) {
				minVal = lowcost[j];
				minIdx = j;
			}
		}	// 找到权值最小的顶点下标

		cout << "(" << adjvex[minIdx] << ", " << minIdx << ")" << endl;	/* 打印当前顶点中权值最小的边
																		   也就是最小生成树中的一条边
																		*/ 
		lowcost[minIdx] = 0;	// 将当前顶点的权值置为0，表示它已被纳入生成树中

		// 将下标为minIdx的顶点加入生成树后，更新lowcost数组
		for (int k = 0; k < G->Nv; k++)
		{
			/*
			lowcost[k] != 0：表示不考虑已加入生成树的顶点
			G->arcs[minIdx][k]：表示顶点minIdx的邻接点Vk的权值
			G->arcs[minIdx][k] < lowcost[k]：若邻接点的权值小于当前lowcost[k]的值，则需要更新lowcost[k]
			*/
			if (lowcost[k] != 0 && G->arcs[minIdx][k] < lowcost[k]) {
				lowcost[k] = G->arcs[minIdx][k];
				adjvex[k] = minIdx;
			}
		}
	}
}

int main() {
	MGraph* G = new MGraph;
	createMGraph(G);

	minSpanTreePrim(G);

	delete G;
}