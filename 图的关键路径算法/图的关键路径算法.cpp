#include <iostream>
using namespace std;

/**************************************************************************************
******************************** 图的邻接表结构定义及操作 ********************************
***************************************************************************************/
typedef char VertexType;	// 顶点类型，自定义成char
typedef int  WeightType;	// 边上的权值类型，自定义成int

#define MAXVEX	 (100)		// 最大顶点数

/* 边表结点 */
typedef struct EdgeNode {
	int			adjvex;		// 邻接点域，存储该顶点对应的下标
	WeightType	weight;		// 权值域，存储顶点权值，非网图(无权图)不必定义
	EdgeNode* next;			// 链域，指向下一个邻接点
} EdgeNode;

/* 顶点结点 */
typedef struct VertexNode {
	int in;						// 顶点入度
	VertexType	data;			// 顶点域，存储顶点值
	EdgeNode* firstEdge;		// 边表头指针，指向第一个邻接点
} VertexNode, AdjList[MAXVEX];	// AdjList表示邻接表类型

typedef struct {
	AdjList adjList;		// 邻接表，相当于：VertexNode adjList[MAXVEX];
	int Nv, Ne;				// 图中顶点数和边数
} ALGraph;

/* 建立图的邻接表结构 */
void createALGraph(ALGraph* G) {
	cout << "输入顶点数和边数：";
	cin >> G->Nv >> G->Ne;

	// 读入顶点信息
	for (int i = 0; i < G->Nv; i++)
	{
		cout << "输入顶点数据及其入度：";
		cin >> G->adjList[i].data;			// 读入顶点数值
		cin >> G->adjList[i].in;			// 读入顶点入度
		G->adjList[i].firstEdge = nullptr;	// 将边表指针置为空
	}

	// 读入Ne条边，建立邻接表
	int i, j;
	WeightType w;
	EdgeNode* e;
	for (int k = 0; k < G->Ne; k++)
	{
		cout << "输入边(vi, vj)的下标i、j及权值w：";
		cin >> i >> j >> w;
		
		/*
		cout << "输入边(vi, vj)的下标i、j：";
		cin >> i >> j;
		*/

		e = new EdgeNode;
		e->adjvex = j;						// 邻接点下标为j
		e->weight = w;						// 边(vi, vj)上的权值
		e->next = G->adjList[i].firstEdge;	// 将e的next指针指向当前顶点firstEdge指向的结点
		G->adjList[i].firstEdge = e;		// 将当前顶点的firstEdge指针指向e
		/* 上面两行：使用头插法将结点插入链表中 */

		// 以下为无向图需要部分，有向图不需要 
		/*e = new EdgeNode;
		e->adjvex = i;
		e->weight = w;
		e->next = G->adjList[j].firstEdge;
		G->adjList[j].firstEdge = e;*/
	}
}

/* 销毁邻接表 */
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

/* 全局变量 */
WeightType* etv, * ltv;	// 事件最早发生时间和最迟发生时间数组
int* stack2;			// 用于存储拓扑序列的栈
int top2;				// 用于stack2的栈顶指针

/**************************************************************************************
*************************************** 拓扑排序 ***************************************
***************************************************************************************/
/**
* @brief:	拓扑排序，若G无回路，则输出拓扑排序序列并返回0，若有回路返回-1
* @param G:	邻接表表示的图指针
* @return:	0 —— 成功
*			-1 —— 失败
*/
int TopologicalSort(ALGraph* G)
{
	EdgeNode* e;
	int i, k, gettop;
	int top = -1;	// 用于栈指针下标
	int count = 0;	// 用于统计输出顶点的个数
	int* stack;		// 建栈存储入度为0的顶点
	stack = new int[G->Nv];

	for (i = 0; i < G->Nv; i++)
	{
		if (G->adjList[i].in == 0)
		{
			stack[++top] = i;	// 将入度为0的顶点入栈
		}
	}

	/* 全局变量初始化 */
	top2 = -1;
	stack2 = new int[G->Nv];
	etv = new WeightType[G->Nv];	// 事件最早发生时间全部初始化尾0
	for (size_t i = 0; i < G->Nv; i++)
	{
		etv[i] = 0;
	}

	while (top != -1)
	{
		gettop = stack[top--];		// 出栈
		stack2[++top2] = gettop;	// 将弹出的顶点序号压入拓扑序列的栈
		count++;

		/* 遍历该顶点对应的边表 */
		for (e = G->adjList[gettop].firstEdge; e; e = e->next)
		{
			k = e->adjvex;
			G->adjList[k].in--;			// 将k号顶点的入度减1
			if (G->adjList[k].in == 0)	// 若入度为0，入栈
			{
				stack[++top] = k;
			}

			if (etv[gettop] + e->weight > etv[k])	// 求各顶点事件最早发生时间
			{
				etv[k] = etv[gettop] + e->weight;
			}
		}

	}

	delete[] stack;			// 释放分配的内存

	if (count < G->Nv)		// 如果count小于顶点数，说明存在环
	{
		return -1;
	}
	else
	{
		return 0;
	}
}

/**************************************************************************************
*************************************** 关键路径 ***************************************
***************************************************************************************/
/**
* @brief:		关键路径
* @param G:		邻接表表示的图指针
* @return:		void
*/
void CriticalPath(ALGraph* G)
{
	TopologicalSort(G);				// 拓扑排序，计算数组etv和stack2
	ltv = new WeightType[G->Nv];	// 事件最晚发生时间，初始化为拓扑序列最后一个顶点的最早发生时间
	for (size_t i = 0; i < G->Nv; i++)
	{
		ltv[i] = etv[G->Nv - 1];
	}
	
	/* 求ltv */
	int gettop2, k;
	EdgeNode* e;
	while (top2 != -1)	// stack2不空
	{
		gettop2 = stack2[top2--];	// 拓扑序列出栈，后进先出，相当于将拓扑序列从尾至头遍历
		for (e = G->adjList[gettop2].firstEdge; e; e = e->next)
		{
			k = e->adjvex;
			if (ltv[k] - e->weight < ltv[gettop2])	// 求各顶点事件最晚发生事件
			{
				ltv[gettop2] = ltv[k] - e->weight;
			}
		}
	}
	
	cout << "stack2: ";
	for (size_t i = 0; i < G->Nv; i++)
	{
		cout << stack2[i] << "\t";
	}
	cout << "\netv: ";
	for (size_t i = 0; i < G->Nv; i++)
	{
		cout << etv[i] << "\t";
	}
	cout << "\nltv: ";
	for (size_t i = 0; i < G->Nv; i++)
	{
		cout << ltv[i] << "\t";
	}

	cout << "\ncritical path: ";
	WeightType ete, lte;					// 声明活动最早发生时间和最迟发生时间
	for (size_t j = 0; j < G->Nv; j++)		// 求 ete、lte，关键路径
	{
		for (e = G->adjList[j].firstEdge; e; e = e->next)
		{
			k = e->adjvex;
			ete = etv[j];				// 活动最早发生时间
			lte = ltv[k] - e->weight;	// 活动最迟发生时间
			if (ete == lte)				// 两者相等即在关键路径上		
			{
				cout << "<V" << j << ",V" << k << "> " << e->weight << "\t";
			}
		}
	}
}

int main()
{
	ALGraph* G = new ALGraph;
	// 建图
	createALGraph(G);

	// 关键路径
	CriticalPath(G);

	// 销毁邻接表
	destroyAdjList(G);

	delete G;
	delete[] etv;
	delete[] ltv;
	delete[] stack2;
}