// 2022-08-19
// 1939 중량제한
// https://www.acmicpc.net/problem/1939
/*
    이분 탐색, BFS (7,656KB, 72ms)
    시간 복잡도: ?
    풀이)
    - 이분 탐색을 이용하여 임의의 최소 중량제한 mid를 정함.
    다리를 건널 때 다리의 중량제한인 c가 mid보다 작을 경우, 해당 다리를 이용할 수 없음.
    - 해당 섬까지 이동할 수 있는지를 저장할 visited[]. (visited[i] = true일 경우, i번 섬은 mid 이상의 무게로 방문할 수 있음)
    방문한 섬에 다시 방문할 필요가 없으므로, 다시 방문한 기록은 탐색에서 제외한다.
    - BFS를 이용하여 mid 이상으로 목적지 st에서 도착지 ed까지 도달할 수 있는지를 확인.
    만약 도달할 수 있으면, le를 조정하여 mid를 높힌 후 다시 BFS. (중량의 최댓값을 구해야 하므로)
    만약 도달할 수 없으면, ri를 조정하여 mid를 낮춘 후 다시 BFS. (mid가 너무 커 목적지까지 도달할 수 없으므로)
    etc.) 단순 그래프 문제인줄 알았으나 이분탐색이 포함된 문제였으며 스스로 못푼 몬제
    참고)
    - 시간 복잡도: https://www.acmicpc.net/board/view/73375
 */

#include <iostream>
#include <queue>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using pii = pair<int, int>;
#define MAX 100'003 // max n

vector<pii> path[MAX]; // path[a] = {{b1, c1}, {b2, c2}}일 때, a to b1의 중량제한은 c1, a to b2의 중량제한은 c2

bool isValid(int st, int ed, int mn) // bfs
{
    bool visited[MAX]{};
    queue<int> q;
    q.push(st);

    while (q.size())
    {
        int cur = q.front();
        q.pop();

        for (auto &[next, dist] : path[cur])
        {
            if (dist < mn || visited[next]) // 최솟값을 넘지 못하거나 방문한 적이 있을 경우
                continue;

            visited[next] = true, q.push(next);
        }
    }

    return visited[ed];
}

int main()
{
    FAST_IO;

    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        path[a].push_back({b, c}), path[b].push_back({a, c});
    }

    int st, ed;
    cin >> st >> ed;

    int le = 0, ri = 1e9 + 1;
    while (le <= ri)
    {
        int mid = (le + ri) >> 1; // 임의의 최소 중량제한

        isValid(st, ed, mid) ? le = mid + 1
                             : ri = mid - 1;
    }

    cout << ri;
}