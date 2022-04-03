// 1251 단어 나누기, 2993 세 부분
// https://boj.kr/1251 https://boj.kr/2993
/*
    구현, 문자열 (2,024KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 세 개의 문자열로 쪼개면 되므로, 두 개의 범위를 잡아줌.
    - 0에서부터 i, i+1부터 j, j+1부터 end()까지 문자열을 쪼갠 후 뒤집음.
    이후, 세 문자열 a, b, c를 합친 문자열과 이전에 완성한 문자열(혹은 빈 문자열)과 비교하여 사전 순으로 더 빠른 문자열을 ans에 저장.
 */

#include <iostream>
#include <algorithm>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

int main()
{
    FAST_IO;

    string s; // 3 ≤ s.len ≤ 50
    cin >> s;

    string ans;
    int n = s.length();
    for (int i = 1; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
        {
            string a = string(s.begin(), s.begin() + i),
                   b = string(s.begin() + i, s.begin() + j),
                   c = string(s.begin() + j, s.end());

            reverse(a.begin(), a.end());
            reverse(b.begin(), b.end());
            reverse(c.begin(), c.end());

            ans = ans.empty() ? a + b + c
                              : min(ans, a + b + c);
        }

    cout << ans;
}