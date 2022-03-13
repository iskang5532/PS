// 4179 불!
// https://boj.kr/4179
/*
    BFS (10,994KB, 60ms)
    시간 복잡도: ?
    풀이)
    - 입력에서 시작점과 불을 따로 저장함.
    시작점은 s에, 불은 큐에 저장.
    - 큐에 BFS를 사용하여 불이 붙을 수 있는 구역 및 시간을 구함.
    - 시작점에서부터 이동할 수 있는 모든 구역을 구함.
    만약 현재 이동한 장소까지의 시간이 불이 이동한 시간과 같거나 클 경우, 이동하지 못함. (같을 경우 불과 동시에 도착이며, 클 경우 이미 불이 번짐)
    - 탈출 구역을 설정하기 위해 (0, r]이 아닌 (1, r)로 영역을 잡아 영역의 밖으로 도달할 경우 탈출시킴.
    etc.) https://boj.kr/3055 탈출과 비슷한 문제.
 */

#include <iostream>
#include <queue>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define INF 0x7fffffff
#define MAX 1'007
using pii = pair<int, int>;

constexpr int dy[4] = {-1, 0, 1, 0};
constexpr int dx[4] = {0, 1, 0, -1};

int r, c; // 1 ≤ R, C ≤ 1000
char board[MAX][MAX];
int t[MAX][MAX]; // t[i][j] = k일 경우, {i, j}로 불이 번지는 시간은 k

void get_t(queue<pii> &q)
{
    while (q.size())
    {
        auto [y, x] = q.front();
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            const auto &[ny, nx] = pii{y + dy[i], x + dx[i]};

            if (!(1 <= ny && ny <= r) || !(1 <= nx && nx <= c)) // OOB
                continue;
            if (board[ny][nx] == '#' || t[ny][nx] != INF)
                continue;

            q.push({ny, nx}), t[ny][nx] = t[y][x] + 1;
        }
    }
}

int get_ans(const pii &s)
{
    queue<pii> q;
    q.push(s);

    int dist[MAX][MAX];
    fill(&dist[0][0], &dist[0][0] + sizeof(dist) / sizeof(dist[0][0]), INF);
    dist[s.first][s.second] = 0;

    while (q.size())
    {
        auto [y, x] = q.front();
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            const auto &[ny, nx] = pii{y + dy[i], x + dx[i]};
            if (board[ny][nx] == '\0')
                return dist[y][x] + 1;

            if (!(1 <= ny && ny <= r) || !(1 <= nx && nx <= c)) // OOB
                continue;
            if (board[ny][nx] == '#' || dist[ny][nx] != INF || dist[y][x] + 1 >= t[ny][nx])
                continue;

            q.push({ny, nx}), dist[ny][nx] = dist[y][x] + 1;
        }
    }

    return INF;
}

int main()
{
    FAST_IO;

    fill(&t[0][0], &t[0][0] + sizeof(t) / sizeof(t[0][0]), INF);

    queue<pii> q;
    pii s;
    cin >> r >> c;
    for (int i = 1; i <= r; i++)
        for (int j = 1; j <= c; j++)
        {
            cin >> board[i][j];
            if (board[i][j] == 'J')
                s = {i, j};
            else if (board[i][j] == 'F')
                q.push({i, j}), t[i][j] = 0;
        }

    get_t(q);
    int ans = get_ans(s);
    ans == INF ? cout << "IMPOSSIBLE" : cout << ans;
}

// 5427 불
// https://boj.kr/5427
#include <iostream>
#include <queue>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

using pii = pair<int, int>;
#define endl '\n'
#define INF 0x7fffffff
#define MAX 1'007
#define HUMAN '@'
#define WALL '#'
#define FIRE '*'

constexpr int dy[4] = {-1, 0, 1, 0};
constexpr int dx[4] = {0, 1, 0, -1};

int r, c; // 1 ≤ R, C ≤ 1000
char board[MAX][MAX];
int t[MAX][MAX];

void get_t(queue<pii> &q)
{
    while (q.size())
    {
        auto [y, x] = q.front();
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            const auto &[ny, nx] = pii{y + dy[i], x + dx[i]};

            if (!(1 <= ny && ny <= r) || !(1 <= nx && nx <= c)) // OOB
                continue;
            if (board[ny][nx] == WALL || t[ny][nx] != INF)
                continue;

            q.push({ny, nx}), t[ny][nx] = t[y][x] + 1;
        }
    }
}

int get_ans(const pii &s)
{
    queue<pii> q;
    q.push(s);

    int dist[MAX][MAX];
    fill(&dist[0][0], &dist[0][0] + sizeof(dist) / sizeof(dist[0][0]), INF);
    dist[s.first][s.second] = 0;

    while (q.size())
    {
        auto [y, x] = q.front();
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            const auto &[ny, nx] = pii{y + dy[i], x + dx[i]};
            if (board[ny][nx] == '\0')
                return dist[y][x] + 1;

            if (!(1 <= ny && ny <= r) || !(1 <= nx && nx <= c)) // OOB
                continue;
            if (board[ny][nx] == WALL || dist[ny][nx] != INF || dist[y][x] + 1 >= t[ny][nx])
                continue;

            q.push({ny, nx}), dist[ny][nx] = dist[y][x] + 1;
        }
    }

    return INF;
}

int main()
{
    FAST_IO;

    int tc;
    cin >> tc;
    while (tc--)
    {

        fill(&t[0][0], &t[0][0] + sizeof(t) / sizeof(t[0][0]), INF);
        fill(&board[0][0], &board[0][0] + sizeof(board) / sizeof(board[0][0]), '\0');

        queue<pii> q;
        pii s;
        cin >> c >> r;
        for (int i = 1; i <= r; i++)
            for (int j = 1; j <= c; j++)
            {
                cin >> board[i][j];
                if (board[i][j] == HUMAN)
                    s = {i, j};
                else if (board[i][j] == FIRE)
                    q.push({i, j}), t[i][j] = 0;
            }

        get_t(q);
        int ans = get_ans(s);
        ans == INF ? cout << "IMPOSSIBLE" << endl : cout << ans << endl;
    }
}