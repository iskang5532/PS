// 2022-06-23
// 3005 크로스워드 퍼즐 쳐다보기
// https://www.acmicpc.net/problem/3005
/*
    sol.1) 구현 (2,020KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 모든 좌표에 대해 가로로 만들 수 있는 문자열과 세로로 만들 수 있는 문자열을 구함.
    이때, 구한 문자열 s를 이용하여 이전에 구한 사전적으로 가장 짧은 문자열 ans와 비교하여 ans에 저장.
    단, s의 길이는 2 이상이여야 하며 ans가 빈 문자열일 수 있음에 주의.
    - 문자열은 퍼즐의 중간부터 시작하여 구해선 안되므로, 시작 위치의 이전 값이 '#'이거나 범위를 벗어날 경우에만 수행.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 23 // max r, c

int r, c; // 2 ≤ R, C ≤ 20
char board[MAX][MAX];
string ans;

bool OOB(int ny, int nx) { return !(0 <= ny && ny < r) || !(0 <= nx && nx < c); }

void get_ans(int y, int x)
{
    if (OOB(y - 1, x) || board[y - 1][x] == '#')
    {
        string s = "";
        int l = 0;
        while (y + l < r && board[y + l][x] != '#')
            s += board[y + l][x], l++;
        if (l >= 2)
            ans = ans.empty() ? s : min(ans, s);
    }

    if (OOB(y, x - 1) || board[y][x - 1] == '#')
    {
        string s = "";
        int l = 0;
        while (x + l < c && board[y][x + l] != '#')
            s += board[y][x + l], l++;

        if (l >= 2)
            ans = ans.empty() ? s : min(ans, s);
    }
}

int main()
{
    FAST_IO;

    cin >> r >> c;
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            cin >> board[i][j];

    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            get_ans(i, j);

    cout << ans;
}

/*
    sol.2) 구현 (2,020KB, 0ms)
    시간 복잡도: ?
    풀이)
    - (0, 0)과 맞닿는 외곽 부분만을 탐색하여 가장 짧은 문자열을 구함.
    이때, 문자열을 구하는 도중 현재 위치의 문자가 '#"일 경우, 이전에 구한 문자열 s는 ans와 비교하여 더 작은 값을 ans에 저장한 후 값을 비움.
    - 문자열 s만 구하고 ans에 저장이 안 될 수도 있으므로 탐색이 완료되었다면 ans의 값을 갱신해야 함.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 23 // max r, c

char board[MAX][MAX];

int main()
{
    FAST_IO;

    int r, c; // 2 ≤ R, C ≤ 20
    cin >> r >> c;
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            cin >> board[i][j];

    string ans;
    for (int y = 0; y < r; y++)
    {
        string s = "";
        for (int x = 0; x < c; x++)
            if (board[y][x] == '#')
            {
                if (s.length() >= 2)
                    ans = ans.empty() ? s : min(ans, s);
                s.clear();
            }
            else
                s += board[y][x];

        if (s.length() >= 2)
            ans = ans.empty() ? s : min(ans, s);
    }
    for (int x = 0; x < c; x++)
    {
        string s = "";
        for (int y = 0; y < r; y++)
            if (board[y][x] == '#')
            {
                if (s.length() >= 2)
                    ans = ans.empty() ? s : min(ans, s);
                s.clear();
            }
            else
                s += board[y][x];

        if (s.length() >= 2)
            ans = ans.empty() ? s : min(ans, s);
    }

    cout << ans;
}