#include <iostream>
#include <vector>
using namespace std;

#define HASHSIZE (5)	// ɢ�б�����Զ���

struct HashNode {
	int			key;		// �ؼ���
	HashNode*	next;		// ָ����һ�����

	HashNode() {
		key = -1;
		next = nullptr;
	};
	HashNode(int key) : key(key), next(nullptr) {};
};

/* ��ϣ��ṹ */
struct HashTable {
	HashNode** elem;		// ��ϣ�����飬ÿ��Ԫ�ض���һ��ָ��HashNode�ṹ��ָ�루ÿ��������׵�ַ��		
};


/**
* @brief:		ɢ�б��ʼ��
* @param H:		ɢ�б�ָ��
* @return:		
*/
void InitHashTable(HashTable *H)
{
	H->elem = new HashNode*[HASHSIZE];	// �����ϣ������ռ�
	for (size_t i = 0; i < HASHSIZE; i++)
	{
		H->elem[i] = nullptr;
	}
}

/**
* @brief:		ɢ�б����٣����տռ�
* @param H:		ɢ�б�ָ��
* @return:
*/
void DestroyHashTable(HashTable* H)
{
	// ��ÿ�������ÿ�����Ԫ�ؽ��л���
	for (size_t i = 0; i < HASHSIZE; i++)
	{
		HashNode* root;
		HashNode* tmp;
		root = H->elem[i];
		while (root)
		{
			tmp = root->next;
			delete root;
			root = tmp;
		}
	}

	delete[] H->elem;
}


/**
* @brief:		ɢ�к���������������
* @param key:	�ؼ���
* @return:		ɢ��ֵ
*/
int Hash(int key)
{
	return key % HASHSIZE;
}


/**
* @brief:		���ؼ��ֲ���ɢ�б�
* @param H:		ɢ�б�ָ��
* @param key:	�ؼ���
* @return:		
*/
void InsertHash(HashTable *H, int key)
{	
	int addr = Hash(key);			// ɢ��ֵ��Ӧ�÷ŵ�ɢ�б���ĸ�������

	HashNode* node = new HashNode(key);
	// ͷ�巨
	node->next = H->elem[addr];
	H->elem[addr] = node;
}


/**
* @brief:		ɢ�б����
* @param H:		ɢ�б�ָ��
* @param key:	�ؼ���
* @return:		true/false
*/
bool SearchHash(HashTable* H, int key)
{
	int addr = Hash(key);			// ɢ��ֵ��Ӧ����ɢ�б���ĸ������ϲ���
	HashNode* root = H->elem[addr];	// ����ͷ���
	while (root)
	{
		if (key == root->key)		// �ҵ���¼
		{
			return true;
		}

		root = root->next;
	}

	return false;
}


int main()
{
	HashTable* H = new HashTable;
	// ��ʼ����ϣ��
	InitHashTable(H);

	// ����ϣ���в�ֵ
	vector<int> searchTable = { 1, 16, 24, 35, 47, 59, 62, 73, 88, 99 };	// ���ұ�Ԫ��
	for (size_t i = 0; i < searchTable.size(); i++)
	{
		InsertHash(H, searchTable[i]);
	}

	// ��ϣ�����
	int key = 98;
	if (SearchHash(H, key))
	{
		cout << "found" << endl;
	}
	else
	{
		cout << "not found" << endl;
	}

	// ����ɢ�б�
	DestroyHashTable(H);
	delete H;

	return 0;
}