#include <iostream>
using namespace std;

// ȫ�ֱ��� ���ұ�
#define LEN	(11)
int searchTable[LEN] = { 0, 1, 16, 24, 35, 47, 59, 62, 73, 88, 99 };

/**
* @brief:		����˳�����
* @param a:		˳���ָ��
* @param n:		˳�����
* @param key:	Ҫ���ҵĹؼ���
* @return:		�����ҳɹ����򷵻�key�����±꣬���򷵻�0
*/
int sequentialSearch(int* a, int n, int key)
{
	for (size_t i = 1; i <= n; i++)	// ע�⣬˳���Ԫ�ش��±�1��ʼ�洢��a[0]����Ԫ��
	{
		if (a[i] == key)
		{
			return i;	// ���ҳɹ�
		}
	}
	return 0;	// ����ʧ��
}


/**
* @brief:		���ڱ��Ż���˳�����
* @param a:		˳���ָ��
* @param n:		˳�����
* @param key:	Ҫ���ҵĹؼ���
* @return:		�����ҳɹ����򷵻�key�����±꣬���򷵻�0
*/
int sequentialSearchOpt(int* a, int n, int key)
{
	a[0] = key;	// �ڱ�
	int i = n;	// ѭ����β����ʼ	
	while (a[i] != key)
	{
		i--;	
	}
	// ����������a[0]=key�����Լ�ʹ��a[1]~a[n]��������key����ôwhileѭ��Ҳ����i=0ʱ��������ʱ����ʧ��
	return i;
}

int main(int argc, char* argv[])
{
	int key = 99;
	// int pos = sequentialSearch(searchTable, LEN, key);
	int pos = sequentialSearchOpt(searchTable, LEN, key);
	if (pos)
	{
		cout << "the index of " << key << " is " << pos << endl;
	}
	else
	{
		cout << "not found" << endl;
	}
}