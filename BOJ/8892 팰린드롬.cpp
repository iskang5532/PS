// 2023-03-28
// 8892 팰린드롬
// https://www.acmicpc.net/problem/8892
/*
    완전 탐색, 문자열 (2,160KB, 44ms)
    시간 복잡도: ?
    풀이)
    - 두 단어를 합쳐 만든 단어가 팰린드롬인지를 확인.
    - 단어의 개수는 최대 100 만들어진 단어의 길이는 최대 10,000이므로 최대 1억의 연산을 필요로 한다.
    즉, 완전 탐색을 이용하여 팰린드롬인 단어을 찾는다.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"
#define MAX 103 // max k

string v[MAX];

bool isPalindrome(const string &s)
{
    for (int i = 0; i < s.length() >> 1; i++)
        if (s[i] != s[s.length() - 1 - i])
            return false;
    return true;
}

int main()
{
    FAST_IO;

    int tc;
    cin >> tc;
    while (tc--)
    {
        int k;
        cin >> k;
        for (int i = 0; i < k; i++)
            cin >> v[i];

        string ans = "0";
        for (int i = 0; i < k; i++)
            for (int j = 0; j < k; j++)
                if (i != j && isPalindrome(v[i] + v[j]))
                    ans = v[i] + v[j];

        cout << ans << endl;
    }
}