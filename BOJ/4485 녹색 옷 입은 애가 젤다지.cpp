/* 
 * 4485 녹색 옷 입은 애가 젤다지?
 * 다익스트라
 * 시간 복잡도: ?
 * 문제: https://www.acmicpc.net/problem/4485
 * etc.) 여러 다익스트라 문제들과 비슷
 */

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define endl "\n"

const int dim_col[] = {-1, 0, 1, 0};
const int dim_row[] = {0, 1, 0, -1};

struct P // 각 지점의 위치 및 비용 저장
{
    int col, row, cost;
};

struct _greater
{
    bool operator()(const P p1, const P p2)
    {
        return p1.cost > p2.cost; // 비용 오름차순 (낮은 순서대로 탐색)
    }
};

int dijkstra(const vector<vector<int>> &arr, const int &n)
{
    // 정의: visited[col][row]일 때 (col, row)까지 이동시의 최소 비용
    vector<vector<bool>> visited(n, vector<bool>(n, false)); // 추가로 방문 여부)
    visited[0][0] = arr[0][0];                               // 첫 번째 위치의 비용은 자기 자신

    priority_queue<P, vector<P>, _greater> pq; // 탐색할 위치를 저장 (비용이 낮은 순서대로 탐색)
    const P start = {0, 0, arr[0][0]};         // 시작 지점
    pq.push(start);

    while (!pq.empty())
    {
        int curr_col = pq.top().col; // 현재 위치
        int curr_row = pq.top().row;
        int curr_cost = pq.top().cost;
        pq.pop();

        for (int i = 0; i < 4; i++)
        {
            int next_col = curr_col + dim_col[i]; // 다음 위치
            int next_row = curr_row + dim_row[i];

            if (!(0 <= next_col && next_col < n) || !(0 <= next_row && next_row < n)) // 범위를 벗어난 경우
                continue;
            if (visited[next_col][next_row] == true) // 방문했을 경우
                continue;

            int next_cost = curr_cost + (arr[next_col][next_row]); // 다음 위치의 값

            // 만약 다음 위치가 최종 위치인 경우, 다음 거리까지의 비용 반환
            // 가능한 이유는, 목적지에 가장 먼저 도착한 값은 최소 비용(pq덕분)이며, 벗어난 범위는 위에서 걸러내졌기 때문
            if (next_col == n - 1 && next_row == n - 1)
                return next_cost;

            visited[next_col][next_row] = true;       // 방문 시킴
            pq.push({next_col, next_row, next_cost}); // 다음 위치에 대한 정보를 넣음
        }
    }

    return 0;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    int n, cnt = 0;  // 배열의 크기, 예제를 입력한 횟수
    while (cin >> n) // 2 <= 125
    {
        if (n == 0) // 0일 경우 종료
            return 0;

        vector<vector<int>> arr(n, vector<int>(n));
        for (auto &col : arr)
            for (auto &row : col)
                cin >> row; // 0 <= 9

        cout << "Problem " << ++cnt << ": " << dijkstra(arr, n) << endl;
    }
}