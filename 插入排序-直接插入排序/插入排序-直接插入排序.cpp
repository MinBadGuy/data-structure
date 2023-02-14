#include <iostream>
#include <vector>
using namespace std;


/*
* @brief:	ֱ�Ӳ�������
* @param v: ��������������
*/
void insertSort(vector<int>& v)
{
	int temp;	// �����ռ䣺���ڼ�¼ÿ��Ҫ�����Ԫ��ֵ
	for (int i = 1; i < v.size(); i++)	// �϶�v[0]�Ѿ���������i��1��ʼ
	{
		temp = v[i];
		int j;
		for (j = i - 1; j >= 0; j--)	// ��[0, i-1]����tempӦ�ò����λ��
		{
			if (v[j] > temp)
			{
				v[j + 1] = v[j];	// ��¼����һλ
			}
			else	// ˵��v[0...j]��ֵ����tempС�������ٱ�
			{
				break;
			}
		}

		v[j + 1] = temp;	// j+1����tempҪ�����λ��	
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
	insertSort(v);

	cout << "�����" << endl;
	printVec(v);
}