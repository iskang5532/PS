// 2023-01-10
// 12865 평범한 배낭
// https://www.acmicpc.net/problem/12865
/*
    DP, Knapsack (42,136KB, 40ms)
    시간 복잡도: ?
    풀이)
    2차원, 즉 현재와 이전 값을 나눈 이유는, 현재 값만을 사용하게 된다면 동일한 보석을 연속으로 배낭에 넣게 된다. (맞나? 작성 시에 확인해볼 것)
    etc.)
    참고)
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using pii = pair<int, int>;
#define MAX_N 103
#define MAX_K 100'003
#define w first
#define v second

int main()
{
    FAST_IO;

    int n, k;
    cin >> n >> k;
    pii arr[MAX_N]{};
    for (int i = 0; i < n; i++)
        cin >> arr[i].w >> arr[i].v;

    int dp[MAX_K]{};
    for (int w = 1; w <= n; w++)
    {
        auto [_w, _v] = arr[w - 1];
        for (int v = 0; v <= k; v++)
            dp[v] = max(dp[v], // 이전 최댓값
                        (v - _w >= 0 ? _v + dp[v - _w] : 0));
    }

    cout << dp[k];
}

// ~2023-01-10
/*
 * 12865 평범한 배낭
 * DP, knapsack
 * 시간 복잡도: ?
 * 문제: https://www.acmicpc.net/problem/12865
 * etc.) 이렇게 풀면 되겠다~ 하고 감을 잡기가 어려움.
 * 참고: https://gsmesie692.tistory.com/113
 */

#include <iostream>
#include <vector>

using namespace std;

#define endl "\n"

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    int n, k; // 1 <= n <= 100, 1 <= k <= 100k
    cin >> n >> k;

    vector<int> w(n), v(n); // 1 <= w <= 100k, 0 <= v <= 1k
    for (int i = 0; i < n; i++)
        cin >> w[i] >> v[i];

    vector<int> curr(k + 1, 0), prev(k + 1, 0); // dp[n]일 경우, 무게 n일 때 만들 수 있는 최대 가치
    for (int i = 0; i < n; i++)                 // 물건을 하나씩 확인함
    {
        for (int pos = w[i]; pos <= k; pos++)                    // 현재 물건의 무게(= pos)에서부터 측정
            curr[pos] = max(prev[pos], v[i] + prev[pos - w[i]]); // 이전 값의 가치 or 현재 물건의 가치 + 이전 값 (현재 물건을 포함시킨 경우이기 때문에 무게는 0에서부터)

        prev = curr;
    }

    cout << curr.back();
}

// 4 10
// 6 13
// 3 6
// 4 8
// 5 100
// ans: 108

// []: i번째 값의 시작점
//         0   1   2   3   4   5   6   7   8   9   10
// 3 6     0   0   0  [6]  6   6   6   6   6   6   6
// 4 8     0   0   0   6  [8]  8   8   14  14  14  14
// 5 100   0   0   0   6   8 [100] 100 100 106 108 108
// 6 13    0   0   0   6   8  100 [100] ...