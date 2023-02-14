#include <iostream>
#include <vector>
using namespace std;


/*
* @brief:	快速排序
* @param v: 待排序序列引用
*/
void quickSort(vector<int>& v, int start, int end)
{
	if (start >= end)
		return;

	int low = start, high = end;
	int pivot = v[low];	// 枢轴
	while (low < high)
	{
		while (low < high && v[high] >= pivot)	// 将比枢轴小的放到左边
			high--;
		v[low] = v[high];

		while (low < high && v[low] <= pivot)	// 将比枢轴大的放到右边
			low++;
		v[high] = v[low];
	}
	v[low] = pivot;	// 将枢轴放置中间某个位置

	// 递归左右子表
	quickSort(v, start, low - 1);
	quickSort(v, low + 1, end);
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
	quickSort(v, 0, v.size() - 1);

	cout << "排序后：" << endl;
	printVec(v);
}