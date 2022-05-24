#include <iostream>
using namespace std;

// 全局变量 查找表
#define LEN	(10)
int searchTable[LEN + 1] = { 0, 1, 16, 24, 35, 47, 59, 62, 73, 88, 99 };	// 查找表元素从下标为1处开始

/**
* @brief:		二分查找迭代形式
* @param a:		查找表指针
* @param n:		查找表长度
* @param key:	要查找的关键字
* @return:		若查找成功，则返回key所在下标，否则返回0
*/
int binarySearch(int* a, int n, int key)
{
	int low = 1;	// 记录最低下标
	int high = n;	// 记录最高下标
	int mid;		// 记录中值下标

	while (low <= high)
	{
		mid = (low + high) / 2;		
		if (key > a[mid])			// 若查找值大于中值
		{
			low = mid + 1;
		}
		else if (key < a[mid])		// 若查找值小于中值
		{
			high = mid - 1;
		}
		else						// 若查找值等于中值
		{
			return mid;
		}
	}
	return 0;
}

/**
* @brief:		二分查找递归形式
* @param a:		查找表指针
* @param n:		查找表长度
* @param key:	要查找的关键字
* @return:		若查找成功，则返回key所在下标，否则返回0
*/
int binarySearchRec(int* a, int low, int high, int key)
{
	if (low > high)
	{
		return 0;
	}
	
	int mid = (low + high) / 2;
	if (key > a[mid])		// 若查找值大于中值
	{
		return binarySearchRec(a, mid + 1, high, key);
	}
	else if (key < a[mid])	// 若查找值小于中值
	{
		return binarySearchRec(a, low, mid - 1, key);
	}
	else					// 若查找值等于中值
	{
		return mid;
	}
}

/**
* @brief:		插值查找
* @param a:		查找表指针
* @param n:		查找表长度
* @param key:	要查找的关键字
* @return:		若查找成功，则返回key所在下标，否则返回0
*/
int insertSearch(int* a, int n, int key)
{
	int low = 1;
	int high = n;
	int mid;

	while (low <= high)
	{
		mid = low + (key - a[low]) / (a[high] - a[low]) * (high - low);		// 插值
		if (key > a[mid])
		{
			low = mid + 1;
		}
		else if (key < a[mid])
		{
			high = mid - 1;
		}
		else
		{
			return mid;
		}
	}
	return 0;
}

int main(int argc, char* argv[])
{
	int key = 35;
	// int pos = binarySearch(searchTable, LEN, key);
	// int pos = binarySearchRec(searchTable, 1, LEN, key);
	int pos = insertSearch(searchTable, LEN, key);
	if (pos)
	{
		cout << "the index of " << key << " is " << pos << endl;
	}
	else
	{
		cout << "not found" << endl;
	}
}