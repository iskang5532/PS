// 2022-05-28
// 4096 팰린드로미터
// https://www.acmicpc.net/problem/4096
/*
    완전 탐색 (2,024KB, 4ms)
    시간 복잡도: O(10^(s.length / 2 - 1))?
    풀이)
    - 현재 문자열 s가 팰린드롬이 될 때까지 탐색.
    - 만약 s가 팰린드롬이 아닐 경우, 값에 1을 더함.
     - s에서 현재 탐색중인 값의 위치는 r. (r의 초기 위치는 s.length - 1)
     - 만약 s[r] == '9'일 경우, s[r]을 '0'으로 바꾼 후 왼쪽 위치인 r-1을 탐색.
     - 만약 s[r] != '9'일 경우, s[r]++.
    - 형변환을 이용한 풀이를 사용할 시, 수의 가장 앞 값이 0일 때 형변환 할 경우 값이 사라질 수 있음에 주의.
    etc.) 이게 완탐이 되네
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"

bool isPalindrome(const string &s)
{
    int l = s.length();
    for (int i = 0; i < l / 2; i++)
        if (s[i] != s[l - 1 - i])
            return false;
    return true;
}

void get_next_num(string &s) // 문자열 s에 +1
{
    int r = s.length() - 1;
    while (s[r] == '9')
        s[r] = '0', r--;
    s[r]++;
}

int main()
{
    FAST_IO;

    string s;

    while (cin >> s)
    {
        if (s == "0")
            break;

        int cnt = 0;
        while (!isPalindrome(s))
            cnt++, get_next_num(s);

        cout << cnt << endl;
    }
}