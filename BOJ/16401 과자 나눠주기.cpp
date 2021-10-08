/* 
 * 16401 과자 나눠주기
 * 파라메트릭 서치
 * 시간 복잡도: O(logN) (이분 탐색에서의 시간 복잡도)
 * 문제: https://www.acmicpc.net/problem/16401
 * etc.)
 * - 결정 문제로 바꿔 품.
 * - 과자를 기준값(= mid)으로 나눌 수 있는 개수(= cnt)가 m과 일치하는가를 판단. (나눈 과자의 개수는 곧 조카에게 줄 수 있는 개수)
 * 만약 cnt > m인 경우 mid가 작아 분배가 많이 된 것이며, cnt < m인 경우 mid가 커서 분배가 적은 것이다.
 * 또한 조건을 만족하는 최댓값을 구해야 하기 때문에 cnt == m인 경우에도 mid를 키워준 후 최종적으로 r값을 도출한다.
 */

#include <iostream>
#include <vector>

using namespace std;

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"
#define INF 1'000'000'000 + 1

int main()
{
#ifdef CUSTOM
    cout << "[CUSTOM]" << endl;
#else // BOJ
    FAST_IO;
#endif

    int m, n; //  조카의 수 m(1 ≤ m ≤ 1M), 과자의 수 n(1 ≤ n ≤ 1M)
    cin >> m >> n;
    vector<int> arr(n); // 과자의 길이 (1 ≤ L1, L2, ..., Ln ≤ 1G)
    for (auto &elem : arr)
        cin >> elem;

    int l = 1, r = INF;
    while (l <= r)
    {
        int mid = (l + r) / 2;

        int cnt = 0; // 기준값으로 나눈 과자의 개수
        for (const auto &elem : arr)
            cnt += elem / mid;

        if (cnt >= m)
            l = mid + 1;
        else
            r = mid - 1;
    }

    cout << r;
}