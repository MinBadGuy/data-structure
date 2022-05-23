#include <iostream>
using namespace std;

// 全局变量 查找表
#define LEN	(11)
int searchTable[LEN] = { 0, 1, 16, 24, 35, 47, 59, 62, 73, 88, 99 };

/**
* @brief:		常规顺序查找
* @param a:		顺序表指针
* @param n:		顺序表长度
* @param key:	要查找的关键字
* @return:		若查找成功，则返回key所在下标，否则返回0
*/
int sequentialSearch(int* a, int n, int key)
{
	for (size_t i = 1; i <= n; i++)	// 注意，顺序表元素从下标1开始存储，a[0]不放元素
	{
		if (a[i] == key)
		{
			return i;	// 查找成功
		}
	}
	return 0;	// 查找失败
}


/**
* @brief:		带哨兵优化的顺序查找
* @param a:		顺序表指针
* @param n:		顺序表长度
* @param key:	要查找的关键字
* @return:		若查找成功，则返回key所在下标，否则返回0
*/
int sequentialSearchOpt(int* a, int n, int key)
{
	a[0] = key;	// 哨兵
	int i = n;	// 循环从尾部开始	
	while (a[i] != key)
	{
		i--;	
	}
	// 由于设置了a[0]=key，所以即使在a[1]~a[n]处不等于key，那么while循环也会在i=0时结束，此时查找失败
	return i;
}

int main(int argc, char* argv[])
{
	int key = 99;
	// int pos = sequentialSearch(searchTable, LEN, key);
	int pos = sequentialSearchOpt(searchTable, LEN, key);
	if (pos)
	{
		cout << "the index of " << key << " is " << pos << endl;
	}
	else
	{
		cout << "not found" << endl;
	}
}