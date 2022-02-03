// 1738 골목길
// https://www.acmicpc.net/problem/1738
/*
    SPFA + BFS (2,160KB, 4ms)
    시간 복잡도: O(VE) (최악: O(V + E); SPFA의 시간 복잡도)
    풀이)
    - SPFA를 이용해 시작점(민승이의 집)에서부터 도착점(코레스코 콘도)까지의 최대 액수(이하 거리)를 구함.
    최단 거리를 구하는 방식으로 작성할 것이기에, board에 저장할 거리는 입력된 값의 음수로 바꿔줌. (입력이 음수일 경우, 양수로)
    - prev[next] = cur일 경우, next의 이전 정점은 cur. (최단 거리를 위한 경로)
    1) dist[n]이 갱신 가능한 경우, prev에 값을 저장함.
    2) 사이클이 발생한 지점을 찾은 후, bfs_q에 저장.
    사이클이 생기는 구간은 하나가 아닐 수 있음.
    3) bfs_q에 저장된 정점들을 이용하여 사이클이 발생한 정점에서 도착점까지의 경로가 존재하는지 탐색.
    사이클이 발생하여도 도착점에 도달하지 못하는 경우가 있음. 이때는 "-1'
    만약 사이클이 아니거나, 사이클이 발생하여도 도착점까지 도달할 수 있을 경우, 해당 도착점에 도달하기까지의 정점을 출력.
    - prev의 값을 n-1부터 탐색하며, 값을 ans에 저장. 이후 ans 출력. (뒤에서부터 저장되었으므로 rbegin부터 출력)
    etc.) 사이클이 발생하여도 사이클이 발생한 지점에서 도착점까지 길이 없다면, 사이클 여부는 상관 없음.
 */

#include <iostream>
#include <queue>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#define endl "\n"
#define INF 98754321
#define MAX 100 + 1
using pii = pair<int, int>;

vector<pii> board[MAX];
queue<int> bfs_q;

vector<int> SPFA(int n)
{
    int st = 0, ed = n - 1;

    vector<int> dist(n + 1, INF); // dist[n] = k일 경우, n까지의 최단 거리는 k
    queue<int> q;
    bool inQ[MAX];  // inQ[k] = true일 경우, 값 k는 큐에 존재
    int cycle[MAX]; // cycle[n] = k일 경우, 정점 n을 k번 방문

    dist[st] = 0;
    q.push(st), inQ[st] = true;
    fill(inQ, inQ + MAX, false);
    fill(cycle, cycle + MAX, false);

    vector<int> prev(n + 1, 0); // prev[next] = cur일 경우, 정점 next에 도달하기 이전의 정점은 cur
    while (q.size())
    {
        int cur = q.front();
        q.pop(), inQ[cur] = false;

        for (const auto &elem : board[cur])
        {
            auto [next, cost] = elem;

            if (dist[next] > dist[cur] + cost)
            {
                dist[next] = dist[cur] + cost;
                prev[next] = cur;

                if (!inQ[next])
                {
                    cycle[next]++;

                    if (cycle[next] > n)
                        bfs_q.push(next);
                    else
                        q.push(next), inQ[next] = true;
                }
            }
        }
    }

    return prev;
}

bool isCycled(int ed)
{
    bool visited[MAX];
    fill(visited, visited + MAX, false);

    while (bfs_q.size())
    {
        int cur = bfs_q.front();
        bfs_q.pop();
        visited[cur] = true;

        for (const auto &elem : board[cur])
        {
            auto [next, c] = elem;
            if (next == ed) // 사이클이 발생한 정점에서부터 도착점까지 도달 가능한 경우
                return true;

            if (!visited[next])
                bfs_q.push(next);
        }
    }

    return false;
}

int main()
{
    FAST_IO;

    int n, m; // 교차점의 개수 n(2 ≤ n ≤ 100), 골목길의 개수 m(1 ≤ m ≤ 20,000)
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int u, v, w; // u에서 v로 갈 때의 금액 w(0 ≤ |w| ≤ 1,000)
        cin >> u >> v >> w;

        board[u - 1].push_back({v - 1, -w});
    }

    vector<int> prev = SPFA(n);

    int ed = n - 1;
    if (isCycled(ed)) // 발생한 사이클은 도착점까지 가는데 영향을 끼치는가?
        cout << -1;
    else
    {
        vector<int> ans;
        int k = ed;
        while (k != 0)
        {
            ans.push_back(k + 1);
            k = prev[k];
        }
        ans.push_back(1);

        for (auto itr = ans.rbegin(); itr != ans.rend(); itr++)
            cout << *itr << ' ';
    }
}