/* 
 * 7453 합이 0인 네 정수
 * 정렬, 이분 탐색
 * 시간 복잡도: ?
 * 문제: https://www.acmicpc.net/problem/7453
 * etc.) a, b, c, d의 합이 0인 값을 일일이 구할 경우 시간 초과.
 * 때문에 a+b와 c+d를 따로 만든 ab와 cd를 이용해 서로 값을 비교하여 상반된 값(= ab-cd = 0)이 나올 경우 ans++를 해줌.
 */

#include <iostream>
#include <vector>
#include <algorithm> // sort

using namespace std;

#define endl "\n"
#define MAX 4000 + 1
typedef long long ll;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    int n; // 배열의 크기 (1 ≤ n ≤ 4k)
    cin >> n;

    vector<vector<int>> arr(n, vector<int>(4));
    for (auto &col : arr)
        for (auto &row : col)
            cin >> row; // ≤ |2^28|

    vector<int> ab, cd; // a + b 및 c + d
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            ab.push_back(arr[i][0] + arr[j][1]), cd.push_back(arr[i][2] + arr[j][3]);

    sort(ab.begin(), ab.end()), sort(cd.begin(), cd.end());

    ll ans = 0; // max: n^4 (= 256,000,000,000,000)
    for (const auto &elem : ab)
    {
        auto [lo, hi] = equal_range(cd.begin(), cd.end(), -elem);
        ans += hi - lo;
    }

    cout << ans;
}

// 2    ans:16
// 0 0 0 0
// 0 0 0 0