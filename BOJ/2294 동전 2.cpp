// 2023-02-04
// 2294 동전 2
// https://www.acmicpc.net/problem/2294
/*
    DP (2,180KB, 4ms)
    시간 복잡도: ?
    풀이)
    - i개의 동전을 이용하여 만든 금액이면서 사용한 동전의 최소 개수를 저장할 dp.
    - i번 동전을 이용하여 구한 최소 개수를 이용하여 i+1번과 함께 만들 수 있는 최소 개수를 구함.
    금액 m에서 i+1번 동전의 가치만큼 뺀 dp값이 존재할 경우, 현재 dp값과 이전 dp값+1과 비교하여 최솟값을 저장.
    - 해당 금액을 만들 수 없을 경우, -1을 출력.
    etc.) 설명이 어려움
 */

#include <iostream>
#include <vector>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define INF 0x3f3f3f3f
#define MAX 103

int main()
{
    FAST_IO;

    int n, k; // 동전의 개수 n(1 ≤ n ≤ 100), 원하는 가치 k(1 ≤ k ≤ 10,000)
    cin >> n >> k;
    int v[MAX]{};
    for (int i = 0; i < n; i++)
        cin >> v[i];

    vector<int> dp(k + 1, INF);
    dp[0] = 0;
    for (int i = 0; i < n; i++)
        for (int m = v[i]; m <= k; m++)
            dp[m] = min(dp[m], dp[m - v[i]] + 1);

    cout << (dp[k] == INF ? -1 : dp[k]);
}