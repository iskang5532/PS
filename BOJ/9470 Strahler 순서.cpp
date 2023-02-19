// 2022-11-22
// 9470 Strahler 순서
// https://www.acmicpc.net/problem/9470
/*
    위상정렬 (2,056KB, 0ms)
    시간 복잡도: ?
    풀이)
    - in_degree[]에 해당 노드에 들어오는 간선의 개수를 저장.
    - 맵 m에 해당 노드의 정보를 저장. (m[i] = {order, cnt}일 경우, i번 노드로 들어오는 간선의 가장 큰 순서는 order이며, 총 cnt개)
    - bfs를 이용하여 n번 노드의 정보를 구함.
    - 현재 노드 cur에서 갈 수 있는 다음 노드 next와 비교.
    만약 cur의 순서(m[cur].first)가 next보다 높은 경우, next의 순서를 변경.
    만약 cur의 순서와 next의 순서가 같을 경우, next의 횟수(m[next].second) +1
    만약 in_degree[next]가 0이 될 경우, next의 순서를 갱신할 수 있는지 확인.
     next의 횟수가 1일 경우, 순서는 그대로 유지.
     next의 횟수가 2 이상일 경우, 순서는 +1.
    - m[n]에 저장된 n번 노드의 순서를 출력.
    - m에서 순서 .first는 .order로, 개수 .cnt는 .second로 치환하여 작성.
    etc.)
    - 재밌었음. 초기화에 주의
    - 테케가 굉장히 약해보임
 */

#include <iostream>
#include <queue>
#include <map>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);
#define endl "\n"
#define MAX 1'003 // max m
using pii = pair<int, int>;
#define order first // 순서
#define cnt second  // 개수

vector<int> adj[MAX];
int in_degree[MAX]; // 노드로 들어오는 간선의 개수를 저장 (in_degree[i] = k일 경우, i번 노드에 들어오는 간선의 개수는 k개)
map<int, pii> m;    // 노드의 정보를 저장 (m[i] = {order, cnt}일 경우, i번 노드로 들어오는 간선의 가장 큰 순서는 order이며, cnt개)

void bfs(int n)
{
    queue<int> q;
    for (int i = 0; i < n; i++)
        if (in_degree[i] == 0)
            q.push(i), m[i] = pii{1, 1}; // 순서와 개수를 초기화

    while (q.size())
    {
        int cur = q.front();
        q.pop();
        for (const int &next : adj[cur])
        {
            int a = m[cur].order, b = m[next].order;
            if (a > b) // 더 높은 순서일 경우, 순서를 변경함
                m[next] = pii{a, 1};
            else if (a == b) // 같은 순서일 경우, 순서의 개수 +1
                m[next].cnt++;

            if (--in_degree[next] == 0)
            {
                q.push(next);
                if (m[next].cnt >= 2) // next 노드의 순서를 정함
                    m[next].order++;
            }
        }
    }
}

int main()
{
    FAST_IO;

    int tc; // 1 ≤ tc ≤ 1000
    cin >> tc;
    while (tc--)
    {
        for (int i = 0; i < MAX; i++)
            adj[i].clear();
        fill(in_degree, in_degree + MAX, 0), m.clear();

        int k, n, p; // tc의 번호 k, 노드의 수 n(2 ≤ n ≤ 1,000), 간선의 수 p
        cin >> k >> n >> p;
        for (int i = 0; i < p; i++)
        {
            int a, b; // a에서 b로 흐름
            cin >> a >> b;

            adj[a - 1].push_back(b - 1), in_degree[b - 1]++;
        }

        bfs(n);

        cout << k << ' ' << m[n - 1].order << endl;
    }
}