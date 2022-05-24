#include <iostream>
using namespace std;

// ȫ�ֱ��� ���ұ�
#define LEN	(10)
int searchTable[LEN + 1] = { 0, 1, 16, 24, 35, 47, 59, 62, 73, 88, 99 };	// ���ұ�Ԫ�ش��±�Ϊ1����ʼ

/**
* @brief:		���ֲ��ҵ�����ʽ
* @param a:		���ұ�ָ��
* @param n:		���ұ���
* @param key:	Ҫ���ҵĹؼ���
* @return:		�����ҳɹ����򷵻�key�����±꣬���򷵻�0
*/
int binarySearch(int* a, int n, int key)
{
	int low = 1;	// ��¼����±�
	int high = n;	// ��¼����±�
	int mid;		// ��¼��ֵ�±�

	while (low <= high)
	{
		mid = (low + high) / 2;		
		if (key > a[mid])			// ������ֵ������ֵ
		{
			low = mid + 1;
		}
		else if (key < a[mid])		// ������ֵС����ֵ
		{
			high = mid - 1;
		}
		else						// ������ֵ������ֵ
		{
			return mid;
		}
	}
	return 0;
}

/**
* @brief:		���ֲ��ҵݹ���ʽ
* @param a:		���ұ�ָ��
* @param n:		���ұ���
* @param key:	Ҫ���ҵĹؼ���
* @return:		�����ҳɹ����򷵻�key�����±꣬���򷵻�0
*/
int binarySearchRec(int* a, int low, int high, int key)
{
	if (low > high)
	{
		return 0;
	}
	
	int mid = (low + high) / 2;
	if (key > a[mid])		// ������ֵ������ֵ
	{
		return binarySearchRec(a, mid + 1, high, key);
	}
	else if (key < a[mid])	// ������ֵС����ֵ
	{
		return binarySearchRec(a, low, mid - 1, key);
	}
	else					// ������ֵ������ֵ
	{
		return mid;
	}
}

/**
* @brief:		��ֵ����
* @param a:		���ұ�ָ��
* @param n:		���ұ���
* @param key:	Ҫ���ҵĹؼ���
* @return:		�����ҳɹ����򷵻�key�����±꣬���򷵻�0
*/
int insertSearch(int* a, int n, int key)
{
	int low = 1;
	int high = n;
	int mid;

	while (low <= high)
	{
		mid = low + (key - a[low]) / (a[high] - a[low]) * (high - low);		// ��ֵ
		if (key > a[mid])
		{
			low = mid + 1;
		}
		else if (key < a[mid])
		{
			high = mid - 1;
		}
		else
		{
			return mid;
		}
	}
	return 0;
}

int main(int argc, char* argv[])
{
	int key = 35;
	// int pos = binarySearch(searchTable, LEN, key);
	// int pos = binarySearchRec(searchTable, 1, LEN, key);
	int pos = insertSearch(searchTable, LEN, key);
	if (pos)
	{
		cout << "the index of " << key << " is " << pos << endl;
	}
	else
	{
		cout << "not found" << endl;
	}
}