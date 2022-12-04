// 2022-11-29
// 6146 신아를 만나러
// https://www.acmicpc.net/problem/6146
/*
    BFS (6,084KB, 12ms)
    시간 복잡도: ?
    풀이)
    - 물웅덩이 및 해당 위치까지의 거리를 dist[][]에 저장.
    - 입력이 음수가 있으므로, 배열을 사용하기 위해서는 양수로 만들어야 함. 그러므로 최댓값인 500을 더함.
    - 시작점 (0 + C, 0 + C)를 큐에 넣어 bfs 수행.
    만약 다음 위치가 산이의 위치인 경우, 거리를 출력.
    - 물웅덩이의 값이 dist에서 -1로 사용해도 되는 이유는, bfs에서 반복적인 탐색에 영향을 주지 않기 때문이다.
    큐에 들어가기 위해서는 현재 탐색 중인 거리가 이전에 저장된 dist보다 작은 값이어야 한다.
    그러나, dist가 항상 최솟값이다. 탐색 도중 해당 위치에 도달하는 어떠한 값도 갱신될 일이 없어 큐에 넣어질 일은 없다.
 */

#include <iostream>
#include <queue>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define INF 0x3f3f3f3f
using pii = pair<int, int>;
#define MAX 1'003
#define C 500 // 음수를 양수로 만들어주기 위한 값

constexpr int dy[] = {-1, 0, 1, 0}; // 북 서 남 동
constexpr int dx[] = {0, 1, 0, -1};

int dist[MAX][MAX];

bool OOB(int ny, int nx) { return !(0 <= ny && ny < MAX) || !(0 <= nx && nx < MAX); }

int bfs(int ed_x, int ed_y)
{
    queue<pii> q;
    q.push({C, C});

    dist[C][C] = 0;

    while (q.size())
    {
        auto [y, x] = q.front();
        q.pop();

        for (int d = 0; d < 4; d++)
        {
            auto [ny, nx] = pii{y + dy[d], x + dx[d]};
            if (OOB(ny, nx))
                continue;
            if (dist[ny][nx] <= dist[y][x] + 1) // 웅덩이 or 최소 거리가 아닌 경우
                continue;

            if (ny == ed_y && nx == ed_x) // 목적지(신아의 위치)인 경우
                return dist[y][x] + 1;

            q.push({ny, nx}), dist[ny][nx] = dist[y][x] + 1;
        }
    }

    return dist[ed_y][ed_x];
}

int main()
{
    FAST_IO;

    int x, y, n;
    cin >> x >> y >> n;

    fill(&dist[0][0], &dist[0][0] + MAX * MAX, INF);
    for (int i = 0; i < n; i++)
    {
        int _x, _y;
        cin >> _x >> _y;
        dist[_y + C][_x + C] = -1;
    }

    cout << bfs(x + C, y + C);
}