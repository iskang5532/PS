// [1차] 프렌즈4블록 (코딩테스트 연습 > 2018 KAKAO BLIND RECRUITMENT > [1차] 프렌즈4블록)
// https://programmers.co.kr/learn/courses/30/lessons/17679
/*
    구현
    시간 복잡도: O(5n^2)
    풀이)
    - 2중 for문으로 (n-1, m-1)까지 탐색하며 2x2블록이 형성되느지를 확인.
    이때 주의할 점은, (n, m)까지 탐색하게 된다면 2x2블록인지를 확인하기 위해 (n+1, m+1)를 탐색하게 되는데, 이 경우 OOB이다.
    - 2x2블록을 찾은 경우, 해당 네 칸이 2x2블록임을 check에 저장.
    - 모든 영역의 탐색을 마쳤다면, 다시 한 번 2중 for문을 이용해 check 배열을 탐색.
    만약 현재 위치가 true일 경우, 즉 2x2블록인 경우 board의 값을 제거시켜주며 cnt++.
    - 2중 for문을 이용한 탐색에도 제거된 블록이 없을 경우, 종료.
    만약 제거된 블록이 있을 경우, 위에 있는 블록을 아래로 내림.
    - x = 0부터 m - 1까지 x축을 하나씩 확인하며, y축은 공백의 시작점과 블록의 시작점을 저장.
    이후 블록을 공백의 위치에 옮기며, y가 마지막 위치까지 갈 떄까지 반복한다.
    etc.) 2중 for문에 bfs까지 추가하여 풀었지만, 풀고 나니 bfs는 필요 없었음.
    - 풀고난 후에 최적화가 3~4번 이루어진 문제.
 */

#include <bits/stdc++.h>

using namespace std;
using pii = pair<int, int>;
#define MAX 33 // max n, m

int get_cnt(vector<string> &board, int n, int m)
{
    int ret = 0;

    bool check[MAX][MAX];
    fill(&check[0][0], &check[0][0] + size(check[0]) * size(check), false);

    for (int y = 0; y < n - 1; y++) // (n-1, m-1)에서는 2x2블록일 수가 없으므로 제외 (and 탐색 시 OOB)
        for (int x = 0; x < m - 1; x++)
        {
            if (board[y][x] == '\0')
                continue;

            char c = board[y][x];
            if (board[y][x + 1] == c && board[y + 1][x] == c && board[y + 1][x + 1] == c)
                check[y][x] = check[y][x + 1] = check[y + 1][x] = check[y + 1][x + 1] = true;
        }

    for (int y = 0; y < n; y++)
        for (int x = 0; x < m; x++)
            if (check[y][x])
                ret++, board[y][x] = '\0';

    return ret;
}

void Push(vector<string> &board, int n, int m)
{
    for (int x = 0; x < m; x++)
    {
        int under = n - 1;
        for (; under >= 0; under--)
            if (board[under][x] == '\0')
                break;

        int upper = under - 1;
        for (; upper >= 0; upper--)
            if (board[upper][x] != '\0')
                break;

        if (upper == -1)
            continue;

        for (; upper >= 0; upper--)
            if (board[upper][x] != '\0' && board[under][x] == '\0')
                board[under][x] = board[upper][x], board[upper][x] = '\0', under--;
    }
}

int solution(int n, int m, vector<string> board)
{
    int ans = 0;

    while (true)
    {
        int cnt = get_cnt(board, n, m);
        if (cnt == 0) // 제거한 블록이 없는 경우
            return ans;

        ans += cnt;

        Push(board, n, m);
    }
}

// int main()
// {
//     cout << solution(6, 6, {"TTTANT", "RRFACC", "RRRFCC", "TRRRAA", "TTMMMF", "TMMTTJ"}) << '\n'; // 14
//     cout << solution(4, 5, {"CCBDE", "AAADE", "AAABF", "CCBBF"}) << '\n';                         // 15
// }