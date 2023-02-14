#include <iostream>
#include <vector>
using namespace std;

/*
* @brief:	��v[start~end]�ļ�¼����Ϊһ���󶥶�
*			��֪v[start~end]�еļ�¼��v[start]�������ѵĶ���
* @param v: ��������������
*/
void heapAdjust(vector<int>& v, int start, int end)
{
	int temp = v[start];
	for (size_t j = 2 * start; j <= end; j *= 2)	// �عؼ��ֽϴ�ĺ��ӽڵ�����ɸѡ
	{
		if (j < end && v[j] < v[j + 1])	// j:����	j+1:�Һ���
		{
			++j;	// �Һ��ӽϴ󣬽�j��1
		}
		if (temp >= v[j])
		{
			break;	// temp��ֵ�����Һ���ֵ���󣬲���Ҫ����
		}

		v[start] = v[j];	// ���ϴ�ĺ��ӽڵ��ϵ������ڵ�
		start = j;
		// j *= 2�������Խϴ��ӽڵ���е���
	}

	v[start] = temp;
}

/*
* @brief:	������
* @param v: ��������������
*/
void heapSort(vector<int>& v)
{
	int length = v.size() - 1;	// ��ȫ���������Ѷ�Ԫ�ش�1��ʼ��ţ��������Ƕ�v
								// �����1��Ϊ�˲�����v[0]��ֻ��v[1~length]����
	// ��ʼ�ѻ�
	for (size_t i = length / 2; i > 0; i--)
	{
		heapAdjust(v, i, length);
	}

	for (size_t i = length; i > 1; i--)
	{
		// ���Ѷ�Ԫ�������һ��Ԫ�ؽ���
		int temp = v[1];
		v[1] = v[i];
		v[i] = temp;

		// ��v[1~i-1]�ٵ����ƴ󶥶�
		heapAdjust(v, 1, i - 1);
	}
}

/*
* @brief:	��ӡԪ��
* @param v: ��������������
*/
void printVec(vector<int>& v)
{
	for (size_t i = 1; i < v.size(); i++)
	{
		cout << v[i] << "\t";
	}
	cout << endl;
}

int main(int argc, char* argv[])
{
	// vector<int> v = { 0,81,94,11,96,12,35,17,95,28,58,41,75,15 };
	vector<int> v = { 0,50,10,90,30,70,40,80,60,20 };

	cout << "����ǰ��" << endl;
	printVec(v);

	// ����
	heapSort(v);

	cout << "�����" << endl;
	printVec(v);
}