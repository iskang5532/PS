// 2023-02-15
// 2623 음악프로그램
// https://www.acmicpc.net/problem/2623
/*
    위상정렬 (2,188KB, 0ms)
    시간 복잡도: ?
    풀이)
    - 가수의 번호를 하나의 정점으로 생각하며, 정점 간 연결된 값을 ans에 저장하여 출력한다.
    이때, ans 원소의 개수가 n개가 아니면 사이클이 존재한다는 것이므로 0을 출력한다.
    - in_degree[]에 해당 정점이 도착지인 정점의 개수를 저장하며, 탐색 도중 0이 되었을 경우 큐 및 ret에 추가.
    etc.)
    - 출력이 n개의 줄로 이뤄져야 함. 즉, 입력에 존재하지 않는 가수 또한 출력에 있어야 함.
 */

#include <iostream>
#include <queue>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"
#define MAX 1'003 // max n

int n, m; // 가수의 수 n(1 ≤ n ≤ 1,000), PD의 수 m(1 ≤ m ≤ 100)
vector<int> adj[MAX];
int in_degree[MAX]; // in_degree[i] = k일 경우, i로 도착하는 정점은 k개

vector<int> bfs()
{
    vector<int> ret;

    queue<int> q;
    for (int i = 0; i < n; i++)
        if (in_degree[i] == 0)
            q.push(i), ret.push_back(i);

    while (q.size())
    {
        int cur = q.front();
        q.pop();
        for (const int &nxt : adj[cur])
            if (--in_degree[nxt] == 0)
                q.push(nxt), ret.push_back(nxt);
    }

    return ret;
}

int main()
{
    FAST_IO;

    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int p;
        cin >> p;
        { // 입력된 값들을 이용하여 정점 간 간선을 연결
            int v[MAX]{};
            for (int j = 0; j < p; j++)
                cin >> v[j], v[j]--;

            for (int j = 0; j < p - 1; j++)
                adj[v[j]].push_back(v[j + 1]), in_degree[v[j + 1]]++;
        }
    }

    vector<int> ans = bfs();

    if (ans.size() != n)
        cout << 0;
    else
        for (const int &i : ans)
            cout << i + 1 << endl;
}