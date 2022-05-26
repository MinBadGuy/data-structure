#include <iostream>
#include <vector>
using namespace std;

// 全局变量，斐波拉契数列
vector<int> FibArray = { 1, 1 };	// 初始第一、二项
vector<int> searchTable = { 0, 1, 16, 24, 35, 47, 59, 62, 73, 88, 99 };	// 查找表元素从下标为1处开始

/**
* @brief:		斐波拉契查找
* @param a:		查找表 vector
* @param key:	要查找的关键字
* @return:		若查找成功，则返回key所在下标，否则返回0
*/
int fibonacciSearch(vector<int>& a, int key)
{
	int n = a.size() - 1;	// 查找表长度，有效元素从下标1开始
	int low = 1;			// 记录最低下标
	int high = n;			// 记录最高下标
	int mid;				// 记录中值下标

	int k = 0;
	while (n > FibArray[k] - 1)		// 计算n位于斐波拉契数列的位置
	{
		k++;
		if (k >= FibArray.size())
		{
			FibArray.push_back(FibArray[k - 1] + FibArray[k - 2]);
		}
	}

	for (size_t i = n; i < FibArray[k] - 1; i++)	// 查找表起初长度可能不足 FibArray[k] - 1，将其补足
	{
		a.push_back(a[n]);
	}

	while (low <= high)
	{
		mid = low + FibArray[k - 1] - 1;	// 分隔点mid位置
		if (key < a[mid])		// 若查找值大于中值
		{
			high = mid - 1;
			k -= 1;
		}
		else if (key > a[mid])	// 若查找值小于中值
		{
			low = mid + 1;
			k -= 2;
		}
		else
		{
			if (mid <= n)
			{
				return mid;
			}
			else				// 若mid>n说明是补全的数值，直接返回n
			{
				return n;
			}
		}
	}

	return 0;
}

int main(int argc, char* argv[])
{
	int key = 59;
	int pos = fibonacciSearch(searchTable, key);
	if (pos)
	{
		cout << "the index of " << key << " is " << pos << endl;
	}
	else
	{
		cout << "not found" << endl;
	}		
}