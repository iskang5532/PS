// 2023-03-06
// 14719 빗물
// https://www.acmicpc.net/problem/14719
/*
    구현 (3,008KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 물이 고이기 위해서는 해당 라인의 양 옆이 블록으로 막혀 있어야 한다.
    - 빗물이 고일 수 있는 위치인지를 저장할 valid[][].
    - 입력된 값을 이용하여 valid를 변경. (주의할 점은, 문제 속 사진과는 y축이 반전되도록 값을 저장함)
    - 양 옆인 x = 0과 x = w-1이 블록으로 막혀 있는지 확인.
    만약 현재 위치 (y, 0)가 블록으로 막혀 있지 않을 경우, 해당 열의 빗물은 옆으로 빠져 나가므로 고이지 않음.
    단, 모두 01010과 같이 블록 사이에 고일 수 있는 공간이 존재할 수 있으므로, (y, 0)에서 (y, w)까지 블록이 없을 때까지만 valid의 값을 변경한다.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 503 // max h. w

int valid[MAX][MAX]; // valid[][] = true일 경우, 해당 위치는 물이 고일 수 있음

int main()
{
    FAST_IO;

    fill(&valid[0][0], &valid[0][0] + MAX * MAX, true);

    int h, w; // 1 ≤ h, w ≤ 500
    cin >> h >> w;
    for (int i = 0; i < w; i++)
    {
        int k;
        cin >> k;

        for (int y = 0; y < k; y++)
            valid[y][i] = false;
    }

    for (int y = 0; y < h; y++) // 옆이 뚫려 있는지 확인
    {
        // 왼쪽
        if (valid[y][0]) // 뚫려 있을 경우, 해당 라인은 물이 찰 수 없음 (단, 중간에 블록이 있을 경우 예외 상황이 생길 수 있음)
            for (int x = 0; x < w; x++)
            {
                if (!valid[y][x])
                    break;
                valid[y][x] = false;
            }
        // 오른쪽
        if (valid[y][w - 1])
            for (int x = w - 1; x >= 0; --x)
            {
                if (!valid[y][x])
                    break;
                valid[y][x] = false;
            }
    }

    int ans = 0;
    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++)
            if (valid[i][j])
                ans++;
    cout << ans;
}