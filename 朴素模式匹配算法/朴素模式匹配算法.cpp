#include <iostream>
using namespace std;

/* ����ģʽ��P������S�е�λ�ã��������ڣ���������ֵΪ-1 */
int index(const char* s, const char* p)
{
	int sLen = strlen(s);
	int pLen = strlen(p);
	int i = 0;	// i��������s�е�ǰλ�õ��±�
	int j = 0;	// j����ģʽ��p�е�ǰλ�õ��±�
	while (i < sLen && j < pLen)
	{
		if (s[i] == p[j])	// ���ַ���ȣ������i��j���Ƚ���һλ���ַ�
		{
			i++;
			j++;
		}
		else	// ���ַ�����
		{
			i = i - j + 1;	// ����i���ص��ϴ�ƥ�俪ʼ����λ����һλ
							/* ��ʱT[j]��S[i]ƥ��ʧ�ܣ���j�Ǵ�0��ʼ�����ģ�����ǰj���ַ�ƥ�䶼�ǳɹ��ģ�
							   �ɴ˿ɵõ�i�Ǵӣ�i-j����ʼ�����ģ����´�ƥ��ӣ�i-j+1����ʼ��
							*/
			j = 0;			// ��j����Ϊ0
		}
	}
	
	if (j == pLen)
	{
		return i - j;
	}
	else
	{
		return -1;
	}
}


int main() {
	const char* S = "BBCABCDABABCDABCDABDE";
	const char* P = "ABCDABD";
	int ret = index(S, P);
	cout << "ret = " << ret << endl;
}