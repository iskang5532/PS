/* 
 * 17069 파이브 옮기기 2
 * DP
 * 시간 복잡도: ?
 * 문제: https://www.acmicpc.net/problem/17069
 * ETC) 대각선 파이프를 둘 시 파이프 주변 영역에 벽이 있으면 안되며, 횟수를 long long 해줘야 하며, 도착 지점이 벽일 수도 있음. (깨닫는 데 오래 걸림)
 */

#include <iostream>
#include <vector>

using namespace std;

#define endl "\n"
#define MAX 32 + 1 // 한 칸을 추가하여 탐색 범위의 런타임 에러를 막아줌
#define WALL 1

long long solution(const vector<vector<int>> &arr, const int n)
{
    // vector<vector<vector<long long>>> visited(n + 1, vector<vector<long long>>(n + 1, vector<long long>(n + 1, 0)));

    // visited[n][m][k]이며 (col, row)일 때, 위치 (n, m)으로 k 형태로 이동시킬 수 있는 횟수.
    // k = 0일 때는 수평(ㅡ), k = 1일 때는 대각선(\),  k = 2일 때는 수직(|) 형태의 파이프
    long long visited[MAX][MAX][MAX] = {0};
    visited[0][1][0] = 1; // 처음 존재하는 파이프.

    // 모든 위치를 돌아다니며 현재 위치에서부터 다음 위치에 이동할 수 있는 경우의 수를 넘김
    for (int col = 0; col < n; col++)
        for (int row = 0; row < n; row++)
        {
            if (arr[col][row] == WALL) // 만약 현재 확인중인 곳이 벽일 경우 (= 이동 가능 방법의 수를 넘기면 안 됨)
                continue;

            long long cnt_0 = visited[col][row][0], // 현재 위치까지에서 k번 형태로 도착할 수 있는 경우의 수
                cnt_1 = visited[col][row][1],
                      cnt_2 = visited[col][row][2];

            visited[col][row + 1][0] += cnt_0; // ㅡ -> ㅡ

            visited[col][row + 1][0] += cnt_1; // \ -> ㅡ
            visited[col + 1][row][2] += cnt_1; // \ -> |

            visited[col + 1][row][2] += cnt_2; // | -> |

            if (arr[col][row + 1] == WALL || arr[col + 1][row + 1] == WALL || arr[col + 1][row] == WALL) // 대각선 파이프를 둬야 하는데 벽이 존재할 경우
                continue;
            visited[col + 1][row + 1][1] += cnt_0; // ㅡ -> \'
            visited[col + 1][row + 1][1] += cnt_1; // \ -> \'
            visited[col + 1][row + 1][1] += cnt_2; // | -> \'
        }

    if (arr[n - 1][n - 1] == WALL) // 만약 도착 지점이 벽인 경우 (= 이동 가능한 방법이 없음)
        return 0;
    else // 이동이 가능한 모든 형태들을 다 더해줌
        return (visited[n - 1][n - 1][0] + visited[n - 1][n - 1][1] + visited[n - 1][n - 1][2]);
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    int n;
    cin >> n;

    vector<vector<int>> arr(MAX + 1, vector<int>(MAX + 1));
    for (int col = 0; col < n; col++)
        for (int row = 0; row < n; row++)
            cin >> arr[col][row];

    cout << solution(arr, n);
}
