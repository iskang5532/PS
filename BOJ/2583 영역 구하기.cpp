/*
    2583 영역 구하기
    BFS (2,036KB, 0ms)
    시간 복잡도: ?
    문제: https://www.acmicpc.net/problem/2583
    풀이)
    - 이 풀이의 주의점: 왼쪽 아래가 원점이 아닌, 왼쪽 위가 원점. (= 입력된 그림을 한번 뒤집었음.)
    - 직사각형 및 방문 기록을 저장할 visited[][]. (visited[][] = true일 경우, 직사각형이 있거나 방문한 적이 있음.)
    1) 입력된 두 좌표를 이용해 직사각형의 크기만큼 visited에 저장해줌.
    2) (0,0)에서부터 (n,m)까지 한 칸씩 확인. (영역의 개수를 저장할 ans와 해당 영역의 크기를 저장할 cnt, 영역의 크기를 저장할 width)
    만약 (x,y)의 visited가 0일 경우, ans++해주며 인접한 칸을 탐색.
     만약 인접한 칸의 visited가 0일 경우, 마찬가지로 인접한 칸을 탐색해주며 cnt++.
     만약 인접한 칸의 visited가 1일 경우, 해당 위치의 탐색을 종료.
    (x,y)에서부터의 탐색이 끝마쳤을 경우, cnt값을 width에 저장시켜주며 다음 위치(x+i, y+j)를 탐색함.
    3) 탐색을 모두 마쳤을 시, ans를 출력해주며 width 또한 정렬 후 출력.
    etc.) 지문을 잘 읽어야 하는 문제.
    - 정답을 맞추고 나서 원점의 위치가 왼쪽 아래란 걸 알았다. AC 처리돼서 다행.
 */

#include <iostream>
#include <queue>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define endl "\n"
#define MAX 100 + 1

const int dx[4] = {0, 1, 0, -1}; // 상, 좌, 하, 우
const int dy[4] = {-1, 0, 1, 0};

struct pii
{
    int y, x;
};

int m, n, k;            // 1 ≤ 100
bool visited[MAX][MAX]; // 직사각형  및 방문 기록

int get_width(int row, int col)
{
    int cnt = 1; // 현재 영역의 크기
    queue<pii> q;

    q.push({row, col});
    visited[row][col] = true;
    while (!q.empty())
    {
        auto [y, x] = q.front();
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (!(0 <= nx && nx < n) || !(0 <= ny && ny < m)) // OOB
                continue;
            if (visited[ny][nx])
                continue;

            q.push({ny, nx});
            visited[ny][nx] = true;
            cnt++;
        }
    }

    return cnt;
}

int main()
{
#ifdef CUSTOM
    cout << "[CUSTOM]" << endl;
#else // BOJ
    FAST_IO;
#endif

    cin >> m >> n >> k;
    for (int i = 0; i < k; i++)
    {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;

        for (int y = y1; y < y2; y++)
            for (int x = x1; x < x2; x++)
                visited[y][x] = true;
    }

    int ans = 0;
    vector<int> width; // 각 영역의 크기를 저장
    for (int row = 0; row < m; row++)
        for (int col = 0; col < n; col++)
            if (visited[row][col])
                continue;
            else
                ans++, width.push_back(get_width(row, col));

    sort(width.begin(), width.end()); // ASC
    cout << ans << endl;
    for (const auto &elem : width)
        cout << elem << " ";
}