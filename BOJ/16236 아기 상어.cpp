/* 
 * 16236 아기 상어
 * BFS
 * 시간 복잡도: ?
 * 문제: https://www.acmicpc.net/problem/16236
 * 참고: https://www.acmicpc.net/board/view/73362 (반례)
 */

// sol.1) 164ms
// 1. 상어가 먹을 수 있는 물고기까지의 거리를 모든 공간에 대해 조사
// 2. 확인 할 때마다 거리를 비교하며, 더 짧은 거리가 나올 경우 위치 및 거리 저장
// 3. 상어를 옮기며 물고기를 먹음.
// 4. 이후 물고기를 먹을 수 없는 경우가 나올 때까지 반복하며, 그 경우 상어가 움직인 거리를 출력하며 종료.
#include <iostream>
#include <queue>

using namespace std;

#define endl "\n"
#define MAX 20 // 공간의 최대 크기
#define INF 987654321
typedef pair<int, int> pii;

int n;              // 공간의 크기 (2 <= 20)
int lv = 2, st = 0; // 상어의 크기 및 먹은 횟수
const int dim_col[4] = {-1, 0, 1, 0}; // 위, 오른, 아래, 왼
const int dim_row[4] = {0, 1, 0, -1};

struct P
{
    int col, row;
    int dist;

    friend bool operator==(const P &p1, const P &p2)
    {
        if (p1.col == p2.col && p1.row == p2.row && p1.dist == p2.dist)
            return true;
        return false;
    }
};

int bfs(vector<vector<int>> &arr, const P shk, const int y, const int x) // 목적지까지의 거리를 구함
{
    queue<P> q;
    q.push(shk);
    int dist[MAX][MAX] = {0};

    while (!q.empty())
    {
        int col = q.front().col;
        int row = q.front().row;
        q.pop();

        if (col == y && row == x) // 목적지까지의 거리를 확보한 경우
            return dist[y][x];

        for (int i = 0; i < 4; i++)
        {
            int next_col = col + dim_col[i];
            int next_row = row + dim_row[i];

            if (!(0 <= next_col && next_col < n) || !(0 <= next_row && next_row < n)) // 공간 범위
                continue;
            if (dist[next_col][next_row] != 0) // 방문한 적이 있는가
                continue;
            if (arr[next_col][next_row] > lv)  // 크기가 큰 경우
                continue;

            q.push(P{next_col, next_row});
            dist[next_col][next_row] = dist[col][row] + 1;
        }
    }
    return INF;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    cin >> n;

    vector<vector<int>> arr(n, vector<int>(n, 0));
    P shk; // 상어의 위치
    for (int col = 0; col < n; col++)
        for (int row = 0; row < n; row++)
        {
            cin >> arr[col][row];
            if (arr[col][row] == 9) // 상어의 위치
                shk = P{col, row, 0}, arr[col][row] = 0;
        }

    while (true) // 먹을 수 있는 물고기가 없을 때까지 반복
    {
        P next_pos = shk;
        int dist = INF;
        for (int col = 0; col < n; col++)
            for (int row = 0; row < n; row++)
            {
                if (!(0 < arr[col][row] && arr[col][row] < lv)) // 먹지 못하는 장소일 경우
                    continue;
                int dist_tmp = bfs(arr, shk, col, row); // 가장 가까운 물고기 찾기
                if (dist_tmp < dist) // (col, row) 물고기까지의 거리가 더 짧은 경우, 갱신
                    next_pos = P{col, row, shk.dist + dist_tmp}, dist = dist_tmp;
            }

        if (next_pos == shk) // 다음 위치가 제자리인 경우 (= 먹을 수 있는 물고기가 없음)
            break;

        arr[next_pos.col][next_pos.row] = 0, st++; // 먹은 후 공간을 비우며, 먹은 횟수 +1
        if (st == lv) // 만약 크기를 키울 수 있을 만큼 먹은 경우
            lv++, st = 0;

        shk = next_pos; // 상어를 다음 위치로 옮김
    }

    cout << shk.dist; // 상어가 움직인 거리
}


// sol.2) 0ms
// 1. 모든 공간에 대해 상어의 이동 거리를 구한다. (접근 불가일 경우 INF)
// 2. 최단거리의 위치를 구한 후, 저장 (= 상어의 다음 위치)
// 3. 상어를 옮기며 물고기를 먹음.
// 4. 이후 물고기를 먹을 수 없는 경우가 나올 때까지 반복하며, 그 경우 상어가 움직인 거리를 출력하며 종료.
#include <iostream>
#include <queue>

using namespace std;

#define endl "\n"
#define MAX 20 // 공간의 최대 크기
#define INF 987654321
#define _col first
#define _row second
typedef pair<int, int> pii;

int n;      // 공간의 크기 (2 <= 20)
int lv = 2; // 상어의 크기
const int dim_col[4] = {-1, 0, 1, 0}; // 위, 오른, 아래, 왼
const int dim_row[4] = {0, 1, 0, -1};

vector<vector<int>> bfs(const vector<vector<int>> &arr, const pii shk) // 공간으로 가는 거리 모두 구하기
{
    queue<pii> q;
    q.push(shk);
    vector<vector<int>> dist(n, vector<int>(n, INF));
    dist[shk._col][shk._row] = 0;

    while (!q.empty()) // 각 공간까지의 거리를 모두 구함
    {
        const auto [col, row] = q.front();
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            int next_col = col + dim_col[i];
            int next_row = row + dim_row[i];

            if (!(0 <= next_col && next_col < n) || !(0 <= next_row && next_row < n)) // 공간 범위
                continue;
            if (dist[next_col][next_row] != INF) // 방문한 적이 있는가
                continue;
            if (arr[next_col][next_row] > lv) // 크기가 큰 경우
                continue;

            q.push(pii{next_col, next_row});
            dist[next_col][next_row] = dist[col][row] + 1;
        }
    }
    return dist;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    cin >> n;

    vector<vector<int>> arr(n, vector<int>(n, 0));
    pii shk; // 상어의 위치
    for (int col = 0; col < n; col++)
        for (int row = 0; row < n; row++)
        {
            cin >> arr[col][row];
            if (arr[col][row] == 9) // 상어의 위치
                shk = pii{col, row}, arr[col][row] = 0;
        }

    int st = 0, ans = 0; // 물고기를 먹은 횟수 및 이동 거리
    while (true) // 먹을 수 있는 물고기가 없을 때까지 반복
    {
        auto dist = bfs(arr, shk); // 가장 가까운 물고기 찾기
        pii next_pos = shk; // 물고기의 다음 위치
        int mn = INF;
        for (int col = 0; col < n; col++)
            for (int row = 0; row < n; row++)
                if (dist[col][row] < mn && 0 < arr[col][row] && arr[col][row] < lv) // 거리가 짧으면서 먹을 수 있는 물고기일 경우
                    mn = dist[col][row], next_pos = pii{col, row};

        if (mn == INF) // 최단 거리가 없는 경우 (= 먹을 수 있는 물고기가 없음)
            break;
        ans += mn; // 거리 갱신
        arr[next_pos._col][next_pos._row] = 0, st++; // 먹은 후 공간을 비우며, 먹은 횟수 +1
        if (st == lv) // 만약 크기를 키울 수 있을 만큼 먹은 경우
            lv++, st = 0;

        shk = next_pos; // 상어를 다음 위치로 옮김
    }

    cout << ans; // 상어가 움직인 거리
}