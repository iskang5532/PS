// 5014 스타트링크
// https://www.acmicpc.net/problem/5014
/*
    BFS (2,876KB, 16ms)
    시간 복잡도: ?
    풀이)
    - BFS를 이용해 시작 높이 s에서부터 도착 높이 g까지 버튼을 누른 최소 횟수 cnt를 구함.
    - 큐에 {높이 pos, 횟수 cnt}를 저장한 후, pos + u, pos - d를 큐에 넣어준다.
    이때, 버튼을 한 번 눌렀으므로, cnt에는 cnt + 1을 넣는다.
    - 시간을 줄여주기 위해 해당 높이에 도달한 적이 있는지를 visited에 저장. (visited[i] = true일 경우, 높이 i에 도달한 적이 있음.)
    - 큐에 존재하는 값들을 이용해 도달할 수 있는 높이를 탐색하며, 현재 높이가 g와 같을 경우, cnt를 출력한다.
    만약 큐에 존재하는 모든 값을 이용했음에도 pos != g일 경우, "use the stairs"를 출력한다.
 */

#include <iostream>
#include <queue>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define INF 0x7fffffff
#define MAX 1'000'003
using pii = pair<int, int>; // {현재 높이, 버튼 누른 횟수}

int f, s, g, u, d; // 건물 높이 f, 시작 s, 도착 g, 윗층 u, 아랫층 d (1 ≤ S, G ≤ F ≤ 1,000,000, 0 ≤ U, D ≤ 1,000,000)

int bfs()
{
    queue<pii> q;
    q.push({s, 0});

    bool visited[MAX];
    fill(visited, visited + MAX, false);
    visited[s] = true;

    while (q.size())
    {
        auto [pos, cnt] = q.front();
        q.pop();
        if (pos == g)
            return cnt;

        if (pos + u <= f && !visited[pos + u]) // OOB 및 방문 여부
            q.push({pos + u, cnt + 1}), visited[pos + u] = true;
        if (pos - d >= 1 && !visited[pos - d])
            q.push({pos - d, cnt + 1}), visited[pos - d] = true;
    }

    return INF;
}

int main()
{
    FAST_IO;

    cin >> f >> s >> g >> u >> d;

    int ans = bfs();
    if (ans == INF)
        cout << "use the stairs";
    else
        cout << ans;
}