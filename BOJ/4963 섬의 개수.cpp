// 4963 섬의 개수
// https://www.acmicpc.net/problem/4963
/*
    BFS (2,024KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 지도의 모든 칸을 하나 씩 확인.
     만약 확인한 구역이 섬일 경우
      - 섬의 개수(= ans)++
      - 해당 구역을 바다로 만든 후 인접(대각선 포함)한 구역을 확인. (인접한 구역이 섬일 시 반복 수행)
    etc.) 기본적인 BFS 문제인듯. 다른 점이 하나 있다면, 대각선까지 고려 한다는 것.
    - board를 초기화 안함. 이유는 w*h만큼 무조건 입력이 되며, 그 외에 입력되었던 값은 사용하지 않기 때문. (사용될 경우 OOB)
 */

#include <iostream>
#include <queue>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define endl "\n"
#define MAX 50 + 1
typedef pair<int, int> pii;

const int dx[8] = {0, 1, 1, 1, 0, -1, -1, -1}; // 12시부터 시계방향으로
const int dy[8] = {-1, -1, 0, 1, 1, 1, 0, -1};

int w, h;             // 1 ≤ w, h ≤ 50
bool board[MAX][MAX]; // 지도

void bfs(int y, int x)
{
    queue<pii> q;
    q.push({y, x});
    board[y][x] = false;
    while (!q.empty())
    {
        auto [y, x] = q.front();
        q.pop();

        for (int i = 0; i < 8; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (!(0 <= nx && nx < w) || !(0 <= ny && ny < h)) // OOB?
                continue;
            if (!board[ny][nx]) // Sea?
                continue;

            q.push({ny, nx});
            board[ny][nx] = false;
        }
    }
}

int main()
{
#ifdef CUSTOM
    cout << "[CUSTOM]" << endl;
#else // BOJ
    FAST_IO;
#endif

    while (cin >> w >> h)
    {
        if (!w && !h) // 0 0
            break;

        for (int i = 0; i < h; i++)
            for (int j = 0; j < w; j++)
                cin >> board[i][j];

        int ans = 0;
        for (int y = 0; y < h; y++)
            for (int x = 0; x < w; x++)
                if (board[y][x])
                    bfs(y, x), ans++;

        cout << ans << endl;
    }
}