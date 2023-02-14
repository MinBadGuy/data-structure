#include <iostream>
#include <vector>
using namespace std;


/*
* @brief:	希尔排序
* @param v: 待排序序列引用
*/
void ShellSort(vector<int>& v)
{
	int temp;						// 辅助空间
	int increment = v.size() / 2;	// 初始增量
	while (increment >= 1)	// 最后一步的插入排序增量一定是1
	{
		for (int i = increment; i < v.size(); i++)
		{
			temp = v[i];
			int j;
			for (j = i - increment; j >= 0; j -= increment)
			{
				if (v[j] > temp)
				{
					v[j + increment] = v[j];	// 记录后移increment位
				}
				else	// 说明v[0...j]的值都比temp小，无需再比
				{
					break;
				}
			}

			v[j + increment] = temp;	// j+increment就是temp要插入的位置
		}

		increment /= 2;	// 更新缩小增量
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
	ShellSort(v);

	cout << "排序后：" << endl;
	printVec(v);
}