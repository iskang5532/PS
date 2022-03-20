// 파괴되지 않은 건물 (코딩테스트 연습 > 2022 KAKAO BLIND RECRUITMENT > 파괴되지 않은 건물)
// https://programmers.co.kr/learn/courses/30/lessons/92344
/*
    누적합
    시간 복잡도: O(K + N * M)
    풀이)
    * 추가적인 내용은 해설 참고
    - 행렬의 크기와 skill의 원소의 개수가 많아 skill의 원소마다 행렬을 갱신하게 된다면 TLE.
    누적합을 이용해 skill의 갱신을 모아둔 후 한 번에 수행하는 식으로 시간 문제를 해결.
    etc.)
    - 누적합임을 알았지만 2차원 배열에 응용할 줄 몰라서 못푼 문제.
    - 해설을 보고난 후에 떠올랐는데, 비슷한 풀이를 백준에서 본 것 같은데 찾지 못함..
    참고)
    - 문제해설 및 참고: https://tech.kakao.com/2022/01/14/2022-kakao-recruitment-round-1/
 */

#include <bits/stdc++.h>

using namespace std;
#define MAX 1'003

constexpr int dy[2] = {0, 1}; // 우 하
constexpr int dx[2] = {1, 0};

int pSum[MAX][MAX];

void get_pSum(int n, int m)
{
    for (int i = 0; i < n; i++)
        for (int j = 1; j < m; j++)
            pSum[i][j] += pSum[i][j - 1];

    for (int j = 0; j < m; j++)
        for (int i = 1; i < n; i++)
            pSum[i][j] += pSum[i - 1][j];
}

int solution(vector<vector<int>> board, vector<vector<int>> skill)
{
    int n = board.size(), m = board[0].size();

    for (const auto &v : skill)
    {
        int t = v[0], r1 = v[1], c1 = v[2], r2 = v[3], c2 = v[4], h = v[5];

        if (t == 1) // down
            h *= -1;

        pSum[r1][c1] += h, pSum[r2 + 1][c2 + 1] += h;
        pSum[r2 + 1][c1] -= h, pSum[r1][c2 + 1] -= h;
    }

    get_pSum(n, m);

    int ans = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (board[i][j] + pSum[i][j] > 0)
                ans++;
    return ans;
}

// int main()
// {
//     cout << solution({{5, 5, 5, 5, 5},
//                       {5, 5, 5, 5, 5},
//                       {5, 5, 5, 5, 5},
//                       {5, 5, 5, 5, 5}},
//                      {{1, 0, 0, 3, 4, 4},
//                       {1, 2, 0, 2, 3, 2},
//                       {2, 1, 0, 3, 1, 2},
//                       {1, 0, 1, 3, 3, 1}})
//          << '\n'; // 10
//     cout << solution({{1, 2, 3},
//                       {4, 5, 6},
//                       {7, 8, 9}},
//                      {{1, 1, 1, 2, 2, 4},
//                       {1, 0, 0, 1, 1, 2},
//                       {2, 2, 0, 2, 0, 100}})
//          << '\n'; // 6
// }

// TLE
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;
#define INF 0x7fffffff
#define MAX 1'003

int cnt[MAX][MAX];

int solution(vector<vector<int>> board, vector<vector<int>> skill)
{
    fill(&cnt[0][0], &cnt[0][0] + MAX * MAX, 0);
    int n = board.size(), m = board[0].size();

    for (const auto &v : skill)
    {
        int t = v[0], r1 = v[1], c1 = v[2], r2 = v[3], c2 = v[4], h = v[5];

        if (t == 1) // down
            h *= -1;

        for (int y = r1; y <= r2; y++)
            cnt[y][c1] += h, cnt[y][c2 + 1] -= h;
    }

    for (int y = 0; y < n; y++)
    {
        int k = 0;
        for (int x = 0; x < m; x++)
        {
            k += cnt[y][x];
            board[y][x] += k;
        }
    }

    int ans = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (board[i][j] > 0)
                ans++;
    return ans;
}

// int main()
// {
//     cout << solution({{5, 5, 5, 5, 5},
//                       {5, 5, 5, 5, 5},
//                       {5, 5, 5, 5, 5},
//                       {5, 5, 5, 5, 5}},
//                      {{1, 0, 0, 3, 4, 4},
//                       {1, 2, 0, 2, 3, 2},
//                       {2, 1, 0, 3, 1, 2},
//                       {1, 0, 1, 3, 3, 1}})
//          << '\n'; // 10
//     cout << solution({{1, 2, 3},
//                       {4, 5, 6},
//                       {7, 8, 9}},
//                      {{1, 1, 1, 2, 2, 4},
//                       {1, 0, 0, 1, 1, 2},
//                       {2, 2, 0, 2, 0, 100}})
//          << '\n'; // 6
// }