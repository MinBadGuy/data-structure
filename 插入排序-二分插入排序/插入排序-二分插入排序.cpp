#include <iostream>
#include <vector>
#include <assert.h>
using namespace std;


/*
* @brief:	二分插入排序
* @param v: 待排序序列引用
*/
void BinsertSort(vector<int>& v)
{
	int temp;	// 用于记录每次要插入的元素值
	for (int i = 1; i < v.size(); i++)	// 认定v[0]已经有序，所以i从1开始
	{
		temp = v[i];
		// 利用二分法在[0, i-1]中找temp应该插入的位置
		int low = 0, high = i - 1;
		while (low <= high)
		{	
			int mid = (low + high) / 2;
			if (v[mid] > temp)
			{
				high = mid - 1;
			}
			else
			{
				low = mid + 1;
			}
		}	// low就是该插入的位置
		
		// 将[low, i-1]处的元素依次向后移动一位
		for (int j = i - 1; j >= low; j--)
		{
			v[j + 1] = v[j];
		}

		v[low] = temp;	// low就是temp要插入的位置	
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
	BinsertSort(v);

	cout << "排序后：" << endl;
	printVec(v);
}