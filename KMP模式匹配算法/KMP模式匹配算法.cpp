#include <iostream>
#include <string>
using namespace std;

/* 计算KMP算法中模式串P下标j的变化数组next */
void get_next(string P, int* next) {
	int pLen = P.size();
	next[0] = -1;
	int k = -1;	// 前缀末尾字符下标
	int j = 0;	// 后缀末尾字符下标
	while (j < pLen - 1)
	{
		// p[k]表示前缀，p[j]表示后缀 
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

/* KMP算法：返回模式串P在主串S中的位置，若不存在，则函数返回值为-1 */
int index_KMP(string S, string P, int* next) {
	int sLen = S.size();
	int pLen = P.size();
	int i = 0;
	int j = 0;
	while (i < sLen && j < pLen)
	{
		/*
		备注：
		这里的 j == -1，是考虑到next[0]值为-1的情况，若j为-1，就不能作为P[j]的索引了
		*/
		if (j == -1 || S[i] == P[j])	// 当前字符匹配成功，继续匹配下一字符
		{ 
			i++; 
			j++;
		}
		else	// 当前字符匹配失败，更新j为next[j]，i不变
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
