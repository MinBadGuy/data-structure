#include <iostream>
#include <vector>
using namespace std;

// ȫ�ֱ�����쳲���������
vector<int> FibArray = { 1, 1 };	// ��ʼ��һ������
vector<int> searchTable = { 0, 1, 16, 24, 35, 47, 59, 62, 73, 88, 99 };	// ���ұ�Ԫ�ش��±�Ϊ1����ʼ

/**
* @brief:		쳲���������
* @param a:		���ұ� vector
* @param key:	Ҫ���ҵĹؼ���
* @return:		�����ҳɹ����򷵻�key�����±꣬���򷵻�0
*/
int fibonacciSearch(vector<int>& a, int key)
{
	int n = a.size() - 1;	// ���ұ��ȣ���ЧԪ�ش��±�1��ʼ
	int low = 1;			// ��¼����±�
	int high = n;			// ��¼����±�
	int mid;				// ��¼��ֵ�±�

	int k = 0;
	while (n > FibArray[k] - 1)		// ����nλ��쳲��������е�λ��
	{
		k++;
		if (k >= FibArray.size())
		{
			FibArray.push_back(FibArray[k - 1] + FibArray[k - 2]);
		}
	}

	for (size_t i = n; i < FibArray[k] - 1; i++)	// ���ұ�������ȿ��ܲ��� FibArray[k] - 1�����䲹��
	{
		a.push_back(a[n]);
	}

	while (low <= high)
	{
		mid = low + FibArray[k - 1] - 1;	// �ָ���midλ��
		if (key < a[mid])		// ������ֵ������ֵ
		{
			high = mid - 1;
			k -= 1;
		}
		else if (key > a[mid])	// ������ֵС����ֵ
		{
			low = mid + 1;
			k -= 2;
		}
		else
		{
			if (mid <= n)
			{
				return mid;
			}
			else				// ��mid>n˵���ǲ�ȫ����ֵ��ֱ�ӷ���n
			{
				return n;
			}
		}
	}

	return 0;
}

int main(int argc, char* argv[])
{
	int key = 59;
	int pos = fibonacciSearch(searchTable, key);
	if (pos)
	{
		cout << "the index of " << key << " is " << pos << endl;
	}
	else
	{
		cout << "not found" << endl;
	}		
}