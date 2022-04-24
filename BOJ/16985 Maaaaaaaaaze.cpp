// 2022-04-20
// 16985 Maaaaaaaaaze
// https://www.acmicpc.net/problem/16985
/*
    구현 (2,028KB, 400ms)
    시간 복잡도: ?
    풀이)
    etc.)
    참고)
 */

#include <iostream>
#include <queue>
#include <algorithm> // permuutation

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define INF 0x7fffffff
#define MAX 5 // max n

constexpr int dz[] = {0, 0, 0, 0, -1, 1}; // 북 서 남 동 상 하
constexpr int dy[] = {-1, 0, 1, 0, 0, 0};
constexpr int dx[] = {0, 1, 0, -1, 0, 0};

struct P
{
    int z, y, x;

    friend bool operator==(const P &p1, const P &p2) { return p1.z == p2.z && p1.y == p2.y && p1.x == p2.x; }
};

vector<vector<vector<int>>> board(MAX, vector<vector<int>>(MAX, vector<int>(MAX)));

int bfs()
{
    int dist[MAX][MAX][MAX]{};

    queue<P> q;
    q.push({0, 0, 0});
    while (q.size())
    {
        auto [z, y, x] = q.front();
        q.pop();
        for (int i = 0; i < 6; i++)
        {
            auto [nz, ny, nx] = P{z + dz[i], y + dy[i], x + dx[i]};
            if (!(0 <= nz && nz < MAX) || !(0 <= ny && ny < MAX) || !(0 <= nx && nx < MAX)) // OOB
                continue;
            if (dist[nz][ny][nx] != 0 || board[nz][ny][nx] == 0)
                continue;

            if (P{nz, ny, nx} == P{4, 4, 4})
                return dist[z][y][x] + 1;
            q.push({nz, ny, nx}), dist[nz][ny][nx] = dist[z][y][x] + 1;
        }
    };

    return INF;
}

int main()
{
    FAST_IO;

    auto rotated = [&](vector<vector<int>> &v)
    {
        vector<vector<int>> ret(MAX, vector<int>(MAX));
        for (int y = 0; y < MAX; y++)
            for (int x = 0; x < MAX; x++)
                ret[x][MAX - 1 - y] = v[y][x];

        v = move(ret);
    };

    vector<vector<int>> rot_board[MAX][4];
    for (int pos = 0; pos < MAX; pos++)
    {
        vector<vector<int>> v(MAX, vector<int>(MAX));
        for (int i = 0; i < MAX; i++)
            for (int j = 0; j < MAX; j++)
                cin >> v[i][j];

        for (int r = 0; r < 4; r++)
            rot_board[pos][r] = v, rotated(v);
    }

    int ans = INF;
    vector<int> v = {0, 1, 2, 3, 4};
    do
    {
        for (int bit = 0; bit < 1024; bit++) // 4^5
        {
            int _bit = bit;
            for (int pos = 0; pos < 5; pos++)
                board[pos] = rot_board[v[pos]][_bit % 4], _bit /= 4;

            if (board[0][0][0] == 0 || board[4][4][4] == 0)
                continue;

            ans = min(ans, bfs());
        }
    } while (next_permutation(v.begin(), v.end()));

    cout << (ans == INF ? -1 : ans);
}