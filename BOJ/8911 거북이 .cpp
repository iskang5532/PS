// 2023-03-16
// 8911 거북이
// https://www.acmicpc.net/problem/8911
/*
    구현 (2,024KB, 36ms)
    시간 복잡도: ?
    풀이)
    - 이동한 위치 중 y와 x가 가장 작은 좌표와 가장 큰 좌표를 구하여 y1과 x1, y2과 x2에 각각 저장한다.
    이후, y의 차이와 x의 차이를 서로 곱하여 출력한다.
    - 주의할 점은, 시작 지점 또한 거북이가 방문한 장소로 표시해야 한다.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"
#define INF 0x3f3f3f3f
#define MAX 2503 // max board size

constexpr int dy[] = {-1, 0, 1, 0}; // 북 서 남 동
constexpr int dx[] = {0, 1, 0, -1};

int main()
{
    FAST_IO;

    int tc;
    cin >> tc;

    constexpr int st_y = 501, st_x = 501; // st point
    while (tc--)
    {
        string cmd;
        cin >> cmd;

        int y1 = st_y, y2 = st_y, x1 = st_x, x2 = st_x;

        int y = st_y, x = st_x, dir = 0; // cur
        for (const char &c : cmd)
        {
            if (c == 'F') // front
                y += dy[dir], x += dx[dir];
            else if (c == 'L') // left
                dir = (dir + 3) % 4;
            else if (c == 'R') // right
                dir = (dir + 1) % 4;
            else if (c == 'B') // back
                y += dy[(dir + 2) % 4], x += dx[(dir + 2) % 4];

            y1 = min(y1, y), y2 = max(y2, y), x1 = min(x1, x), x2 = max(x2, x);
        }

        cout << (y2 - y1) * (x2 - x1) << endl;
    }
}