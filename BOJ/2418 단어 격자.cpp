// 2022-05-27
// 2418 단어 격자
// https://www.acmicpc.net/problem/2418
/*
    DP (4,972KB, 4ms)
    시간 복잡도: O(hwl * 8)
    풀이)
    - dp[y][x][dep] == k일 때, (y, x)에 도달하면서 dep번째 단어까지 만들 수 있는 개수는 k개.
    - 단어에서 탐색중인 문자의 위치를 dep이라 할 때, dep번째까지의 단어를 만들 수 있는 경우의 수를 구한 후 dp에 저장.
    - (y, x)가 board[dep]의 문자와 일치하는 경우, 이전 위치 [py][px]에서 이전 문자 board[dep - 1]를 찾음.
    이후, 현재 위치 dp인 dp[y][x]에 이전 문자의 경우의 수인 dp[py][nx]를 더함. (= dp[y][x][dep] += dp[py][px][dep - 1])
    etc.)
    - 이러한 dp 문제를 푼 적이 있었는데, 결국 까먹고 헤맴..
 */

#include <iostream>
#include <vector>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using pii = pair<int, int>;
using ll = long long;
#define MAX 203 // max h, w

constexpr int dy[] = {-1, -1, 0, 1, 1, 1, 0, -1}; // 북에서부터 시계 방향
constexpr int dx[] = {0, 1, 1, 1, 0, -1, -1, -1};

int h, w, l; // 크기 h, w(1 ≤ h, w ≤ 200), 단어의 길이 l(1 ≤ l ≤ 100)
char board[MAX][MAX];
string s;

bool OOB(int py, int px) { return !(0 <= py && py < h) || !(0 <= px && px < w); }

vector<vector<vector<ll>>> get_dp()
{
    // dp[y][x][dep] == k일 때, (y, x)에 도달하면서 dep번째 단어까지 만들 수 있는 개수는 k개
    vector<vector<vector<ll>>> dp(h, vector<vector<ll>>(w, vector<ll>(l, 0)));

    for (int y = 0; y < h; y++)
        for (int x = 0; x < w; x++)
            if (board[y][x] == s.front())
                dp[y][x][0]++;

    for (int dep = 1; dep < l; dep++)
        for (int y = 0; y < h; y++)
            for (int x = 0; x < w; x++)
                if (board[y][x] == s[dep]) // 필요한 문자인 경우
                    for (int d = 0; d < 8; d++)
                    {
                        auto [py, px] = pii{y + dy[d], x + dx[d]}; // 이전 문자의 위치
                        if (OOB(py, px))
                            continue;
                        if (board[py][px] != s[dep - 1])
                            continue;

                        dp[y][x][dep] += dp[py][px][dep - 1];
                    }

    return dp;
}

int main()
{
    FAST_IO;

    cin >> h >> w >> l;
    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++)
            cin >> board[i][j];
    cin >> s;

    auto dp = get_dp();

    ll ans = 0;
    for (int y = 0; y < h; y++)
        for (int x = 0; x < w; x++)
            ans += dp[y][x][l - 1];
    cout << ans;
}

// TLE (완전 탐색)
#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using pii = pair<int, int>;
using ll = long long;
#define MAX 203 // max h, w

constexpr int dy[] = {-1, -1, 0, 1, 1, 1, 0, -1};
constexpr int dx[] = {0, 1, 1, 1, 0, -1, -1, -1};

int h, w, l; // 크기 h, w(1 ≤ h, w ≤ 200), 단어의 길이 l(1 ≤ l ≤ 100)
char board[MAX][MAX];
string s;
ll ans = 0;

bool OOB(int py, int px) { return !(0 <= py && py < h) || !(0 <= px && px < w); }

void dfs(int dep, int y, int x)
{
    if (dep == l)
    {
        ans++;
        return;
    }

    for (int d = 0; d < 8; d++)
    {
        auto [py, px] = pii{y + dy[d], x + dx[d]};
        if (OOB(py, px))
            continue;
        if (board[py][px] != s[dep])
            continue;

        dfs(dep + 1, py, px);
    }
}

int main()
{
    FAST_IO;

    cin >> h >> w >> l;
    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++)
            cin >> board[i][j];
    cin >> s;

    for (int y = 0; y < h; y++)
        for (int x = 0; x < w; x++)
            if (board[y][x] == s.front())
                dfs(1, y, x);

    cout << ans;
}