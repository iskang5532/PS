/* 
 * 12865 평범한 배낭
 * DP, knapsack
 * 시간 복잡도: ?
 * 문제: https://www.acmicpc.net/problem/12865
 * etc.) 이렇게 풀면 되겠다~ 하고 감을 잡기가 어려움.
 */

#include <iostream>
#include <vector>
#include <algorithm> // sort

using namespace std;

#define endl "\n"
#define w first
#define v second

typedef pair<int, int> pii;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    int n, k; // 1 <= n <= 100, 1 <= k <= 100k
    cin >> n >> k;

    vector<pii> arr(n); // 1 <= w <= 100k, 0 <= v <= 1k
    for (auto &elem : arr)
        cin >> elem.w >> elem.v;
    sort(arr.begin(), arr.end());

    vector<int> curr(k + 1, 0), prev(k + 1, 0); // dp[n]일 경우, 무게 n일 때 만들 수 있는 최대 가치
    for (const auto &elem : arr)                // 물건을 하나 씩 확인함
    {
        if (elem.w > k) // 만약 현재 물건이 원하는 무게를 충족하지 않는 경우 (이는 곧 앞으로의 물건 또한 무게가 나간다는 뜻이기 때문에 종료시킴)
            break;

        for (int pos = elem.w; pos <= k; pos++)                      // 현재 물건의 무게(= pos)에서부터 측정
            curr[pos] = max(prev[pos], elem.v + prev[pos - elem.w]); // 이전 값의 가치 or 현재 물건의 가치 + 이전 값 (현재 물건을 포함시킨 경우이기 때문에 무게는 0에서부터)

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