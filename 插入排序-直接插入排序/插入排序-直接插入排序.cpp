#include <iostream>
#include <vector>
using namespace std;


/*
* @brief:	直接插入排序
* @param v: 待排序序列引用
*/
void insertSort(vector<int>& v)
{
	int temp;	// 辅助空间：用于记录每次要插入的元素值
	for (int i = 1; i < v.size(); i++)	// 认定v[0]已经有序，所以i从1开始
	{
		temp = v[i];
		int j;
		for (j = i - 1; j >= 0; j--)	// 在[0, i-1]中找temp应该插入的位置
		{
			if (v[j] > temp)
			{
				v[j + 1] = v[j];	// 记录后移一位
			}
			else	// 说明v[0...j]的值都比temp小，无需再比
			{
				break;
			}
		}

		v[j + 1] = temp;	// j+1就是temp要插入的位置	
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
	insertSort(v);

	cout << "排序后：" << endl;
	printVec(v);
}