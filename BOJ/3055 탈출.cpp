/*
    3055 탈출
    BFS (2,156KB, 0ms)
    시간 복잡도: ?
    문제: https://www.acmicpc.net/problem/3055
    풀이)
    - 비버의 위치와 굴의 위치를 저장.
    - 비버가 이동할 때 침수 또한 진행됨. 침수는 flooded 함수를 만들었으며, 탐색중이 칸과 인접한 칸에 물이 존재할 경우 침수.
    - 비버가 다음 칸으로 이동할 때, 해당 칸이 비버가 이동한 후 침수될 경우 비버는 해당 칸으로 이동할 수 없음.
    이를 이용해 비버-침수 순서가 아닌 침수-비버 순으로 동작시킴.
    - BFS의 특성상 특정 위치에서 다음 위치로 이동하는 비버가 많은데, 여러 비버들이 이동 시마다 침수를 시킨다면 부적절한 값을 얻게 됨.
    그러므로 비버의 이동 시간과 침수가 진행된 횟수를 연관지어 비버의 이동 시간이 변경될 떄마다 침수시킴.
    etc.)
    - 메모리 초과가 계속 떠서 헤맨 문제. 벡터를 배열로 바꾸니까 해결됨.
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
#define MAX 50 + 1
typedef pair<int, int> pii;

const int dx[4] = {0, 1, 0, -1}; // 상, 우, 하, 좌
const int dy[4] = {-1, 0, 1, 0};

int R, C; // 1 ≤ R, C ≤ 50

void flooded(vector<vector<char>> &arr, int R, int C) // 물과 인접한 칸을 침수시킴
{
    auto ret = arr;

    for (int y = 0; y < R; y++) // 인접한 칸에 물이 존재할 경우 해당 칸을 침수시킴
        for (int x = 0; x < C; x++)
        {
            if (arr[y][x] == 'D' || arr[y][x] == 'X')
                continue;
            for (int i = 0; i < 4; i++)
            {
                int nx = x + dx[i];
                int ny = y + dy[i];
                if (!(0 <= ny && ny < R) || !(0 <= nx && nx < C)) // OOB
                    continue;
                if (arr[ny][nx] == '*')
                {
                    ret[y][x] = '*';
                    break;
                }
            }
        }

    arr = move(ret);
}

int bfs(vector<vector<char>> &arr, pii start, pii end)
{
    int dist[MAX][MAX];
    for (int i = 0; i < R; i++)
        fill(dist[i], dist[i] + C, INF);

    queue<pii> q;
    q.push(start);
    dist[start.first][start.second] = 0;
    int cnt = 0; // 침수 횟수 (= 비버의 이동 시간)
    while (!q.empty())
    {
        auto [y, x] = q.front();
        q.pop();
        if (dist[y][x] == cnt)
            flooded(arr, R, C), cnt++; // 침수시키며, 침수 횟수 +1

        for (int i = 0; i < 4; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (!(0 <= ny && ny < R) || !(0 <= nx && nx <= C)) // OOB
                continue;
            if (arr[ny][nx] == '*' || arr[ny][nx] == 'X')
                continue;

            if (dist[ny][nx] > dist[y][x] + 1)
            {
                dist[ny][nx] = dist[y][x] + 1;
                q.push({ny, nx});
            }
            if (arr[ny][nx] == 'D')
                return dist[ny][nx];
        }
    }

    return INF;
}

int main()
{
#ifdef CUSTOM
    cout << "[CUSTOM]" << endl;
#else // BOJ
    FAST_IO;
#endif

    cin >> R >> C;

    vector<vector<char>> arr(R, vector<char>(C));
    pii start, end; // 비버의 시작점 및 굴의 위치
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
        {
            cin >> arr[i][j];
            if (arr[i][j] == 'S')
                start = {i, j};
            else if (arr[i][j] == 'D')
                end = {i, j};
        }

    int ans = bfs(arr, start, end); // BFS를 통해 비버의 이동 시간을 구함
    ans == INF ? cout << "KAKTUS" : cout << ans;
}

// sol.2) BFS
// 침수 상황을 sol.1과는 다르게 한번에 시킴.
// 해당 칸이 언제 침수가 되는지를 저장하였으며, 이를 이용해 비버가 이동한 후에 침수되는 칸 또한 갈 수 없도록 함.
// 참고)
// - 이론: https://blog.naver.com/jinhan814/222120230732
#include <iostream>
#include <queue>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define endl "\n"
#define INF 1234567890
#define MAX 50 + 1
typedef pair<int, int> pii;

const int dx[4] = {0, 1, 0, -1};
const int dy[4] = {-1, 0, 1, 0};

int R, C; // 1 ≤ R, C ≤ 50
char arr[MAX][MAX];
int cnt[MAX][MAX]; // 각 칸의 침수 시간 (cnt[2][1] = 3일 경우, y = 2, x = 1인 칸의 침수는 비버가 3번 움직인 후에 침수)

void get_cnt(queue<pii> &q)
{
    while (!q.empty())
    {
        auto [y, x] = q.front();
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (!(0 <= ny && ny < R) || !(0 <= nx && nx <= C)) // OOB
                continue;
            if (arr[ny][nx] == 'X' || arr[ny][nx] == 'D')
                continue;
            if (cnt[ny][nx] > cnt[y][x] + 1)
            {
                cnt[ny][nx] = cnt[y][x] + 1;
                q.push({ny, nx});
            }
        }
    }
}

int bfs(pii start, pii end)
{
    int ret = INF;

    vector<vector<int>> dist(R, vector<int>(C, INF)); // 시작점부터 각 칸까지의 거리(= 시간)
    queue<pii> q;
    q.push(start);
    dist[start.first][start.second] = 0;

    while (!q.empty())
    {
        auto [y, x] = q.front();
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (!(0 <= ny && ny < R) || !(0 <= nx && nx < C)) // OOB
                continue;
            if (arr[ny][nx] == '*' || arr[ny][nx] == 'X')
                continue;
            if (cnt[ny][nx] <= dist[y][x] + 1) // 침수가 진행될 or 진행된 칸인 경우
                continue;
            if (dist[ny][nx] > dist[y][x] + 1)
            {
                dist[ny][nx] = dist[y][x] + 1;
                q.push({ny, nx});
            }
            if (arr[ny][nx] == 'D')
                return dist[ny][nx];
        }
    }
    return ret;
}

int main()
{
#ifdef CUSTOM
    cout << "[CUSTOM]" << endl;
#else // BOJ
    FAST_IO;
#endif

    cin >> R >> C;

    for (int i = 0; i < R; i++)
        fill(cnt[i], cnt[i] + C, INF);

    queue<pii> _q; // 물의 위치를 저장.
    pii start, end;
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
        {
            cin >> arr[i][j];
            if (arr[i][j] == 'S')
                start = {i, j};
            else if (arr[i][j] == 'D')
                end = {i, j};
            else if (arr[i][j] == '*')
                _q.push({i, j}), cnt[i][j] = 0;
        }

    get_cnt(_q); // 모든 칸의 침수 시간을 확인.
    int ans = bfs(start, end);
    ans == INF ? cout << "KAKTUS" : cout << ans;
}