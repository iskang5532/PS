// 2023-01-12
// 27115 통신소
// https://www.acmicpc.net/problem/27115
/*
    BFS (67,704KB, 824ms)
    시간 복잡도: ?
    풀이)
    - bfs를 이용하여 전파가 닿는 구역을 구함.
    이때, 전파 세기가 강한 값이 우선적으로 탐색이 되어야 중복 탐색을 막을 수 있음.
    - 해당 위치에 도달한 전파의 남은 거리를 저장할 visited.
    - 입력된 통신소의 정보를 v에 저장한 후 세기 p를 기준으로 내림차순 정렬.
    - v에서 전파가 가장 센 값인 v[0]을 큐에 넣어 bfs 수행.
    이후, 나머지 값은 큐에 저장된 값과 비교하며 사용하거나 넘김. (v의 인덱스를 저장할 pos)
    큐에서 전파가 가장 센 값인 f.front()의 p와 v[pos].p를 비교.
    만약 두 전파가 같을 경우, 큐에 넣을지 판단.
    bfs를 이용하여 v[pos]의 위치에 도달한 적이 없을 경우 큐에 넣으며, 있을 경우 v[pos]의 p가 더 약하므로 넣지 않음.
    - 큐에 저장된 위치와 p를 이용하여 다음 위치를 구함.
    다음 위치의 visited와 p를 비교하며, 갱신이 가능한 경우 큐에 넣음.
    etc.)
    - 핵심은 v에 저장된 값을 큐에 한꺼번에 넣는게 아닌, 큐에 저장된 값을 봐가며 값을 넣어 항상 최대 p가 선택될 수 있게끔 해주는 것.
    이는 priority_queue와 같은 효과인듯 하며, 속도는 더 빠름. (= pq 사용시 TLE)
    참고)
    - 풀이: https://upload.acmicpc.net/4f56c116-3464-467c-8a59-f4aab43da360/
 */

#include <iostream>
#include <queue>
#include <algorithm> // sort

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using pii = pair<int, int>;
#define MAX 3'003 // max n, m

constexpr int dy[] = {-1, 0, 1, 0}; // 북 서 남 동
constexpr int dx[] = {0, 1, 0, -1};

struct P
{
    int y, x, p; // 전파 세기 p

    friend bool operator<(const P &p1, const P &p2) { return p1.p > p2.p; } // 전파 세기 p를 기준으로 내림차순 정렬
};

int n, m, k;             // 세로 및 가로 크기 n, m(1 ≤ n, m ≤ 3,000), 통신소의 개수 k(1 ≤ k ≤ 300,000)
int visited[MAX][MAX]{}; // visited[y][x] = k일 경우, (y, x)에서 전달할 수 있는 최대 거리는 k (2일 경우 전파가 전달된 곳이면서 2만큼 전달 가능하며, -1일 경우 전파가 전달되지 않은 곳)

bool OOB(int ny, int nx) { return !(1 <= ny && ny <= n) || !(1 <= nx && nx <= m); }

void bfs(const vector<P> &v)
{
    fill(&visited[0][0], &visited[0][0] + MAX * MAX, -1);

    queue<P> q;
    q.push(v[0]), visited[v[0].y][v[0].x] = v[0].p; // 전파가 가장 센 값

    int pos = 1; // v의 인덱스
    while (q.size())
    {
        auto [y, x, p] = q.front();
        q.pop();
        while (pos != v.size() && v[pos].p == p) // v의 전파가 q의 전파와 동일한 경우 (= 큐에 넣음)
        {
            auto [_y, _x, _p] = v[pos];
            if (visited[_y][_x] < _p) // 현재 전파가 더 강한 경우 (= 해당 위치에 존재하는 전파보다 강함)
                q.push({_y, _x, _p}), visited[_y][_x] = _p;
            pos++;
        }

        for (int d = 0; d < 4; d++)
        {
            auto [ny, nx] = pii{y + dy[d], x + dx[d]};
            if (OOB(ny, nx))
                continue;
            if (visited[ny][nx] >= p - 1) // 해당 위치에 더 강한 전파가 존재할 경우
                continue;

            visited[ny][nx] = p - 1;
            q.push({ny, nx, p - 1});
        }
    }
}

int main()
{
    FAST_IO;

    cin >> n >> m >> k;
    vector<P> v;
    for (int i = 0; i < k; i++)
    {
        int y, x, p; // 세로 및 가로 위치 y, x, 전파 세기 p
        cin >> y >> x >> p;

        v.push_back({y, x, p});
    }

    sort(v.begin(), v.end()); // p를 기준으로 내림차순 정렬

    bfs(v);

    int ans = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (visited[i][j] != -1)
                ans++;
    cout << ans;
}