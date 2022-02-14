#include <iostream>
using namespace std;

typedef char VertexType;	// �������ͣ��Զ���
typedef int  WeightType;	// ����Ȩֵ���ͣ��Զ���

#define MAXVEX (100)		// ��󶥵���

int visited[MAXVEX] = { 0 };	// �������飬��¼ÿ�������Ƿ񱻷��ʹ���0��δ���ʣ�1���ѷ���

typedef struct {
	VertexType vexs[MAXVEX];			// ��������
	WeightType arcs[MAXVEX][MAXVEX];	// �ڽӾ���
	int Nv, Ne;							// ������������
} MGraph;

/**
* @brief: ����ͼ���ڽӾ���ṹ
* @param��ָ��ͼ��ָ��
*/
void createMGraph(MGraph* G) {
	cout << "���붥�����ͱ�����";
	cin >> G->Nv >> G -> Ne;

	// ��ʼ���ڽӾ���
	for (int i = 0; i < G->Nv; i++)
	{
		for (int j = 0; j < G->Nv; j++)
		{
			G->arcs[i][j] = 0;	// ��Ȩͼ���ڽӾ���ȫ����ʼ��Ϊ0����ʾû�б�
		}
	}

	cout << "���붥����Ϣ��";
	for (int i = 0; i < G->Nv; i++)
	{
		cin >> G->vexs[i];
	}

	// ����Ne������Ϣ�������ڽӾ���
	int i, j;
	for (int k = 0; k < G->Ne; k++)
	{
		cout << "�����(Vi, Vj)���±�i��j��";
		cin >> i >> j;
		G->arcs[i][j] = 1;
		G->arcs[j][i] = G->arcs[i][j];	// ����ͼ���ڽӾ���Ϊ�Գ���
	}
}

/**
* @brief: �ڽӾ����DFS�ݹ��㷨
* @param G��ָ��ͼ��ָ��
* @param i�������Ķ�����
*/
void DFS(MGraph* G, int i) {
	cout << G->vexs[i] << "\t";		// ��ӡ����ֵ
	visited[i] = 1;					// ����visited����
	for (int j = 0; j < G->Nv; j++)
	{
		if (G->arcs[i][j] == 1 && visited[j] == 0)	// ��δ���ʹ����ڽӵ�ݹ����DFS
		{
			DFS(G, j);
		}
	}
}

/**
* @brief: DFS�����غ���
* @param��ָ��ͼ��ָ��
*/
void DFSTraverse(MGraph* G) {
	for (int i = 0; i < G->Nv; i++)	// ��ͼ��ÿ������DFS����ֹͼ����ͨ���ж���û�ñ�����
	{
		if (0 == visited[i])
		{
			DFS(G, i);
		}
	}
}

int main() {
	MGraph* G = new MGraph;
	createMGraph(G);

	DFSTraverse(G);
	
	delete G;
}