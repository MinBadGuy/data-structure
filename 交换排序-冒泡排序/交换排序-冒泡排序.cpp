#include <iostream>
#include <vector>
using namespace std;


/*
* @brief:	冒泡排序
* @param v: 待排序序列引用
*/
void bubbleSort(vector<int>& v)
{
	int temp;	// 辅助空间
	int n = v.size();
	for (int i = 1; i < n; i++)	// 每次找出一个最大的，n个元素要比较n趟
	{
		for (int j = 0; j < n - i; j++)
		{
			if (v[j] > v[j + 1])	// 比较相邻两个元素大小
			{
				// 交换元素
				temp = v[j];
				v[j] = v[j + 1];
				v[j + 1] = temp;
			}
		}	
	}
}

/**
* @brief:	冒泡排序优化
* @param v: 待排序序列引用
*/
void bubbleSortOpt(vector<int>& v)
{
	int temp;
	int n = v.size();
	bool flag = true;	// 记录某一趟中是否交换了元素位置
	for (int i = 1; i < n && flag; i++)
	{
		flag = false;	// 先将当前趟元素交换标记设为false
		for (int j = 0; j < n - i; j++)
		{
			if (v[j] > v[j + 1])	// 比较相邻两个元素大小
			{
				// 交换元素
				temp = v[j + 1];
				v[j + 1] = v[j];
				v[j] = temp;
				flag = true;	// 发生了元素交换
			}
		}
	}
}

/*
* @brief:	打印元素
* @param v: 待排序序列引用
*/
void printVec(vector<int>& v)
{
	for (size_t i = 0; i < v.size(); i++)
	{
		cout << v[i] << "\t";
	}
	cout << endl;
}

int main(int argc, char* argv[])
{
	vector<int> v = { 81,94,11,96,12,35,17,95,28,58,41,75,15 };

	cout << "排序前：" << endl;
	printVec(v);

	// 排序
	// bubbleSort(v);
	bubbleSortOpt(v);

	cout << "排序后：" << endl;
	printVec(v);
}