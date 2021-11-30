/*
    5719 거의 최단 경로
    다익스트라 (2,528KB, 44ms)
    시간 복잡도: ?
    문제: https://www.acmicpc.net/problem/5719
    풀이)
    - 세 번의 다익스트라를 수행.
     - 첫 번째 다익스트라는 시작점에서 도착점까지의 최단 거리(= d_mn)를 파악.
     - 두 번째 다익스트라는 각 정점까지의 최단 거리(= dist_mn)와 최단 경로(= visited)를 파악.
     - 세 번째 다익스트라는 첫 번째 다익스트와 마찬가지로 시작점에서 도착점까지의 최단 거리(= ans)를 파악.
     이때, (탐색 중인 경로 == 최단 경로) 혹은 (다음 정점까지의 거리 == 최단 거리)일 경우, 탐색하지 않는다.
    - 다익스트라에서 flag를 이용해 구해야 할 값이 최단 경로인지 거의 최단 경로인지를 판별함.
    etc.) tc 다 맞았는데도 83%에서 틀렸습니다 나와서 아이러니했던 문제. 배열과 벡터 등이 너무 많아서 지저분해 보이는 풀이..
    - dist_mn이랑 visited를 하나로 합칠 수 있을듯 싶은데 해결하지 못했음.
    참고)
    - tc: https://maratona.ime.usp.br/hist/2008/problemas08.html (Almost Shortest Path)
 */

#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define endl "\n"
#define INF 1234567890
#define MAX 500 + 1
typedef pair<int, int> pii;

int n, m;               // 장소의 수 n(2 ≤ n ≤ 500), 도로의 수 m(1 ≤ m ≤ 10k)
int s, d;               // 시작점 s, 도착점 d (s ≠ d; 0 ≤ s, d < n)
int d_mn;               // 도착점까지의 최단 거리
int dist_mn[MAX];       // 시작점에서 각 정점까지의 최단 거리
bool visited[MAX][MAX]; // a to b가 최단 경로인가? (visited[2][4] == true일 경우, 2에서 4로 가는 경로는 최단 경로)

int dijkstra(const vector<vector<pii>> &arr, const bool flag = false) // flag: 최단 경로를 제거하는가?
{
    vector<int> prev(n, INF), dist(n, INF); // 이전 정점 prev, 시작점에서 각 정점까지의 거리 dist
    prev[0] = INF, dist[s] = 0;

    queue<pii> q;
    q.push({s, 0});
    while (!q.empty())
    {
        auto [curr, c] = q.front();
        q.pop();
        for (const auto &[next, nc] : arr[curr])
        {
            if (flag && (c + nc == dist_mn[next] || visited[curr][next])) // 다음 정점까지의 거리가 최단 거리 or 현재 경로가 최단 경로인 경우
                continue;
            if (dist[next] >= dist[curr] + nc) // >가 아닌 >=인 이유는, 두 번째 다익스트라로 최단 경로를 탐색할 때, 여러 개의 최단 경로가 존재할 수 있기 때문
            {
                if (dist[next] > dist[curr] + nc) // 거리 갱신이 가능한 경우
                    q.push({next, dist[next] = dist[curr] + nc});
                prev[next] = curr;

                if (next == d && dist[next] == d_mn) // 다음 정점이 도착점이면서 최단 거리인 경우, 시작점ㅇ서 도착점까지의 경로를 저장
                    for (int x = next; prev[x] != INF; x = prev[x])
                        dist_mn[x] = dist[x], visited[prev[x]][x] = true;
            }
        }
    }

    return dist[d];
}

int main()
{
    FAST_IO;

    while (cin >> n >> m)
    {
        if (!n && !m)
            break;

        cin >> s >> d;

        vector<vector<pii>> arr(n);
        for (int i = 0; i < m; i++)
        {
            int u, v, p; // U에서 V로 가는 도로의 길이가 P (U ≠ V ; 0 ≤ U, V < n; 1 ≤ P ≤ 103)
            cin >> u >> v >> p;

            arr[u].push_back({v, p});
        }

        for (int i = 0; i < MAX; i++)
            fill(visited[i], visited[i] + MAX, false);
        fill(dist_mn, dist_mn + MAX, INF);

        d_mn = dijkstra(arr);          // 1. 최단 거리 구하기 (시작점에서 도착점까지의)
        dijkstra(arr);                 // 2. 최단 경로 구하기 (시작점에서 도착점까지의)
        int ans = dijkstra(arr, true); // 3. 답 구하기 (= 거의 최단 경로의 길이)
        ans == INF ? cout << -1 << endl : cout << ans << endl;
    }
}

// 16% (not used dist_mn[])
// 4 5
// 0 2
// 0 1 1
// 0 3 5
// 1 2 2
// 1 3 1
// 3 2 1
// 0 0
// ans: -1

// 83% (not used visited[])
// 6 8 0 5
// 0 1 1
// 1 2 1
// 2 3 1
// 3 4 1
// 4 5 1
// 0 2 2
// 2 5 10
// 0 5 5
// 0 0
// ans: -1
