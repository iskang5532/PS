// 2023-02-11
// 27445 Gorani Command
// https://www.acmicpc.net/problem/27445
/*
    구현, 완전 탐색 (2,020KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 기준점에서부터 모든 (r, c)의 거리가 입력된 거리 dist와 같은지 확인하여 valid[][]에 저장.
    만약 다를 경우, 해당 위치는 고라니가 존재할 수 없음.
    - 고라니가 존재할 수 있는 장소는 유일하므로, valid[r][c]가 true일 때의 r과 c를 출력.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 53 // max n, m

int get_dist(int y1, int x1, int y2, int x2) {return abs(y1 - y2) + abs(x1 - x2); }

int main()
{
    FAST_IO;

    int n, m;
    cin >> n >> m;

    bool valid[MAX][MAX]; // 해당 위치에 고라니가 존재할 수 있는지를 저장
    fill(&valid[0][0], &valid[0][0] + MAX * MAX, true);
    for (int i = 1; i <= n - 1; i++)
    {
        int dist;
        cin >> dist;
        for (int y = 1; y <= n; y++)
            for (int x = 1; x <= m; x++)
                if (dist != get_dist(i, 1, y, x))
                    valid[y][x] = false;
    }
    for (int i = 1; i <= m; i++)
    {
        int dist;
        cin >> dist;
        for (int y = 1; y <= n; y++)
            for (int x = 1; x <= m; x++)
                if (dist != get_dist(n, i, y, x))
                    valid[y][x] = false;
    }

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (valid[i][j]) // 고라니가 존재 가능한 위치인 경우
            {
                cout << i << ' ' << j;
                return 0;
            }
}