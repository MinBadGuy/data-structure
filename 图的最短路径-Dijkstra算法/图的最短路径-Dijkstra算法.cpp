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
********************************* ���·��֮Dijkstra�㷨 *********************************
***************************************************************************************/

typedef int Patharc[MAXVEX];		// ���ڴ洢���·���±�(ǰ��������±�)������
typedef int ShortPathTable[MAXVEX];	// ���ڴ洢���������·����Ȩֵ��

/**
* @brief:	Dijkstra�㷨����v0���㵽���ඥ��v�����·��P[v]����Ȩ����D[v]
*			P[v]��ֵΪǰ�������±꣬D[v]��ʾv0��v�����·��Ȩֵ��
* @param G: ͼ
* @param v0:����v0�±�
* @param P:	��¼���·���±������
* @param D:	��¼���·��Ȩֵ�͵�����
* @return: void
*/
void ShortestPath_Dijkstra(MGraph G, int v0, Patharc P, ShortPathTable D)
{
	/* ��ʼ�� P��D������״̬����final */
	int v, w, k, min;
	int final[MAXVEX];	// final[w]=1��ʾ�Ѿ����v0ֵvw�����·��
	for (v = 0; v < G.Nv; v++)
	{
		final[v] = 0;			// ȫ�������ʼ��Ϊδ֪���·��״̬
		P[v] = 0;				// ��ʼ��·������PΪ0
		D[v] = G.arcs[v0][v];	// ��ʼ��·��Ȩֵ������DΪv0�������ඥ��v��Ȩֵ
	}
	
	D[v0] = 0;		// v0��v0��·������Ϊ0��ʵ�ʿɲ��ã���Ϊ����forѭ���ѽ��丳ֵ0
	final[v0] = 1;	// v0��v0����Ҫ��·��

	/* ��ѭ����ÿ�����v0��ĳ��v��������·�� */
	for (v = 0; v < G.Nv; v++)
	{
		min = INFINITY;
		for (w = 0; w < G.Nv; w++)
		{
			if (!final[w] && D[w] < min)
			{
				min = D[w];		// w������v0�������
				k = w;			// ��¼w����
			}
		}
		
		final[k] = 1;			// ��Ŀǰ�ҵ�����������Ӧ��finalλ�ô���1
		for (w = 0; w < G.Nv; w++)
		{
			// �������k�����·������������·�����ȶ̵Ļ�������D[w]��P[w]
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

	cout << "\n����P: " << endl;
	for (size_t i = 0; i < G->Nv; i++)
	{
		cout << P[i] << "\t";
	}

	cout << "\n����D: " << endl;
	for (size_t i = 0; i < G->Nv; i++)
	{
		cout << D[i] << "\t";
	}

	delete G;
}