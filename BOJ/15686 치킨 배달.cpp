// 15686 치킨 배달
// https://www.acmicpc.net/problem/15686
/*
    구현 (2,024KB, 4ms)
    시간 복잡도: ?
    풀이)
    etc.)
    참고)
 */

#include <iostream>
#include <vector>
#include <algorithm> // permutation
#include <numeric>   // accumulate

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define INF 98754321
#define MAX_N 50 + 1
using pii = pair<int, int>;

vector<pii> h, ch; // 집의 위치 h, 치킨집 위치 ch
vector<int> dist;  // dist[i] = k일 떄, i번째 집의 최소 치킨 거리는 k

void get_dist(int cur) // 현재 치킨집과의 거리를 구함
{
    auto [y1, x1] = ch[cur];
    for (int i = 0; i < h.size(); i++) // i번째 집
    {
        const auto &[y2, x2] = h[i];
        int l = abs(y1 - y2) + abs(x1 - x2); // h[i] to ch[cur]의 치킨 거리

        dist[i] = min(dist[i], l);
    }
}

int main()
{
    FAST_IO;

    int n, m; // 크기 n(2 ≤ N ≤ 50), 치킨집의 개수 M(1 ≤ M ≤ 13)
    cin >> n >> m;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            int k;
            cin >> k;
            if (k == 1)
                h.push_back({i, j});
            else if (k == 2)
                ch.push_back({i, j});
        }

    vector<bool> check(ch.size(), false); // check[i] = true일 때, i번째 치킨집은 사용하는 치킨집
    fill(check.begin(), check.begin() + m, true);

    int ans = INF;
    dist.resize(h.size());
    do
    {
        fill(dist.begin(), dist.end(), INF);
        for (int i = 0; i < check.size(); i++)
            if (check[i]) // i번째 치킨집은 사용하는 치킨집인가
                get_dist(i);

        ans = min(ans, accumulate(dist.begin(), dist.end(), 0));
    } while (prev_permutation(check.begin(), check.end()));

    cout << ans;
}