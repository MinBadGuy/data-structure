#include <iostream>
#include <vector>
using namespace std;

/**
* @brief:		����������vSrc[s...m]��vSrc[m+1...t]�ϲ���vDst[s...t]
* @param vSrc:	Դ��������
* @param vDst:	Ŀ����������
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
* @brief:		�鲢���򣬽�vSrc[s...t]�鲢����ΪvDst[s...t]
* @param vSrc:	��������������
* @param vDst:	��������������
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
* @brief:	��ӡԪ��
* @param v: ��������������
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

	cout << "����ǰ��" << endl;
	printVec(v);

	// ����
	int length = v.size();
	vector<int> vRes(length);
	cout << "aa" << endl;
	mergeSort(v, vRes, 0, length - 1);

	cout << "�����" << endl;
	printVec(vRes);
}