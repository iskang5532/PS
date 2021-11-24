/*
    16929 Two Dots
    DFS (2,032KB, 0ms)
    시간 복잡도: ?
    문제: https://www.acmicpc.net/problem/16929
    풀이)
    - 모든 위치에 대해 DFS를 돌려 같은 색상으로 이루어진 사이클을 확인.
    - 현재 위치에서부터 다음 위치까지의 거리를 visited에 저장하며,  다음 위치로 이동할 때 사용.
    visited[y][x] - visited[ny][nx]의 값을 이용하여 사이클 형성을 위한 재방문 이외의 재방문을 하지 않도록 함.
    - 다음 위치로 이동하던 도중 이전 위치에 재방문하게 된 경우, Yes 출력.
    etc.)
    - 출력을 실수해서 헤맨 문제.. 질문 검색을 보니 이런 일을 겪은 사람이 많았다는게 좀 웃겼음.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define endl "\n"
#define MAX 50 + 1

const int dx[4] = {0, 1, 0, -1};
const int dy[4] = {-1, 0, 1, 0};
int n, m; // y, x (2 ≤ N, M ≤ 50)
char arr[MAX][MAX];
int visited[MAX][MAX]; // 방문 기록 및 시작점부터의 거리

void dfs(int y, int x, int k = 1)
{
    if (!visited[y][x])
    {
        visited[y][x] = k;

        for (int i = 0; i < 4; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (!(0 <= ny && ny < n) || !(0 <= nx && nx < m)) // OOB?
                continue;
            if (arr[ny][nx] != arr[y][x]) // 색이 다른 경우
                continue;
            if (!visited[ny][nx] || visited[y][x] - visited[ny][nx] + 1 >= 4) // 방문한 적이 없으며 길이가 4 이상이 되는 경우
                dfs(ny, nx, k + 1);
        }
    }
    else if (visited[y][x]) // 방문한 적이 있는가? (= 사이클 형성. 추가로, 위 if문에서 길이가 4 이상이어야만 다음 위치로 이동할 수 있으므로 조건 또한 만족시킴)
    {
        cout << "Yes" << endl;
        exit(0);
    }
}

int main()
{
#ifdef CUSTOM
    cout << "[CUSTOM]" << endl;
#else // BOJ
    FAST_IO;
#endif

    cin >> n >> m;

    for (int y = 0; y < n; y++)
        for (int x = 0; x < m; x++)
            cin >> arr[y][x];

    for (int y = 0; y < n; y++)
        fill(visited[y], visited[y] + MAX, false);

    for (int y = 0; y < n; y++)
        for (int x = 0; x < m; x++)
            if (!visited[y][x])
                dfs(y, x);

    cout << "No" << endl;
}

// sol.2) DFS (이전 지점을 저장하는 방식)
// 현재 위치 이전의 위치로 가는 것을 막는 변수 py, px를 두어 이전 위치로 돌아가지 못하도록 함.
// 덕분에 사이클이 형성 시 크기는 4 이상이 되므로 크기에 대한 예외 처리 등을 안 해도 됨.
// 참고)
// - 이론: https://blog.naver.com/jinhan814/222114813546
#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define endl "\n"
#define MAX 50 + 1

const int dx[4] = {0, 1, 0, -1};
const int dy[4] = {-1, 0, 1, 0};
int n, m; // y, x (2 ≤ N, M ≤ 50)
char arr[MAX][MAX];
int visited[MAX][MAX]; // 방문 기록 및 시작점부터의 거리

void dfs(int y, int x, int py = -1, int px = -1, int k = 1)
{
    if (!visited[y][x])
    {
        visited[y][x] = k;

        for (int i = 0; i < 4; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (!(0 <= ny && ny < n) || !(0 <= nx && nx < m)) // OOB?
                continue;
            if (arr[ny][nx] != arr[y][x]) // 색이 다른 경우
                continue;
            if (ny == py && nx == px) // 이전 위치인가?
                continue;
            dfs(ny, nx, y, x, k + 1);
        }
    }
    else if (visited[y][x]) // 방문한 적이 있는가? (= 사이클 형성. 추가로, 위 if문에서 길이가 4 이상이어야만 다음 위치로 이동할 수 있으므로 조건 또한 만족시킴)
    {
        cout << "Yes" << endl;
        exit(0);
    }
}

int main()
{
#ifdef CUSTOM
    cout << "[CUSTOM]" << endl;
#else // BOJ
    FAST_IO;
#endif

    cin >> n >> m;

    for (int y = 0; y < n; y++)
        for (int x = 0; x < m; x++)
            cin >> arr[y][x];

    for (int y = 0; y < n; y++)
        fill(visited[y], visited[y] + MAX, false);

    for (int y = 0; y < n; y++)
        for (int x = 0; x < m; x++)
            if (!visited[y][x])
                dfs(y, x);

    cout << "No" << endl;
}