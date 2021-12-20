// 1726 로봇
// https://www.acmicpc.net/problem/1726
/*
    구현, BFS (2,072KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 기존 BFS에서 방향이 추가됨.
    기존 BFS는 2차원 배열을 선언해 각 위치에 최소 이동 횟수를 저장했다면,
    이 문제는 2차원 배열에 방향까지 추가한 3차원 배열을 선언하여 위치 (x,y)에서 방향 dir로 만들 수 있는 최소 명령 횟수르 저장.
    - 두 가지 명령을 나누어 수행. (직진 명령과 방향 전환 명령)
    - 시작점에서부터 탐색을 시작함.
    만약 다음칸 혹은 다음 방향까지의 최소 명령 횟수가 갱신 가능인 경우, 갱신 시켜주며 큐에 넣어 재탐색.
    etc.) 헷갈린 문제.
    참고)
    - 3차원 배열 초기화: https://stackoverflow.com/questions/50971310/how-to-fill-3d-array-with-zeros
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
#define MAX 100 + 1

const int dx[4] = {1, -1, 0, 0}; // 동 서 남 북
const int dy[4] = {0, 0, 1, -1};
const int dd[4][4] = {{0, 2, 3, 1}, // 회전 시의 다음 방향
                      {1, 3, 2, 0},
                      {2, 1, 0, 3},
                      {3, 0, 1, 2}};

struct P
{
    int y, x, dir;
    P &operator--(int)
    {
        y--, x--, dir--;
        return *this;
    }
    bool operator==(const P &p) { return y == p.y && x == p.x && dir == p.dir; }
    friend istream &operator>>(istream &in, P &p)
    {
        in >> p.y >> p.x >> p.dir;
        return in;
    }
};

int m, n; // 세로 길이 m, 가로 길이 n (1 ≤ m, n ≤ 100)
bool board[MAX][MAX];
P st, ed; // 시작점 및 도착점

int bfs()
{
    int visited[MAX][MAX][4]; // [y][x][dir] = k일 때, 시작점에서부터 위치 (x,y)의 dir 방향으로 만드는데 필요한 최소 명령 횟수는 k
    fill(&visited[0][0][0], &visited[0][0][0] + sizeof(visited) / sizeof(visited[0][0][0]), INF);

    queue<P> q;
    q.push(st);
    visited[st.y][st.x][st.dir] = 0;
    while (q.size())
    {
        auto [y, x, dir] = q.front();
        q.pop();
        for (int dist = 1; dist <= 3; dist++) // cmd 1. Go k
        {
            int nx = x + (dx[dir] * dist);
            int ny = y + (dy[dir] * dist);

            if (!(0 <= ny && ny < m) || !(0 <= nx && nx < n)) // OOB
                break;
            if (board[ny][nx])
                break;
            if (visited[y][x][dir] + 1 < visited[ny][nx][dir])
            {
                visited[ny][nx][dir] = visited[y][x][dir] + 1;
                q.push({ny, nx, dir});
            }
        }
        for (int i = 0; i < 4; i++) // cmd 2. Turn dir
        {
            int ndir = dd[dir][i];

            const int bit_cnt[4] = {0, 1, 1, 2}; // 회전 시 필요한 명령 횟수
            if (visited[y][x][dir] + bit_cnt[i] < visited[y][x][ndir])
            {
                visited[y][x][ndir] = visited[y][x][dir] + bit_cnt[i];
                q.push({y, x, ndir});
            }
        }
    }
    return visited[ed.y][ed.x][ed.dir];
}

int main()
{
#ifdef CUSTOM
    cout << "[CUSTOM]" << endl;
#else // BOJ
    FAST_IO;
#endif

    cin >> m >> n;
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            cin >> board[i][j];

    cin >> st >> ed;
    st--, ed--;

    cout << bfs();
}

// 9 12
// 0 0 0 0 0 0 0 0 0 0 0 1
// 0 1 1 1 1 0 0 1 1 1 1 0
// 0 0 0 0 0 0 0 1 1 1 1 0
// 0 1 1 1 1 0 0 1 1 1 1 0
// 0 0 0 0 0 0 0 0 0 0 0 0
// 0 1 1 1 1 0 0 1 1 1 1 0
// 0 1 1 1 1 0 0 0 0 0 0 0
// 0 1 1 1 1 0 0 1 1 1 1 0
// 1 0 0 0 0 0 0 0 0 0 0 0
// 1 1 3
// 9 12 3
// ans: 10