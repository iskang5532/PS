/*
    방문 길이 (코딩테스트 연습 > Summer/Winter Coding(~2018) > 방문 길이)
    DP
    시간 복잡도: ?
    문제: https://programmers.co.kr/learn/courses/30/lessons/49994
    etc.) 4차원 배열을 이용함.
    - DP를 이용해 품. (4차원 배열)
    - 좌표평면 크기의 최솟값은 -5이며, 배열을 이용했으므로 모든 좌표에 대해 +5를 시켜 음수를 제거시켜줌.
    - dp[x][y][nx][ny]일 때, 두 좌표 (x, y), (nx, ny)간 이동한 적이 있는가? (x to nx or nx to x)
 */

#include <string>
#include <vector>

using namespace std;

#define MAX 10 // 5+5
typedef pair<int, int> pii;

const int dx[4] = {0, 1, 0, -1}; // U, R, D, L
const int dy[4] = {1, 0, -1, 0};

int solution(string dirs)
{
    bool dp[MAX + 1][MAX + 1][MAX + 1][MAX + 1]; // dp[x][y][nx][ny]일 때, 두 좌표 (x, y), (nx, ny)간 이동한 적이 있는가?
    for (int a = 0; a <= MAX; a++)
        for (int b = 0; b <= MAX; b++)
            for (int c = 0; c <= MAX; c++)
                fill(dp[a][b][c], dp[a][b][c] + MAX + 1, false);

    int ans = 0;
    pii pos = {5, 5}; // 시작점 (모든 좌표에 대해 +5를 시킴)
    for (const auto &c : dirs)
    {
        int dir;
        if (c == 'U')      dir = 0;
        else if (c == 'R') dir = 1;
        else if (c == 'D') dir = 2;
        else if (c == 'L') dir = 3;

        auto [x, y] = pos;
        int nx = x + dx[dir], ny = y + dy[dir];

        if (!(0 <= nx && nx <= MAX) || !(0 <= ny && ny <= MAX)) // 범위를 벗어나는 경우
            continue;

        if (dp[x][y][nx][ny] == false) // 이용한 적이 없는 경우
            dp[x][y][nx][ny] = dp[nx][ny][x][y] = true, ans++;
        pos = {nx, ny};
    }

    return ans;
}

// #include <iostream>
// #define endl "\n"
// int main()
// {
//     cout << solution("ULURRDLLU") << endl; // 7
//     cout << solution("LULLLLLLU") << endl; // 7
//     cout << solution("UD") << endl;        // 1
// }