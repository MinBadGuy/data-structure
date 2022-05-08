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
********************************* 最短路径之Floyd算法 **********************************
***************************************************************************************/
typedef int Pathmatrix[MAXVEX][MAXVEX];
typedef int ShortPathTable[MAXVEX][MAXVEX];

/**
@brief:		Floyd算法，求图G中各顶点v到其余顶点w最短路径P[v][w]及带权长度D[v][w]
@param G:	图
@param P:	记录最短路径下标的二维数组
@param D:	记录最短路径权值和的二维数组
#return:	void
*/
void ShortestPath_Floyd(MGraph G, Pathmatrix P, ShortPathTable D)
{
	int v, w, k;
	/* 初始化P和D */
	for (v = 0; v < G.Nv; v++)
	{
		for (w = 0; w < G.Nv; w++)
		{
			D[v][w] = G.arcs[v][w];		// 初始化为邻接矩阵对应的权值
			P[v][w] = w;
		}
	}

	/* 算法主循环 */
	for (k = 0; k < G.Nv; k++)
	{
		for (v = 0; v < G.Nv; v++)
		{
			for (w = 0; w < G.Nv; w++)
			{	
				// 如果经过下标为k的顶点路径比原两点间路径更短，更新
				if (D[v][w] > D[v][k] + D[k][w])
				{
					D[v][w] = D[v][k] + D[k][w];
					P[v][w] = P[v][k];		// 路径设置经过下标为k的顶点
				}
			}
		}
	}
}

int main()
{
	MGraph* G = new MGraph;
	createMGraph(G);

	Pathmatrix P;
	ShortPathTable D;
	ShortestPath_Floyd(*G, P, D);

	cout << "\n数组P: " << endl;
	for (size_t i = 0; i < G->Nv; i++)
	{
		for (size_t j = 0; j < G->Nv; j++)
		{
			cout << P[i][j] << "\t";
		}
		cout << endl;
	}

	cout << "\n数组D: " << endl;
	for (size_t i = 0; i < G->Nv; i++)
	{
		for (size_t j = 0; j < G->Nv; j++)
		{
			cout << D[i][j] << "\t";
		}
		cout << endl;
	}

	delete G;
}