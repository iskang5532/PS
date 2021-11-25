/*
    2638 치즈
    BFS (2,104KB, 12ms)
    시간 복잡도: ?
    문제: https://www.acmicpc.net/problem/2638
    풀이)
    1) BFS로 외곽에 존재하는 공기를 조사하며, 공기와 치즈가 인접하면 인접한 공기의 개수를 세어줌 (= cnt)
    가장자리에 치즈가 놓일 경우는 없으므로 (0,0)에서부터 조사.
    2) 칸마다 조사하며, cnt >= 2인 치즈는 공기로 만들어줌.
    만약 치즈지만 cnt < 2일 경우 치즈는 남게 되며, 이는 1)을 다시 진행해야 함.
    3) 치즈가 남아 있으면 시간 +1, 없으면 정답을 출력.
    만약 치즈가 남아 있으면, 1)부터 진행하여 치즈가 없어질 때까지 반복.
    etc.)
    - 치즈가 존재하지 않는 경우는 없는듯
 */

#include <iostream>
#include <queue>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define endl "\n"
#define MAX 100 + 1
typedef pair<int, int> pii;

const int dx[4] = {0, 1, 0, -1};
const int dy[4] = {-1, 0, 1, 0};

int n, m; // 5 ≤ n, m ≤ 100
int arr[MAX][MAX];
int cnt[MAX][MAX]; // 치즈와 인접한 공기의 개수를 저장

bool OOB(const int ny, const int nx) { return ny < 0 || n <= ny || nx < 0 || m <= nx; }
void get_cnt()
{
    vector<vector<bool>> visited(n, vector<bool>(m, false));
    queue<pii> q;
    q.push({0, 0});
    visited[0][0] = true;
    while (!q.empty())
    {
        auto [y, x] = q.front();
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (OOB(ny, nx) || visited[ny][nx])
                continue;

            if (arr[ny][nx] == 1) // 치즈인 경우, 인접한 공기의 개수 +1
                cnt[ny][nx]++;
            else
            {
                visited[ny][nx] = true;
                q.push({ny, nx});
            }
        }
    }
}

bool isValid() // 치즈가 남아 있는가?
{
    bool valid = false;

    for (int y = 0; y < n; y++)
        for (int x = 0; x < m; x++)
            if (arr[y][x] == 1)
            {
                if (cnt[y][x] >= 2) // 인접한 공기가 2개 이상인 경우, 치즈를 녹임
                    arr[y][x] = 0;
                else // 2개 이상이 아닌 경우 (= 치즈를 녹일 수 없으며, 이는 치즈가 남아 시간이 더 걸리게 됨)
                    valid = true;
            }

    return valid;
}

int main()
{
#ifdef CUSTOM
    cout << "[CUSTOM]" << endl;
#else // BOJ
    FAST_IO;
#endif

    cin >> n >> m;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> arr[i][j];

    int ans = 1;
    while (true)
    {
        for (int i = 0; i < n; i++)
            fill(cnt[i], cnt[i] + MAX, 0);

        get_cnt();
        if (isValid()) // 치즈가 남아 있는 경우
            ans++;
        else
        {
            cout << ans;
            return 0;
        }
    }
}