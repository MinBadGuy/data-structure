#include <iostream>
#include <vector>
using namespace std;


/*
* @brief:	选择排序
* @param v: 待排序序列引用
*/
void selectSort(vector<int>& v)
{
	int temp;	// 辅助空间
	int n = v.size();
	for (int i = 0; i < n; i++)
	{
		int minIdx = i;	// 将当前下标定义为最小下标
		for (int j = minIdx + 1; j < n; j++)	// 找出[i...n-1]中最小元素对应index
		{
			if (v[j] < v[minIdx])
			{
				minIdx = j;	// 更新minIdx
			}
		}

		if (minIdx != i)
		{
			// 交换v[i]和v[minIdx]
			temp = v[i];
			v[i] = v[minIdx];
			v[minIdx] = temp;
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
	selectSort(v);

	cout << "排序后：" << endl;
	printVec(v);
}