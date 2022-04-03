// 15683 감시
// https://www.acmicpc.net/problem/15683
/*
    구현, 완전 탐색 (2,024KB, 0ms)
    시간 복잡도: ?
    풀이)
    - CCTV의 위치를 벡터 v에 저장.
    - CCTV는 90도 방향으로 회전이 가능하므로, 네 방향을 감시할 수 있다.
    CCTV의 개수가 적으므로 완전 탐색을 이용해 CCTV의 모든 방향에 따른 사각 지대의 최소 크기 ans를 구한다. (= 4^8)
    - 모든 CCTV의 방향이 정해졌다면, 각 CCTV마다 감시할 수 있는 영역을 구한다.
    CCTV의 방향은 일직선이므로, 함수를 구현하여 입력된 위치와 방향으로 감시 구역을 구한다.
    - 주의할 점은, 벽은 사각 지대에서 제외된다.
    etc.) 어려..웠나?
 */

#include <iostream>
#include <vector>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define INF 0x7fffffff
#define MAX 11 // max n, m
#define WALL 6

constexpr int dy[4] = {-1, 0, 1, 0}; // 북 동 남 서
constexpr int dx[4] = {0, 1, 0, -1};

struct pii
{
    int y, x;

    void operator+=(const pii &p) { y += p.y, x += p.x; }
    friend bool operator<=(int k, pii &p) { return k <= p.x && k <= p.y; }
    friend bool operator<(pii p, int k) { return p.x < k && p.y < k; }
};

int n, m; // 세로 크기 N, 가로 크기 M (1 ≤ N, M ≤ 8)
int board[MAX][MAX];
vector<pii> v;  // CCTV의 위치
int state[MAX]; // i번째 CCTV의 방향
int ans = INF;

int get_ans()
{
    bool seen[MAX][MAX]{}; // seen[i][j] = true일 경우, 위치 (i, j)는 감시 구역 (= 사각 지대가 아님)

    auto watched = [&](int y, int x, int d) -> void
    {
        pii next = pii{y, x};
        for (; 0 <= next && next < MAX; next += pii{dy[d], dx[d]}) // 범위 안일 경우, CCTV의 감시 수행
        {
            auto [ny, nx] = next;
            if (board[ny][nx] == WALL)
                return;

            seen[ny][nx] = true;
        }
    };

    for (int i = 0; i < v.size(); i++) // i번째 CCTV
    {
        auto [y, x] = v[i];
        if (board[y][x] == 1)
            watched(y, x, state[i]);
        else if (board[y][x] == 2)
        {
            watched(y, x, state[i]);
            watched(y, x, (state[i] + 2) % 4);
        }
        else if (board[y][x] == 3)
        {
            watched(y, x, state[i]);
            watched(y, x, (state[i] + 1) % 4);
        }
        else if (board[y][x] == 4)
        {
            watched(y, x, state[i]);
            watched(y, x, (state[i] + 1) % 4);
            watched(y, x, (state[i] + 3) % 4);
        }
        else // board[y][x] == 5
        {
            watched(y, x, 0);
            watched(y, x, 1);
            watched(y, x, 2);
            watched(y, x, 3);
        }
    }

    int ret = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (board[i][j] != WALL && !seen[i][j])
                ret++;
    return ret;
}

void dfs(int dep)
{
    if (dep == v.size())
    {
        ans = min(ans, get_ans());
        return;
    }

    for (int i = 0; i < 4; i++) // [dep] CCTV가 바라보는 방향
        state[dep] = i, dfs(dep + 1);
}

int main()
{
    FAST_IO;

    cin >> n >> m;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            cin >> board[i][j];
            if (1 <= board[i][j] && board[i][j] <= 5) // CCTV인 경우
                v.push_back({i, j});
        }

    dfs(0);

    cout << ans;
}