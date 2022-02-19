// 3085 사탕 게임
// https://www.acmicpc.net/problem/3085
/*
    완전 탐색 (2,024KB, 0ms)
    시간 복잡도: O(1,000,000)
    풀이)
    - 보드의 크기 N의 최댓값은 50이다.
    현재 탐색 중인 (y, x)를 네 방향의 값과 자리를 바꾼 후 연속된 수를 구할 때의 시간 복잡도는, (50*2) * 4 * 50^2 = 1e6이다.
    1) 기준값 (x, y)와 바꿔줄 값인 (ny, nx)를 정하여 서로 바꾼다.
    2) 이후 모든 칸을 탐색하여 상근이가 먹을 수 있는 사탕의 최대 개수 l을 구한다.
    3) 이전에 구한 값과 비교하여, 더 큰 값을 ans에 저장한다.
    4) (x, y)와 (ny, nx)를 바꾸어 이전과 같게 만든다.
    이후 모든 기준값을 탐색할 때까지 위 과정을 반복한다.
    etc.) 대각선도 구해야 하는줄 알았지만 아녔음.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX_N 50

constexpr int dy[4] = {-1, 0, 1, 0}; // 위 오 아 왼
constexpr int dx[4] = {0, 1, 0, -1};

int n; // 보드의 크기 (3 ≤ N ≤ 50)
char board[MAX_N][MAX_N];

int get_mxm_len(int y, int x)
{
    int ret = 1;
    { // 가로
        int l = 1;
        for (int i = 1; i < n; i++)
            if (board[y][i - 1] == board[y][i])
                l++, ret = max(ret, l);
            else
                l = 1;
    }
    { // 세로
        int l = 1;
        for (int i = 1; i < n; i++)
            if (board[i - 1][x] == board[i][x])
                l++, ret = max(ret, l);
            else
                l = 1;
    }

    return ret;
}

int main()
{
    FAST_IO;

    cin >> n;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> board[i][j];

    int ans = 0;
    for (int y = 0; y < n; y++)
        for (int x = 0; x < n; x++)
            for (int i = 0; i < 4; i++)
            {
                int nx = x + dx[i],
                    ny = y + dy[i];

                if (!(0 <= ny && ny < n) || !(0 <= nx && nx < n)) // OOB
                    continue;

                swap(board[y][x], board[ny][nx]);
                ans = max(ans, get_mxm_len(y, x));
                swap(board[y][x], board[ny][nx]);
            }

    cout << ans;
}