/* 
 * 7579 앱
 * DP, knapsack
 * 시간 복잡도: O(nm)? (dp 구성 시의 시간복잡도)
 * 문제: https://www.acmicpc.net/problem/7579
 * etc.) 메모리 M을 기준으로 공간을 확보할 경우 시간 및 메모리가 비효율적이라 생각하여 비용 c를 기준으로 작성.
 * 참고: 
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define endl "\n"

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    int n, m; // 앱의 개수 (1 <= n <= 100), 필요한 메모리 (1 <= m <= 10M)
    cin >> n >> m;

    int mx = 0; // 입력된 비활성화 비용의 총합
    vector<int> a(n), c(n); // 메모리 크기 (M <= a1 + a2 + ... +  aN), 비활성화 비용 (0 <=  c1, ..., cN <= 100)
    for (auto &elem : a)
        cin >> elem;
    for (auto &elem : c)
    {
        cin >> elem;
        mx += elem;
    }

    vector<int> curr(mx + 1, 0), prev(mx + 1, 0); // dp[idx]는 비용 idx로 확보할 수 있는 메모리의 값
    for (int i = 0; i < n; i++)
    {
        for (int j = c[i]; j <= mx; j++) // 현재 비용부터 채워 나감
            curr[j] = max(prev[j], a[i] + prev[j - c[i]]); // 이전 비용 or 현재 비용을 추가하고 남아 있는 비용으로 얻을 수 있는 최댓값을 넣어줌 (남은 값: prev[j - c[i]])

        prev = curr;
    }

    cout << lower_bound(curr.begin(), curr.end(), m) - curr.begin(); // 필요한 메모리 이상을 얻을 수 있는 위치(= 최소 비용)를 찾음
}