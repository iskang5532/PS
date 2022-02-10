// 3860 할로윈 묘지
// https://www.acmicpc.net/problem/3860
/*
    SPFA (2,040KB, 120ms)
    시간 복잡도: ?
    주의할 점)
    - 첫 번째 우선순위는 해당 케이스에서 사이클 발생의 여부이다.
    사이클이 발생한 곳에서 목적지까지 도달할 수 없어도, 출력은 Never.
    - 두 번쨰 우선순위는 목적지까지 도달 여부이다.
    사이클이 없다고 가정 하에, 목적지까지 도달할 수 없을 경우의 출력은 Impossible.
    - 그 외는 목적지까지의 최단 거리를 출력.
    etc.) 맞왜틀 엄청 외친 문제. (inQ 처리를 제대로 안해준게 문제였음)
    - tc가 무족한 건지, inQ가 굳이 필요 없는 건지, inQ를 사용하지 않았을 떄의 시간이 더 빠름. why?
    참고)
    - 내용 보충: https://www.acmicpc.net/board/view/19946
 */

#include <iostream>
#include <queue>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#define endl "\n"
#define INF 98754321
#define MAX 30 + 1
#define GRAVE -1
#define HOLE 1
using pii = pair<int, int>;

constexpr int dy[4] = {1, 0, -1, 0}; // 북 서 남 동
constexpr int dx[4] = {0, 1, 0, -1};
constexpr pii st = {0, 0};

struct Info
{
    int y, x, t; // 도착점 {y, x}, 시간 t
};

int w, h;
int board[MAX][MAX];
Info hole[MAX][MAX];
bool isCycle; // 사이클이 생성됐는가?

int SPFA()
{
    int dist[MAX][MAX];  // dist[y][x] = k일 떄, {0, 0}에서 {y, x}까지의 거리는 k
    bool inQ[MAX][MAX];  // inQ[y][x] = true일 때, 큐에 {y, x}가 존재
    int cycle[MAX][MAX]; // cycle[y][x] = k일 때, {y, x}에 방문한 횟수는 k
    fill(&dist[0][0], &dist[0][0] + sizeof(dist) / sizeof(dist[0][0]), INF);
    fill(&inQ[0][0], &inQ[0][0] + sizeof(inQ) / sizeof(inQ[0][0]), false);
    fill(&cycle[0][0], &cycle[0][0] + sizeof(cycle) / sizeof(cycle[0][0]), 0);

    queue<pii> q;
    q.push(st), dist[0][0] = 0;

    while (q.size())
    {
        auto [y, x] = q.front();
        q.pop(), inQ[y][x] = false;
        if (y == h - 1 && x == w - 1) // 도착점은 제외 (도착점에서 추가로 탐색할 필요는 없음)
            continue;

        if (board[y][x] == HOLE) // 귀신 구멍인가?
        {
            auto [ny, nx, t] = hole[y][x];
            if (dist[ny][nx] > dist[y][x] + t)
            {
                dist[ny][nx] = dist[y][x] + t;
                if (!inQ[ny][nx])
                {
                    cycle[ny][nx]++;
                    if (cycle[ny][nx] > h * w) // 사이클이 형성됐는가?
                    {
                        isCycle = true;
                        return -1;
                    }
                    q.push({ny, nx}), inQ[ny][nx] = true;
                }
            }
        }
        else // not HOLE
            for (int i = 0; i < 4; i++)
            {
                int nx = x + dx[i];
                int ny = y + dy[i];
                if (!(0 <= ny && ny < h) || !(0 <= nx && nx < w)) // OOB
                    continue;
                if (board[ny][nx] == GRAVE)
                    continue;

                if (dist[ny][nx] > dist[y][x] + 1)
                {
                    dist[ny][nx] = dist[y][x] + 1;
                    if (!inQ[ny][nx])
                    {
                        cycle[ny][nx]++;
                        q.push({ny, nx}), inQ[ny][nx] = true;
                    }
                }
            }
    }

    return dist[h - 1][w - 1];
}

int main()
{
    FAST_IO;

    while (true)
    {
        isCycle = false;
        fill(&board[0][0], &board[0][0] + sizeof(board) / sizeof(board[0][0]), 0);
        fill(&hole[0][0], &hole[0][0] + sizeof(hole) / sizeof(hole[0][0]), Info{0, 0, 0});

        cin >> w >> h; // 묘지의 너비 및 높이(1 ≤ W, H ≤ 30)
        if (w == 0 && h == 0)
            break;
        int g; // 묘비의 개수 (G ≥ 0)
        cin >> g;
        for (int i = 0; i < g; i++)
        {
            int x, y;
            cin >> x >> y; // 묘비의 위치 (0 ≤ X < W, 0 ≤ Y < H)
            board[y][x] = GRAVE;
        }
        int e;
        cin >> e; // 귀신 구멍의 수 E(E ≥ 0)
        for (int i = 0; i < e; i++)
        {
            int x1, y1, x2, y2, t; // 입구 {X1, Y1}, 출구 {X2, Y2}, 시간 t (0 ≤ X1, X2 < W, 0 ≤ Y1, Y2 < H, |T| ≤ 10k)
            cin >> x1 >> y1 >> x2 >> y2 >> t;
            board[y1][x1] = HOLE;
            hole[y1][x1] = {y2, x2, t};
        }

        int ans = SPFA();
        if (isCycle)
            cout << "Never" << endl;
        else if (ans == INF)
            cout << "Impossible" << endl;
        else
            cout << ans << endl;
    }
}