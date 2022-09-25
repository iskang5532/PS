// 2022-09-19
// 1389 케빈 베이컨의 6단계 법칙
// https://www.acmicpc.net/problem/1389
/*
    sol.1) BFS (2,060KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 1번부터 n번까지 유저를 선택. 이후 나머지 유저와의 거리를 구하며, 가장 짧은 값이 나온 유저가 정답.
    - 현재 유저를 st라 하며, i번 유저까지의 거리를 dist에 저장.
    - bfs를 이용하여 유저까지의 거리를 구함.
    만약 dist[i] != 0일 경우, i번 유저에게는 이미 도달한 적이 있음.
    - dist에 저장된 1번부터 n번까지의 값을 모두 더한 후 리턴.
    - 리턴된 값 dist와 이전에 구한 mn을 비교.
    만약 dist가 더 작을 경우, st를 ans에 저장.
    etc.) 문제를 잘못 해석해서 오래걸림
 */

#include <iostream>
#include <queue>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using pii = pair<int, int>;
#define INF 0x3f3f3f3f
#define MAX 103 // max n

int n, m; // 유저의 수 n(2 ≤ n ≤ 100), 관계의 수 m(1 ≤ m ≤ 5,000)
vector<int> path[MAX];

int bfs(int st)
{
    int dist[MAX]{};
    fill(dist, dist + MAX, INF), dist[st] = 0;
    queue<pii> q;
    q.push({st, 0});

    while (q.size())
    {
        auto [cur, l] = q.front();
        q.pop();
        for (auto &next : path[cur])
            if (l + 1 < dist[next]) // 거리 갱신이 가능한 경우 (= 첫 방문)
            {
                dist[next] = l + 1;
                q.push({next, dist[next]});
            }
    }

    int ret = 0;
    for (int i = 1; i <= n; i++) // st에서 i까지의 거리를 모두 더함
        ret += dist[i];
    return ret;
}

int main()
{
    FAST_IO;

    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        path[a].push_back(b), path[b].push_back(a);
    }

    int ans = -1;
    int mn = INF; // 구한 케빈 베이컨의 최솟값을 저장
    for (int i = 1; i <= n; i++)
    {
        int dist = bfs(i);
        if (dist < mn)
            mn = dist, ans = i;
    }

    cout << ans;
}

/*
    sol.2) 플로이드 워셜 (2,028KB, 0ms)
    시간 복잡도: O(n^3)
    풀이)
    - 각 유저간 연걸 상태를 dist[][]에 저장.
    - 플로이드 워셜을 이용하여 i to j보다 i to mid, mid to j가 더 짧은 경우를 구함.
    - 2중 for문을 이용하여 플로이드 워셜이 구한 거리의 합을 l에 저장.
    만약 l이 이전에 구한 거리 mn보다 작을 경우, i를 ans에 저장.
    etc.) 플로이드 워셜은 항상 헷갈림.
    - 플로이드 워셜 함수 안에 있는 if문을 문제마다 어떻게 작성하느냐가 핵심인듯
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using pii = pair<int, int>;
#define INF 0x3f3f3f3f
#define MAX 103 // max n

int n, m;           // 유저의 수 n(2 ≤ n ≤ 100), 관계의 수 m(1 ≤ m ≤ 5,000)
int dist[MAX][MAX]; // dist[i][j] = k일 경우, i와 j는 k단계만에 이어질 수 있음

void Floyd_Warshall()
{
    for (int mid = 1; mid <= n; mid++)
        for (int st = 1; st <= n; st++)
            for (int ed = 1; ed <= n; ed++)
            {
                if (st == ed)
                    continue;
                if (dist[st][mid] + dist[mid][ed] < dist[st][ed]) // mid를 거치는 것이 더 빠른 경우
                    dist[st][ed] = dist[ed][st] = dist[st][mid] + dist[mid][ed];
            }
}

int main()
{
    FAST_IO;

    fill(&dist[0][0], &dist[0][0] + MAX * MAX, INF);

    cin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        int a, b;
        cin >> a >> b;
        dist[a][b] = dist[b][a] = true;
        dist[i][i] = 0; // 초기화
    }

    Floyd_Warshall();

    int ans = -1;
    int mn = INF; // 구한 케빈 베이컨의 최솟값을 저장
    for (int i = 1; i <= n; i++)
    {
        int l = 0;
        for (int j = 1; j <= n; j++)
            l += dist[i][j];

        if (l < mn)
            mn = l, ans = i;
    }

    cout << ans;
}
