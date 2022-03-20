// 1613 역사
// https://www.acmicpc.net/problem/1613
/*
    sol.1) 플로이드 와샬 (2,180KB, 96ms)
    시간 복잡도: O(n^3)
    풀이)
    - "물론 사건의 전후 관계가 모순인 경우는 없다."이므로 사이클이 존재하지 않는 단방향 간선임을 알 수 있음.
    이를 이용해 정점 간 간선을 연결해준 후, 입력된 두 정점의 연결 여부를 판단하여 출력해주는 문제.
    - 플로이드 와샬을 이용해 각 정점 간 경로가 존재할 수 있는지 확인하며, path에 저장. (path[i][j] = true일 경우, i to j의 길이 존재)
    만약 i에서 k를 거쳐 j로 갈 수 있다면, i에서 j까지의 길은 존재.
    - path[a][b]와 path[b][a]의 값을 이용하여 답을 출력한다.
    path[a][b]가 존재한다면, a가 b보다 먼저 일어난 경우이다.
    path[b][a]가 존재한다면, b가 a보다 먼저 일어난 경우이다.
    path[a][b]와 path[b][a]가 존재하지 않는다면, a와 b의 순서를 모르는 경우이다.
 */

#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"
#define MAX 403

int n, k;            // 사건의 개수 n(1 ≤ n ≤ 400), 관계의 개수 k(1 ≤ k ≤ 50,000)
bool path[MAX][MAX]; // path[i][j] = true일 경우, i to j는 존재.

void Floyd_Warshall()
{
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
            {
                if (i == j) // i to i
                    continue;
                if (path[i][k] && path[k][j])
                    path[i][j] = true;
            }
}

int main()
{
    FAST_IO;

    cin >> n >> k;
    for (int i = 0; i < k; i++)
    {
        int a, b; // 1 ≤ a, b ≤ n
        cin >> a >> b;
        path[a][b] = true;
    }

    Floyd_Warshall();

    int s; // 사건 쌍의 수 (1 ≤ s ≤ 50,000)
    cin >> s;
    for (int i = 0; i < s; i++)
    {
        int a, b;
        cin >> a >> b;
        cout << (path[a][b] ? -1 : (path[b][a] ? 1 : 0)) << endl;
    }
}

/*
    sol.2) BFS (2,588KB, 24ms)
    시간 복잡도: ?
    풀이)
    - 기준이 되는 정점에서부터 갈 수 있는 모든 정점을 BFS를 이용해 구한 후, path에 저장.
    만약 a to b가 가능한 경우, path[a][b] = true이며, 갈 수 없을 경우 path[a][b] = false.
 */

#include <iostream>
#include <queue>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"
#define MAX 403

int n, k; // 사건의 개수 n(1 ≤ n ≤ 400), 관계의 개수 k(1 ≤ k ≤ 50,000)
vector<int> g[MAX];
bool path[MAX][MAX];

void bfs(int st)
{
    queue<int> q;
    q.push(st);

    bool visited[MAX];
    fill(visited, visited + MAX, false);
    visited[st] = true;

    while (q.size())
    {
        int cur = q.front();
        q.pop();

        for (int next : g[cur])
        {
            if (visited[next])
                continue;

            path[st][next] = true;
            q.push(next), visited[next] = true;
        }
    }
}

int main()
{
    FAST_IO;

    cin >> n >> k;
    for (int i = 0; i < k; i++)
    {
        int a, b; // 1 ≤ a, b ≤ n
        cin >> a >> b;
        g[a].push_back(b);
    }

    for (int i = 1; i <= n; i++)
        bfs(i);

    int s; // 사건 쌍의 수 (1 ≤ s ≤ 50,000)
    cin >> s;
    for (int i = 0; i < s; i++)
    {
        int a, b;
        cin >> a >> b;
        cout << (path[a][b] ? -1 : (path[b][a] ? 1 : 0)) << endl;
    }
}