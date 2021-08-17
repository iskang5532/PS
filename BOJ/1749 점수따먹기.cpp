/* 
 * 1749 점수따먹기
 * DP
 * 시간 복잡도: ?
 * 문제: https://www.acmicpc.net/problem/1749
 * ETC.) 너무 어려웠음
 * 참고: https://blog.naver.com/gkswns3708/222203698498 (엄청난 필기에 의한 설명)
 */

#include <iostream>
#include <vector>

using namespace std;

#define endl "\n"
#define INF 987654321

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> arr(n + 1, vector<int>(m + 1));
    for (int col = 1; col <= n; col++)
        for (int row = 1; row <= m; row++)
            cin >> arr[col][row]; // -10k <= 10k

    vector<vector<int>> sum(n + 1, vector<int>(m + 1, 0)); // (col, row)까지의 값을 더하여 저장
    for (int col = 1; col <= n; col++)
        for (int row = 1; row <= m; row++)
            sum[col][row] = arr[col][row] + sum[col][row - 1] + sum[col - 1][row] -
                            sum[col - 1][row - 1]; // col - 1과 row - 1은 (col - 1, row - 1)을 한 번 씩 포함하므로, 한 번 빼줌

    int mx = -INF; // 최댓값
    // 기준점: (col, row)
    // 라인: (y, row), (x, col)
    // 라인 안에 존재하는 값들(y와 x를 포함함)을 제거하여 제거되지 않은 영역(= (y+1, x+1))부터 기준점까지의 크기(= 기준점 (col,row))를 구함 (위 사이트의 그림 참고)
    // 여기서, 라인을 제거할 때 겹치는 부분인 (y, x)가 존재함. 두 번 제거되기 때문에, 한 번 더해주어 한 번만 제거된 것처럼 해줌
    for (int col = 1; col <= n; col++)
        for (int row = 1; row <= m; row++)
            for (int y = 0; y < col; y++) // 기준점까지 제거될 수 있기 때문에 col - 1까지
                for (int x = 0; x < row; x++)
                {
                    int temp = sum[col][row] - sum[y][row] - sum[col][x] + sum[y][x];
                    mx = max(mx, temp);
                }

    cout << mx << endl;
}

// ans: 21
// 2 3
// 1 2 3 4 5 6

// ans: -1
// 3 3
// -1 -1 -1 -1 -1 -1 -1 -1 -1