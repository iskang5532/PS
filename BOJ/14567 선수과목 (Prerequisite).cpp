// 2022-11-21
// 14567 선수과목 (Prerequisite)
// https://www.acmicpc.net/problem/14567
/*
    위상정렬 (4,960KB, 84ms)
    시간 복잡도: ?
    풀이)
    - cnt[]에 과목을 이수하기까지 필요한 학기의 수를 저장.
    - in_degree[]에 각 과목마다 필요한 선행 과목의 개수를 저장.
    수행하여 in_degree의 값이 0이 된 정점부터 큐에 넣어 bfs를 수행.
    만약 인접한 다음 정점의 in_degree가 0이 될 경우, cnt는 현재 정점의 cnt + 1의 값을 가지게 된다.
 */

#include <iostream>
#include <queue>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 1'003 // max n

vector<int> adj[MAX];
int in_degree[MAX]; // 필요한 선행 과목의 개수 (in_degree[i] = k일 경우, i번 과목의 선행 과목은 k개)
int cnt[MAX];       // 필요한 학기 저장 (cnt[i] = k일 경우, i번 과목은 k학기에 이수할 수 있음)

void bfs(int n)
{
    queue<int> q;
    for (int i = 0; i < n; i++)
        if (in_degree[i] == 0)
            q.push(i), cnt[i] = 1;

    while (q.size())
    {
        int cur = q.front();
        q.pop();
        for (const int &next : adj[cur])
            if (--in_degree[next] == 0)
                q.push(next), cnt[next] = cnt[cur] + 1;
    }
}

int main()
{
    FAST_IO;

    int n, m; // 과목의 수 n(1 ≤ n ≤ 1,000), 조건의 수 m(0 ≤ m ≤ 500,000)
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        adj[a - 1].push_back(b - 1), in_degree[b - 1]++;
    }

    bfs(n);

    for (int i = 0; i < n; i++)
        cout << cnt[i] << ' ';
}