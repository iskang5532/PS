// 2023-03-01
// 27627 Splitology
// https://www.acmicpc.net/problem/27627
/*
    구현 (2,024KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 입력된 문자열 s를 반으로 나눈 후, 나눈 두 문자열이 팰린드롬인지 확인.
    만약 두 문자열 모두 팰린드롬일 경우, 두 문자열 출력.
    만약 두 문자열 모두 팰린드롬인 적이 없을 경우, "NO" 출력.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

bool isPalindrome(const string &s)
{
    for (int i = 0; i < s.length() / 2; i++)
        if (s[i] != s[s.length() - 1 - i])
            return false;
    return true;
}

int main()
{
    FAST_IO;

    string s;
    cin >> s;
    bool flag = false;
    for (int l = 1; l < s.length(); l++) // 한 쪽 문자열의 길이
    {
        string s1 = string(s.begin(), s.begin() + l);
        string s2 = string(s.begin() + l, s.end());
        if (isPalindrome(s1) && isPalindrome(s2))
        {
            flag = true;
            cout << s1 << ' ' << s2;
            break;
        }
    }

    if (!flag)
        cout << "NO";
}