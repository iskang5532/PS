// 2022-07-14
// 2258 정육점
// https://www.acmicpc.net/problem/2258
/*
    그리디, 정렬 (3,464KB, 28ms)
    시간 복잡도: ?
    풀이)
    - 비싼 고기를 구매할 경우, 해당 고기보다 가격이 미만인 고기들은 무료가 된다.
    여기서 주의할 점은, '미만'이라는 점이다.
    즉, 동일한 가격의 고기는 원가로 구매해야 한다는 것.
    두 고기 a, b가 있으며 a.p == w.p이며 a.w < b.w일 때, 무게가 더 높은 b를 구매해야 효율이 좋다.
    또한 a와 b를 동시에 구매하여 무게 m을 충족시킬 수도 있으며, a, b보다 가격이 높은 고기 c를 구매하여 a, b를 무료로 구매할 수도 있다.
    - 입력된 고기를 가격 p를 기준으로 오름차순 정렬. 만약 가격이 같다면 무게 w를 기준으로 내림차순 정렬.
    - 가격이 같은 고기가 연속으로 몇 번 나온지를 저장할 cnt.
    - 현재까지 탐색한 무게의 합을 저장할 sum.
    만약 sum >= m일 경우, 무게를 저장한다.
    이때, 가격이 같은 고기가 연속되었을 경우 해당 고기는 무료가 아니므로 개수만큼 가격에 추가되어야 한다.
    또한, 위에서 언급한 것과 같이 가격이 큰 고기를 구매하였지만 p*cnt보다 가격이 덜 나갈 수 있으므로, min을 이용하여 가격을 최소화한다.
    etc.) WA 두번뜨고 정답률 확인했는데 쎄했던 문제.
    참고)
    - 반례: https://www.acmicpc.net/board/view/90723
 */

#include <iostream>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using ll = long long;
using pll = pair<ll, ll>;
#define MAX 100'003 // max n
#define w first
#define p second

bool cmp(const pll &p1, const pll &p2)
{
    return p1.p != p2.p ? p1.p < p2.p : p1.w > p2.w;
}

int main()
{
    FAST_IO;

    int n, m; // 덩어리의 개수 n(1 ≤ n ≤ 100,000), 필요 무게 m(1 ≤ m ≤ 2,147,483,647)
    cin >> n >> m;
    pll v[MAX];
    for (int i = 0; i < n; i++)
        cin >> v[i].w >> v[i].p; // 무게 w, 가격 p

    sort(v, v + n, cmp);

    ll ans = 0x80000000;
    int sum = 0;
    for (int i = 0, cnt = 1; i < n; i++) // cnt: 가격의 연속된 개수
    {
        auto [w, p] = v[i];
        sum += w;

        p == v[i - 1].p ? cnt++ : cnt = 1; // 이전 가격과 같은가

        if (sum >= m)
            ans = min(ans, p * cnt);
    }

    cout << (ans == 0x80000000 ? -1 : ans);
}