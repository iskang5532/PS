// 2022-06-16
// 2866 문자열 잘라내기
// https://www.acmicpc.net/problem/2866
/*
    셋 (5,076KB, 648ms)
    시간 복잡도: ?
    풀이)
    - 문제에서의 행과 열의 개념을 바꿔 품.
    - 입력된 문자열을 벡터 v에 저장한 후, 시계 방향으로 90도 rotate. (편하게 문자열을 추출하기 위함)
    - 행으로 만든 문자열 s를 저장할 셋 S.
    만약 s가 셋에 존재할 경우 종료.
    만약 s가 셋에 존재하지 않을 경우, 셋에 넣음.
    etc.) 문제 이해가 어려웠음.
 */

#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 1'003

unordered_set<string> S;

void rotate(vector<vector<char>> &v, int r, int c)
{
    vector<vector<char>> temp(c, vector<char>(r));

    for (int i = 0; i < c; i++)
        for (int j = 0; j < r; j++)
            temp[i][j] = v[r - 1 - j][i];

    v = temp;
}

int main()
{
    FAST_IO;

    int r, c;
    cin >> r >> c;
    vector<vector<char>> v(r, vector<char>(c));
    for (auto &row : v)
        for (auto &c : row)
            cin >> c;

    rotate(v, r, c);

    int ans = 0;
    for (int x = 1, valid = true; x < c && valid; x++, S.clear())
    {
        for (int y = 0; y < c && valid; y++)
        {
            string s = string(v[y].begin(), v[y].end() - x);
            if (S.find(s) == S.end())
                S.insert(s);
            else
                valid = false;
        }

        if (valid)
            ans++;
    }

    cout << ans;
}

// char v[MAX][MAX];
// for (int y = 0; y < r; y++)
//     for (int x = 0; x < c; x++)
//         cin >> v[x][y];
