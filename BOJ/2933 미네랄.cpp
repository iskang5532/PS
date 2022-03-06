// 2933 미네랄
// https://www.acmicpc.net/problem/2933
/*
    구현, BFS (2,036KB, 20ms)
    시간 복잡도: ?
    풀이)
    1. 제거할 클러스터가 들어온 경우, 왼쪽인지 오른쪽인지에 맞춰 board에서 제거함.
    2.  클러스터를 아래로 누름. (하늘에 떠 있는 클러스터가 존재할 경우, 바닥에 붙어 있는 클러스터인 body와 붙음)
     1. BFS를 이용해 바닥에 붙어 있는 클러스터 body를 구함.
     2. x = 0부터 c-1까지 공중에 뜬 클러스터가 있는지 탐색.
     - 만약 공중에 뜬 클러스터가 있는 경우, 해당 높이를 ys에 저장함.
     또한, 해당 위치가 body 혹은 땅에서부터 얼마나 높은지를 구함.
     3. c-1까지 구한 높이 중 가장 낮은 높이를 h에 저장. (이는 얼만큼 push할 건지를 나타냄)
     4. x = 0부터 c-1까지 눌러줌.
     - 공중에 뜬 클러스터의 시작점을 저장한 ys를 이용해 시작점 ys[x]에서부터 0까지 h만큼 밑으로 내림.
     - 만약 ys[x] == INF일 경우, 위치 x에는 공중에 뜬 클러스터가 없으므로, 다음 x+1를 탐색.
     - ys[x]에서부터 0까지 탐색하던 도중, body가 존재할 수 있음. 그러므로, 해당 위치가 body인지 확인해야 함.
    참고)
    - 이론: https://blog.naver.com/jinhan814/222116189402
 */

#include <iostream>
#include <queue>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#define endl "\n"
#define INF 0x7fffffff
#define MAX 103
using pii = pair<int, int>;

constexpr int dy[4] = {-1, 0, 1, 0}; // 상 우 하 좌
constexpr int dx[4] = {0, 1, 0, -1};

int r, c; // 동굴의 크기 (1 ≤ R,C ≤ 100)
char board[MAX][MAX];

void l_pop(int h) // 왼쪽에서 시작하여 클러스터를 제거
{
    for (int i = 0; i < c; i++)
        if (board[h][i] == 'x')
        {
            board[h][i] = '.';
            return;
        }
}
void r_pop(int h) // 오른쪽에서 시작하여 클러스터를 제거
{
    for (int i = c - 1; i >= 0; i--)
        if (board[h][i] == 'x')
        {
            board[h][i] = '.';
            return;
        }
}

void Push() // 클러스터를 밑으로 내림 (하늘에 떠 있을 경우)
{
    bool body[MAX][MAX]; // body[i][j] = true일 경우, (i, j)는 바닥에 있는 클러스터와 붙어 있음
    fill(&body[0][0], &body[0][0] + sizeof(body) / sizeof(body[0][0]), false);

    queue<pii> q;
    for (int i = 0; i < c; i++)
        if (board[r - 1][i] == 'x')
            q.push({r - 1, i});

    // 1. get body
    while (q.size())
    {
        auto [y, x] = q.front();
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            auto [ny, nx] = pii{y + dy[i], x + dx[i]};
            if (!(0 <= ny && ny < r) || !(0 <= nx && nx < c)) // OOB
                continue;
            if (body[ny][nx] || board[ny][nx] == '.')
                continue;

            q.push({ny, nx}), body[ny][nx] = true;
        }
    }

    // 2. check h
    vector<int> ys(c, INF); // 곻중에 뜬 클러스터의 시작 부분 (ys[x] = h일 경우, x에서 공중에 뜬 클러스터의 지상에서 가장 가까운 위치는 h)
    int h = INF;
    for (int x = 0; x < c; x++)
    {
        int y = r - 1;
        while (y >= 0 && (body[y][x] || board[y][x] == '.'))
            y--;

        if (y == -1) // 공중에 뜬 클러스터가 없음
            continue;

        int cnt = 0;
        while (board[y + 1 + cnt][x] == '.')
            cnt++;

        h = min(h, cnt);
        ys[x] = y;
    }

    // 3. push
    for (int x = 0; x < c; x++)
        for (int y = ys[x]; y != INF && !body[y][x] && y >= 0; y--) // 공중에 뜬 클러스터가 있음 && body가 아님
            board[y + h][x] = board[y][x], board[y][x] = '.';
}

int main()
{
    FAST_IO;

    cin >> r >> c;
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            cin >> board[i][j];

    int n;
    cin >> n; //던진 막대의 개수 (1 ≤ n ≤ 100)
    for (int i = 0; i < n; i++)
    {
        int h;
        cin >> h;
        if (!(i & 1)) // 0 포함 짝수 (0, 2, 4, ...)
            l_pop(r - h);
        else // 홀수 (1, 3, 5, ...)
            r_pop(r - h);

        Push();
    }

    for (int i = 0; i < r; i++, cout << endl)
        for (int j = 0; j < c; j++)
            cout << board[i][j];
}

// input:
// 2 2
// .x
// xx
// 2
// 1 1
// ans:
// ..
// .x

// input:
// 4 4
// xxxx
// xx.x
// x..x
// ...x
// 1 3
// ans:
// xxxx
// .x.x
// ...x
// x..x