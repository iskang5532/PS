// 1890 점프, 4620 Pascal's Travels
// https://boj.kr/1890 https://boj.kr/4620
// TC: https://www.cs.helsinki.fi/group/boi2006/ (Day 2 - Jump)
/*
    sol.1) DP (2,020KB, 0ms)
    시간 복잡도: O(n^2)
    풀이)
    - 현재 탐색 중인 위치에서 이동할 수 있는 다음 위치는 우측과 하단뿐이며, 이전에 왔던 곳으로 돌아갈 수 없다.
    이를 이용해 {y, x}에서 도달할 수 있는 다음 위치 ny, nx에 현재 위치까지 도달할 수 있는 경우의 수 dp[y][x]를 더해준다.
    - 값이 int형의 범위를 넘어갈 수 있으므로, long long을 사용해줌.
    - {n-1, n-1}을 탐색할 때 입력된 board[n-1][n-1]의 값이 0이어서 필요 없는 값까지 dp에 저장될 수 있으므로, {n-1, n-1}에서 break 해준다.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 100 + 1 // max n
using ll = long long;

int main()
{
    FAST_IO;

    int n; //  판의 크기
    cin >> n;

    int board[MAX][MAX]; //  0 ≤ k ≤ 9
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> board[i][j];

    ll dp[MAX][MAX];
    fill(&dp[0][0], &dp[0][0] + sizeof(dp) / sizeof(dp[0][0]), 0);
    dp[0][0] = 1;

    for (int y = 0; y < n; y++)
        for (int x = 0; x < n; x++)
        {
            if (y == n - 1 && x == n - 1)
                break;

            int nx = x + board[y][x];
            if (nx < n) // OOB
                dp[y][nx] += dp[y][x];

            int ny = y + board[y][x];
            if (ny < n)
                dp[ny][x] += dp[y][x];
        }

    cout << dp[n - 1][n - 1] << '\n';
}

/*
    sol.2) BFS (2,156KB, ms)
    시간 복잡도: O(n^2)
    풀이)
    - 현재 탐색중인 위치에서 이동할 수 있는 다음 위치는 우측과 하단 뿐이며, 이전에 왔던 곳으로 돌아갈 수 없다.
    그러므로, 탐색할 때 현재 위치보다 이전의 위치를 탐색하지 않도록 정렬해줘야 한다. (= pq cmp)
    - 값이 int형의 범위를 넘어갈 수 있으므로, long long을 사용해줌.
 */

#include <iostream>
#include <queue>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 100 + 1 // max n
using ll = long long;

const int dy[2] = {0, 1};
const int dx[2] = {1, 0};

struct pii
{
    int y, x;
};

struct cmp
{
    bool operator()(const pii &p1, const pii &p2) { return p1.y != p2.y ? p1.y > p2.y : p1.x > p2.x; }
};

ll bfs(const vector<vector<int>> &board, const int n)
{
    vector<vector<ll>> dist(n, vector<ll>(n, 0));
    priority_queue<pii, vector<pii>, cmp> pq;

    pq.push({0, 0});
    dist[0][0] = true;

    while (!pq.empty())
    {
        auto [y, x] = pq.top();
        int d = board[y][x];
        pq.pop();

        if (y == n - 1 && x == n - 1)
            return dist[n - 1][n - 1];

        for (int i = 0; i < 2; i++)
        {
            int ny = y + (d * dy[i]),
                nx = x + (d * dx[i]);

            if (!(0 <= ny && ny < n) || !(0 <= nx && nx < n))
                continue;

            if (dist[ny][nx] == false)
                pq.push({ny, nx});
            dist[ny][nx] += dist[y][x]; // if문 안에 넣을 경우, 가장 먼저 이동 가능한 경우의 횟수, 즉 한 번밖에 저장하지 못함
        }
    }

    return dist[n - 1][n - 1];
}

int main()
{
    FAST_IO;

    int n;
    cin >> n;

    vector<vector<int>> board(n, vector<int>(n));
    for (auto &y : board)
        for (auto &x : y)
            cin >> x;

    cout << bfs(board, n);
}

// 6%
// 4
// 1 2 2 3
// 1 1 3 3
// 3 1 1 3
// 3 2 1 0
// ans: 5