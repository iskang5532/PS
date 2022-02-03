// 10994 별 찍기 = 19
// https://www.acmicpc.net/problem/10994
/*
    재귀, 구현 (2,176KB, 4ms)
    시간 복잡도: ?
    풀이)
    - n이 주어졌을 때, 출력할 사각형의 길이 len은 4*n - 3.
    - 좌측 상단 별의 위치를 (0,0)이라 했을 때, 공백이 채워지는 구간은 홀수의 값을 가짐.
    - board에 별과 공백의 값을 채운 후, 출력.
    - 값을 채울 때는, 두 부분으로 나누어 채움.
    첫 번째는 좌측 상단에서부터 우측과 하단으로 이동하며 채움.
    두 번째는 우측 하단에서부터 상단과 좌측으로 이동하며 채움.
    이를 홀수일 때 수행시켜 board를 채움.
    etc.) dep > len*2: 좌상단과 우하단의 중복 수행을 막기 위함.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"
#define MAX 400 + 1

int n; // 1 ≤ N ≤ 100
char board[MAX][MAX];

void dfs(int dep, int len)
{
    if (dep > len >> 1)
        return;

    if (dep & 1)
    {
        for (int i = dep; i < len - dep; i++) // 왼쪽 위부터
            board[i][dep] = board[dep][i] = ' ';
        for (int i = len - 1 - dep; i > dep; i--) // 오른쪽 아래부터
            board[i][len - 1 - dep] = board[len - 1 - dep][i] = ' ';
    }

    dfs(dep + 1, len);
}

int main()
{
    FAST_IO;

    cin >> n;

    fill(&board[0][0], &board[0][0] + sizeof(board) / sizeof(board[0][0]), '*');

    const int len = 4 * n - 3;
    dfs(0, len);

    for (int i = 0; i < len; i++)
    {
        for (int j = 0; j < len; j++)
            cout << board[i][j];
        cout << endl;
    }
}