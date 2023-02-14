#include <iostream>
#include <vector>
using namespace std;


/*
* @brief:	ð������
* @param v: ��������������
*/
void bubbleSort(vector<int>& v)
{
	int temp;	// �����ռ�
	int n = v.size();
	for (int i = 1; i < n; i++)	// ÿ���ҳ�һ�����ģ�n��Ԫ��Ҫ�Ƚ�n��
	{
		for (int j = 0; j < n - i; j++)
		{
			if (v[j] > v[j + 1])	// �Ƚ���������Ԫ�ش�С
			{
				// ����Ԫ��
				temp = v[j];
				v[j] = v[j + 1];
				v[j + 1] = temp;
			}
		}	
	}
}

/**
* @brief:	ð�������Ż�
* @param v: ��������������
*/
void bubbleSortOpt(vector<int>& v)
{
	int temp;
	int n = v.size();
	bool flag = true;	// ��¼ĳһ�����Ƿ񽻻���Ԫ��λ��
	for (int i = 1; i < n && flag; i++)
	{
		flag = false;	// �Ƚ���ǰ��Ԫ�ؽ��������Ϊfalse
		for (int j = 0; j < n - i; j++)
		{
			if (v[j] > v[j + 1])	// �Ƚ���������Ԫ�ش�С
			{
				// ����Ԫ��
				temp = v[j + 1];
				v[j + 1] = v[j];
				v[j] = temp;
				flag = true;	// ������Ԫ�ؽ���
			}
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
	// bubbleSort(v);
	bubbleSortOpt(v);

	cout << "�����" << endl;
	printVec(v);
}