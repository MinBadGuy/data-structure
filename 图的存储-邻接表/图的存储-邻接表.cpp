#include <iostream>
using namespace std;

typedef char VertexType;	// 顶点类型，自定义成char
typedef int  WeightType;	// 边上的权值类型，自定义成int

#define MAXVEX	 (100)		// 最大顶点数

/* 边表结点 */
typedef struct EdgeNode {
	int			adjvex;		// 邻接点域，存储该顶点对应的下标
	WeightType	weight;		// 权值域，存储顶点权值，非网图(无权图)不必定义
	EdgeNode	*next;		// 链域，指向下一个邻接点
} EdgeNode;

/* 顶点结点 */
typedef struct VertexNode {
	VertexType	data;			// 顶点域，存储顶点值
	EdgeNode	*firstEdge;		// 边表头指针，指向第一个邻接点
} VertexNode, AdjList[MAXVEX];	// AdjList表示邻接表类型

typedef struct {
	AdjList adjList;		// 邻接表，相当于：VertexNode adjList[MAXVEX];
	int Nv, Ne;				// 图中顶点数和边数
} ALGraph;

/* 建立图的邻接表结构 */
void createALGraph(ALGraph* G) {
	cout << "输入顶点数和边数：" << endl;
	cin >> G->Nv >> G->Ne;

	// 读入顶点信息
	cout << "输入顶点信息：" << endl;
	for (int i = 0; i < G->Nv; i++)
	{
		cin >> G->adjList[i].data;			// 读入顶点数值
		G->adjList[i].firstEdge = nullptr;	// 将边表指针置为空
	}

	// 读入Ne条边，建立邻接表
	int i, j;
	WeightType w;
	EdgeNode* e;
	for (int k = 0; k < G->Ne; k++)
	{
		cout << "输入边(vi, vj)的下标及i、j及权值w：" << endl;
		cin >> i >> j >> w;
		
		e = new EdgeNode;
		e->adjvex = j;						// 邻接点下标为j
		e->weight = w;						// 边(vi, vj)上的权值
		e->next = G->adjList[i].firstEdge;	// 将e的指针指向当前顶点指向的结点
		G->adjList[i].firstEdge = e;		// 将当前顶点的指针指向e
		/* 52、53这两行：使用头插法将结点插入链表中 */

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

ostream& operator<<(ostream& os, VertexNode vex) {
	os << vex.data;
	return os;
}

int main() {
	ALGraph* G = new ALGraph;
	// 建图
	createALGraph(G);

	// 打印顶点数组
	cout << "\n顶点数组" << endl;
	for (int i = 0; i < G->Nv; i++)
	{
		cout << G->adjList[i].data << "\t";
	}

	// 打印邻接表的值
	cout << "\n邻接表" << endl;
	for (int i = 0; i < G->Nv; i++)
	{
		cout << "顶点" << G->adjList[i].data << "的邻接点有：";
		EdgeNode* p = G->adjList[i].firstEdge;
		while (p)
		{
			cout << G->adjList[p->adjvex] << "(" << p->weight << ")" << "\t";
			p = p->next;
		}
		cout << endl;
	}

	// 销毁邻接表
	destroyAdjList(G);
	
	delete G;
}