/* 
 * 15686 치킨 배달
 * brute-force
 * 시간 복잡도: ?
 * 문제: https://www.acmicpc.net/problem/15686
 * etc.) 복잡해 보이지만 딱 맞게 풀려서 기분이 좋았던 문제.
 */

#include <iostream>
#include <vector>
#include <algorithm> // next_permutation
#include <numeric>   // accumulate

using namespace std;

#define endl "\n"
#define INF 987654321
typedef pair<int, int> pii;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    int n, m; // 도시의 크기 (2 <= n <= 50), 치킨집의 개수 (1 <= m <= 13)
    cin >> n >> m;

    vector<pii> H, C; // 집의 위치, 치킨집의 위치
    for (int col = 0; col < n; col++)
        for (int row = 0; row < n; row++)
        {
            int k;
            cin >> k;
            if (k == 1) // 집
                H.push_back(pii{col, row});
            else if (k == 2) // 치킨집
                C.push_back(pii{col, row});
        }

    int ans = INF;                  // 치킨 거리의 최솟값
    vector<bool> P(C.size(), true); // 사용할 치킨집 (false 경우) ex.) 001일 경우, [0], [1] 사용하며 [2] 폐업
    fill(P.begin(), P.begin() + m, false);
    do
    {
        vector<int> dist(H.size(), INF);   // dist[i]는 i번째 집의 최소 치킨 거리
        for (int i = 0; i < P.size(); i++) // i번쨰 치킨집의 위치
            if (!P[i])
            {
                const auto [y, x] = C[i];
                for (int j = 0; j < H.size(); j++) // j번째 집
                {
                    const auto [col, row] = H[j];
                    dist[j] = min(dist[j], abs(y - col) + abs(x - row));
                }
            }

        ans = min(ans, accumulate(dist.begin(), dist.end(), 0));
    } while (next_permutation(P.begin(), P.end()));

    cout << ans;
}