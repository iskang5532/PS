/*
    1445 일요일 아침의 데이트
    다익스트라 (2,184KB, 0ms)
    시간 복잡도: ?
    문제: https://www.acmicpc.net/problem/1445
    풀이)
    - 쓰레기가 있는 칸의 주변에 쓰레기가 존재할 때, 이는 쓰레기를 치울 뿐 쓰레기 주변을 지나가는 것은 아니다.
    - 현재 칸에 인접한 쓰레기가 2개 이상 있어도 쓰레기를 지나치는 횟수는 +1이다.
    - 입력된 쓰레기의 위치를 저장한 후, 각 쓰레기의 위치 및 인접한 컨에 표시함. (= cnt)
    - 우선순위 큐를 이용했으며, 정렬을 조건에 맞춰줌. (통과할 쓰레기의 양이 적어야 하며, 같을 시 옆을 지나가는 쓰레기의 개수가 적어야 함.)
    - 칸마다 정보를 저장하며, 방문하지 않았을 경우 INF값을 넣음.
    BFS 특성상 임의의 칸에 가장 먼저 도착한 정보는 조건을 만족하는 가장 좋은 정보이다. (그러므로 INF값이 아닌 칸에 재방문하게 된 경우, pq에 넣지 않음)
    - 다음 칸이 도착지점일 경우, 도착지점까지의 정보를 반환한 후 출력한다.
    etc.) 구현 난이도는 어렵지 않았지만 문제를 이해하는데에 시간이 좀 걸림.
    참고)
    - 반례: https://www.acmicpc.net/board/view/5981
 */

#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define endl "\n"
#define INF 1234567890
#define MAX 50 + 1
typedef pair<int, int> pii;

const int dx[4] = {0, 1, 0, -1}; // 상, 우, 하, 좌
const int dy[4] = {-1, 0, 1, 0};

int n, m; // 세로 n, 가로 m (3 ≤ n, m ≤ 50)
char arr[MAX][MAX];
pii s, f;           // 시작점 s, 도착점 f
pii info[MAX][MAX]; // 쓰레기가 있는 칸인지 혹은 쓰레기와 인접한 칸인지를 저장 ({1, 0}일 경우 쓰레기가 존재하며, {0, 1}일 경우 인접한 칸에 쓰레기가 존재)

struct P
{
    int y, x, a, b; // 쓰레기를 치운 개수 a, 쓰레기 옆을 지난 횟수 b
};

struct cmp // 지나친 쓰레기의 개수가 가장 적은 순으로
{
    bool operator()(const P &p1, const P &p2)
    {
        if (p1.a == p2.a)
            return p1.b > p2.b;
        return p1.a > p2.a;
    }
};

void get_info(queue<pii> &q) // 각 칸의 정보를 구함 (현재 칸에 쓰레기가 있는가 혹은 쓰레기와 인접해 있는가)
{
    while (!q.empty())
    {
        auto [y, x] = q.front();
        q.pop();

        for (int i = 0; i < 4; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (!(0 <= ny && ny < n) || !(0 <= nx && nx < m)) // OOB
                continue;
            if (arr[ny][nx] == '.')
                info[ny][nx].second = 1;
        }
    }
}

pii dijkstra()
{
    pii cnt[MAX][MAX]; // 현재 칸까지의 정보를 저장 (통과한 쓰레기의 개수 혹은 옆을 지난 쓰레기의 개수)
    for (int i = 0; i < n; i++)
        fill(cnt[i], cnt[i] + m, pii{INF, INF});

    priority_queue<P, vector<P>, cmp> pq;
    pq.push({s.first, s.second, 0, 0});
    cnt[s.first][s.second] = {0, 0};

    while (!pq.empty())
    {
        auto [y, x, a, b] = pq.top();
        pq.pop();

        for (int i = 0; i < 4; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (!(0 <= ny && ny < n) || !(0 <= nx && nx < m)) // OOB
                continue;
            if (cnt[ny][nx].first != INF) // 이미 방문 (= 조건에 적합한 가장 좋은 정보가 이미 저장됐음)
                continue;

            cnt[ny][nx] = {cnt[y][x].first + info[ny][nx].first, cnt[y][x].second + info[ny][nx].second}; // 이전 위치까지의 횟수 + 다음 위치의 정보
            pq.push({ny, nx, cnt[ny][nx].first, cnt[ny][nx].second});

            if (arr[ny][nx] == 'F')
                return cnt[f.first][f.second];
        }
    }

    return cnt[f.first][f.second];
}

int main()
{
#ifdef CUSTOM
    cout << "[CUSTOM]" << endl;
#else // BOJ
    FAST_IO;
#endif

    cin >> n >> m;

    for (int i = 0; i < n; i++)
        fill(info[i], info[i] + m, pii{0, 0});

    queue<pii> _q;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            cin >> arr[i][j];
            if (arr[i][j] == 'S') // 시작점
                s = {i, j};
            else if (arr[i][j] == 'F') // 도착점
                f = {i, j};
            else if (arr[i][j] == 'g') // 쓰레기
                info[i][j].first++, _q.push({i, j});
        }

    get_info(_q);
    auto ans = dijkstra();
    cout << ans.first << " " << ans.second;
}