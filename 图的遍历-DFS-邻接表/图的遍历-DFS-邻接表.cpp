#include <iostream>
using namespace std;

#define MAXVEX (100)		// ��󶥵���

int visited[MAXVEX] = { 0 };	// �������飬��Ƕ����Ƿ񱻷���

typedef char VertexType;	// �������ͣ��Զ���
typedef int  WeightType;	// ����Ȩֵ���ͣ��Զ���

typedef struct EdgeNode {
	int		  adjvex;		// �ڽӵ��򣬴洢�ö����Ӧ���±�
	EdgeNode* next;			// ����ָ����һ���ڽӵ�
	// WeightType	weight;		// Ȩֵ�򣬴洢���ϵ�Ȩֵ		��Ȩͼ����Ҫ
} EdgeNode;

typedef struct VertexNode {
	VertexType data;		// ������Ϣ
	EdgeNode* firstEdge;	// ָ���һ���ڽӵ�
} VertexNode, AdjList[MAXVEX];

typedef struct {
	AdjList adjList;	// �ڽӱ�
	int Nv, Ne;			// ������������
} ALGraph;

/**
* @brief: ����ͼ���ڽӱ�ṹ
* @param G��ָ��ͼ��ָ��
*/
void createALGraph(ALGraph* G) {
	cout << "���붥�����ͱ�����";
	cin >> G->Nv >> G->Ne;

	cout << "���붥����Ϣ��";
	for (int i = 0; i < G->Nv; i++)
	{
		cin >> G->adjList[i].data;			// ������Ϣ
		G->adjList[i].firstEdge = nullptr;	// �߱�ָ���ʼ��Ϊ��
	}

	int i, j;
	EdgeNode* e;
	for (int k = 0; k < G->Ne; k++)
	{
		cout << "�����(Vi, Vj)���±�i��j��";
		cin >> i >> j;
		e = new EdgeNode;
		e->adjvex = j;
		e->next = G->adjList[i].firstEdge;	// 1
		G->adjList[i].firstEdge = e;		// 2
		// 1��2������ͷ�巨

		// ����ͼ�Ķ������
		e = new EdgeNode;
		e->adjvex = i;
		e->next = G->adjList[j].firstEdge;
		G->adjList[j].firstEdge = e;
	}
}

/**
* @brief: ����ͼ���ڽӱ�
* @param G��ָ��ͼ��ָ��
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
* @brief: �ڽӱ��DFS�ݹ��㷨
* @param G: ָ��ͼ��ָ��
* @param i: �����±�
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
* @brief: �ڽӱ��DFS�ݹ��㷨
* @param G: ָ��ͼ��ָ��
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