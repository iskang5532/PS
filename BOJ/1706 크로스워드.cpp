// 2022-10-26
// 1706 크로스워드
// https://www.acmicpc.net/problem/1706
/*
    구현 (2,024KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 입력된 퍼즐의 모든 세로 단어를 확인 후, 사전식 순으로 가장 앞서 있는 낱말을 s1에 저장.
    - 퍼즐을 시계방향으로 90도 회전.
    이후, 회전된 퍼즐에서 모든 세로 단어를 확인 후, 사전식 순으로 가장 앞서 있는 낱말을 s2에 저장.
    - s1과 s2를 비교 후 사전식 순으로 앞서 있는 낱말을 출력.
    - 단어 확인 중에 '#'을 만날 경우, 그전에 나온 문자들을 모아놓은 문자열 s를 단어로 취급.
    주의할 점은, s의 길이가 1일 수 있음. 이때는 단어로 취급하지 않음.
    etc.) 가로 단어와 세로 단어를 확인하는 식으로 풀려다가, 배열 회전이 떠올라 풀이를 바꿈
 */

#include <iostream>
#include <vector>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

string get_ans(const vector<vector<char>> &board) // 세로 단어 확인
{
    string ret;
    ret += ('z' + 1); // 첫 단어가 항상 사전순으로 앞설 수 있도록

    int r = board.size(), c = board.front().size();
    for (int x = 0; x < c; x++)
    {
        string s;
        for (int y = 0; y < r; y++)
            if (board[y][x] != '#')
                s += board[y][x];
            else
            {
                if (s.length() >= 2 && s < ret)
                    ret = s;
                s.clear();
            }

        if (s.length() >= 2 && s < ret)
            ret = s;
    }

    return ret;
}

void rotate(vector<vector<char>> &board) // 시계 방향 회전
{
    int r = board.size(), c = board.front().size();

    vector<vector<char>> ret(c, vector<char>(r));
    for (int y = 0; y < c; y++)
        for (int x = 0; x < r; x++)
            ret[y][x] = board[r - 1 - x][y];

    board = move(ret);
}

int main()
{
    FAST_IO;

    int r, c; // (2 ≤ R, C ≤ 20)
    cin >> r >> c;
    vector<vector<char>> board(r, vector<char>(c));
    for (auto &v : board)
        for (auto &i : v)
            cin >> i;

    string s1 = get_ans(board);
    rotate(board);
    string s2 = get_ans(board);

    cout << (s1 < s2 ? s1 : s2);
}