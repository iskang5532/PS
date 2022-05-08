// 2022-05-02
// 2239 스도쿠, 2580 스도쿠
// https://boj.kr/2239 https://boj.kr/2580
/*
    구현, DFS (2,020KB, 308ms)
    시간 복잡도: ?
    풀이)
    - dfs를 이용하여 빈 칸에 들어가는 수를 탐색.
    - 해당 위치가 포함된 행와 열, 그리고 3*3칸을 탐색해준 후, 값이 들어갈 수 있을 경우 다음 빈 칸을 탐색.
 */

#include <iostream>
#include <vector>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using pii = pair<int, int>;
#define endl "\n"
#define MAX 9

char board[MAX][MAX];
vector<pii> v; // 0의 위치를 저장

void dfs(int dep)
{
    auto [y, x] = v[dep];

    if (dep == v.size())
    {
        for (int i = 0; i < MAX; i++, cout << endl)
            for (int j = 0; j < MAX; j++)
                cout << board[i][j];
        exit(0);
    }

    for (int k = '1'; k <= '9'; k++)
    {
        bool valid = true; // 위치 (y, x)에 값 k가 들어갈 수 있는가
        for (int pos = 0; pos < MAX && valid; pos++)
            if (board[pos][x] == k || board[y][pos] == k)
                valid = false;

        for (int ny = y / 3 * 3; ny < y / 3 * 3 + 3 && valid; ny++)
            for (int nx = x / 3 * 3; nx < x / 3 * 3 + 3 && valid; nx++)
                if (board[ny][nx] == k)
                    valid = false;

        if (!valid)
            continue;

        board[y][x] = k;
        dfs(dep + 1);
        // board[y][x] = '0';
    }
}

int main()
{
    FAST_IO;

    for (int i = 0; i < MAX; i++)
        for (int j = 0; j < MAX; j++)
        {
            cin >> board[i][j];
            if (board[i][j] == '0')
                v.push_back({i, j});
        }

    dfs(0);
}