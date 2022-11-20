// 2022-11-16
// 1005 ACM Craft
// https://www.acmicpc.net/problem/1005
/*
    위상정렬 (2,848KB, 156ms)
    시간 복잡도: ?
    풀이)
    - 단순하게 BFS로 구현할 시 TLE.
    i번 정점에 도달할 수 있는 정점들이 모두 도달했을 때, 비로소 i번 정점을 큐에 넣음. (반복적인 탐색을 방지; TLE 해결)
    - 해당 정점으로 올 수 있는 정점의 개수를 저장할 in_degree.
    - 해당 정점까지의 거리를 저장할 dist[]. (시간을 거리로 표현)
    in_degree[i] == 0이 되어야 i번 정점을 탐색할 수 있다.
    그러므로, dist[i]를 구할 때 이전 정점 prev의 dist 중에서 최댓값을 이용한다. (결국 i를 건설하기 위해서는 가장 큰 값을 거쳐야 하기 때문)
    - in_degree가 0인 정점들을 큐에 넣은 후 bfs.
    etc.) ed에서부터 역으로 탐색해도 될 줄 알았으나 WA.
    - 태그는 위상정렬과 DP인데 사용한건지 잘 모르겠다.
    참고)
    - 이론 및 코드: https://blog.naver.com/jinhan814/222088685430
 */

#include <iostream>
#include <queue>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
using pii = pair<int, int>;
#define endl "\n"
#define MAX 1'003 // max n

int c[MAX]; // 건물의 건설 시간
vector<int> adj[MAX];
int in_degree[MAX]; // in_degree[i] = k일 경우, i번 건물을 건설하기 위해서는 인접한 k개의 건물이 완성되어야 함

int bfs(int n, int k, int ed)
{
    int dist[MAX]{};
    queue<int> q;
    for (int i = 0; i < n; i++)
        if (in_degree[i] == 0)
            q.push(i), dist[i] = c[i];

    while (q.size())
    {
        int cur = q.front();
        q.pop();

        for (const int &next : adj[cur])
        {
            dist[next] = max(dist[next], dist[cur] + c[next]);

            if (--in_degree[next] == 0) // 더 이상 필요로 하는 건물이 없을 경우
                q.push(next);
        }
    }

    return dist[ed];
}

int main()
{
    FAST_IO;

    int tc;
    cin >> tc;
    while (tc--)
    {
        fill(c, c + MAX, 0), fill(in_degree, in_degree + MAX, 0);
        for (int i = 0; i < MAX; i++)
            adj[i].clear();

        int n, k; // 건물의 개수 n(2 ≤ n ≤ 1,000), 규칙의 개수 k(1 ≤ k ≤ 100,000)
        cin >> n >> k;
        for (int i = 0; i < n; i++)
            cin >> c[i];
        for (int i = 0; i < k; i++)
        {
            int x, y; // 출발지 x, 도착지 y
            cin >> x >> y;
            adj[x - 1].push_back(y - 1);

            in_degree[y - 1]++;
        }

        int w; // 필요 건물 w
        cin >> w;

        cout << bfs(n, k, w - 1) << endl;
    }
}