#include <iostream>
using namespace std;

typedef char VertexType;	// �������ͣ��Զ����char
typedef int  WeightType;	// ���ϵ�Ȩֵ���ͣ��Զ����int

#define MAXVEX	 (100)		// ��󶥵���

/* �߱��� */
typedef struct EdgeNode {
	int			adjvex;		// �ڽӵ��򣬴洢�ö����Ӧ���±�
	WeightType	weight;		// Ȩֵ�򣬴洢����Ȩֵ������ͼ(��Ȩͼ)���ض���
	EdgeNode	*next;		// ����ָ����һ���ڽӵ�
} EdgeNode;

/* ������ */
typedef struct VertexNode {
	VertexType	data;			// �����򣬴洢����ֵ
	EdgeNode	*firstEdge;		// �߱�ͷָ�룬ָ���һ���ڽӵ�
} VertexNode, AdjList[MAXVEX];	// AdjList��ʾ�ڽӱ�����

typedef struct {
	AdjList adjList;		// �ڽӱ��൱�ڣ�VertexNode adjList[MAXVEX];
	int Nv, Ne;				// ͼ�ж������ͱ���
} ALGraph;

/* ����ͼ���ڽӱ�ṹ */
void createALGraph(ALGraph* G) {
	cout << "���붥�����ͱ�����" << endl;
	cin >> G->Nv >> G->Ne;

	// ���붥����Ϣ
	cout << "���붥����Ϣ��" << endl;
	for (int i = 0; i < G->Nv; i++)
	{
		cin >> G->adjList[i].data;			// ���붥����ֵ
		G->adjList[i].firstEdge = nullptr;	// ���߱�ָ����Ϊ��
	}

	// ����Ne���ߣ������ڽӱ�
	int i, j;
	WeightType w;
	EdgeNode* e;
	for (int k = 0; k < G->Ne; k++)
	{
		cout << "�����(vi, vj)���±꼰i��j��Ȩֵw��" << endl;
		cin >> i >> j >> w;
		
		e = new EdgeNode;
		e->adjvex = j;						// �ڽӵ��±�Ϊj
		e->weight = w;						// ��(vi, vj)�ϵ�Ȩֵ
		e->next = G->adjList[i].firstEdge;	// ��e��ָ��ָ��ǰ����ָ��Ľ��
		G->adjList[i].firstEdge = e;		// ����ǰ�����ָ��ָ��e
		/* 52��53�����У�ʹ��ͷ�巨�������������� */

		// ����Ϊ����ͼ��Ҫ���֣�����ͼ����Ҫ 
		/*e = new EdgeNode;
		e->adjvex = i;
		e->weight = w;
		e->next = G->adjList[j].firstEdge;
		G->adjList[j].firstEdge = e;*/
	}
}

/* �����ڽӱ� */
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
	// ��ͼ
	createALGraph(G);

	// ��ӡ��������
	cout << "\n��������" << endl;
	for (int i = 0; i < G->Nv; i++)
	{
		cout << G->adjList[i].data << "\t";
	}

	// ��ӡ�ڽӱ��ֵ
	cout << "\n�ڽӱ�" << endl;
	for (int i = 0; i < G->Nv; i++)
	{
		cout << "����" << G->adjList[i].data << "���ڽӵ��У�";
		EdgeNode* p = G->adjList[i].firstEdge;
		while (p)
		{
			cout << G->adjList[p->adjvex] << "(" << p->weight << ")" << "\t";
			p = p->next;
		}
		cout << endl;
	}

	// �����ڽӱ�
	destroyAdjList(G);
	
	delete G;
}