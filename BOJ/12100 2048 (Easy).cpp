/* 
 * 12100 2048 (Easy)
 * brute-force, backtracking
 * 시간 복잡도: ?
 * 문제: https://www.acmicpc.net/problem/12100
 * etc.) 빈 칸을 어떻게 채워야 하나 고민했었는데, 빈 벡터에 push한 후 그대로 반환하는 식으로 품.
 * - 모든 푸쉬는 왼쪽으로 밈.
 * 만약 미는 방향이 왼쪽이 아닌 경우, board 자체를 회전시켜 미는 방향을 맞춰줌.
 * - 밀면서 넣은 값이 결합된 값일 수 있기 때문에 그것에 대한 예외처리가 필요.
 * 참고: https://blog.naver.com/jinhan814/222238490920 (push하는 방법에 대해)
 * https://blog.naver.com/jinhan814/222498451844 (회전 방법)
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define endl "\n"
#define MAX_CNT 5 // 이동 제한 횟수
#define UP 0      // 위로 합치기
#define RIGHT 1   // 오른쪽으로 합치기
#define DOWN 2    // 아래로 합치기

int n; // 보드의 크기 (1 <= n <= 20)
int ans = 0;

vector<vector<int>> pushed(const vector<vector<int>> &board)
{
    vector<vector<int>> ret;
    for (const auto &col : board)
    {
        vector<int> row;
        bool isCombined = false; // row의 마지막 값이 결합되며 들어온 값인가? (true일 경우, 다음 값이 그냥 들어오며, false일 경우 결합)
        for (const auto &k : col)
        {
            if (k == 0)
                continue;
            else if (row.empty() || row.back() != k || isCombined == true) // 값이 다르거나 마지막 값이 결합되어 들어간 경우
                row.push_back(k), isCombined = false;
            else if (row.back() == k) // 값이 같은 경우 (= 결합)
                row.back() <<= 1,
                    isCombined = true;
        }
        while (row.size() < n) // 빈 공간을 0으로 채워줌
            row.push_back(0);
        ret.push_back(row);
    }

    return ret;
}

vector<vector<int>> rotated(const vector<vector<int>> &board, const int idx)
{
    vector<vector<int>> ret(n, vector<int>(n, 0));

    switch (idx) // 미는 방향에 따른 회전의 변화
    {
    case RIGHT: // 우측으로 미는 경우 (= 180도 회전 필요)
        for (int col = 0; col < n; col++)
            for (int row = 0; row < n; row++)
                ret[col][row] = board[n - 1 - col][n - 1 - row];
        break;
    case UP: // 위쪽으로 미는 경우 (= 90도 (왼쪽으로))
        for (int col = 0; col < n; col++)
            for (int row = 0; row < n; row++)
                ret[col][row] = board[n - 1 - row][col];
        break;
    case DOWN: // 아래쪽으로 미는 경우 (= 90도 (오른쪽으로))
        for (int col = 0; col < n; col++)
            for (int row = 0; row < n; row++)
                ret[col][row] = board[row][n - 1 - col];
        break;
    }

    return ret;
}

void dfs(const vector<vector<int>> &board, const int cnt = 0)
{
    if (cnt == MAX_CNT) // 모든 push를 끝마친 경우
    {
        for (int i = 0; i < n; i++)
            ans = max(ans, *max_element(board[i].begin(), board[i].end())); // 최댓값 갱신
        return;
    }

    for (int idx = 0; idx < 4; idx++)
        if (idx == 3) // 3 (왼쪽으로 밀기)
            dfs(pushed(board), cnt + 1);
        else // 0, 1, 2 (위, 오른쪽, 아래)
            dfs(pushed(rotated(board, idx)), cnt + 1);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    cin >> n;

    vector<vector<int>> board(n, vector<int>(n)); // 2 <= 1024, i는 2^n꼴
    for (auto &col : board)
        for (auto &row : col)
            cin >> row;

    dfs(board);

    cout << ans;
}