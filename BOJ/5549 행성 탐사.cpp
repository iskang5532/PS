/* 
 * 5549 행성 탐사
 * 누적합
 * 시간 복잡도: ?
 * 문제: https://www.acmicpc.net/problem/5549
 * ETC.) 1749 점수따먹기와 같은 문제.
 * P의 변수는 J, O, I 순으로 선언했는데 연산에 대한 반환(= ret값)을 J, I, O와 같이 다르게 반환하는 실수를 해서 오래 걸림
 * 참고: 1749 점수따먹기.cpp
 */

#include <iostream>
#include <vector>

using namespace std;

#define endl "\n"

struct P
{
    int J, O, I;

    friend P operator+(const P &a, const P &b)
    {
        P ret = P{a.J + b.J, a.O + b.O, a.I + b.I};
        return ret;
    }
    friend P operator-(const P &a, const P &b)
    {
        P ret = P{a.J - b.J, a.O - b.O, a.I - b.I};
        return ret;
    }
    P &operator+=(const P &a)
    {
        J += a.J, O += a.O, I += a.I;
        return *this;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    int n, m, k; // 1 <= n, m <= 1k, 1 <= k <= 100k
    cin >> m >> n >> k;

    vector<vector<P>> sum(m + 1, vector<P>(n + 1, {0, 0, 0}));
    for (int col = 1; col <= m; col++)
    {
        for (int row = 1; row <= n; row++)
        {
            char c;
            cin >> c;

            if (c == 'J')
                sum[col][row].J++;
            else if (c == 'O')
                sum[col][row].O++;
            else if (c == 'I')
                sum[col][row].I++;

            sum[col][row] += sum[col - 1][row] + sum[col][row - 1] - sum[col - 1][row - 1];
        }
    }

    while (k--)
    {
        // 왼쪽 위 모서리 좌표 (a, b)
        // 오른쪽 아래 모서리 좌표 (c, d)
        int a, b, c, d;
        cin >> a >> b >> c >> d;

        P answer = sum[c][d] - sum[a - 1][d] - sum[c][b - 1] + sum[a - 1][b - 1];
        cout << answer.J << " " << answer.O << " " << answer.I << endl;
    }
}