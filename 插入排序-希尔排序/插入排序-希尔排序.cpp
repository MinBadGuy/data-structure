#include <iostream>
#include <vector>
using namespace std;


/*
* @brief:	ϣ������
* @param v: ��������������
*/
void ShellSort(vector<int>& v)
{
	int temp;						// �����ռ�
	int increment = v.size() / 2;	// ��ʼ����
	while (increment >= 1)	// ���һ���Ĳ�����������һ����1
	{
		for (int i = increment; i < v.size(); i++)
		{
			temp = v[i];
			int j;
			for (j = i - increment; j >= 0; j -= increment)
			{
				if (v[j] > temp)
				{
					v[j + increment] = v[j];	// ��¼����incrementλ
				}
				else	// ˵��v[0...j]��ֵ����tempС�������ٱ�
				{
					break;
				}
			}

			v[j + increment] = temp;	// j+increment����tempҪ�����λ��
		}

		increment /= 2;	// ������С����
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
	ShellSort(v);

	cout << "�����" << endl;
	printVec(v);
}