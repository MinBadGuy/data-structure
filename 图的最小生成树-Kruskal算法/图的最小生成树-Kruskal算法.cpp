#include <iostream>
using namespace std;

/**************************************************************************************
*********************************** ͼ�ı߼������ʾ ***********************************
***************************************************************************************/
typedef int	 WeightType;	// ����Ȩֵ���ͣ��Զ���
typedef char VertexType;	// �������ͣ��Զ���

#define MAXVEX	(100)	// ��󶥵���
#define MAXEDGE	(100)	// ������

/* �߼������Edge�ṹ���� */
typedef struct {
	int begin;		// �洢�ߵ�����±�
	int end;		// �洢�ߵ��յ��±�
	WeightType w;	// Ȩֵ
} Edge;

typedef struct {
	VertexType vexs[MAXVEX];	// ��������
	Edge edges[MAXEDGE];		// �߼�����
	int Nv, Ne;					// ������������
} EGraph;

/**
* @brief:	����ͼ�ı߼������ʾ
* @param G��ָ��ͼ��ָ��
* @return��	void
*/
void createEGraph(EGraph* G) {
	cout << "���붥�����ͱ�����";
	cin >> G->Nv >> G->Ne;

	cout << "���붥����Ϣ��";
	for (int i = 0; i < G->Nv; i++)
	{
		cin >> G->vexs[i];
	}

	// ����Ne������Ϣ�������߼�����
	int i, j;
	WeightType w;
	Edge e;
	for (int k = 0; k < G->Ne; k++)
	{
		cout << "�����(Vi, Vj)���±�i��j����Ȩֵw��";
		cin >> i >> j >> w;
		e.begin = i;
		e.end = j;
		e.w = w;
		G->edges[k] = e;
	}
}

/**
* @brief:	�Ա߼��������������(����ð������)
* @param G��ָ��ͼ��ָ��
* @return��	void
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
	// ��ӡ�����Ľ��
	for (int i = 0; i < G->Ne; i++)
	{
		cout << G->edges[i].w << "\t";
	}
	cout << endl;
	*/
}

/**************************************************************************************
******************************** ��С������֮Kruskal�㷨 ********************************
***************************************************************************************/
int parent[MAXVEX] = { 0 };		// �������飬�����жϱ�����Ƿ��γɻ�·

/**
* @brief:		 �������߶����β���±�
* @param parent: �����ж��Ƿ��γɻ�·������
* @param f:		 �����±�
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
* @brief:	��С������Kruskal�㷨
* @param G: ָ��ͼ��ָ��
* @return:  void
*/
void minSpanTreeKruskal(EGraph* G) {
	int n, m;
	for (int i = 0; i < G->Ne; i++)	// ѭ��ÿһ����
	{
		n = Find(parent, G->edges[i].begin);
		m = Find(parent, G->edges[i].end);
		if (n != m)	// ����n��m���ȣ�˵���˱�û���������������γɻ�·
		{
			parent[n] = m;	/* ���˱ߵĽ�β��������±�Ϊ����parent�У�
							   ��ʾ�˶����Ѿ���������������
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