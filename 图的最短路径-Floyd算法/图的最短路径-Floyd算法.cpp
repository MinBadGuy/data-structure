#include <iostream>
using namespace std;

/**************************************************************************************
*********************************** ͼ�ṹ���弰���� ***********************************
***************************************************************************************/
typedef char VertexType;	// �������ͣ��Զ���
typedef int  WeightType;	// ����Ȩֵ���ͣ��Զ���

#define MAXVEX		(100)	// ��󶥵���
#define INFINITY	(65535)	// ��65535��ʾ�ޣ���ʾ����֮��û�б�

typedef struct {
	VertexType vexs[MAXVEX];			// ��������
	WeightType arcs[MAXVEX][MAXVEX];	// �ڽӾ���
	int Nv, Ne;							// ������������
} MGraph;

/**
* @brief:	����ͼ���ڽӾ���ṹ
* @param G��ָ��ͼ��ָ��
* @return:	void
*/
void createMGraph(MGraph* G) {
	cout << "���붥�����ͱ�����";
	cin >> G->Nv >> G->Ne;

	// ��ʼ���ڽӾ���
	for (int i = 0; i < G->Nv; i++)
	{
		for (int j = 0; j < G->Nv; j++)
		{
			G->arcs[i][j] = (i == j) ? 0 : INFINITY;	// �ڽӾ������Խ��߳�ʼ��Ϊ0�������ʼ��ΪINFINITY
		}
	}

	cout << "���붥����Ϣ��";
	for (int i = 0; i < G->Nv; i++)
	{
		cin >> G->vexs[i];
	}

	// ����Ne������Ϣ�������ڽӾ���
	int i, j;
	WeightType w;
	for (int k = 0; k < G->Ne; k++)
	{
		cout << "�����(Vi, Vj)���±�i��j����Ȩֵw��";
		cin >> i >> j >> w;
		G->arcs[i][j] = w;
		G->arcs[j][i] = G->arcs[i][j];	// ����ͼ���ڽӾ���Ϊ�Գ���
	}
}

/**************************************************************************************
********************************* ���·��֮Floyd�㷨 **********************************
***************************************************************************************/
typedef int Pathmatrix[MAXVEX][MAXVEX];
typedef int ShortPathTable[MAXVEX][MAXVEX];

/**
@brief:		Floyd�㷨����ͼG�и�����v�����ඥ��w���·��P[v][w]����Ȩ����D[v][w]
@param G:	ͼ
@param P:	��¼���·���±�Ķ�ά����
@param D:	��¼���·��Ȩֵ�͵Ķ�ά����
#return:	void
*/
void ShortestPath_Floyd(MGraph G, Pathmatrix P, ShortPathTable D)
{
	int v, w, k;
	/* ��ʼ��P��D */
	for (v = 0; v < G.Nv; v++)
	{
		for (w = 0; w < G.Nv; w++)
		{
			D[v][w] = G.arcs[v][w];		// ��ʼ��Ϊ�ڽӾ����Ӧ��Ȩֵ
			P[v][w] = w;
		}
	}

	/* �㷨��ѭ�� */
	for (k = 0; k < G.Nv; k++)
	{
		for (v = 0; v < G.Nv; v++)
		{
			for (w = 0; w < G.Nv; w++)
			{	
				// ��������±�Ϊk�Ķ���·����ԭ�����·�����̣�����
				if (D[v][w] > D[v][k] + D[k][w])
				{
					D[v][w] = D[v][k] + D[k][w];
					P[v][w] = P[v][k];		// ·�����þ����±�Ϊk�Ķ���
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

	cout << "\n����P: " << endl;
	for (size_t i = 0; i < G->Nv; i++)
	{
		for (size_t j = 0; j < G->Nv; j++)
		{
			cout << P[i][j] << "\t";
		}
		cout << endl;
	}

	cout << "\n����D: " << endl;
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