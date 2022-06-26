// 2022-06-25
// 1080 행렬
// https://www.acmicpc.net/problem/1080
/*
    그리디 (2,028KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 그리디하게 풀기 위해서는, 행렬을 변환하는 연산인 플립을 최소화하여야 한다.
    이는 이전에 플립한 값을 다시 플립하지 않아야 한다. 즉, 플립을 최대 한 번만 수행해야 한다.
    이를 충족하는 최적의 장소는, 현재 탐색중인 위치가 (y, x)라고 한다면 (y - 1, x - 1)이 된다.
    - 위치 (y - 1, x - 1)의 행렬 A의 값과 행렬 B의 값이 서로 다를 경우, (y, x)를 기준으로 주변을 플립한다.
    - 주의할 점은, 3x3만큼 플립해야 한다. 또한, n, m < 3이지만 입력된 두 행렬이 서로 같을 수 있음. (이 경우, 출력은 0)
    참고)
    - 60% 반례: https://www.acmicpc.net/board/view/77533
    - 추가적인 해설: https://www.acmicpc.net/board/view/13509
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using pii = pair<int, int>;
#define MAX 53 // max n, m

int n, m;
char board[MAX][MAX], done[MAX][MAX];

bool isSame()
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (board[i][j] != done[i][j])
                return false;
    return true;
}

int main()
{
    FAST_IO;

    cin >> n >> m;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> board[i][j];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> done[i][j];

    if (n < 3 || m < 3)
    {
        cout << (isSame() ? 0 : -1);
        return 0;
    }

    int ans = 0;
    for (int y = 1; y < n - 1; y++)
        for (int x = 1; x < m - 1; x++)
            if (board[y - 1][x - 1] != done[y - 1][x - 1])
            {
                for (int i = y - 1; i <= y + 1; i++)
                    for (int j = x - 1; j <= x + 1; j++)
                        board[i][j] ^= 1; // flip
                ans++;
            }

    cout << (isSame() ? ans : -1);
}