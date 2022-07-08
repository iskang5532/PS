// 2022-07-06
// 5911 선물
// https://www.acmicpc.net/problem/5911
/*
    그리디, 정렬 (2,024KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 선물을 보내는데 필요한 선물 비용을 기준으로 오름차순 정렬.
    만약, 선물 비용이 같으면 선물의 가격을 기준으로 내림차순 정렬.
    내림차순 정렬의 이유는, 더 비싼 가격의 선물을 할인하게 되면 선물 비용이 줄어들기 때문.
    - 현재까지 가장 비싼 선물 가격을 저장할 mx.
    - i번째 선물과 이전까지의 선물 비용의 합이 b를 넘을 수 있음.
    이때, 현재까지 확인한 선물 가격 중 가장 비싼 선물인 mx를 할인시킨다면 남은 b원으로 살 수 있는지를 확인.
 */

#include <iostream>
#include <vector>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using pii = pair<int, int>;
#define p first
#define s second

bool cmp(const pii &p1, const pii &p2)
{
    int a = p1.p + p1.s, b = p2.p + p2.s;
    return a != b ? a < b : p1.p > p2.p; // 선물 비용 오름차순, 선물 가격 내림차순
}

int main()
{
    FAST_IO;
    int n, b;
    cin >> n >> b;

    vector<pii> v(n);
    for (auto &[p, s] : v)
        cin >> p >> s;

    sort(v.begin(), v.end(), cmp);

    int ans = 0;
    int mx = 0;
    for (const auto &[p, s] : v)
    {
        mx = max(mx, p);

        if (b - (p + s) + mx - (mx / 2) < 0)
            break;
        b -= p + s, ans++;
    }

    cout << ans;
}