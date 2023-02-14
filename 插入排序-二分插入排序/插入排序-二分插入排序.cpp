#include <iostream>
#include <vector>
#include <assert.h>
using namespace std;


/*
* @brief:	���ֲ�������
* @param v: ��������������
*/
void BinsertSort(vector<int>& v)
{
	int temp;	// ���ڼ�¼ÿ��Ҫ�����Ԫ��ֵ
	for (int i = 1; i < v.size(); i++)	// �϶�v[0]�Ѿ���������i��1��ʼ
	{
		temp = v[i];
		// ���ö��ַ���[0, i-1]����tempӦ�ò����λ��
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
		}	// low���Ǹò����λ��
		
		// ��[low, i-1]����Ԫ����������ƶ�һλ
		for (int j = i - 1; j >= low; j--)
		{
			v[j + 1] = v[j];
		}

		v[low] = temp;	// low����tempҪ�����λ��	
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
	BinsertSort(v);

	cout << "�����" << endl;
	printVec(v);
}