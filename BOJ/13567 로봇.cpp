// 2022-04-25
// 13567 로봇
// https://www.acmicpc.net/problem/13567
/*
    구현 (2,024KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 입력된 명령어에 맞춰 수행해주면 되는 문제.
    - 방향 전환 후 이동 시 범위를 벗어날 경우 -1 출력.
    그 외의 경우, 모든 명령을 소화한 후의 위치를 출력.
    - 주의할 점
     - (m m)까지 존재.
     - 좌측 상단부터 (0, 0)이 아님. (이 풀이는 좌측 상단을 (0, 0)으로 봄. 그러므로 방향 전환을 0은 시계 방향, 1은 반시계 방향으로 구현)
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using pii = pair<int, int>;

constexpr int dy[] = {-1, 0, 1, 0}; // 북 동 남 서
constexpr int dx[] = {0, 1, 0, -1};

int main()
{
    FAST_IO;

    int m, n; // 크기 m, 명령의 수 n (1 ≤ m, n ≤ 1,000)
    cin >> m >> n;

    int y = 0, x = 0, dir = 1;
    while (n--)
    {
        string cmd;
        int k;
        cin >> cmd >> k;

        if (cmd == "MOVE")
        {
            int ny = y + dy[dir] * k,
                nx = x + dx[dir] * k;

            if (!(0 <= ny && ny <= m) || !(0 <= nx && nx <= m)) // OOB
            {
                cout << -1;
                return 0;
            }

            y = ny, x = nx;
        }
        else if (cmd == "TURN")
            if (k == 0)
                dir = (dir + 1) % 4;
            else if (k == 1)
                dir = (dir + 3) % 4;
    }

    cout << x << ' ' << y;
}