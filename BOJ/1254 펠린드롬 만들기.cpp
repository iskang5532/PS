// 2022-10-25
// 1254 펠린드롬 만들기
// https://www.acmicpc.net/problem/1254
/*
    완전 탐색 (2,024KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 문자를 i개 추가했을 때, 해당 문자열이 팰린드롬이 되는지 확인한다.
    - 문자를 i개 추가했을 때, i번 문자부터 팰린드롬인지 확인한다.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using pii = pair<int, int>;

bool isPalindrome(const string &s, int st)
{
    int l = st, r = s.length() - 1;
    while (l <= r)
    {
        if (s[l] != s[r])
            return false;
        l++, r--;
    }

    return true;
}

int main()
{
    FAST_IO;

    string s;
    cin >> s;

    int ans = s.length();
    for (int i = 0; i < s.length(); i++) // 추가할 문자의 개수
        if (isPalindrome(s, i))          // i개 추가했을 때 펠린드롬이 되는가
        {
            ans += i;
            break;
        }

    cout << ans;
}