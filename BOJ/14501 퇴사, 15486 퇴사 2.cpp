// 2022-05-23
// 14501 퇴사, 15486 퇴사 2
// https://boj.kr/14501 https://boj.kr/15486
/*
    DP (7,760KB, 216ms)
    시간 복잡도: O(n)
    풀이)
    - dp[i] = k일 때, i일에 얻을 수 있는 최대 금액은 k.
    - n+1일에 퇴사. 즉, n+1일에 얻을 수 있는 최대 금액을 출력해야 함.
    현재 풀이에서는 for문에서 n일까지 갱신됨.
    즉, dp[n+1]은 갱신되지 않았으므로 두 값을 비교 후 더 큰 값을 출력함. (dp[n] > dp[n+1]일 수 있음)
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 1'500'100

int main()
{
    FAST_IO;

    int n;
    cin >> n;
    int dp[MAX]{}; // dp[i] = k일 때, i일에 얻을 수 있는 최대 금액은 k
    for (int i = 1; i <= n; i++)
    {
        dp[i] = max(dp[i], dp[i - 1]); // 이전까지의 최대 금액과 비교하여 더 높은 금액을 저장

        int t, p;
        cin >> t >> p;

        int nt = i + t;
        dp[nt] = max(dp[nt], dp[i] + p);
    }

    cout << max(dp[n], dp[n + 1]);
}
