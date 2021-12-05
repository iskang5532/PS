/*
    1520 내리막 길
    BFS, DP (3,860KB, 24ms)
    시간 복잡도: ?
    문제: https://www.acmicpc.net/problem/1520
    풀이)
    - 높은 곳에서 낮은 곳으로 이동해야 함. 즉, 왔던 곳을 다시 갈 수는 없으며, 이는 DAG.
    - DAG이므로 BFS로 접근하였으며, 목적지까지 도달 가능한 경로의 개수를 세는 것이므로, 개수를 저장하며 탐색.
    - 높이가 제일 낮은 지점은 제일 마지막에 탐색해야 이전까지 탐색하여 저장한 경로의 개수를 모두 얻을 수 있음.
    그러므로 높이를 기준으로 내림차순 정렬을 시킨 후, 높이가 상대적으로 높은 지점을 먼저 탐색시킴.
    1) visited 배열을 선언하여 방문 기력 및 현재 위치까지 올 수 있는 최대 개수를 저장.
    2) 시작점인 (0,0)을 넣어 가능한 모든 지점을 탐색시킴.
    3) 다음 위치까지의 경로는 현재 경로를 더한 값이다. 이후 다음 위치에 대해 탐색할 수 있도록 큐어 줘야 하나,
    만약 다음 위치가 앞서 방문한 적이 있을 시 다음 위치는 이미 큐에 저장되어 있으므로 넣지 않음.
    etc.)
 */

#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define endl "\n"
#define MAX 500 + 1

struct P
{
    int h, y, x;
};

struct h_greater // 높이를 기준으로 내림차순
{
    bool operator()(const P &p1, const P &p2) { return p1.h < p2.h; }
};

const int dx[4] = {0, 1, 0, -1};
const int dy[4] = {-1, 0, 1, 0};

int n, m; // 1 ≤ n, m ≤ 500
int board[MAX][MAX];

int get_ans() // BFS
{
    int visited[MAX][MAX]; //
    for (int i = 0; i < m; i++)
        fill(visited[i], visited[i] + MAX, 0);

    priority_queue<P, vector<P>, h_greater> pq;
    pq.push({board[0][0], 0, 0});
    visited[0][0] = 1;
    while (!pq.empty())
    {
        auto [h, y, x] = pq.top();
        pq.pop();

        for (int i = 0; i < 4; i++)
        {
            int ny = y + dy[i];
            int nx = x + dx[i];

            if (!(0 <= ny && ny < n) || !(0 <= nx && nx < m)) // OOB
                continue;
            if (board[ny][nx] >= board[y][x]) // 내리막길인가?
                continue;
            if (!visited[ny][nx]) // 방문한 적이 있는가?
                pq.push({board[ny][nx], ny, nx});

            visited[ny][nx] += visited[y][x];
        }
    }
    return visited[n - 1][m - 1];
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
            cin >> board[i][j]; // 1 ≤ 10h

    cout << get_ans();
}