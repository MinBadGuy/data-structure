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
********************************* ��С������֮Prim�㷨 *********************************
***************************************************************************************/
void minSpanTreePrim(MGraph* G) {
	int adjvex[MAXVEX];
	WeightType lowcost[MAXVEX];	/* ������ض����ߵ�Ȩֵ
								   ��lowcost[i]��ֵΪ0����ʾ�±�Ϊi�Ķ����ѱ�������������
								*/ 
	/* ��ʼ����������V0���㿪ʼ������С������ */

	adjvex[0] = 0;		// ��ʼ����һ��������±�Ϊ0
	lowcost[0] = 0;		// ��lowcost[0]��ʼ��Ϊ0����������V0����������
	for (int i = 1; i < G->Nv; i++)
	{
		lowcost[i] = G->arcs[0][i];	// ��V0�����ڽӵ�֮��ı���Ȩֵ����lowcost����
		adjvex[i] = 0;				// ����ʼ��ΪV0���±�
	}

	for (int i = 1; i < G->Nv; i++)	// ����ѭ����1��ʼ����Ϊ��������n-1����
	{
		WeightType minVal = INFINITY;	// ��¼��СȨֵ����ʼ��ΪINFINITY
		int minIdx;						// ��¼��СȨֵ�����±�
		for (int j = 0; j < G->Nv; j++)
		{
			if (lowcost[j] != 0 && lowcost[j] < minVal) {
				minVal = lowcost[j];
				minIdx = j;
			}
		}	// �ҵ�Ȩֵ��С�Ķ����±�

		cout << "(" << adjvex[minIdx] << ", " << minIdx << ")" << endl;	/* ��ӡ��ǰ������Ȩֵ��С�ı�
																		   Ҳ������С�������е�һ����
																		*/ 
		lowcost[minIdx] = 0;	// ����ǰ�����Ȩֵ��Ϊ0����ʾ���ѱ�������������

		// ���±�ΪminIdx�Ķ�������������󣬸���lowcost����
		for (int k = 0; k < G->Nv; k++)
		{
			/*
			lowcost[k] != 0����ʾ�������Ѽ����������Ķ���
			G->arcs[minIdx][k]����ʾ����minIdx���ڽӵ�Vk��Ȩֵ
			G->arcs[minIdx][k] < lowcost[k]�����ڽӵ��ȨֵС�ڵ�ǰlowcost[k]��ֵ������Ҫ����lowcost[k]
			*/
			if (lowcost[k] != 0 && G->arcs[minIdx][k] < lowcost[k]) {
				lowcost[k] = G->arcs[minIdx][k];
				adjvex[k] = minIdx;
			}
		}
	}
}

int main() {
	MGraph* G = new MGraph;
	createMGraph(G);

	minSpanTreePrim(G);

	delete G;
}