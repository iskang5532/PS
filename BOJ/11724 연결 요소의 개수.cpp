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

// 100%
// 6 2
// 3 4
// 4 2
// ans: 4