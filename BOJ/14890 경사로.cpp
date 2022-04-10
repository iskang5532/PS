// 14890 경사로
// https://www.acmicpc.net/problem/14890
// 2022-04-10
/*
    구현 (2,060KB, 0ms)
    풀이)
    - 위에서 아래로 n개만큼 탐색하여 길이 존재할 수 있는지 탐색. (= left_to_right())
    - 왼쪽에서 오른쪽으로 n개만큼 탐색하여 길이 존재할 수 있는지 탐색. (= top_to_bot())
    - 현재 칸과 다음 칸의 높이가 0일 경우, 다음 칸을 탐색
    - 현재 칸과 다음 칸의 높이 차이가 1일 경우
     - 현재 칸이 더 높은 경우, 다음 칸부터 l개의 칸을 탐색.
     - 현재 칸이 더 낮은 경우, 현재 칸을 포함하여 이전 칸을 l개 탐색.
     만약 l개의 칸 중 높이가 다른 칸이 있거나, 이미 경사로가 설치되어 있거나, OOB인 경우 길은 존재할 수 없음.
     그 외의 경우, 칸에 경사로를 설치.
    - 현재 칸과 다음 칸의 높이 차이가 2 이상일 경우, 길이 존재할 수 없음.
    - 길이 존재할 수 없는 경우가 생기지 않고 탐색이 완료된 경우, ans++.
    etc.) 더 최적화하고 싶은데 생각이 나질 않음
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 103

int n, l;            // 크기 n(2 ≤ n ≤ 100), 길이 l(1 ≤ l ≤ n)
int board[MAX][MAX]; // 1 ≤ k ≤ 10

int left_to_right() // 왼쪽에서 오른쪽으로
{
    int ret = 0;
    for (int y = 0; y < n; y++)
    {
        bool valid = true;
        bool visited[MAX]{}; // visited[i] = true일 경우, i번째에는 경사로가 설치됨
        for (int x = 0; x < n - 1; x++)
            if (board[y][x] - 1 == board[y][x + 1]) // 다음 칸 높은 칸일 경우 (단, 차이는 1)
                for (int nx = x + 1; nx <= x + l; nx++)
                {
                    if (!(nx < n) || board[y][x] - 1 != board[y][nx] || visited[nx])
                        valid = false;
                    else // !OOB
                        visited[nx] = true;
                }
            else if (board[y][x] + 1 == board[y][x + 1]) // 다음 칸은 낮은 칸일 경우 (단, 차이는 1)
                for (int px = x; px > x - l; px--)
                {
                    if (!(0 <= px) || board[y][px] != board[y][x] || visited[px])
                        valid = false;
                    else // !OOB
                        visited[px] = true;
                }
            else if (abs(board[y][x] - board[y][x + 1]) >= 2) // 다음 칸과의 차이가 2 이상일 경우
                valid = false;

        if (valid)
            ret++;
    }

    return ret;
}

int top_to_bot() // 위에서 아래로
{
    int ret = 0;
    for (int x = 0; x < n; x++)
    {
        bool valid = true;
        bool visited[MAX]{}; // visited[i] = true일 경우, i번째에는 경사로가 설치됨
        for (int y = 0; y < n - 1; y++)
            if (board[y][x] - 1 == board[y + 1][x]) // 다음 칸 높은 칸일 경우 (단, 차이는 1)
                for (int ny = y + 1; ny <= y + l; ny++)
                {
                    if (!(ny < n) || board[y][x] - 1 != board[ny][x] || visited[ny])
                        valid = false;
                    else // !OOB
                        visited[ny] = true;
                }
            else if (board[y][x] + 1 == board[y + 1][x]) // 다음 칸은 낮은 칸일 경우 (단, 차이는 1)
                for (int py = y; py > y - l; py--)
                {
                    if (!(0 <= py) || board[py][x] != board[y][x] || visited[py])
                        valid = false;
                    else // !OOB
                        visited[py] = true;
                }
            else if (abs(board[y][x] - board[y + 1][x]) >= 2) // 다음 칸과의 차이가 2 이상일 경우
                valid = false;

        if (valid)
            ret++;
    }

    return ret;
}

int main()
{
    FAST_IO;

    cin >> n >> l;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> board[i][j];

    cout << left_to_right() + top_to_bot();
}