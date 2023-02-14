#include <iostream>
#include <vector>
using namespace std;


/*
* @brief:	��������
* @param v: ��������������
*/
void quickSort(vector<int>& v, int start, int end)
{
	if (start >= end)
		return;

	int low = start, high = end;
	int pivot = v[low];	// ����
	while (low < high)
	{
		while (low < high && v[high] >= pivot)	// ��������С�ķŵ����
			high--;
		v[low] = v[high];

		while (low < high && v[low] <= pivot)	// ���������ķŵ��ұ�
			low++;
		v[high] = v[low];
	}
	v[low] = pivot;	// ����������м�ĳ��λ��

	// �ݹ������ӱ�
	quickSort(v, start, low - 1);
	quickSort(v, low + 1, end);
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
	quickSort(v, 0, v.size() - 1);

	cout << "�����" << endl;
	printVec(v);
}