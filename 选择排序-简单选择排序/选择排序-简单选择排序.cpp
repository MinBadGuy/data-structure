#include <iostream>
#include <vector>
using namespace std;


/*
* @brief:	ѡ������
* @param v: ��������������
*/
void selectSort(vector<int>& v)
{
	int temp;	// �����ռ�
	int n = v.size();
	for (int i = 0; i < n; i++)
	{
		int minIdx = i;	// ����ǰ�±궨��Ϊ��С�±�
		for (int j = minIdx + 1; j < n; j++)	// �ҳ�[i...n-1]����СԪ�ض�Ӧindex
		{
			if (v[j] < v[minIdx])
			{
				minIdx = j;	// ����minIdx
			}
		}

		if (minIdx != i)
		{
			// ����v[i]��v[minIdx]
			temp = v[i];
			v[i] = v[minIdx];
			v[minIdx] = temp;
		}
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
	selectSort(v);

	cout << "�����" << endl;
	printVec(v);
}