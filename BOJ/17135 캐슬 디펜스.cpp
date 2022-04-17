// 2022-04-16
// 17135 캐슬 디펜스
// https://www.acmicpc.net/problem/17135
/*
    완전 탐색, BFS (2,028KB, 8ms)
    시간 복잡도: ?
    풀이)
    - 판의 최대 크기는 15이며, 궁수는 3명이므로 완전 탐색 시 15C3이다.
    - 궁수의 공격으로 제거한 적의 수를 구하는 함수 get_cnt(), 적이 성을 향해 움직이도록 해주는 함수 Push().
    - bfs를 이용하여 현재 궁수와의 거리가 d 이하이면서 가장 가까운 적의 위치를 구하여 v에 저장. (v는 궁수와 가장 가까운 적의 위치를 저장하며, 없을 경우 -1)
    - v의 원소를 탐색. 만약 해당 위치에 적이 존재할 경우, board에서 해당 위치의 적을 없앤 후 cnt++.
    해당 위치에 적이 없다면, 앞서 궁수가 적을 없앰. (= 동일한 적)
 */

#include <iostream>
#include <queue>
#include <algorithm> // prev_permutation

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using pii = pair<int, int>;
#define MAX 18 // max n,

constexpr int dy[4] = {0, -1, 0, 1}; // 서 북 동 남
constexpr int dx[4] = {-1, 0, 1, 0};

int n, m, d; // 행과 열의 수 n, m(3 ≤ n, m ≤ 15), 궁수의 공격 거리 제한 d(1 ≤ d ≤ 10)

int get_cnt(vector<vector<int>> &board)
{
    int ret = 0;

    auto bfs = [&](int y, int x) -> pii
    {
        queue<pii> q;
        q.push({y, x});

        int dist[MAX][MAX]{};
        dist[y][x] = 0;

        while (q.size())
        {
            auto [y, x] = q.front();
            q.pop();
            for (int i = 0; i < 4; i++)
            {
                auto [ny, nx] = pii{y + dy[i], x + dx[i]};
                if (!(0 <= ny && ny < n) || !(0 <= nx && nx < m)) // OOB
                    continue;
                if (dist[ny][nx] != 0 || dist[y][x] + 1 > d)
                    continue;

                if (board[ny][nx])
                    return {ny, nx};

                q.push({ny, nx}), dist[ny][nx] = dist[y][x] + 1;
            }
        }

        return {-1, -1};
    };

    vector<pii> v; // 궁수와 가장 가까운 적의 위치를 저장
    for (int x = 0; x < m; x++)
        if (board[n][x])
            v.push_back(bfs(n, x));

    for (const auto &[y, x] : v)
        if (y != -1 && board[y][x])
            board[y][x] = 0, ret++;

    return ret;
}

void Push(vector<vector<int>> &board)
{
    for (int x = 0; x < m; x++)
    {
        for (int y = n - 1; y >= 1; y--)
            board[y][x] = board[y - 1][x];
        board[0][x] = 0;
    }
}

int main()
{
    FAST_IO;

    cin >> n >> m >> d;
    vector<vector<int>> board(n + 1, vector<int>(m));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> board[i][j];

    vector<bool> bit(m, false);
    fill(bit.begin(), bit.begin() + 3, true);
    int ans = 0;
    do
    {
        int cnt = 0; // 제거한 적의 수

        auto _board = board;
        for (int i = 0; i < m; i++)
            _board[n][i] = bit[i]; // 궁수 배치
        for (int i = 0; i < n; i++)
        {
            cnt += get_cnt(_board);
            Push(_board);
        }

        ans = max(ans, cnt);

    } while (prev_permutation(bit.begin(), bit.end()));

    cout << ans;
}