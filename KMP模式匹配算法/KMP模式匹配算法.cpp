#include <iostream>
#include <string>
using namespace std;

/* ����KMP�㷨��ģʽ��P�±�j�ı仯����next */
void get_next(string P, int* next) {
	int pLen = P.size();
	next[0] = -1;
	int k = -1;	// ǰ׺ĩβ�ַ��±�
	int j = 0;	// ��׺ĩβ�ַ��±�
	while (j < pLen - 1)
	{
		// p[k]��ʾǰ׺��p[j]��ʾ��׺ 
		if (k == -1 || P[k] == P[j])
		{
			++k;
			++j;
			next[j] = k;
		}
		else
		{
			k = next[k];
		}
	}
}

/* KMP�㷨������ģʽ��P������S�е�λ�ã��������ڣ���������ֵΪ-1 */
int index_KMP(string S, string P, int* next) {
	int sLen = S.size();
	int pLen = P.size();
	int i = 0;
	int j = 0;
	while (i < sLen && j < pLen)
	{
		/*
		��ע��
		����� j == -1���ǿ��ǵ�next[0]ֵΪ-1���������jΪ-1���Ͳ�����ΪP[j]��������
		*/
		if (j == -1 || S[i] == P[j])	// ��ǰ�ַ�ƥ��ɹ�������ƥ����һ�ַ�
		{ 
			i++; 
			j++;
		}
		else	// ��ǰ�ַ�ƥ��ʧ�ܣ�����jΪnext[j]��i����
		{
			j = next[j];
		}
	}
	if (j == P.size())
	{
		return i - j;
	}
	else
	{
		return -1;
	}
}

int main() {
	string S, P;
	cout << "Please input string S: ";
	cin >> S;
	cout << "Please input string P: ";
	cin >> P;

	int* next = new int[P.size()];
	get_next(P, next);

	// print next array
	cout << "next: " << endl;
	for (int i = 0; i < P.size(); i++)
	{
		cout << next[i] << "\t";
	}
	cout << endl << endl;

	int ret = index_KMP(S, P, next);
	cout << "ret = " << ret << endl;
	
	delete[] next;
}
