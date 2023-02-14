#include <iostream>
#include <vector>
using namespace std;

/**
* @brief:		将有序序列vSrc[s...m]和vSrc[m+1...t]合并到vDst[s...t]
* @param vSrc:	源数组引用
* @param vDst:	目标数组引用
* @param s:		start index
* @param m:		'middle' index, s < m < t
* @param t:		end index
*/
void merge(vector<int>& vSrc, vector<int>& vDst, int s, int m, int t)
{
	int i = s, j = m + 1;
	int k = s;
	while (i <= m && j <= t)
	{
		if (vSrc[i] < vSrc[j])
		{
			vDst[k++] = vSrc[i++];
		}
		else
		{
			vDst[k++] = vSrc[j++];
		}
	}

	while (i <= m)
	{
		vDst[k++] = vSrc[i++];
	}
	while (j <= t)
	{
		vDst[k++] = vSrc[j++];
	}	
}


/*
* @brief:		归并排序，将vSrc[s...t]归并排序为vDst[s...t]
* @param vSrc:	待排序序列引用
* @param vDst:	排序结果序列引用
* @param s:		start index
* @param t:		end index
*/
void mergeSort(vector<int>& vSrc, vector<int>& vDst, int s, int t)
{
	if (s == t)
	{
		vDst[s] = vSrc[s];
		return;
	}
	else
	{
		int m = (s + t) / 2;
		vector<int> vTemp(vSrc.size());
		mergeSort(vSrc, vTemp, s, m);
		mergeSort(vSrc, vTemp, m + 1, t);
		merge(vTemp, vDst, s, m, t);
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
	int length = v.size();
	vector<int> vRes(length);
	cout << "aa" << endl;
	mergeSort(v, vRes, 0, length - 1);

	cout << "排序后：" << endl;
	printVec(vRes);
}