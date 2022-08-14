// 2022-08-09
// 1049 기타줄
// https://www.acmicpc.net/problem/1049
/*
    그리디 (2,020KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 필요한 기타줄의 개수 n을 최소한의 금액으로 n개 이상을 구매해야 한다.
    또한, 패키지 혹은 낱개 중 하나를 골라 구매해야 한다.
    즉, 패키지 중 최소 가격과 낱개 중 최소 가격만을 이용한다. 각각 mn_p, mn_u에 저장.
    - 패키지는 기타줄이 6개이다. 즉, 상대적으로 효율적인 mn_p를 구매할 경우 6개씩 구매해야 한다.
    - 더욱 효율적인 기타줄을 6개씩 구매한다.
    만약 6개씩 구매하였음에도 기타줄이 부족한 경우, 패키지의 가격과 낱개를 부족한 n개만큼의 가격을 비교 후 구매한다.
    - 주의할 점은, 입력된 브랜드의 패키지와 낱개를 하나만 골라 구매하는 것이 아니다.
    즉, 같은 브랜드라는 것은 아무 상관이 없다고 봐도 무방하다.
    etc.) 첫 풀이로 풀리긴 했지만 엉뚱하게 풀었음
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 1'003

int main()
{
    FAST_IO;

    int n, m; // 끊어진 기타줄의 개수 n(1 ≤ n ≤ 100), 브랜드의 개수 m(1 ≤ m ≤ 50)
    cin >> n >> m;
    int mn_p = MAX, mn_u = MAX; // 브랜드 및 낱개 중 가장 싼 가격
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        mn_p = min(mn_p, a), mn_u = min(mn_u, b);
    }

    int ans = 0;
    int k = n / 6;                              // 6개씩 구매 시 거래 가능한 횟수
    ans += min(mn_p * k, mn_u * 6 * k), n %= 6; // 6개씩 구매할 때 더 싼 것을 구매
    ans += min(mn_p, mn_u * n);                 // 남은 개수를 구매하기 위한 최솟값

    cout << ans;
}

// 첫 풀이
/*
    정렬 (2,024KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 패키지를 낱개로 구매 시의 가격과 비교하여 효율이 높은 순으로 정렬.
    - 가장 효율적인 가격인 v[0]으로 6개씩 구매.
    6개씩 구매하였음에도 기타줄이 부족한 경우, v[0]이 낱개가 아님.
    패키지 구매의 가격과 낱개 구매의 가격을 비교해야 하므로, v[0]부터 v[n-1]까지 낱개 판매를 탐색.
    이후, v[0]과 v[i]를 비교하여 더 싼 가격의 기타줄을 구매.
    etc.) 가장 싼 가격들만 이용한다는 것을 몰랐음.
 */

#include <iostream>
#include <vector>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using pii = pair<int, int>;
#define a first  // package
#define b second // unit
#define UNIT 0
#define PACKAGE 1

bool cmp(const pii &p1, const pii &p2)
{
    return (double)p1.a / (p1.b == UNIT ? 1 : 6) <
           (double)p2.a / (p2.b == UNIT ? 1 : 6);
}

int main()
{
    FAST_IO;

    int n, m; // 끊어진 기타줄의 개수 n(1 ≤ n ≤ 100), 브랜드의 개수 m(1 ≤ m ≤ 50)
    cin >> n >> m;
    vector<pii> v;
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;

        v.push_back({a, PACKAGE});
        v.push_back({b, UNIT});
    }

    sort(v.begin(), v.end(), cmp);

    int ans = 0;
    ans += v.front().a * (v.front().b == UNIT ? n : n / 6), n %= 6;

    int pos = 0; // v.front
    if (n)
    {
        while (v[pos].b)
            pos++;

        ans += (v.front().a < v[pos].a * n) ? v[0].a : v[pos].a * n;
    }

    cout << ans;
}