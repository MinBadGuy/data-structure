#include <iostream>
using namespace std;

/* 返回模式串P在主串S中的位置，若不存在，则函数返回值为-1 */
int index(const char* s, const char* p)
{
	int sLen = strlen(s);
	int pLen = strlen(p);
	int i = 0;	// i用于主串s中当前位置的下标
	int j = 0;	// j用于模式串p中当前位置的下标
	while (i < sLen && j < pLen)
	{
		if (s[i] == p[j])	// 两字符相等，则递增i和j，比较下一位置字符
		{
			i++;
			j++;
		}
		else	// 两字符不等
		{
			i = i - j + 1;	// 回退i，回到上次匹配开始的首位的下一位
							/* 此时T[j]与S[i]匹配失败，而j是从0开始递增的，表明前j个字符匹配都是成功的，
							   由此可得到i是从（i-j）开始递增的，则下次匹配从（i-j+1）开始。
							*/
			j = 0;			// 将j重置为0
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