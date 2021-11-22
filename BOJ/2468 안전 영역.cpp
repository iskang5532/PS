/*
    2468 안전 영역
    BFS (2,156KB, 28ms)
    시간 복잡도: ?
    문제: https://www.acmicpc.net/problem/2468
    풀이)
    - 깊이에 따라 나눠지는 영역의 개수가 다르므로, 각 깊이에 따른 영역의 개수를 세어줘야 함.
    그러므로 깊이의 최댓값을 위해 높이의 최댓값을 구함. (= mx)
    - BFS를 이용해 모든 지역을 조사함.
     - 만약 현재 조사중인 지역이 안전한 영역인 경우, 영역의 횟수(= cnt)를 +1해주며 주변 지역을 탐색. (또한, 재방문을 하지 않도록 visited = 1)
     - 만약 현재 조사중인 지역이 안전하지 않은 영역인 경우, 다음 지역을 탐색.
    - 깊이에 따른 BFS로 구한 값을 이전에 구한 값과 비교하여 높은 값을 저장.
 */

#include <iostream>
#include <queue>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define endl "\n"
typedef pair<int, int> pii;

const int dx[4] = {0, 1, 0, -1}; //상, 우, 하, 좌
const int dy[4] = {-1, 0, 1, 0};

int check(const vector<vector<int>> &arr, int n, int deep)
{
    int ret = 0; // 영역의 개수

    vector<vector<int>> visited(n, vector<int>(n, 0));
    for (int row = 0; row < n; row++)
        for (int col = 0; col < n; col++)
        {
            if (visited[col][row] || arr[col][row] <= deep) // 방문한 경우 or 잠기는 경우
                continue;
            ret++; // 영역 +1

            queue<pii> q;
            q.push({col, row});
            while (!q.empty())
            {
                auto [x, y] = q.front();
                q.pop();

                for (int i = 0; i < 4; i++)
                {
                    int nx = x + dx[i];
                    int ny = y + dy[i];

                    if (!(0 <= nx && nx < n) || !(0 <= ny && ny < n)) // 범위
                        continue;
                    if (visited[nx][ny] || arr[nx][ny] <= deep)
                        continue;

                    visited[nx][ny] = true;
                    q.push({nx, ny});
                }
            }
        }

    return ret;
}

int main()
{
#ifdef CUSTOM
    cout << "[CUSTOM]" << endl;
#else // BOJ
    FAST_IO;
#endif

    int n; // 2채원 배열의 행과 열의 개수
    cin >> n;

    int mx = 0; // 주어지는 지역 중 가장 큰 높이
    vector<vector<int>> arr(n, vector<int>(n));
    for (auto &row : arr)
        for (auto &col : row)
        {
            cin >> col;
            mx = max(mx, col);
        };

    int ans = 0;
    for (int deep = 0; deep <= mx; deep++)
        ans = max(ans, check(arr, n, deep));

    cout << ans;
}