// 10709 기상캐스터
// https://www.acmicpc.net/problem/10709
/*
    BFS (2,192KB, 0ms)
    시간 복잡도: O(n^2)
    풀이)
    - 'c'인 칸을 큐에 넣은 후, 하나씩 꺼내어 탐색.
    - 현재 칸과 인접한 우측 칸을 탐색하며, 다음 칸의 ans에 현재 칸의 ans + 1을 넣어줌.
 */

#include <iostream>
#include <queue>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#define endl "\n"
#define MAX 100 + 1
using pii = pair<int, int>;

int h, w;
queue<pii> q;
int ans[MAX][MAX];

void bfs()
{
    while (q.size())
    {
        auto [y, x] = q.front();
        q.pop();

        if (ans[y][x + 1] != -1)
            continue;
        if (x + 1 > w) // OOB
            continue;

        ans[y][x + 1] = ans[y][x] + 1;
        q.push({y, x + 1});
    }
}

int main()
{
    FAST_IO;
    fill(&ans[0][0], &ans[0][0] + sizeof(ans) / sizeof(ans[0][0]), -1);

    cin >> h >> w;

    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++)
        {
            char c;
            cin >> c;
            if (c == 'c')
            {
                q.push({i, j});
                ans[i][j] = 0;
            }
        }

    bfs();

    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
            cout << ans[i][j] << ' ';
        cout << endl;
    }
}

/*
    구현 (2,072KB, 0ms)
    시간 복잡도: O(n^2)
    풀이)
    - 현재 탐색 중인 칸이 'c'일 경우, 범위 끝까지 탐색을 수행.
    만약 현재 탐색 중인 칸의 ans가 -1이 아닌 경우, 종료. (= 이미 탐색 완료한 칸)
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#define endl "\n"
#define MAX 100 + 1

int h, w;
char ans[MAX][MAX];
int ans[MAX][MAX];

void solution()
{
    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++)
        {
            int cnt = 0;
            if (ans[i][j] == 'c')
                for (int x = j; x < w; x++)
                    if (ans[i][x] == 'c')
                        ans[i][x] = 0, cnt = 0;
                    else if (ans[i][x] != -1)
                        break;
                    else
                        ans[i][x] = ++cnt;
        }
}

int main()
{
    FAST_IO;
    fill(&ans[0][0], &ans[0][0] + sizeof(ans) / sizeof(ans[0][0]), -1);

    cin >> h >> w;

    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++)
            cin >> ans[i][j];

    solution();

    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < w; j++)
            cout << ans[i][j] << ' ';
        cout << endl;
    }
}