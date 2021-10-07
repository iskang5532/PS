/* 
 * 2613 숫자 구슬
 * 파라메트릭 서치
 * 시간 복잡도: O(logN) (이분 탐색에서의 시간 복잡도)
 * 문제: https://www.acmicpc.net/problem/2613
 * etc.) 구한 최댓값으로 분할 시에 m과 다를 수가 있었음. 결국 스스로 해결하지 못함.
 * - 결정 문제로 바꿔 품.
 * - 만약 기준값(= mid)으로 분할했을 때의 개수(= cnt)가 조건을 만족시키는가?
 * 분할 시 cnt > m인 경우 mid값이 너무 작아서이며, cnt < m인 경우 mid값이 너무 커서이다.
 * 또한 조건을 만족시키는 최솟값을 구하는 것이기 때문에 cnt <= m을 해주며 l값을 구했음.
 * 주의할 점은, 그룹을 나눈 후에 구한 최댓값(= l)을 제대로 구했다고 하더라도 cnt != m이 될 수 있음. (반례는 밑에)
 * - 아직 의문인 분할 대상이 l값일 경우, 분할 시에는 l값이 아니게 되지 않는가? (1을 출력하는 것을 보아 입력이 1일 때에만 생기는 일인듯 싶기도)
 * 참고: https://www.acmicpc.net/board/view/25042 (반례)
 */

#include <iostream>
#include <vector>

using namespace std;

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"

int main()
{
#ifdef CUSTOM
    cout << "[CUSTOM]" << endl;
#else // BOJ
    FAST_IO;
#endif
    int n, m; // 구슬의 개수 (1 <= N <= 300), 그룹의 개수 (1 <= M <= N)
    cin >> n >> m;

    int mx = 0;
    vector<int> arr(n); // 1 <= 100
    for (auto &elem : arr)
        cin >> elem, mx = max(mx, elem);

    int l = mx, r = mx * n;
    while (l <= r)
    {
        int mid = (l + r) / 2;
        int sum = 0; // 구간의 합

        int cnt = 1; // 그룹의 개수
        for (const auto &elem : arr)
        {
            sum += elem;
            if (sum > mid)
                cnt++, sum = elem;
        }

        if (cnt > m)
            l = mid + 1;
        else
            r = mid - 1;
    }

    vector<int> p; // i번째에 저장되어 있는 구슬의 개수
    int sum = 0, cnt = 0;
    for (const auto &elem : arr)
    {
        sum += elem, cnt++;
        if (sum > l)
            p.push_back(cnt - 1), cnt = 1, sum = elem;
    }
    p.push_back(cnt); // 마지막 카운트 추가

    int lack = m - p.size(); // 부족한 그룹의 개수

    cout << l << endl;
    for (auto &elem : p)
    {
        if (lack && elem > 1) // 분할이 가능할 경우
            cout << "1 ", lack--, elem--;

        cout << elem << " ";
    }
}

// 9%
// 2 2 1 10
// ans: 10 1 1

// 45%
// 9 6
// 1 1 1 1 1 1 1 1 1

// 4 4
// 3 1 1 1
// ans: 1 1 1 1