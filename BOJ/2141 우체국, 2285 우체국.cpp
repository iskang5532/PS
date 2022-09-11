// 2022-09-10
// 2141 우체국, 2285 우체국
// https://boj.kr/2141 https://boj.kr/2285
/*
    그리디, 정렬 (2,804KB, 32ms)
    시간 복잡도: ?
    풀이)
    - 입력된 수를 v에 저장한 후 마을의 위치 x를 기준으로 오름차순 정렬.
    - 0에서 가까운 가장 왼쪽 마을부터 확인. (마을에 우체국을 세울 시, 거리가 얼마인지를 확인)
    - i번 마을에서 i+1마을로 기준을 옮길 시, 이동한 거리만큼 왼쪽 구간인 (0, i]의 인원만큼 거리 손실이 발생한다.
    또한, 오른쪽 구간인 [i, n-1)만큼의 인원만큼 거리 이득이 발생한다.
    즉, 왼쪽 구간보다 오른쪽 구간의 인원이 만을 경우, 거리 이득이 발생하므로 기준이 된 마을에 우체국을 세우면 된다.
    etc.)
    참고)
    - 이론: https://www.acmicpc.net/board/view/78301
            https://blog.naver.com/jinhan814/222492135284
 */

#include <iostream>
#include <vector>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using ll = long long;
using pii = pair<int, int>;

int main()
{
    FAST_IO;

    int n; // 마을의 개수 (1 ≤ n ≤ 100,000)
    cin >> n;
    vector<pii> v(n); // {i번 마을의 위치 x, 사람의 수 a} (|xi| ≤ 1,000,000,000, 0 ≤ ai ≤ 1,000,000,000)
    ll r = 0;         // 구간 [i, n-1) 사람의 수
    for (auto &[x, a] : v)
        cin >> x >> a, r += a;

    sort(v.begin(), v.end());

    int ans = 0;
    ll l = 0; // 구간 (0, i] 사람의 수
    for (int i = 0; i < n; i++)
    {
        if (l < r)
            ans = v[i].first;

        l += v[i].second, r -= v[i].second;
    }

    cout << ans;
}

// WA - 첫 풀이
// 투 포인터 느낌으로 풀어보려다가 실패.
// 아마 long long overflow인것 같은데 어떻게 해결해야 할지 모르겠음

#include <iostream>
#include <vector>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using ll = long long;
using pii = pair<int, int>;
#define x first
#define a second

int main()
{
    FAST_IO;

    int n; // 마을의 개수 (1 ≤ n ≤ 100,000)
    cin >> n;
    ll tot_l = 0, tot_r = 0; // (0, cur] 사람의 수 tot_l, [cur, n-1) 사람의 수 tot_r
    vector<pii> v(n);        // {i번 마을의 위치 x, 사람의 수 a} (|xi| ≤ 1,000,000,000, 0 ≤ ai ≤ 1,000,000,000)
    for (auto &[x, a] : v)
        cin >> x >> a, tot_r += a;
    tot_r -= v[0].a;

    sort(v.begin(), v.end());

    ll l = 0, r = 0; // (0, cur]에서 cur까지 거리의 합 l, cur에서 [cur, n-1)까지 거리의 합 r
    for (int i = 1; i < n; i++)
        r += 1LL * (v[i].x - v[0].x) * v[i].a;

    int ans = v[0].x;
    ll mn = r;
    for (int cur = 1; cur < n; cur++)
    {
        int dist = v[cur].x - v[cur - 1].x; // 두 구간 사이의 거리

        tot_l += v[cur - 1].a;
        l += tot_l * dist;

        r -= tot_r * dist;
        tot_r -= v[cur].a;

        if (mn > l + r)
            ans = v[cur].x, mn = l + r;
    }

    cout << ans;
}