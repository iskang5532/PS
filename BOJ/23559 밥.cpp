// 2022-07-28
// 23559 밥
// https://www.acmicpc.net/problem/23559
/*
    그리디, 정렬 (2,808KB, 28ms)
    시간 복잡도: ?
    풀이)
    - 준원이는 모든 메뉴를 5,000원짜리로 구매하였다고 가정.
    - 입력된 5,000원 메뉴의 수치 a와 1,000원 메뉴의 수치 b의 차이를 기준으로 오름차순 정렬. (앞에 존재할수록 1,000원으로 옮길 시에 떨어지는 수치가 큼)
    - 5,000원에서 1,000원으로 옮기며 가격을 x원을 넘지 않도록 맞춤.
    값을 맞히는 과정에서 a를 빼고 b를 더하며, 가격 또한 5,000원을 빼고 1,000원을 더함.
    - 5,000원에서 1,000원으로 옮길 시 수치가 증가할 수 있음.
    이러한 값이 존재하는지 확인하며, 만약 존재하면 1,000원의 수치로 바꿈.
    etc.) 어려웠음
 */

#include <iostream>
#include <vector>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using pii = pair<int, int>;

bool cmp(const pii &p1, const pii &p2) { return p1.first - p1.second < p2.first - p2.second; }

int main()
{
    FAST_IO;

    int n, x; // 일수 n(1 ≤ n ≤ 100,000), 소지금 x(1,000n ≤ x ≤ 5,000n)
    cin >> n >> x;
    int ans = 0;
    vector<pii> v(n);
    for (auto &[a, b] : v)
        cin >> a >> b, ans += a;

    sort(v.begin(), v.end(), cmp);

    int pos = 0;
    int tot = 5000 * n;
    while (pos < n && tot > x) // x원에 맞춤
    {
        auto [a, b] = v[pos];

        ans += b - a;
        tot += 1000 - 5000;

        pos++;
    }

    for (int i = pos; i < n; i++) // 1,000원의 수치가 더 큰 메뉴가 존재하는지 탐색
    {
        auto [a, b] = v[i];
        if (a > b)
            break;
        ans += b - a;
    }

    cout << ans;
}