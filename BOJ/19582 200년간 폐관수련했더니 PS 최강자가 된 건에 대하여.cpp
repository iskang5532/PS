// 2022-08-23
// 19582 200년간 폐관수련했더니 PS 최강자가 된 건에 대하여
// https://www.acmicpc.net/problem/19582
/*
    그리디 (2,804KB, 28ms)
    시간 복잡도: ?
    풀이)
    - 대회는 최대 한 번 빠질 수 있음. 즉, 빠진 대회를 제외한 모든 대회의 금액 조건 x를 만족해야 함.
    - 대회를 몇 번 빠지는지를 확인함. 만약 두 번 이상 빠지게 될 경우 "Zzz" 출력.
    - 최대 금액을 구하는 것이 아니므로, 빠지는 대회는 금액 p가 높은 대회일 수록 좋으므로 현재까지의 최대 p값을 mx에 저장.
    예외가 있는데, 현재까지 얻은 모든 금액 tot에서 mx를 제외하더라도 현재 대회의 x를 만족하지 못할 수가 있음.
    이때는 mx인 대회를 빠지는 것이 아닌 현재 대회를 빠짐으로서 조건 x를 없애버려 해결.
    etc.)
    참고)
    - 반례: https://www.acmicpc.net/board/view/55324
            https://www.acmicpc.net/board/view/55326
 */

#include <iostream>
#include <vector>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using ll = long long;
using pii = pair<int, int>;

int main()
{
    FAST_IO;

    int n; // 1 ≤ n ≤ 100,000
    cin >> n;
    vector<pii> v(n); // {제한 금액 x, 획득 금액 p} (1 ≤ xi, pi ≤ 10^9)
    for (auto &[x, p] : v)
        cin >> x >> p;

    ll tot = 0;
    int cnt = 0, mx = 0; // 대회를 빠져야 하는 횟수 cnt, 최대 금액 mx
    for (const auto &[x, p] : v)
    {
        if (tot > x) // 금액이 너무 커 대회를 빠져야 하는 경우
        {
            tot -= (tot - mx <= x) ? max(mx, p) // 최댓값을 빼면 조건 x를 만족하는가?
                                   : p;         // 현재 대회 자체를 불참해야 함 (불참으로 인해 x를 신경쓰지 않음)
            cnt++;
        }

        mx = max(mx, p);
        tot += p;
    }

    cout << (cnt <= 1 ? "Kkeo-eok" : "Zzz");
}

// input:
// 6
// 0 3
// 4 5
// 9 5
// 4 2
// 13 2
// 12 3
// ans:
// Zzz