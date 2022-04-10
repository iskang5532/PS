// 17144 미세먼지 안녕!
// https://www.acmicpc.net/problem/17144
// 2022-04-08
/*
    구현 (2,032KB, 32ms)
    풀이)
    - 공기청정기의 위치를 저장할 cleaner[].
    - 먼지의 확산을 수행할 spread().
    - 모든 칸을 확인하며 먼지가 있는지 확인.
    만약 먼지가 존재할 경우, 네 방향 중 확산할 수 있는 방향을 확인.
    확산할 수 있는 방향은 확산하며, 기준이 된 장소의 먼지는 확산할 수 있는 방향의 수만큼 감소.
    - 공기청정기의 작동을 수행할 cleaned().
    - cleaner의 값을 이용하여 윗부분과 아랫부분을 나눠 공기청정기를 작동.
    참고) 2d array의 값을 std::move할 수 있는 방법은?
 */

#include <iostream>
#include <vector>
#include <numeric> // iota

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using pii = pair<int, int>;
#define MAX 53 // max r, c

constexpr int dy[4] = {-1, 0, 1, 0};
constexpr int dx[4] = {0, 1, 0, -1};

int r, c, t;         // 크기 r, c(6 ≤ R, C ≤ 50), 시간 t(1 ≤ T ≤ 1,000)
int board[MAX][MAX]; // -1 ≤ k ≤ 1,000 (-1: 공기청정기)
vector<pii> cleaner;

void spread()
{
    int _board[MAX][MAX]{};

    for (int y = 0; y < r; y++)
        for (int x = 0; x < c; x++)
            if (board[y][x] != -1 && board[y][x])
            {
                int cnt = 0;             // 확산 가능한 방향의 수
                int k = board[y][x] / 5; // 확산되는 미세먼지의 양
                for (int i = 0; i < 4; i++)
                {
                    auto [ny, nx] = pii{y + dy[i], x + dx[i]};
                    if (!(0 <= ny && ny < r) || !(0 <= nx && nx < c)) // OOB
                        continue;
                    if (board[ny][nx] == -1)
                        continue;

                    _board[ny][nx] += k, cnt++; // 확산
                }

                _board[y][x] += board[y][x] - k * cnt;
            }

    for (const auto &[y, x] : cleaner)
        _board[y][x] = -1;

    copy(&_board[0][0], &_board[0][0] + MAX * MAX, &board[0][0]); // how to std::move?
}

void cleaned()
{
    { // 위
        auto [y, x] = cleaner[0];
        for (int i = y - 2; i >= 0; i--)
            board[i + 1][x] = board[i][x];
        for (int i = 1; i <= c - 1; i++)
            board[0][i - 1] = board[0][i];
        for (int i = 1; i <= y; i++)
            board[i - 1][c - 1] = board[i][c - 1];
        for (int i = c - 1 - 1; i >= 1; i--)
            board[y][i + 1] = board[y][i];
        board[y][x + 1] = 0;
    }
    { // 아래
        auto [y, x] = cleaner[1];
        for (int i = y + 2; i < r; i++)
            board[i - 1][x] = board[i][x];
        for (int i = 1; i <= c - 1; i++)
            board[r - 1][i - 1] = board[r - 1][i];
        for (int i = r - 1 - 1; i >= y; i--)
            board[i + 1][c - 1] = board[i][c - 1];
        for (int i = c - 1 - 1; i >= 1; i--)
            board[y][i + 1] = board[y][i];
        board[y][x + 1] = 0;
    }
}

int main()
{
    FAST_IO;

    cin >> r >> c >> t;
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
        {
            cin >> board[i][j];
            if (board[i][j] == -1)
                cleaner.push_back({i, j});
        }

    while (t--)
    {
        spread();  // 1.
        cleaned(); // 2.
    }

    cout << accumulate(&board[0][0], &board[0][0] + size(board) * size(board[0]), 0) + 2;
}