#include <iostream>
#include <vector>
using namespace std;

/*
* @brief:	将v[start~end]的记录调整为一个大顶堆
*			已知v[start~end]中的记录除v[start]外均满足堆的定义
* @param v: 待调整序列引用
*/
void heapAdjust(vector<int>& v, int start, int end)
{
	int temp = v[start];
	for (size_t j = 2 * start; j <= end; j *= 2)	// 沿关键字较大的孩子节点向下筛选
	{
		if (j < end && v[j] < v[j + 1])	// j:左孩子	j+1:右孩子
		{
			++j;	// 右孩子较大，将j增1
		}
		if (temp >= v[j])
		{
			break;	// temp的值比左右孩子值都大，不需要调整
		}

		v[start] = v[j];	// 将较大的孩子节点上调至父节点
		start = j;
		// j *= 2：继续对较大孩子节点进行调整
	}

	v[start] = temp;
}

/*
* @brief:	堆排序
* @param v: 待排序序列引用
*/
void heapSort(vector<int>& v)
{
	int length = v.size() - 1;	// 完全二叉树、堆顶元素从1开始编号，所以我们对v
								// 这里减1是为了不考虑v[0]，只对v[1~length]排序
	// 初始堆化
	for (size_t i = length / 2; i > 0; i--)
	{
		heapAdjust(v, i, length);
	}

	for (size_t i = length; i > 1; i--)
	{
		// 将堆顶元素与最后一个元素交换
		int temp = v[1];
		v[1] = v[i];
		v[i] = temp;

		// 将v[1~i-1]再调整称大顶堆
		heapAdjust(v, 1, i - 1);
	}
}

/*
* @brief:	打印元素
* @param v: 待排序序列引用
*/
void printVec(vector<int>& v)
{
	for (size_t i = 1; i < v.size(); i++)
	{
		cout << v[i] << "\t";
	}
	cout << endl;
}

int main(int argc, char* argv[])
{
	// vector<int> v = { 0,81,94,11,96,12,35,17,95,28,58,41,75,15 };
	vector<int> v = { 0,50,10,90,30,70,40,80,60,20 };

	cout << "排序前：" << endl;
	printVec(v);

	// 排序
	heapSort(v);

	cout << "排序后：" << endl;
	printVec(v);
}