// 2022-04-11
// 2636 치즈
// https://www.acmicpc.net/problem/2636
/*
    구현, bfs (2,032KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 입력된 치즈의 개수를 cnt에 저장한 후, 시간마다 녹는 치즈의 개수를 빼줌. (이때, 녹기 전의 값을 prev에 저장)
    - (0, 0)의 값은 치즈가 존재할 수 없으므로, (0, 0)을 기준으로 bfs를 수행하여 치즈를 녹임.
    - cnt의 값이 0이 된 경우, t와 prev를 출력.
 */

#include <iostream>
#include <queue>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using pii = pair<int, int>;
#define endl "\n"
#define MAX 103 // max n, m

constexpr int dy[4] = {-1, 0, 1, 0}; // 북 동 남 서
constexpr int dx[4] = {0, 1, 0, -1};

int n, m; // 1 ≤ n, m ≤ 100
bool cheese[MAX][MAX];
int cnt; // 치즈의 개수

void bfs()
{
    queue<pii> q;
    q.push({0, 0});

    bool visited[MAX][MAX]{};
    visited[0][0] = true;

    while (q.size())
    {
        auto [y, x] = q.front();
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            auto [ny, nx] = pii{y + dy[i], x + dx[i]};
            if (!(0 <= ny && ny < n) || !(0 <= nx && nx < m)) // OOB
                continue;
            if (visited[ny][nx])
                continue;

            visited[ny][nx] = true;
            if (cheese[ny][nx])
                cnt--, cheese[ny][nx] = false;
            else
                q.push({ny, nx});
        }
    }
}

int main()
{
    FAST_IO;

    cin >> n >> m;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            cin >> cheese[i][j];
            if (cheese[i][j])
                cnt++;
        }

    int t = 0, prev = 0; // 시간 t, 녹기 전 치즈의 개수 prev
    for (; cnt; t++)
    {
        prev = cnt;
        bfs();
    }

    cout << t << endl
         << prev;
}