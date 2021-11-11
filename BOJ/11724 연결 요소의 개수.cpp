/*
    11724 연결 요소의 개수
    BFS? (6,380KB, 92ms)
    시간 복잡도: ?
    문제: https://www.acmicpc.net/problem/11724
    풀이)
    - 입력된 정점들을 서로 연결해줌. (양방향)
    - 정점의 개수 == 정점의 최댓값이므로 1부터 N까지의 정점들을 하나 씩 이용.
    - 현재 정점과 이어져 있는 다른 정점을 조사하며, 현재 정점을 처음 방문하는 경우 ans++
     - 간선을 타고 갈 수 있는 다른 정점 또한 현재 정점과 하나의 요소로 취급.
    etc.) 문제를 이해하기 힘들었음.. 서로 이어지지 않은 정점이어도 요소로 취급.
 */

#include <iostream>
#include <queue>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define endl "\n"
#define MAX 1000 + 1 // 정점의 최대 개수

int main()
{
#ifdef CUSTOM
    cout << "[CUSTOM]" << endl;
#else // BOJ
    FAST_IO;
#endif

    int n, m; // 정점의 개수 N(1 ≤ N ≤ 1k), 간선의 개수 M(0 ≤ M ≤ N×(N-1)/2)
    cin >> n >> m;

    vector<int> arr[MAX];
    for (int i = 0; i < m; i++)
    {
        int u, v; // 간선의 양 끝점 u, v(1 ≤ u, v ≤ N, u ≠ v)
        cin >> u >> v;
        arr[u].push_back(v), arr[v].push_back(u); // 양방향
    }

    int ans = 0;
    vector<bool> visited(n + 1, false);
    for (int i = 1; i <= n; i++) // 모든 정점에 대해
    {
        if (visited[i])
            continue;

        queue<int> q;
        q.push(i);
        while (!q.empty()) // 현재 정점과 이어져 있는 정점들을 조사
        {
            int curr = q.front();
            q.pop();
            for (const auto &next : arr[curr])
                if (!visited[next])
                    visited[next] = true, q.push(next);
        }

        ans++;
    }

    cout << ans;
}

// sol.2) 유니온 파인드
// 이론 참고: https://m.blog.naver.com/ndb796/221230967614
#include <iostream>

using namespace std;
#define FAST_IO ios::sync_with_stdio(false), cin.tie(NULL), cout.tie(NULL);

#ifndef ONLINE_JUDGE
#define CUSTOM
#endif

#define endl "\n"
#define MAX 1000 + 1 // 정점의 최대 개수

int parent[MAX];

int find_parent(int x) // 값의 부모 노드 찾기
{
    if (x == parent[x]) // 자기 자신이 부모 노드인 경우 (= 더 이상 올라갈 곳이 없는 근 노드)
        return x;
    else // 부모 노드를 찾으며, 현재 노드의 부모 노드는 찾게될 근 노드로 갱신
        return parent[x] = find_parent(parent[x]);
    // return x == parent[x] ? x : parent[x] = find_parent(parent[x]);
}
void union_parent(int u, int v) { u = find_parent(u), v = find_parent(v), parent[v] = u; } // 근 노드끼리 연결

int main()
{
#ifdef CUSTOM
    cout << "[CUSTOM]" << endl;
#else // BOJ
    FAST_IO;
#endif

    int n, m; // 정점의 개수 N(1 ≤ N ≤ 1k), 간선의 개수 M(0 ≤ M ≤ N×(N-1)/2)
    cin >> n >> m;

    for (int i = 1; i <= n; i++)
        parent[i] = i; // 노드 설정

    for (int i = 0; i < m; i++)
    {
        int u, v; // 간선의 양 끝점 u, v(1 ≤ u, v ≤ N, u ≠ v)
        cin >> u >> v;

        union_parent(u, v);
    }

    int ans = 0;
    for (int i = 1; i <= n; i++)
        if (parent[i] == i) // 만약 근 노드인 경우 (= 더 이상 이어질 곳이 없거나 연결의 중점이며, 이는 구해야 하는 요소)
            ans++;
    cout << ans;
}

// 100%
// 6 2
// 3 4
// 4 2
// ans: 4