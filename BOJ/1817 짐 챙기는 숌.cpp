// 1817 짐 챙기는 숌
// https://www.acmicpc.net/problem/1817
/*
    그리디 (2,020KB, 0ms)
    시간 복잡도: O(n)
    풀이)
    - 가장 위에 있는 책이 현재 박스의 최대 무게를 초과하지 않을 경우, 박스에 넣음.
    만약 박스의 최대 무게를 초과할 경우, 박스의 개수를 늘려주며 무게 초기화 및 책을 넣는다.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 53

int main()
{
    FAST_IO;

    int n, m; // 책의 개수 n(0 ≤ n ≤ 50), 박스의 최대 무게 m(1 ≤ m ≤ 1,000)
    cin >> n >> m;
    int v[MAX]; // 1 ≤ vi ≤ m
    for (int i = 0; i < n; i++)
        cin >> v[i];

    int ans = 0;
    int g = 0; // 횭재 박스의 무게
    for (int i = 0; i < n; i++)
        if (g - v[i] >= 0)
            g -= v[i];
        else
            g = m - v[i], ans++;

    cout << ans;
}