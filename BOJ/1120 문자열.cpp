// 1120 문자열
// https://www.acmicpc.net/problem/1120
/*
    구현, 문자열 (2,024KB, 0ms)
    시간 복잡도: O(a.len^2)
    풀이)
    - s1과 s2를 비교하여 다른 문자의 개수를 파악.
    비교할 때, s1의 길이만큼 비교.
    - s2은 0에서부터 s1의 길이만큼 탐색 및 비교하며, s2의 마지막 문자가 탐색될 때까지 반복.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define INF 98754321

int main()
{
    FAST_IO;

    string s1, s2;
    cin >> s1 >> s2;

    int ans = INF;
    for (int j = 0; j <= s2.length() - s1.length(); j++) // s2의 시작점
    {
        int cnt = 0; // 다른 문자의 개수
        for (int i = 0; i < s1.length(); i++)
            if (s1[i] != s2[j + i])
                cnt++;

        ans = min(ans, cnt);
    }

    cout << ans;
}