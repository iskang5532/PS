/*
    9084 동전, 3067 Coins
    DP, Knapsack (2,020KB, 0ms)
    시간 복잡도: ?
    문제: https://boj.kr/9084 https://boj.kr/3067
    풀이)
    - dp[i] = k일 때, i원을 만드는 모든 방법의 수는 k개.
    - 모든 경우의 수를 저장하는 문제이므로 코인 하나를 선택한 후, 1원씩 늘려가며 탐색하되 이전 값을 가져와 저장한다.
    etc.) 원리 이해가 어려운듯. 되는게 신기
 */

#include <iostream>
#include <vector>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define endl "\n"
#define MAX 10'000 + 1 // 최대 m

int solution()
{
    int c; // 동전의 가지 수 (1 ≤ n ≤ 20)
    cin >> c;
    vector<int> arr(c); // 1 ≤ k ≤ 10k
    for (auto &elem : arr)
        cin >> elem;
    int m; // 만들어야 할 금액 (1 ≤ m ≤ 10k)
    cin >> m;

    int dp[MAX]; // dp[i] = k일 때, i원을 만드는 모든 방법의 수는 k개
    fill(dp, dp + MAX, 0);

    dp[0] = 1;
    for (const auto &curr : arr)
        for (int i = curr; i <= m; i++) // 현재 동전의 금액부터 시작하여 m원까지 탐색
            dp[i] += dp[i - curr];      // 현재 동전의 금액을 제외한 dp값을 가져와 저장

    return dp[m];
}

int main()
{
#ifdef CUSTOM
    cout << "[CUSTOM]" << endl;
#else // BOJ
    FAST_IO;
#endif

    int tc;
    cin >> tc;

    while (tc--)
        cout << solution() << endl;
}