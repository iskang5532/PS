// 2022-08-20
// 17420 깊콘이 넘쳐흘러
// https://www.acmicpc.net/problem/17420
/*
    그리디 (2,864KB, 36ms)
    시간 복잡도: ?
    풀이)
    - 주어진 사용할 날짜 Bi에 맞춰 기프티콘을 순서대로 사용한다면, 최소 횟수의 기한 연장으로 모두 사용할 수 있음.
    - 남은 기한 Ai와 사용할 날짜 Bi를 입력받아 v에 저장한 후, Bi를 기준으로 오름차순 정렬.
    - 현재 선택한 기프티콘 i를 Bi 이후에 사용할 수 있도록 해야 함.
    주의할 점은, 이전에 마지막으로 사용한 기프티콘의 날짜 mx가 Bi를 넘을 수 있음.
    즉, Ai >= max(mx, Bi)를 만족시켜야 함.
    - Ai >= mx를 만족하지 못하는 경우, 30일씩 기한을 연장하여 만족할 수 있도록 함. (이 경우, ans에 횟수를 추가)
    위를 만족하였을 경우, mx에 값을 저장.
    - Bi가 동일한 여러 개의 기프티콘이 존재할 수 있음. 이 경우, Ai >= mx를 만족하는 최대 Ai를 구한 후 mx에 저장해야 함.
    etc.)
    - 나눗셈에 문제가 있는지 모르고 헤맴. 덕분에 나눗셈 연산 잡기술 하나 배움.
    - 작년에 못푼 문제를 품어서 좋음.
 */

#include <iostream>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using ll = long long;
using pii = pair<int, int>;
#define MAX 100'003 // max n
#define T 30

bool cmp(const pii &p1, const pii &p2)
{
    return p1.second < p2.second; // 사용할 날짜를 기준으로 오름차순 정렬
}

int main()
{
    FAST_IO;

    int n; // 기프티콘의 수 (1 ≤ n ≤ 100,000)
    cin >> n;
    pii v[MAX]{}; // {남은 기한, 사용할 날짜}
    for (int i = 0; i < n; i++)
        cin >> v[i].first;
    for (int i = 0; i < n; i++)
        cin >> v[i].second;

    sort(v, v + n, cmp);

    ll ans = 0;
    int l = 0, r = 0, mx = 0;
    while (l < n)
    {
        while (v[l].second == v[r].second) // 동일한 Bi를 갖는 기프티콘의 범위를 구함
            r++;

        int h = max(mx, v[l].second);
        for (int i = l; i < r; i++)
        {
            if (v[i].first >= h) // 연장 없이 사용 가능한 경우
                mx = max(mx, v[i].first);
            else // 연장이 필요한 경우
            {
                int cnt = (h + (T - 1) - v[i].first) / T; // 연장 횟수
                // int cnt = ceil((double)(h - v[i].first) / T);

                ans += cnt;
                mx = max(mx, v[i].first + T * cnt);
            }
        }

        l = r;
    }

    cout << ans;
}

// input:
// 100
// 41 449 328 474 150 709 467 329 936 440 700 117 258 811 952 491 993 931 823 431 359 590 899 153 292 370 404 698 699 876 442 705 757 527 868 893 642 273 18 885 675 788 291 303 656 660 126 704 225 862 522 617 630 725 17 847 715 732 502 778 304 32 168 841 288 76 31 934 245 626 419 782 875 723 346 335 992 70 369 545 610 611 60 935 738 829 962 369 918 282 928 407 602 312 532 517 102 80 907 525
// 86 7 94 65 80 32 39 84 60 65 72 61 58 84 8 72 12 19 47 49 49 59 71 52 34 22 21 20 92 33 80 39 74 9 28 97 100 93 29 25 4 66 79 81 98 21 91 62 82 4 59 100 34 1 51 80 92 69 77 39 38 97 51 34 35 19 22 1 67 9 90 31 82 11 51 84 78 70 74 42 100 88 53 80 57 62 32 51 48 63 92 46 4 61 31 98 69 52 88 20
// ans:
// 3206

// input:
// 2
// 1 30
// 30 30
// ans: 1

// 21-11-29에 실패한 풀이
// 이 풀이 또한 나눗셈 실수일듯
#include <iostream>
#include <queue>
#include <algorithm>
#include <limits.h>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define endl "\n"
typedef long long ll;
const ll MUL = 30;
const ll INF = LLONG_MAX - 1;

ll mx = INF;

struct pll
{
    ll a, b;
};

bool cmp(const pll &p1, const pll &p2)
{
    if (mx == 0 || mx == 1)
        return p1.b != p2.b ? p1.b > p2.b
                            : p1.a > p2.a;
    else if (mx <= p1.b)
        return p1.b != p2.b ? p1.b > p2.b
                            : p1.a % MUL > p2.a % MUL;
    else
        return p1.b != p2.b ? p1.b > p2.b
                            // : (p1.a == p1.b ? 0 >
                            //                 : (p2.a == p2.b ? true
                            : (MUL + p1.a - (mx % MUL)) % MUL >
                                  (MUL + p2.a - (mx % MUL)) % MUL;
}

int main()
{
    FAST_IO;

    int n; // 기프티콘의 수 (1 ≤ n ≤ 100k)
    cin >> n;
    vector<pll> arr(n);
    for (auto &[a, b] : arr)
        cin >> a;
    for (auto &[a, b] : arr)
        cin >> b, mx = min(mx, b);

    ll ans = 0;
    while (!arr.empty())
    {
        sort(arr.begin(), arr.end(), cmp);
        auto [a, b] = arr.back();
        arr.pop_back();

        auto get_ans = [&](ll &a, const ll k) -> ll
        {
            ll cnt = (k - a) / MUL;
            a += MUL * cnt;
            if (a < k)
                cnt++, a += MUL;

            return cnt;
        };

        if (a < b)
            ans += get_ans(a, b);
        if (a < mx)
            ans += get_ans(a, mx);

        mx = max(mx, a);
    }

    cout << ans;
}