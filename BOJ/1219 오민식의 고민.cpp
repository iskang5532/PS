// 1219 오민식의 고민
// https://www.acmicpc.net/problem/1219
/*
    SPFA + BFS (2,024KB, 0ms)
    시간 복잡도: O(VE) (최악: O(V + E); SPFA의 시간 복잡도)
    풀이)
    - SPFA를 이용해 시작점에서부터 도착 도시까지의 최대 액수(이하 거리)를 구함.
    1) 사이클이 발생한 지점을 찾은 후, bfs_q에 저장.
    사이클이 생기는 구간은 하나가 아닐 수 있음.
    2) bfs_q에 저장된 정점들을 이용하여 도착 도시에 도달할 수 있는지를 판단.
    만약 도착할 수 있다면, "Gee" 출력. (= 무한한 돈을 가지고 도착함)
    - 사이클이 발생하여도 도착 도시에 도착할 수 없을 수 있음.
    이때의 출력은 "gg" (= 순서가 있음)
    - ll을 사용해야 함.
    50개의 경로를 통해 100만을 얻을 시 5000만. 이때, 사이클이 발생한다면 n번, 즉 추가로 50번을 더 돌게 된다.
    이는 50*50*1,000,000이며 21억을 넘는 값이 된다.
    etc.) 민식이의 고민보다 내 고민이 컸던 문제
    참고)
    - 음의 사이클에 대해: https://his130.tistory.com/262
 */

#include <iostream>
#include <queue>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#define endl "\n"
#define MAX 50 + 1 // 도시 및 경로의 최대 개수
using ll = long long;
using pii = pair<int, int>;
constexpr ll INF = 1e10; // 50 * 50 * 1,000,000

int n, st, ed, m; // 도시의 수 n, 경로의 수 m (1 ≤ n, m ≤ 50), 시작 도시 st, 도착 도시 ed
vector<pii> v[MAX];
int money[MAX];
queue<int> bfs_q; // 사이클이 생긴 정점을 저장

ll SPFA()
{
    queue<int> q;
    vector<ll> dist(n + 1, INF); // dist[n] = k일 때, st에서 정점 n까지의 거리는 k
    bool inQ[MAX];               // inQ[k] = true일 경우, 값 k는 q에 존재
    int Cycle[MAX];              // cycle[n] = k일 경우, n번 정점은 k번 방문

    q.push(st);
    dist[st] = -money[st]; // 출발점에서부터 money[st]의 비용을 가지고 시작 (예제)
    fill(inQ, inQ + MAX, false);
    fill(Cycle, Cycle + MAX, 0);

    while (q.size())
    {
        int cur = q.front();
        q.pop(), inQ[cur] = false;

        for (const auto &elem : v[cur])
        {
            auto [next, n_c] = elem;

            if (dist[next] > dist[cur] + n_c - money[next])
            {
                dist[next] = dist[cur] + n_c - money[next];

                if (!inQ[next])
                {
                    Cycle[next]++;
                    if (Cycle[next] > n) // 사이클 발생 시, 해당 정점을 저장
                        bfs_q.push(next);
                    else
                        q.push(next), inQ[next] = true;
                }
            }
        }
    }

    return dist[ed];
}

// bfs (bfs_q에 저장된 정점이 ed에 도달할 수 있는가?)
bool isCycled()
{
    vector<bool> visited(MAX, false); // visited[n] = true일 경우, n번째 정점은 방문함 (TLE 방지)

    while (bfs_q.size())
    {
        int cur = bfs_q.front();
        bfs_q.pop();
        visited[cur] = true;

        for (const auto &v : v[cur])
        {
            auto [next, idx] = v;
            if (next == ed) // 도착 도시에 방문할 수 있는가?
                return true;

            if (!visited[next])
            {
                bfs_q.push(next);
                visited[next] = true;
            }
        }
    }

    return false;
}

int main()
{
    FAST_IO;

    cin >> n >> st >> ed >> m;

    for (int i = 0; i < m; i++)
    {
        int a, b, c; // 1 ≤ 1,000,000
        cin >> a >> b >> c;
        v[a].push_back({b, c});
    }

    for (int i = 0; i < n; i++)
        cin >> money[i]; // 1 ≤ 1,000,000

    ll ans = SPFA();

    if (ans == INF)
        cout << "gg";
    else if (isCycled())
        cout << "Gee";
    else
        cout << -ans;
}

// 4 0 3 4
// 0 1 0
// 1 2 0
// 2 1 0
// 0 3 10
// 10 10 10 10
// ans: 10

// 21%
// 6 0 5 7
// 0 1 0
// 1 2 0
// 2 1 0
// 0 3 0
// 3 4 0
// 4 3 0
// 4 5 0
// 0 10 10 0 10 10
// ans: Gee

// 51%
// 4 0 3 4
// 0 1 1
// 1 2 1
// 2 0 1
// 0 3 1
// 2 2 2 0
// ans: Gee
