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
********************************* 最短路径之Dijkstra算法 *********************************
***************************************************************************************/

typedef int Patharc[MAXVEX];		// 用于存储最短路径下标(前驱顶点的下标)的数组
typedef int ShortPathTable[MAXVEX];	// 用于存储到各点最短路径的权值和

/**
* @brief:	Dijkstra算法，求v0顶点到其余顶点v的最短路径P[v]及带权长度D[v]
*			P[v]的值为前驱顶点下标，D[v]表示v0到v的最短路径权值和
* @param G: 图
* @param v0:顶点v0下标
* @param P:	记录最短路径下标的数组
* @param D:	记录最短路径权值和的数组
* @return: void
*/
void ShortestPath_Dijkstra(MGraph G, int v0, Patharc P, ShortPathTable D)
{
	/* 初始化 P、D、辅助状态数组final */
	int v, w, k, min;
	int final[MAXVEX];	// final[w]=1表示已经求得v0值vw的最短路径
	for (v = 0; v < G.Nv; v++)
	{
		final[v] = 0;			// 全部顶点初始化为未知最短路径状态
		P[v] = 0;				// 初始化路径数组P为0
		D[v] = G.arcs[v0][v];	// 初始化路径权值和数组D为v0至各其余顶点v的权值
	}
	
	D[v0] = 0;		// v0至v0的路径长度为0，实际可不用，因为上面for循环已将其赋值0
	final[v0] = 1;	// v0至v0不需要求路径

	/* 主循环，每次求得v0到某个v顶点的最短路径 */
	for (v = 0; v < G.Nv; v++)
	{
		min = INFINITY;
		for (w = 0; w < G.Nv; w++)
		{
			if (!final[w] && D[w] < min)
			{
				min = D[w];		// w顶点离v0顶点更近
				k = w;			// 记录w顶点
			}
		}
		
		final[k] = 1;			// 将目前找到的最近顶点对应的final位置处置1
		for (w = 0; w < G.Nv; w++)
		{
			// 如果经过k顶点的路径比现在这条路径长度短的话，更新D[w]和P[w]
			if (!final[w] && min + G.arcs[k][w] < D[w])
			{
				D[w] = min + G.arcs[k][w];
				P[w] = k;
			}
		}
	}
}


int main()
{
	MGraph* G = new MGraph;
	createMGraph(G);

	Patharc P;
	ShortPathTable D;
	ShortestPath_Dijkstra(*G, 0, P, D);

	cout << "\n数组P: " << endl;
	for (size_t i = 0; i < G->Nv; i++)
	{
		cout << P[i] << "\t";
	}

	cout << "\n数组D: " << endl;
	for (size_t i = 0; i < G->Nv; i++)
	{
		cout << D[i] << "\t";
	}

	delete G;
}