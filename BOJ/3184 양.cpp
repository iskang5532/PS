// 3184 양
// https://www.acmicpc.net/problem/3184
/*
    BFS (2,088KB, 0ms)
    풀이)
    시간 복잡도: ?
    1) 현재 조사중인 칸과 인접한 칸(= 영역)을 조사한다.
    만약 조사중인 칸이 양 혹은 늑대일 경우, 그에 맞춰 값을 올림. (s++ or w++)
    만약 현재 조사중인 칸이나 인접한 칸이 울타리 혹은 이미 조사한 적이 있을 경우, 현재 칸을 조사하지 않음.
    2) 영역에 대한 조사를 끝마친 경우, 구한 양의 수 혹은 늑대의 수를 비교하여 ans에 저장.
    3) 이후 나머지 칸들도 조사하여 ans를 구한 후, 출력.
 */

#include <iostream>
#include <queue>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define endl "\n"
#define MAX 250 + 1
#define sheep first
#define wolf second
typedef pair<int, int> pii;

const int dx[4] = {0, 1, 0, -1}; // 상, 좌, 하, 우
const int dy[4] = {-1, 0, 1, 0};

char board[MAX][MAX]; // .(빈 필드), #(울타리), o(양), v(늑대)
int r, c;             // 행과 열 (3 ≤ R, C ≤ 250)

pii bfs()
{
    bool visited[MAX][MAX];
    for (int i = 0; i < MAX; i++)
        fill(visited[i], visited[i] + MAX, false);

    pii ans = {0, 0}; // 아침까지 살아있는 양과 늑대의 수
    for (int row = 0; row < r; row++)
        for (int col = 0; col < c; col++)
            if (visited[row][col] || board[row][col] == '#')
                continue;
            else
            {
                int s = 0, w = 0;
                if (board[row][col] == 'o')
                    s++;
                else if (board[row][col] == 'v')
                    w++;

                queue<pii> q;
                q.push({row, col});
                visited[row][col] = true;
                while (q.size())
                {
                    auto [y, x] = q.front();
                    q.pop();
                    for (int i = 0; i < 4; i++)
                    {
                        int ny = y + dy[i];
                        int nx = x + dx[i];

                        if (!(0 <= ny && ny < r) || !(0 <= nx && nx < c)) // OOB
                            continue;
                        if (visited[ny][nx] || board[ny][nx] == '#')
                            continue;

                        if (board[ny][nx] == 'o')
                            s++;
                        else if (board[ny][nx] == 'v')
                            w++;

                        q.push({ny, nx});
                        visited[ny][nx] = true;
                    }
                }

                s > w ? ans.sheep += s : ans.wolf += w;
            }

    return ans;
}

int main()
{
#ifdef CUSTOM
    cout << "[CUSTOM]" << endl;
#else // BOJ
    FAST_IO;
#endif

    cin >> r >> c;
    for (int row = 0; row < r; row++)
        for (int col = 0; col < c; col++)
            cin >> board[row][col];

    pii ans = bfs();
    cout << ans.sheep << " " << ans.wolf;
}