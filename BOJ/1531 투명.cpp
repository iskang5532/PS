// 1531 투명
// https://www.acmicpc.net/problem/1531
/*
    sol.1) 구현 (2,060KB, 0ms)
    시간 복잡도: ? (60,000?)
    풀이)
    - 입력된 두 좌표를 시작점과 끝점으로 설정한 후, 2중 for문을 이용해 그 안의 값들을 +1 해줌.
    - 모든 칸을 확인하며, m보다 큰 칸의 개수를 구한 후 출력.
    etc.) 크기가 10,000 x 10,000인줄 알고서 헤맨 문제
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 103

int board[MAX][MAX];

int main()
{
    FAST_IO;

    int n, m; // 종이의 개수 n, 최소 개수 m (0 ≤ n, m ≤ 50)
    cin >> n >> m;

    for (int i = 0; i < n; i++) 
    {
        int x1, y1, x2, y2; // 1 ≤ k ≤ 100
        cin >> x1 >> y1 >> x2 >> y2;
        for (int x = x1; x <= x2; x++)
            for (int y = y1; y <= y2; y++)
                board[x][y]++;
    }

    int ans = 0;
    for (int i = 0; i < MAX; i++) 
        for (int j = 0; j < MAX; j++)
            if (board[i][j] > m)
                ans++;

    cout << ans;
}

/*
    sol.2) 누적합 (2,060KB, 0ms)
    시간 복잡도: ? (30,000?)
    풀이)
    - 입력되는 좌표에 +1을, 나머지 모서리는 -1을 해줌. (정확히는 (x2+1, y2+1))
    - 우측(혹은 아래로)으로 이동하며 값을 모두 더한 후, 아래쪽(혹은 우측)으로 이동하며 값을 모두 더함.
    이후 모든 위치를 확인하며 m보다 큰 값이 몇 개 있는지 확인.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 103

int pSum[MAX][MAX];

int main()
{
    FAST_IO;

    int n, m; // 종이의 개수 n, 최소 개수 m (0 ≤ n, m ≤ 50)
    cin >> n >> m;

    for (int i = 0; i < n; i++)
    {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        pSum[x1][y1]++, pSum[x2 + 1][y2 + 1]++;
        pSum[x1][y2 + 1]--, pSum[x2 + 1][y1]--;
    }

    for (int x = 1; x < MAX; x++)
        for (int y = 1; y < MAX; y++)
            pSum[x][y] += pSum[x - 1][y];
    for (int y = 1; y < MAX; y++)
        for (int x = 0; x < MAX; x++)
            pSum[x][y] += pSum[x][y - 1];

    int ans = 0;
    for (int i = 1; i < MAX; i++)
        for (int j = 1; j < MAX; j++)
            if (pSum[i][j] > m)
                ans++;

    cout << ans;
}