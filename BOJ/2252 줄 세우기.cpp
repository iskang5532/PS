// 2022-11-17
// 2252 줄 세우기
// https://www.acmicpc.net/problem/2252
/*
    위상정렬 (4,148KB, 28ms)
    시간 복잡도: ?
    풀이)
    - in_degree[]에 i번보다 작은 확인된 학생의 수는 k명. (k명 이상이 i번보다 작을 수도 있음)
    확인된 학생 모두 i번보다 앞에 존재해야 함. 그러므로, bfs를 수행할 때 확인된 학생이 모두 탐색한 경우에만 i번을 큐에 추가.
    - in_degree가 0인 학생을 큐에 넣은 후, bfs를 수행. (줄의 앞쪽; 여러 명일 수 있음)
    - 큐에 들어간 값은 ret[]에 저장 후, bfs의 수행이 최종적으로 완료되면 ret를 출력.
 */

#include <iostream>
#include <queue>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define MAX 32'003 // max n

int n, m; // 사람의 수 n(1 ≤ n ≤ 32,000), 비교한 횟수 m(1 ≤ m ≤ 100,000)
vector<int> adj[MAX];
int in_degree[MAX]; // in_degree[i] = k일 경우, i번 학생보다 작은 확인된 학생의 수는 k명

vector<int> bfs()
{
    vector<int> ret;

    queue<int> q;
    for (int i = 1; i <= n; i++)
        if (in_degree[i] == 0) // 앞선 사람이 없음
            q.push(i), ret.push_back(i);

    while (q.size())
    {
        int cur = q.front();
        q.pop();

        for (const int &next : adj[cur])
            if (--in_degree[next] == 0)
            {
                q.push(next);
                ret.push_back(next);
            }
    }

    return ret;
}

int main()
{
    FAST_IO;

    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int lo, hi;
        cin >> lo >> hi;
        adj[lo].push_back(hi), in_degree[hi]++;
    }

    vector<int> ans = bfs();

    for (const auto &i : ans)
        cout << i << ' ';
}