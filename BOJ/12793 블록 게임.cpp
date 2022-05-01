// 2022-04-29
// 12793 블록 게임
// https://www.acmicpc.net/problem/12793
/*
    구현, BFS, 유니온 파인드 (2,264KB, 0ms)
    시간 복잡도: ?
    풀이)
    - bfs 및 uf를 이용하여 인접한 B를 서로 묶음.
    - k의 값에 맞춰 get_ans()를 이용해 얻을 수 있는 B의 개수를 구함.
     - k의 값에 소수부가 존재하지 않는 값, 즉 정수일 경우 k의 값을 이용.
     - k의 값이 소수부가 존재할 경우, 내림한 k의 값과 올림한 k의 값을 이용하여 개수를 구함.
    - 주의할 점은, 벽에 부딪혀 바뀌게 되는 방향은 여러 가지이므로, 모두 처리해줘야 한다.
    etc.) n과 m의 입력을 서로 바꿔 풀이.
 */

#include <iostream>
#include <queue>
#include <numeric> // iota

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using pii = pair<int, int>;
#define MAX 203

constexpr int dy[] = {-1, 0, 1, 0}; // 북 서 남 동
constexpr int dx[] = {0, 1, 0, -1};

int m, n; // 1 ≤ m, n ≤ 100
double k; //  위치 k(0 ≤ k ≤ m, k % 0.5 == 0)
char board[MAX][MAX];

struct Union_Find
{
    int group[MAX * MAX];
    bool visited[MAX * MAX];

    Union_Find()
    {
        iota(group, group + MAX * MAX, 0);
        fill(visited, visited + MAX * MAX, false);
    }
    int find_parent(int x) { return x == group[x] ? group[x] : group[x] = find_parent(group[x]); }
    int find_parent(int y, int x) { return find_parent(y * m + x); };
    void union_parent(int a, int b) { a > b ? group[a] = b : group[b] = a; };
} uf;

void bfs()
{
    bool visited[MAX][MAX]{};
    for (int y = 1; y < n; y += 2)
        for (int x = 1; x < m; x += 2)
            if (!visited[y][x] && board[y][x] == 'B')
            {
                queue<pii> q;
                q.push({y, x});

                visited[y][x] = true;

                while (q.size())
                {
                    auto [y, x] = q.front();
                    q.pop();

                    for (int d = 0; d < 4; d++)
                    {
                        auto [_ny, _nx] = pii{y + dy[d], x + dx[d]}; // 벽
                        auto [ny, nx] = pii{_ny + dy[d], _nx + dx[d]};

                        if (!(0 <= ny && ny < n) || !(0 <= nx && nx < m)) // OOB
                            continue;
                        if (visited[ny][nx] || board[_ny][_nx] != '.')
                            continue;

                        int a = uf.find_parent(y, x), b = uf.find_parent(ny, nx);
                        if (a != b)
                            uf.union_parent(a, b);

                        q.push({ny, nx}), visited[ny][nx] = true;
                    }
                }
            }
}

int get_ans(int y, int x)
{
    auto moved = [&](int &y, int &x, pii &dir) -> void
    {
        auto &[dy, dx] = dir;
        auto [ny, nx] = pii{y + dy, x + dx};
        if ((ny == -1 && nx == -1) || (ny == -1 && nx == m)) // 모서리
            dy *= -1, dx *= -1;
        else if (ny == -1) // 위
            dy *= -1;
        else if (nx == -1 || nx == m) // 왼쪽 오른쪽
            dx *= -1;

        y += dy, x += dx;
    };

    int ret = 0;
    pii dir = {-1, -1};
    do
    {
        int pos = uf.find_parent(y, x);
        if (!uf.visited[pos] && board[y][x] == 'B')
            ret++, uf.visited[pos] = true;

        moved(y, x, dir);

    } while (y != n - 1);

    return ret;
}

int main()
{
    FAST_IO;

    cin >> m >> n >> k;
    m = m * 2 + 1, n = n * 2 + 1;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> board[i][j];

    bfs();

    int ans = 0;
    ans += get_ans(n - 1, (int)k * 2);
    if (k - (int)k) // 소수부가 존재하는 경우
        ans += get_ans(n - 1, k * 2 + 1);

    cout << ans;
}