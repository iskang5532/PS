/* 
 * 2343 기타 레슨
 * 파라메트릭 서치
 * 시간 복잡도: ?
 * 문제: https://www.acmicpc.net/problem/2343
 * etc.) 기본적인 파라메트릭 서치 문제인 듯.
 * - 결정 문제로 바꾸어 품.
 * - 구간의 합이 기준값(= mid)을 초과하는 경우 분할 횟수(= cnt)를 +1 해주며 원하는 분할 횟수(= m)에 대한 mid값을 구해준다.
 * 만약 cnt > m인 경우 mid값이 작기 때문이며 cnt < m인 경우 mid값이 크기 때문이다.
 * 여기서 조건에 적합한 mid의 최솟값을 구해야 하기 때문에 cnt <= m를 해주어 l값을 구해준다.
 */

#include <iostream>
#include <vector>

using namespace std;

#define endl "\n"

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    int n, m; // 강의의 수 (1 ≤ n ≤ 100k), 분할 개수 (1 ≤ m ≤ n)
    cin >> n >> m;

    int mx = 0;
    vector<int> arr(n); // 강의의 길이 (<= 10k)
    for (auto &elem : arr)
        cin >> elem, mx = max(mx, elem);

    int l = mx, r = mx * n;
    while (l <= r)
    {
        int mid = (l + r) / 2;

        int cnt = 1; // 분할 횟수. (default: 1)
        int len = 0; // 구간의 합
        for (const auto &elem : arr)
        {
            len += elem;   // 현재 구간의 값을 추가함
            if (len > mid) // 만약 기준값보다 큰 경우, 횟수 +1 해주며 구간의 합은 0 + elem으로 초기화
                cnt++, len = elem;
        }

        if (cnt > m)
            l = mid + 1;
        else
            r = mid - 1;
    }

    cout << l;
}