#include <iostream>
#include <vector>
using namespace std;

#define HASHSIZE (5)	// 散列表表长，自定义

struct HashNode {
	int			key;		// 关键字
	HashNode*	next;		// 指向下一个结点

	HashNode() {
		key = -1;
		next = nullptr;
	};
	HashNode(int key) : key(key), next(nullptr) {};
};

/* 哈希表结构 */
struct HashTable {
	HashNode** elem;		// 哈希表数组，每个元素都是一个指向HashNode结构的指针（每个链表的首地址）		
};


/**
* @brief:		散列表初始化
* @param H:		散列表指针
* @return:		
*/
void InitHashTable(HashTable *H)
{
	H->elem = new HashNode*[HASHSIZE];	// 分配哈希表数组空间
	for (size_t i = 0; i < HASHSIZE; i++)
	{
		H->elem[i] = nullptr;
	}
}

/**
* @brief:		散列表销毁，回收空间
* @param H:		散列表指针
* @return:
*/
void DestroyHashTable(HashTable* H)
{
	// 对每个链表的每个结点元素进行回收
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
* @brief:		散列函数：除留余数法
* @param key:	关键字
* @return:		散列值
*/
int Hash(int key)
{
	return key % HASHSIZE;
}


/**
* @brief:		将关键字插入散列表
* @param H:		散列表指针
* @param key:	关键字
* @return:		
*/
void InsertHash(HashTable *H, int key)
{	
	int addr = Hash(key);			// 散列值，应该放到散列表的哪个链表上

	HashNode* node = new HashNode(key);
	// 头插法
	node->next = H->elem[addr];
	H->elem[addr] = node;
}


/**
* @brief:		散列表查找
* @param H:		散列表指针
* @param key:	关键字
* @return:		true/false
*/
bool SearchHash(HashTable* H, int key)
{
	int addr = Hash(key);			// 散列值，应该在散列表的哪个链表上查找
	HashNode* root = H->elem[addr];	// 链表头结点
	while (root)
	{
		if (key == root->key)		// 找到记录
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
	// 初始化哈希表
	InitHashTable(H);

	// 往哈希表中插值
	vector<int> searchTable = { 1, 16, 24, 35, 47, 59, 62, 73, 88, 99 };	// 查找表元素
	for (size_t i = 0; i < searchTable.size(); i++)
	{
		InsertHash(H, searchTable[i]);
	}

	// 哈希表查找
	int key = 98;
	if (SearchHash(H, key))
	{
		cout << "found" << endl;
	}
	else
	{
		cout << "not found" << endl;
	}

	// 销毁散列表
	DestroyHashTable(H);
	delete H;

	return 0;
}