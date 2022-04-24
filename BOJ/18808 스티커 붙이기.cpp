// 2022-04-18
// 18808 스티커 붙이기
// https://www.acmicpc.net/problem/18808
/*
    구현 (2,032KB, 4ms)
    시간 복잡도: ?
    풀이)
    - 입력받은 스티커를 노트북에 붙일 수 있는지를 확인. (= isValid())
    - 노트북의 원점 (0, 0)에서부터 스티커의 크기만큼 탐색.
    만약 스티커가 존재하는 부분이면서 노트북에는 스티커가 붙여지지 않았을 시, 스티커를 붙임.
    - 스티커를 붙일 수 없을 경우, 오른쪽으로 90도 회전. (= rotated())
    - 주의할 점은, 기존에 입력받은 스티커의 r와 c를 사용하게 될 경우 OOB가 될 수 있음. (스티커 회전 시에 r와 c가 바뀜)
    그러므로, 입력받은 값이 아닌 현재 회전시킬 스티커의 r과 c를 구하여 사용.
    etc.) 이 문제처럼 가끔 -1을 해줘야 하는 문제들이 있는데, 너무 어렵다.
7 */

#include <iostream>
#include <vector>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 43 // max n, m

int n, m, k; // 가로 및 세로 n, m(1 ≤ n, m ≤ 40), 스티커의 개수 k(1 ≤ k ≤ 100)
int board[MAX][MAX];

bool isValid(const vector<vector<int>> &sticker)
{
    int r = sticker.size(), c = sticker.front().size();

    for (int i = 0; i < n - (r - 1); i++)
        for (int j = 0; j < m - (c - 1); j++)
        {
            bool flag = true;
            for (int y = 0; y < r && flag; y++)
                for (int x = 0; x < c && flag; x++)
                    if (sticker[y][x] && board[i + y][j + x]) // 붙이려는 장소에 이미 스티커가 존재
                        flag = false;

            if (flag)
            {
                for (int y = 0; y < r; y++)
                    for (int x = 0; x < c; x++)
                        if (sticker[y][x])
                            board[y + i][x + j] = true;
                return true;
            }
        }

    return false;
}

void rotated(vector<vector<int>> &sticker)
{
    int r = sticker.size(), c = sticker.front().size();

    vector<vector<int>> ret(c, vector<int>(r));
    for (int y = 0; y < r; y++)
        for (int x = 0; x < c; x++)
            ret[x][r - 1 - y] = sticker[y][x];

    sticker = move(ret);
}

int main()
{
    FAST_IO;

    cin >> n >> m >> k;
    while (k--)
    {
        int r, c; // Ri, Ci(1 ≤ Ci ≤ 10)
        cin >> r >> c;
        vector<vector<int>> sticker(r, vector<int>(c));
        for (auto &v : sticker)
            for (auto &i : v)
                cin >> i;

        for (int d = 0; d < 4; d++)
        {
            if (isValid(sticker))
                break;

            rotated(sticker);
        }
    }

    int ans = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (board[i][j])
                ans++;
    cout << ans;
}