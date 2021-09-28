/* 
 * 16927 배열 돌리기 2
 * 구현
 * 시간 복잡도: ?
 * 문제: https://www.acmicpc.net/problem/16927
 * etc.) 값을 어떻게 옮겨야 하는가, 최소한의 회전을 어떻게 구하는가에 대해 고민을 많이 했음.
 * - 값은 행과 열이 동일한 위치는 옮기기 쉽다는 것을 이용해 네 구역으로 나눈 후 옆 값을 현재 위치로 옮기는 식으로 해결.
 * - 회전은 필요한 회전의 수만큼 일일이 다 돌렸으며, 필요한 회전의 수는 현재 외곽의 칸의 개수.
 * 참고: 
 */

#include <iostream>
#include <vector>

using namespace std;

#define endl "\n"

int n, m, r; // 배열의 크기 (2 <= n, m <= 300), 회전의 수 (1 <= r <= 10^9)

void rotated(vector<vector<int>> &arr)
{
    int x = 0, y = 0; // 시작 지점

    // (0,0)과 (n-1, m-1)을 기준으로 각각 한 칸씩 안쪽으로 들어오며 외곽을 필요 r만큼 돌림.
    // 이후, 기준점들이 서로 맞물릴 경우 종료 (= 모든 외곽을 사용)
    while (y < n - 1 && x < m - 1)
    {
        int r_mx = ((n - y) * 2) + (((m - x) - 2) * 2); // 현재 외곽의 개수 (= r_mx만큼 돌리면 원점)
        int r_temp = r % r_mx;                          // 반복되는 값을 제외한 최소한의 회전 수

        while (r_temp--) // i번째 외곽을 r_temp번 회전
        {
            // 시작점에서부터 반시계 방향으로 돌며 현재 값에 다음 값을 넣어줌 (이때 첫 번째 시작점인 (0,0)의 값은 사라질 수 있기 때문에 변수에 저장)
            // 1 1 1 1 2
            // 4       2
            // 4       2
            // 4 3 3 3 3
            int temp = arr[y][x]; // 값을 옮길 시 첫 번째 값이 사라지며, 그 값을 이후에 넣어주기 위해 저장

            for (int row = x; row < m - 1; row++) // 위 주석에서 1번 라인
                arr[y][row] = arr[y][row + 1];
            for (int col = y; col < n - 1; col++) // 위 주석에서 2번 라인
                arr[col][m - 1] = arr[col + 1][m - 1];
            for (int row = m - 1; row > x; row--) // 위 주석에서 3번 라인
                arr[n - 1][row] = arr[n - 1][row - 1];
            for (int col = n - 1; col > y; col--) // 위 주석에서 4번 라인
                arr[col][x] = arr[col - 1][x];

            arr[y + 1][x] = temp; // 마지막 값을 넣어 줌 (위 주석에서 위치 (1, 0))
        }

        x++, y++; // 기준점을 좁힘
        n--, m--;
    }
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    cin >> n >> m >> r;

    vector<vector<int>> arr(n, vector<int>(m)); // 1 <= Aij <= 10^8
    for (auto &col : arr)
        for (auto &row : col)
            cin >> row;

    rotated(arr);

    for (const auto &col : arr) // print arr
    {
        for (const auto &row : col)
            cout << row << " ";
        cout << endl;
    }
}
