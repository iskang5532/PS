// 2022-10-28
// 17406 배열 돌리기 4
// https://www.acmicpc.net/problem/17406
/*
    구현 (2,156KB, 0ms)
    시간 복잡도: ?
    풀이)
    - k가 최대 6이므로, 완전 탐색을 이용하여 모든 순서에 대한 값을 구한 후, 최솟값을 ans에 저장.
    - 입력된 k개의 연산을 v에 저장하며, 사용할 순서를 bits에 저장.
    next_permutation()을 이용하여 bits의 값을 변경하며, 변경된 값을 사용.
 */

#include <iostream>
#include <vector>
#include <algorithm> // next_permutation

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

struct P
{
    int r, c, s;
};

void rotate(vector<vector<int>> &board, int r, int c, int s)
{
    int st_y = r - 1 - s, st_x = c - 1 - s;
    int ed_y = r - 1 + s, ed_x = c - 1 + s;

    while (st_y < ed_y && st_x < ed_x)
    {
        int k = board[st_y][st_x];

        for (int pos = st_y; pos < ed_y; pos++)
            board[pos][st_x] = board[pos + 1][st_x];
        for (int pos = st_x; pos < ed_x; pos++)
            board[ed_y][pos] = board[ed_y][pos + 1];
        for (int pos = ed_y; pos > st_y; --pos)
            board[pos][ed_x] = board[pos - 1][ed_x];
        for (int pos = ed_x; pos > st_x; --pos)
            board[st_y][pos] = board[st_y][pos - 1];

        board[st_y][st_x + 1] = k;

        st_x++, st_y++; // 기준점을 좁힘
        ed_y--, ed_x--;
    }
}

int get_ans(const vector<vector<int>> &board)
{
    int ret = 0x3f3f3f3f;
    for (int i = 0; i < board.size(); i++)
    {
        int sum = 0;
        for (int j = 0; j < board.front().size(); j++)
            sum += board[i][j];

        ret = min(ret, sum);
    }

    return ret;
}

int main()
{
    FAST_IO;

    int n, m, k; // 크기 n, m(3 ≤ n, m ≤ 50), 연산 횟수 k(1 ≤ k ≤ 6)
    cin >> n >> m >> k;
    vector<vector<int>> board(n, vector<int>(m));
    for (auto &v : board)
        for (auto &i : v)
            cin >> i;

    vector<P> v(k);
    for (auto &[r, c, s] : v)
        cin >> r >> c >> s;

    vector<int> bits;
    for (int i = 0; i < k; i++)
        bits.push_back(i);

    int ans = 0x3f3f3f3f;
    do
    {
        auto _board(board);
        for (const auto &i : bits)
        {
            const auto &[r, c, s] = v[i];
            rotate(_board, r, c, s);
        }

        ans = min(ans, get_ans(_board));

    } while (next_permutation(bits.begin(), bits.end()));

    cout << ans;
}