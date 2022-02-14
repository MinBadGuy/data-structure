#include <iostream>
using namespace std;

typedef char VertexType;	// �������ͣ��Զ����char
typedef int  WeightType;	// ���ϵ�Ȩֵ���ͣ��Զ����int

#define MAXVEX	 (100)		// ��󶥵���
#define INFINITY (65535)	// ��65535��ʾ�ޣ���ʾ����֮��û�б�

typedef struct {
	VertexType vexs[MAXVEX];			// ��������
	WeightType arcs[MAXVEX][MAXVEX];	// �ڽӾ��󣬶�ά���󣬼�¼������������������߱�
	int Nv, Ne;							// ͼ�ж������ͱ���
} MGraph;

/* ����ͼ���ڽӾ���ṹ */
void createMGraph(MGraph* G) {
	cout << "���붥�����ͱ�����" << endl;
	cin >> G->Nv >> G->Ne;

	// ���ڽӾ�������Ԫ�س�ʼ��Ϊ��INFINITY
	for (int i = 0; i < G->Nv; i++)
	{
		for (int j = 0; j < G->Nv; j++)
		{
			if (i == j)
			{
				G->arcs[i][j] = 0;	// ���Խ��߳�ʼ��Ϊ0
			}
			else
			{
				G->arcs[i][j] = INFINITY;
			}	
		}
	}

	cout << "���붥����Ϣ��" << endl;
	for (int i = 0; i < G->Nv; i++)
	{
		cin >> G->vexs[i];
	}

	// ����Ne���ߣ������ڽӾ���
	int i, j;
	WeightType w;
	for (int k = 0; k < G->Ne; k++)
	{
		cout << "�����(vi, vj)���±�i��j��Ȩֵw��" << endl;
		cin >> i >> j >> w;
		G->arcs[i][j] = w;
		// G->arcs[j][i] = G->arcs[i][j];	// ����ͼ���ڽӾ����ǶԳ�����G������ͼ����Ҫ����
	}
}

int main() {
	MGraph* G = new MGraph;
	createMGraph(G);

	// ��ӡ��������
	cout << "\n��������" << endl;
	for (int i = 0; i < G->Nv; i++)
	{
		cout << G->vexs[i] << "\t";
	}

	// ��ӡ�ڽӾ����ֵ
	cout << "\n�ڽӾ���" << endl;
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