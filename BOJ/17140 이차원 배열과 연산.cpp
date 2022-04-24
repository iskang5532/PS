// 2022-04-22
// 17140 이차원 배열과 연산
// https://www.acmicpc.net/problem/17140
/*
    구현, 정렬 (20KB, ms)
    시간 복잡도: ?
    풀이)


    - R()과 C()를 수행할 떄, 최대 크기가 줄어들거나 커질 수도 있으므로 r 혹은 c를 갱신해야 함.
    etc.)
    - 수와 수의 개수로 이루어진 컨테이너를 정렬하는 방법 중 가장 빠른 방법은 무엇인가
    참고)
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using pii = pair<int, int>;
#define MAX 103

int r, c, k;         // (1 ≤ r, c, k ≤ 100
int board[MAX][MAX]; // 1 ≤ x ≤ 100

bool cmp(const pii &p1, const pii &p2) { return p1.second != p2.second ? p1.second < p2.second : p1.first < p2.first; };

void R(int n, int &m) // 행 정렬
{
    int _m = 0;
    for (int y = 0; y < n; y++)
    {
        unordered_map<int, int> um;
        for (int x = 0; x < m; x++)
            um[board[y][x]]++;

        vector<pii> v;
        for (const auto &[i, cnt] : um)
            if (i != 0)
                v.push_back({i, cnt});
        sort(v.begin(), v.end(), cmp);

        int pos = 0;
        for (const auto &[i, cnt] : v)
        {
            if (pos >= 100)
                break;
            board[y][pos] = i, pos++;
            board[y][pos] = cnt, pos++;
        }
        for (int i = pos; i < m; i++)
            board[y][i] = 0;

        _m = max(_m, pos);
    }

    m = _m;
}

void C(int &n, int m) // 열 정렬
{
    int _n = 0;
    for (int x = 0; x < m; x++)
    {
        unordered_map<int, int> um;
        for (int y = 0; y < n; y++)
            um[board[y][x]]++;

        vector<pii> v;
        for (const auto &[i, cnt] : um)
            if (i != 0)
                v.push_back({i, cnt});
        sort(v.begin(), v.end(), cmp);

        int pos = 0;
        for (const auto &[i, cnt] : v)
        {
            if (pos >= 100)
                break;
            board[pos][x] = i, pos++;
            board[pos][x] = cnt, pos++;
        }

        for (int i = pos; i < n; i++)
            board[i][x] = 0;

        _n = max(_n, pos);
    }

    n = _n;
}

int main()
{
    FAST_IO;

    cin >> r >> c >> k;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            cin >> board[i][j];

    int n = 3, m = 3;
    int t = 0;
    while (board[r - 1][c - 1] != k && t <= 100)
    {
        t++;
        if (n >= m)
            R(n, m);
        else if (n < m)
            C(n, m);
    }

    cout << (t <= 100 ? t : -1);
}