/*
    1916 최소비용 구하기
    다익스트라 (3,688, 28ms)
    시간 복잡도: ?
    문제: https://www.acmicpc.net/problem/1916
    풀이)
    - 다익스트라 구현.
    - 시간을 줄이기 위해 c > cost[v]를 넣어줌.
    이는 다음 정점까지 가는 최소비용이 갱신할 경우가 존재하지 않는다. 그러므로 버려준다.
    etc.) 시간 초과에 대해 고민한 시간이 더 길었던 문제.
    참고)
    - 시간 초과에 대해: https://www.acmicpc.net/board/view/71228
 */

#include <iostream>
#include <queue>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define endl "\n"
#define INF 1234567890
#define MAX_N 1000 + 1 // 도시의 최대 개수

int n, m; //  // 도시의 개수 n N(1 ≤ N ≤ 1k), 버스의 개수 m(1 ≤ m ≤ 100k)
int start_vertex, end_vertex;

struct pii
{
    int v, c;
};

int dijkstra(const vector<pii> arr[])
{
    vector<int> cost(n + 1, INF);
    cost[start_vertex] = 0;

    queue<pii> q;
    q.push({start_vertex, 0});

    while (!q.empty())
    {
        auto [v, c] = q.front();
        q.pop();

        if (c > cost[v])
            continue;

        for (const auto &[nv, nc] : arr[v])
        {
            if (cost[nv] > cost[v] + nc)
            {
                cost[nv] = cost[v] + nc;
                q.push({nv, cost[nv]});
            }
        }
    }

    return cost[end_vertex];
}

int main()
{
#ifdef CUSTOM
    cout << "[CUSTOM]" << endl;
#else // BOJ
    FAST_IO;
#endif

    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    cin >> n >> m;

    vector<pii> arr[MAX_N];
    for (int i = 0; i < m; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;

        arr[a].push_back({b, c});
    }
    cin >> start_vertex >> end_vertex;

    cout << dijkstra(arr);
}