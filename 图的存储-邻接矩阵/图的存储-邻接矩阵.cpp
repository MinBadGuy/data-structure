#include <iostream>
using namespace std;

typedef char VertexType;	// 顶点类型，自定义成char
typedef int  WeightType;	// 边上的权值类型，自定义成int

#define MAXVEX	 (100)		// 最大顶点数
#define INFINITY (65535)	// 用65535表示∞，表示顶点之间没有边

typedef struct {
	VertexType vexs[MAXVEX];			// 顶点数组
	WeightType arcs[MAXVEX][MAXVEX];	// 邻接矩阵，二维矩阵，记录顶点间的连接情况，即边表
	int Nv, Ne;							// 图中顶点数和边数
} MGraph;

/* 建立图的邻接矩阵结构 */
void createMGraph(MGraph* G) {
	cout << "输入顶点数和边数：" << endl;
	cin >> G->Nv >> G->Ne;

	// 将邻接矩阵所有元素初始化为：INFINITY
	for (int i = 0; i < G->Nv; i++)
	{
		for (int j = 0; j < G->Nv; j++)
		{
			if (i == j)
			{
				G->arcs[i][j] = 0;	// 主对角线初始化为0
			}
			else
			{
				G->arcs[i][j] = INFINITY;
			}	
		}
	}

	cout << "输入顶点信息：" << endl;
	for (int i = 0; i < G->Nv; i++)
	{
		cin >> G->vexs[i];
	}

	// 读入Ne条边，建立邻接矩阵
	int i, j;
	WeightType w;
	for (int k = 0; k < G->Ne; k++)
	{
		cout << "输入边(vi, vj)的下标i、j及权值w：" << endl;
		cin >> i >> j >> w;
		G->arcs[i][j] = w;
		// G->arcs[j][i] = G->arcs[i][j];	// 无向图的邻接矩阵是对称阵，若G是有向图则不需要这行
	}
}

int main() {
	MGraph* G = new MGraph;
	createMGraph(G);

	// 打印顶点数组
	cout << "\n顶点数组" << endl;
	for (int i = 0; i < G->Nv; i++)
	{
		cout << G->vexs[i] << "\t";
	}

	// 打印邻接矩阵的值
	cout << "\n邻接矩阵" << endl;
	for (int i = 0; i < G->Nv; i++)
	{
		for (int j = 0; j < G->Nv; j++)
		{
			cout << G->arcs[i][j] << "\t";
		}
		cout << endl;
	}

	delete G;
}